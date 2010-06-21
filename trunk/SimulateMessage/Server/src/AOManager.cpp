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
#include "LoadMessageEngine.h"
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

	}

CAOManager::~CAOManager()
	{
	Cancel(); // Cancel any request, if outstanding
	iTimer.Close(); // Destroy the RTimer object
	// Delete instance variables if any
	}

void CAOManager::DoCancel()
	{
	iTimer.Cancel();
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
	else
		{
		iServer.CheckStopServer();
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
	
	ParseDataBuffer(buffer);
	WriteToFile(rfs,KDataFile, buffer->Des());//可能存在过期任务,此时更新
	delete buffer;
	
	rfs.Close();

	return KErrNone;
	}

TInt CAOManager::ParseDataBufferSchedule(RFs& aFs,HBufC8* aBuffer)
	{
	TInt posNumber = aBuffer->Find(KSplitElementNumberFormat);
	TInt posLength = aBuffer->Find(KSplitElementLengthFormat);
	
	while (posNumber != KErrNotFound && posLength != KErrNotFound)
		{
		TPtrC8 ptrDate = aBuffer->Left(KSplitElementDateLength);
		TPtrC8 ptrNumber = aBuffer->Mid(KSplitElementDateLength, posNumber
				- KSplitElementDateLength);
		TPtrC8 ptrLength = aBuffer->Mid(posNumber + 1, posLength - posNumber
				- 1);
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
			posNumber = aBuffer->Find(KSplitElementNumberFormat);
			posLength = aBuffer->Find(KSplitElementLengthFormat);
			}		
		}
	return KErrNotFound;	
	}
TInt CAOManager::ParseDataBuffer(HBufC8* aBuffer)
	{
	TInt posNumber = aBuffer->Find(KSplitElementNumberFormat);
	TInt posLength = aBuffer->Find(KSplitElementLengthFormat);
	CLoadMessageEngine* engine = CLoadMessageEngine::NewL();

	while (posNumber != KErrNotFound && posLength != KErrNotFound)
		{
		TPtrC8 ptrDate = aBuffer->Left(KSplitElementDateLength);
		TPtrC8 ptrNumber = aBuffer->Mid(KSplitElementDateLength, posNumber
				- KSplitElementDateLength);
		TPtrC8 ptrLength = aBuffer->Mid(posNumber + 1, posLength - posNumber
				- 1);
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

		engine->CreateNewMessageL(ptrNum,ptrCon);
		delete number;
		delete content;

		aBuffer->Des().Delete(0, contentLength + posLength + 1);
		posNumber = aBuffer->Find(KSplitElementNumberFormat);
		posLength = aBuffer->Find(KSplitElementLengthFormat);
		}
	delete engine;
	return KErrNone;
	}

TInt CAOManager::WriteToFile(RFs& aFs, const TDesC& aFileName,const TDesC8& aContent,TBool aAppend)
	{
	TFileName filename;
//	aFs.PrivatePath(filename);
	filename.Append(iServer.iPath);
	filename.Append(aFileName);

	RFile file;
	TInt err = file.Replace(aFs, filename, EFileWrite);
	if (KErrNone != err)
		{
		return err;
		}
	if (aAppend)
		{
		TInt end = 0;
		file.Seek(ESeekEnd, end);
		}

	CleanupClosePushL(file);

	file.Write(aContent);
	
	CleanupStack::PopAndDestroy(); // file
	}

TInt CAOManager::RunError(TInt aError)
	{
	return aError;
	}
