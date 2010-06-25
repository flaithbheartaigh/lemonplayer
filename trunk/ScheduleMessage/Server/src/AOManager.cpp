/*
 ============================================================================
 Name		: AOManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAOManager implementation
 ============================================================================
 */

#include "AOManager.h"

#include <apgwgnam.h>

#include "SimulateMessageServer.h"
#include "SimMsgStruct.h"
#include "CommonUtils.h"
#include "OKCDebug.h"

CAOManager::CAOManager(CSimulateMessageServer& aServer) :
	CActive(EPriorityStandard),iServer(aServer)
	{
	}

CAOManager* CAOManager::NewLC(CSimulateMessageServer& aServer)
	{
	CAOManager* self = new (ELeave) CAOManager(aServer);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CAOManager* CAOManager::NewL(CSimulateMessageServer& aServer)
	{
	CAOManager* self = CAOManager::NewLC(aServer);
	CleanupStack::Pop(); // self;
	return self;
	}

void CAOManager::ConstructL()
	{
	User::LeaveIfError(iTimer.CreateLocal()); // Initialize timer
	CActiveScheduler::Add(this); // Add to scheduler

	iEngine = CSmsSendByBoxEngine::NewL(*this);
	}

CAOManager::~CAOManager()
	{
	Cancel(); // Cancel any request, if outstanding
	iTimer.Close(); // Destroy the RTimer object
	// Delete instance variables if any
	delete iEngine;
	}

void CAOManager::DoCancel()
	{
	iTimer.Cancel();
	iEngine->ResetData();
	iEngine->Cancel();
	}

void CAOManager::StartL(TTimeIntervalMicroSeconds32 aDelay)
	{
//	__LOGSTR_TOFILE("start")
	Cancel(); // Cancel any request, just to be sure
	iState = EUninitialized;
	iTimer.After(iStatus, aDelay); // Set for later
	SetActive(); // Tell scheduler a request is active
	}

void CAOManager::RunL()
	{
	if (iState == EUninitialized)
		{
		// Do something the first time RunL() is called
//		__LOGSTR_TOFILE("EInitialized")
		iState = EInitialized;
		}
	else if (iState != EError)
		{
		// Do something
//		__LOGSTR_TOFILE("Run")
		TimeWork();
		}

	AtTime();
	//	iTimer.After(iStatus, 5000000); // Set for 5 sec later
	//	SetActive(); // Tell scheduler a request is active
	}

void CAOManager::SendState(TInt aState)
	{
	if (aState == KErrNone)
		iServer.CheckStopServer();
	}

void CAOManager::AtTime()
	{
	TTime timer;
	//读取配置文件
	if (GetTime(timer))
		{
//		__LOGSTR_TOFILE("Time at")
		iTimer.At(iStatus, timer);
//		iTimer.After(iStatus,1000000);
		SetActive(); // Tell scheduler a request is active
		}
	}

TBool CAOManager::GetTime(TTime& aTime)
	{
	TBool result = EFalse;

	RFs rfs;
	User::LeaveIfError(rfs.Connect());

	TFileName filename;
//	rfs.PrivatePath(filename);
	filename.Append(iServer.iPath);
	filename.Append(KDataFile);

	RFile file;
	TInt err = file.Open(rfs, filename, EFileRead);

	if (KErrNone == err)
		{
		CleanupClosePushL(file);

		//操作
		TInt size;
		file.Size(size);

		HBufC8* buffer = HBufC8::NewL(size);
		TPtr8 ptr = buffer->Des();
		file.Read(ptr);

		CleanupStack::PopAndDestroy();
		
		err = ParseDataBufferSchedule(rfs, buffer);
		
		WriteToFile(rfs,KDataFile, buffer->Des());//可能存在过期任务,此时更新
		
		delete buffer;
		
		}

	rfs.Close();
	
	if (err == KErrNone)
		{
		result = ETrue;
		aTime = iSchedule;
		}

	return result;
	}

TInt CAOManager::TimeWork()
	{
	RFs rfs;
	User::LeaveIfError(rfs.Connect());

	TFileName filename;
//	rfs.PrivatePath(filename);
	filename.Append(iServer.iPath);
	filename.Append(KDataFile);

	RFile file;
	TInt err = file.Open(rfs, filename, EFileRead);

	if (KErrNone != err)
		{
		return err;
		}
	CleanupClosePushL(file);

	//操作
	TInt size;
	file.Size(size);

	HBufC8* buffer = HBufC8::NewL(size);
	TPtr8 ptr = buffer->Des();
	file.Read(ptr);
	CleanupStack::PopAndDestroy();
	
	ParseDataBuffer(rfs, buffer);
	WriteToFile(rfs,KDataFile, buffer->Des());//可能存在过期任务,此时更新
	delete buffer;
	
	rfs.Close();

	return KErrNone;
	}

TInt CAOManager::ParseDataBufferSchedule(RFs& aFs,HBufC8* aBuffer)
	{
	TInt posName = aBuffer->Find(KSplitElementNameFormat);
	TInt posNumber = aBuffer->Find(KSplitElementNumberFormat);
	TInt posLength = aBuffer->Find(KSplitElementLengthFormat);
	
	while (posNumber != KErrNotFound && posLength != KErrNotFound)
		{
		TPtrC8 ptrDate = aBuffer->Left(KSplitElementDateLength);
		TPtrC8 ptrName = aBuffer->Mid(KSplitElementDateLength,posName - KSplitElementDateLength);
		TPtrC8 ptrNumber = aBuffer->Mid(posName+1, posNumber - posName - 1);
		TPtrC8 ptrLength = aBuffer->Mid(posNumber + 1, posLength - posNumber - 1);
		TInt contentLength = CCommonUtils::StrToInt(ptrLength);
		TPtrC8 ptrContent = aBuffer->Mid(posLength + 1,
				contentLength);

		TBuf<KSplitElementDateLength> strDate;
		strDate.Copy(ptrDate);

		TTime time;
		CCommonUtils::TimeSet(strDate,time);
		
		TTime current;
		current.HomeTime();
		
		if (current < time)
			{
			//未到预定时间
			iSchedule = time;
			return KErrNone;
			}
		else
			{
			//超过预定时间  删除任务
			TInt len = contentLength + posLength + 1;
			TPtrC8 ptrRemove = aBuffer->Left(len);
			this->WriteToFile(aFs,KRemovedDataFile,ptrRemove,ETrue);
			aBuffer->Des().Delete(0, len);
			posName = aBuffer->Find(KSplitElementNameFormat);
			posNumber = aBuffer->Find(KSplitElementNumberFormat);
			posLength = aBuffer->Find(KSplitElementLengthFormat);
			}		
		}
	return KErrNotFound;	
	}
TInt CAOManager::ParseDataBuffer(RFs& aFs, HBufC8* aBuffer)
	{
	TInt posName = aBuffer->Find(KSplitElementNameFormat);
	TInt posNumber = aBuffer->Find(KSplitElementNumberFormat);
	TInt posLength = aBuffer->Find(KSplitElementLengthFormat);

	while (posName != KErrNotFound && posNumber != KErrNotFound && posLength != KErrNotFound)
		{
		TPtrC8 ptrDate = aBuffer->Left(KSplitElementDateLength);
		TPtrC8 ptrName = aBuffer->Mid(KSplitElementDateLength,posName - KSplitElementDateLength);
		TPtrC8 ptrNumber = aBuffer->Mid(posName+1, posNumber - posName - 1);
		TPtrC8 ptrLength = aBuffer->Mid(posNumber + 1, posLength - posNumber - 1);
		TInt contentLength = CCommonUtils::StrToInt(ptrLength);
		TPtrC8 ptrContent = aBuffer->Mid(posLength + 1,
				contentLength);

		SimMsgData* task = new (ELeave) SimMsgData;

		TBuf<KSplitElementDateLength> strDate;
		strDate.Copy(ptrDate);

		TTime time;
		CCommonUtils::TimeSet(strDate,time);
//		time.Set(strDate);
		
		if (time != iSchedule)
			break;
		
		HBufC* number = HBufC::NewL(ptrNumber.Length());
		number->Des().Copy(ptrNumber);
		HBufC* content = CCommonUtils::ConvertToUnicodeFromUTF8(ptrContent);
		TPtrC ptrNum = number->Des();
		TPtrC ptrCon = content->Des();

		iEngine->AppendAddressAndContent(ptrNum,ptrCon);
		
		delete number;
		delete content;

		TInt len = contentLength + posLength + 1;
		TPtrC8 ptrRemove = aBuffer->Left(len);
		WriteToFile(aFs,KRemovedDataFile,ptrRemove,ETrue);
		
		aBuffer->Des().Delete(0, len);
		posName = aBuffer->Find(KSplitElementNameFormat);
		posNumber = aBuffer->Find(KSplitElementNumberFormat);
		posLength = aBuffer->Find(KSplitElementLengthFormat);
		}
	iEngine->Start();
	
	return KErrNone;
	}

TInt CAOManager::WriteToFile(RFs& aFs, const TDesC& aFileName,const TDesC8& aContent,TBool aAppend)
	{
	TFileName filename;
//	aFs.PrivatePath(filename);
	filename.Append(iServer.iPath);
	filename.Append(aFileName);

	RFile file;
	TInt err;
	if (aAppend)
		{
		err = file.Open(aFs, filename, EFileWrite);
		if (KErrNone != err)
			err = file.Replace(aFs,filename,EFileWrite);
		}
	else
		{
		err = file.Replace(aFs,filename,EFileWrite);
		}
	
	if (KErrNone != err)
		return err;
	
	CleanupClosePushL(file);

	if (aAppend)
		{
//		TInt size;
//		file.Size(size);
//		file.Seek(ESeekStart,size);
		TInt end = 0;
		file.Seek(ESeekEnd, end);
		}
//	else
//		{
//		TInt start;
//		file.Seek(ESeekStart,start);
//		}
	
	file.Write(aContent);
	
	CleanupStack::PopAndDestroy(); // file
	}

TInt CAOManager::RunError(TInt aError)
	{
	return aError;
	}
