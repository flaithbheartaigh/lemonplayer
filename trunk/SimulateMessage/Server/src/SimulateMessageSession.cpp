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

_LIT(KDataFile,"data.txt");
_LIT(KDateFormat,"%Y%M%D:%H%T");

_LIT8(KSplitItemFormat,"\n");
_LIT8(KSplitElementNumberFormat,"#");
_LIT8(KSplitElementLengthFormat,"@");

const TInt KSplitElementDateLength = 13;		//时间固定长度13位

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
		case ESimulateMessageServQueryState:
		case ESimulateMessageServQueryAllTasks:
			QueryAllTasks(aMessage);
			break;
		case ESimulateMessageServAddTask:
			AddTask(aMessage);
			break;
		case ESimulateMessageServRemoveTask:
			RemoveTask(aMessage);
			break;
		case ESimulateMessageServActiveSchedule:
		case ESimulateMessageServDeactiveSchedule:
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
	TBuf8<512> data;
	//TPtr8 ptr(data);
	aMessage.Read(0, data, 0);
	
	SimMsgData* task = reinterpret_cast<SimMsgData*> (&data);
	AddTask(*task);
	}
void CSimulateMessageServerSession::RemoveTask(const RMessage2& aMessage)
	{
	TBuf8<512> data;
	aMessage.Read(0, data, 0);
	
	SimMsgData* task = reinterpret_cast<SimMsgData*> (&data);
	RemoveTask(*task);
	}

TInt CSimulateMessageServerSession::QueryAllTasks(RSimMsgDataArray& aArray)
	{
	ReadDataFromFile(aArray);
	}

TInt CSimulateMessageServerSession::AddTask(const SimMsgData& aTask)
	{
	RSimMsgDataArray array;
	ReadDataFromFile(array);
	TBool duplicate = EFalse;
	for (TInt i=0; i<array.Count(); i++)
		{
		SimMsgData* task = array[i];
		if (IsSameTask(*task,aTask))
			{
			duplicate = ETrue;
			break;
			}
		}
	if (!duplicate)
		array.Append(&aTask);
	WriteDataToFile(array);
	array.Close();
	}

TInt CSimulateMessageServerSession::RemoveTask(const SimMsgData& aTask)
	{
	RSimMsgDataArray array;
	ReadDataFromFile(array);
	TBool duplicate = EFalse;
	for (TInt i=array.Count()-1; i>=0; i++)
		{
		SimMsgData* task = array[i];
		if (IsSameTask(*task,aTask))
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
	TFileName filename;
//	GetAppPath(filename);
	filename.Append(KDataFile);

	RFile file;
	TInt err = file.Open(CCoeEnv::Static()->FsSession(), filename, EFileRead);

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
	
	CleanupStack::PopAndDestroy();

	return KErrNone;
	}

TInt CSimulateMessageServerSession::WriteDataToFile(
		const RSimMsgDataArray& aArray)
	{
	TFileName filename;
//	GetAppPath(filename);
	filename.Append(KDataFile);

	RFile file;
	TInt err = file.Replace(CCoeEnv::Static()->FsSession(), filename,
			EFileWrite);
	if (KErrNone != err)
		{
		return err;
		}

	CleanupClosePushL(file);
	
	for(TInt i=0; i<aArray.Count(); i++)
		{
		SimMsgData* task = aArray[i];
		WriteData(file,*task);
		}

	CleanupStack::PopAndDestroy(); // file
	return KErrNone;
	}

TInt CSimulateMessageServerSession::ParseDataBuffer(HBufC8* aBuffer,RSimMsgDataArray& aArray)
	{
	TInt posNumber = aBuffer->Find(KSplitElementNumberFormat);
	TInt posLength = aBuffer->Find(KSplitElementLengthFormat);
	while (posNumber != KErrNotFound && posLength != KErrNotFound)
		{
		TPtrC8 ptrDate = aBuffer->Left(KSplitElementDateLength);
		TPtrC8 ptrNumber = aBuffer->Mid(KSplitElementDateLength,posNumber - KSplitElementDateLength);
		TPtrC8 ptrLength = aBuffer->Mid(posNumber+1,	posLength-posNumber-1);
		TInt contentLength = CCommonUtils::StrToInt(ptrLength);
		TPtrC8 ptrContent = aBuffer->Mid(posNumber+ ptrLength.Length() + 1,contentLength);
		
		SimMsgData* task = new (ELeave) SimMsgData;
		
		TBuf<KSplitElementDateLength> strDate;
		strDate.Copy(ptrDate);
//		TBuf<KSplitElementDateLength> date;
//		date.Copy(strDate.Left(8));
//		date.Append(':');
//		date.Append(strDate.Mid(8));
		
		task->iTime.Set(strDate);
		task->iNumber = HBufC::NewL(ptrNumber.Length());
		task->iNumber->Des().Copy(ptrNumber);
		task->iContent = CCommonUtils::ConvertToUnicodeFromUTF8(ptrContent);
		
		aArray.Append(task);
		
		aBuffer->Des().Delete(0,contentLength + posNumber+ ptrLength.Length() + 1);
		posNumber = aBuffer->Find(KSplitElementNumberFormat);
		posLength = aBuffer->Find(KSplitElementLengthFormat);
		}
	return KErrNone;
	}

TInt CSimulateMessageServerSession::WriteData(RFile& aFile,const SimMsgData& aTask)
	{
	TBuf<KSplitElementDateLength> strDate;
	aTask.iTime.FormatL(strDate,KDateFormat);
	TBuf8<KSplitElementDateLength> strDate8;
	strDate8.Copy(strDate);
	
	TBuf8<32> number;
	number.Copy(aTask.iNumber->Des());
	
	HBufC8* content = CCommonUtils::ConvertToUTF8FromUnicode(aTask.iContent->Des());
	
	TBuf8<4> length;
	length.AppendNum(content->Length());
	
	aFile.Write(strDate8);
	aFile.Write(number);
	aFile.Write(KSplitElementNumberFormat);
	aFile.Write(length);
	aFile.Write(KSplitElementLengthFormat);
	aFile.Write(content->Des());
	
	delete content;
	
	return KErrNone;
	}

TBool CSimulateMessageServerSession::IsSameTask(const SimMsgData& aTask1,const SimMsgData& aTask2)
	{
	if (aTask1.iTime != aTask2.iTime)
		return EFalse;
	if (aTask1.iNumber != aTask2.iNumber)
		return EFalse;
	if (aTask1.iContent != aTask2.iContent)
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
