/*
 * ==============================================================================
 *  Name        : timesession.cpp
 *  Part of     : CSSync
 *  Interface   :
 *  Description :
 *  Version     :
 *
 *  Copyright (c) 2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */
// INCLUDE FILES
#include <e32svr.h>
#include <EIKENV.H>
#include "SimulateMessageSession.h"
#include "ClientServerCommon.h"
#include "SimulateMessageServer.h"
#include "CommonUtils.h"
#include "Utils.h"
#include "OKCDebug.h"



// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CTimeServerSession::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageServerSession* CSimulateMessageServerSession::NewL(
		CSimulateMessageServer& aServer)
	{
	CSimulateMessageServerSession* self = CSimulateMessageServerSession::NewLC(
			aServer);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServerSession::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageServerSession* CSimulateMessageServerSession::NewLC(
		CSimulateMessageServer& aServer)
	{
	CSimulateMessageServerSession* self =
			new (ELeave) CSimulateMessageServerSession(aServer);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServerSession::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSimulateMessageServerSession::ConstructL()
	{
	iServer.IncrementSessions();
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServerSession::CSimulateMessageServerSession()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSimulateMessageServerSession::CSimulateMessageServerSession(
		CSimulateMessageServer& aServer) :
	iServer(aServer)
	{
	// Implementation not required
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServerSession::~CSimulateMessageServerSession()
// Destructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageServerSession::~CSimulateMessageServerSession()
	{
	iServer.DecrementSessions();
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServerSession::ServiceL()
// Service request from client.
// -----------------------------------------------------------------------------
//
void CSimulateMessageServerSession::ServiceL(const RMessage2& aMessage)
	{
	switch (aMessage.Function())
		{
		case ESimulateMessageServRequestTime:
			RequestTimeL(aMessage);
			break;
		case ESimulateMessageServSendDriver:
			SendDriver(aMessage);
			break;
		case ESimulateMessageServQueryState:
			QueryState(aMessage);
			break;
		case ESimulateMessageServQueryAllLength:
			QueryAllLength(aMessage);
			break;
		case ESimulateMessageServQueryAllData:
			QueryAllData(aMessage);
			break;
		case ESimulateMessageServQueryRemovedLength:
			QueryRemovedLength(aMessage);
			break;
		case ESimulateMessageServQueryRemovedData:
			QueryRemovedData(aMessage);
			break;
		case ESimulateMessageServQueryAllTasks:
			QueryAllTasks(aMessage);
			break;
		case ESimulateMessageServAddTask:
			AddTask(aMessage);
			break;
		case ESimulateMessageServRemoveTask:
			RemoveTask(aMessage);
			break;
		case ESimulateMessageServClearRemoved:
			ClearRemoved();
			break;
		case ESimulateMessageServActiveSchedule:
			iServer.StartTimer();
			break;
		case ESimulateMessageServDeactiveSchedule:
			iServer.StopTimer();
			break;
		case ESimulateMessageServScheduleReboot:
			iServer.StopTimer();
			iServer.StartTimer();
			break;
		default:
			PanicClient(aMessage, EBadRequest);
			break;
		}
	aMessage.Complete(KErrNone);
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServerSession::RequestTimeL()
// Called as a result of the client requesting the time.
// -----------------------------------------------------------------------------
//

void CSimulateMessageServerSession::RequestTimeL(const RMessage2& aMessage)
	{
	TTime time;
	time.HomeTime();

	TPtr8 ptr(reinterpret_cast<TUint8*> (&time), sizeof(time), sizeof(time));

	// Write time data to the descriptor which is the first message argument
	aMessage.WriteL(0, ptr, 0);
	}

void CSimulateMessageServerSession::SendDriver(const RMessage2& aMessage)
	{
	TBuf<2> driver;
	aMessage.Read(0,driver);
	iServer.GetAppPath(driver);
	}

void CSimulateMessageServerSession::QueryState(const RMessage2& aMessage)
	{
	TBool state = iServer.TimerState();
	TBuf8<8> info;
	info.AppendNum(state);
	
	aMessage.Write(0,info);
	}
void CSimulateMessageServerSession::QueryAllLength(const RMessage2& aMessage)
	{
	RFs rfs;
	User::LeaveIfError(rfs.Connect());

	TFileName filename;
//	rfs.PrivatePath(filename);
	filename.Append(iServer.iPath);
	filename.Append(KDataFile);

	RFile file;
	TInt size = 0;
	TInt err = file.Open(rfs, filename, EFileRead);

	if (KErrNone == err)
		{
		CleanupClosePushL(file);

		//操作
		
		file.Size(size);

		CleanupStack::PopAndDestroy();
		}
	rfs.Close();
	
	TBuf8<16> total;
	total.AppendNum(size);
	aMessage.WriteL(0, total);
	}
void CSimulateMessageServerSession::QueryAllData(const RMessage2& aMessage)
	{
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
		
		aMessage.Write(0,ptr);
		
		delete buffer;
		}
	rfs.Close();

	}

void CSimulateMessageServerSession::QueryRemovedLength(const RMessage2& aMessage)
	{
	RFs rfs;
	User::LeaveIfError(rfs.Connect());

	TFileName filename;
//	rfs.PrivatePath(filename);
	filename.Append(iServer.iPath);
	filename.Append(KRemovedDataFile);

	RFile file;
	TInt size = 0;
	TInt err = file.Open(rfs, filename, EFileRead);

	if (KErrNone == err)
		{
		CleanupClosePushL(file);

		//操作
		
		file.Size(size);

		CleanupStack::PopAndDestroy();
		}
	rfs.Close();
	
	TBuf8<16> total;
	total.AppendNum(size);
	aMessage.WriteL(0, total);
	}
void CSimulateMessageServerSession::QueryRemovedData(const RMessage2& aMessage)
	{
	RFs rfs;
	User::LeaveIfError(rfs.Connect());

	TFileName filename;
//	rfs.PrivatePath(filename);
	filename.Append(iServer.iPath);
	filename.Append(KRemovedDataFile);

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
		
		aMessage.Write(0,ptr);
		
		delete buffer;
		}
	rfs.Close();

	}
void CSimulateMessageServerSession::QueryAllTasks(const RMessage2& aMessage)
	{
	RSimMsgDataArray array;
	QueryAllTasks(array);

	TPtr8 ptr(reinterpret_cast<TUint8*> (&array), sizeof(array), sizeof(array));

	aMessage.WriteL(0, ptr, 0);

	array.Close();
	}

void CSimulateMessageServerSession::AddTask(const RMessage2& aMessage)
	{
	SimMsgData* task = new (ELeave) SimMsgData;

	TInt length;

	length = aMessage.GetDesLength(0);
	task->iNumber = HBufC::NewL(length);
	TPtr ptr0 = task->iNumber->Des();
	aMessage.Read(0, ptr0);

	length = aMessage.GetDesLength(1);
	if (length > 0)
		{
		task->iName = HBufC::NewL(length);
		TPtr ptr1 = task->iName->Des();
		aMessage.Read(1, ptr1);
		}

	length = aMessage.GetDesLength(2);
	TBuf<KSplitElementDateLength> time;
	aMessage.Read(2,time);
	CCommonUtils::TimeSet(time,task->iTime);

	length = aMessage.GetDesLength(3);
	task->iContent = HBufC::NewL(length);
	TPtr ptr3 = task->iContent->Des();
	aMessage.Read(3, ptr3);

	if (AddTask(task))
		delete task;

	}
void CSimulateMessageServerSession::RemoveTask(const RMessage2& aMessage)
	{
	SimMsgData* task = new (ELeave) SimMsgData;

	TInt length;

	length = aMessage.GetDesLength(0);
	task->iNumber = HBufC::NewL(length);
	TPtr ptr0 = task->iNumber->Des();
	aMessage.Read(0, ptr0);

	length = aMessage.GetDesLength(1);
	if (length > 0)
		{
		task->iName = HBufC::NewL(length);
		TPtr ptr1 = task->iName->Des();
		aMessage.Read(1, ptr1);
		}

	length = aMessage.GetDesLength(2);
	TBuf<KSplitElementDateLength> time;
	aMessage.Read(2,time);
	CCommonUtils::TimeSet(time,task->iTime);

	length = aMessage.GetDesLength(3);
	task->iContent = HBufC::NewL(length);
	TPtr ptr3 = task->iContent->Des();
	aMessage.Read(3, ptr3);

	RemoveTask(*task);
	
	delete task;
	}

TInt CSimulateMessageServerSession::ClearRemoved()
	{
	RFs rfs;
	User::LeaveIfError(rfs.Connect());

	TFileName filename;
	//	GetAppPath(filename);
//	rfs.PrivatePath(filename);
	filename.Append(iServer.iPath);
	filename.Append(KRemovedDataFile);

	RFile file;
	TInt err = file.Replace(rfs, filename, EFileWrite);
	if (KErrNone != err)
		{
		return err;
		}

	CleanupClosePushL(file);
	
	file.Write(KNullDesC8);

	CleanupStack::PopAndDestroy(); // file
	rfs.Close();

	return KErrNone;
	}

TInt CSimulateMessageServerSession::QueryAllTasks(RSimMsgDataArray& aArray)
	{
	ReadDataFromFile(aArray);
	}

TInt CSimulateMessageServerSession::AddTask(SimMsgData* aTask)
	{
	RSimMsgDataArray array;
	ReadDataFromFile(array);
	TBool duplicate = EFalse;
	for (TInt i = 0; i < array.Count(); i++)
		{
		SimMsgData* task = array[i];
		if (IsSameTask(*task, *aTask))
			{
			duplicate = ETrue;
			break;
			}
		}
	if (!duplicate)
		{
//		array.Append(aTask);
		AddTaskToArray(aTask,array);
		}
	WriteDataToFile(array);
	array.Close();

	return duplicate;
	}

void CSimulateMessageServerSession::AddTaskToArray(SimMsgData* aTask,RSimMsgDataArray& aArray)
	{
	TInt count = aArray.Count();
	TBool notAdd = ETrue;
		
	for (TInt i = 0; i < count; i++)
		{
		SimMsgData* task = aArray[i];
		if (task->iTime > aTask->iTime )
			{
			aArray.Insert(aTask,i);
			notAdd = EFalse;
			break;
			}
		}
	if (notAdd)
		aArray.Append(aTask);
	}

TInt CSimulateMessageServerSession::RemoveTask(const SimMsgData& aTask)
	{
	RSimMsgDataArray array;
	ReadDataFromFile(array);
	TBool duplicate = EFalse;
	for (TInt i = array.Count() - 1; i >= 0; i--)
		{
		SimMsgData* task = array[i];
		if (IsSameTask(*task, aTask))
			{
			array.Remove(i);
			break;
			}
		}
	WriteDataToFile(array);
	array.Close();
	}

TInt CSimulateMessageServerSession::ReadDataFromFile(RSimMsgDataArray& aArray)
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

	ParseDataBuffer(buffer,aArray);
	
	delete buffer;

	CleanupStack::PopAndDestroy();
	rfs.Close();

	return KErrNone;
	}

TInt CSimulateMessageServerSession::WriteDataToFile(
		const RSimMsgDataArray& aArray)
	{
	RFs rfs;
	User::LeaveIfError(rfs.Connect());

	TFileName filename;
	//	GetAppPath(filename);
	filename.Append(iServer.iPath);
//	rfs.PrivatePath(filename);
	filename.Append(KDataFile);

	
	RFile file;
	TInt err = file.Replace(rfs, filename, EFileWrite);
	if (KErrNone != err)
		{
		return err;
		}

	CleanupClosePushL(file);

	for (TInt i = 0; i < aArray.Count(); i++)
		{
		SimMsgData* task = aArray[i];
		WriteData(file, *task);
		}

	CleanupStack::PopAndDestroy(); // file
	rfs.Close();

	return KErrNone;
	}

TInt CSimulateMessageServerSession::ParseDataBuffer(HBufC8* aBuffer,
		RSimMsgDataArray& aArray)
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

		CCommonUtils::TimeSet(strDate,task->iTime);
//		task->iTime.Set(strDate);
		task->iName = CCommonUtils::ConvertToUnicodeFromUTF8(ptrName);
		task->iNumber = HBufC::NewL(ptrNumber.Length());
		task->iNumber->Des().Copy(ptrNumber);
		task->iContent = CCommonUtils::ConvertToUnicodeFromUTF8(ptrContent);

		aArray.Append(task);

		aBuffer->Des().Delete(0, contentLength + posLength + 1);
		posName = aBuffer->Find(KSplitElementNameFormat);
		posNumber = aBuffer->Find(KSplitElementNumberFormat);
		posLength = aBuffer->Find(KSplitElementLengthFormat);
		}
	return KErrNone;
	}

TInt CSimulateMessageServerSession::WriteData(RFile& aFile,
		const SimMsgData& aTask)
	{
	TBuf<KSplitElementDateLength> strDate;
	CCommonUtils::TimeFormat(aTask.iTime,strDate);
//	aTask.iTime.FormatL(strDate, KDateFormat);
	TBuf8<KSplitElementDateLength> strDate8;
	strDate8.Copy(strDate);

	
	HBufC8* name ;
	if (aTask.iName)
		name = CCommonUtils::ConvertToUTF8FromUnicode(
				aTask.iName->Des());
	else
		name = CCommonUtils::ConvertDesTo8(aTask.iNumber->Des());
	
	TPtrC8 namePtr = name->Des();
	
	TBuf8<32> number;
	number.Copy(aTask.iNumber->Des());
//	TPtrC8 number = aTask.iNumber->Des();

	TInt len = aTask.iContent->Length() - 1;
	if (len < 0)
		len = 0;
	HBufC8* content = CCommonUtils::ConvertToUTF8FromUnicode(
			aTask.iContent->Des().Left(len));

	TBuf8<4> length;
	length.AppendNum(content->Length());

	aFile.Write(strDate8);
	aFile.Write(namePtr);
	aFile.Write(KSplitElementNameFormat);
	aFile.Write(number);
	aFile.Write(KSplitElementNumberFormat);
	aFile.Write(length);
	aFile.Write(KSplitElementLengthFormat);
	aFile.Write(content->Des());
//	aFile.Write(KSplitItemFormat);

	delete content;
	delete name;

	return KErrNone;
	}

TBool CSimulateMessageServerSession::IsSameTask(const SimMsgData& aTask1,
		const SimMsgData& aTask2)
	{
	if (aTask1.iTime != aTask2.iTime)
		return EFalse;
	if (aTask1.iNumber->Des() != aTask2.iNumber->Des())
		return EFalse;
	if (aTask1.iContent->Des() != aTask2.iContent->Des())
		return EFalse;
	return ETrue;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServerSession::PanicClient()
// Causes the client thread to panic.
// -----------------------------------------------------------------------------
//
void CSimulateMessageServerSession::PanicClient(const RMessagePtr2& aMessage,
		TInt aPanic) const
	{
	aMessage.Panic(KSimulateMessageServer, aPanic); // Note: this panics the client thread,
	// not server
	}

// End of File
