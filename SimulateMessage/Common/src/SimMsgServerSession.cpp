/*
 ============================================================================
 Name		: SimMsgServerSession.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSimMsgServerSession implementation
 ============================================================================
 */

#include "SimMsgServerSession.h"
#include "ClientServercommon.h"
#include "CommonUtils.h"

static TInt StartServer();
static TInt CreateServerProcess();

CSimMsgServerSession::CSimMsgServerSession()
: RSessionBase()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// RTimeServerSession::Connect()
// Connects to the server and create a session.
// -----------------------------------------------------------------------------
//
TInt CSimMsgServerSession::Connect()
    {
    TInt error = ::StartServer();

    if ( KErrNone == error )
        {
        error = CreateSession( KSimulateMessageServerName,
                               Version(),
                               KDefaultMessageSlots );
        }
    return error;
    }

// -----------------------------------------------------------------------------
// RTimeServerSession::Version()
// Gets the version number.
// -----------------------------------------------------------------------------
//
TVersion CSimMsgServerSession::Version() const
    {
    return( TVersion( KSimulateMessageServMajorVersionNumber,
    		KSimulateMessageServMinorVersionNumber,
    		KSimulateMessageServBuildVersionNumber ) );
    }

void CSimMsgServerSession::SendDriver(const TDesC& aDriver)
	{
	TIpcArgs args( &aDriver );
		        
	SendReceive( ESimulateMessageServSendDriver, args );
	}

TBool CSimMsgServerSession::IsScheduleActive()
	{
    // Create descriptor to enable copying data between client and server.
    // Note: This can be local since this is a synchronous call.
    // Note : Using TPtr8 since this is binary information.
	TBuf8<8> result;
    
    // Package message arguments before sending to the server
    TIpcArgs args( &result );
        
    // This call waits for the server to complete the request before
    // proceeding. When it returns, the new time will be in aTime.
    SendReceive( ESimulateMessageServQueryState, args );
    
    return CCommonUtils::StrToInt(result);
	}

void CSimMsgServerSession::QueryAllLength(TInt& aLength)
	{ 
	TBuf8<16> length;
	TIpcArgs args( &length );
	        
	SendReceive( ESimulateMessageServQueryAllLength, args );
	
	aLength = CCommonUtils::StrToInt(length);
	}
void CSimMsgServerSession::QueryAllData(TDes8& aData)
	{
	TIpcArgs args( &aData );
	        
	SendReceive( ESimulateMessageServQueryAllData, args );
	}

void CSimMsgServerSession::QueryRemovedLength(TInt& aLength)
	{ 
	TBuf8<16> length;
	TIpcArgs args( &length );
	        
	SendReceive( ESimulateMessageServQueryRemovedLength, args );
	
	aLength = CCommonUtils::StrToInt(length);
	}
void CSimMsgServerSession::QueryRemovedData(TDes8& aData)
	{
	TIpcArgs args( &aData );
	        
	SendReceive( ESimulateMessageServQueryRemovedData, args );
	}

void CSimMsgServerSession::QueryAllTasks(RSimMsgDataArray& aArray)
	{
    TPtr8 descriptor( reinterpret_cast<TUint8*>( &aArray ), sizeof( aArray ),
                      sizeof( aArray ) );
    
    TIpcArgs args( &descriptor );
        
    SendReceive( ESimulateMessageServQueryAllTasks, args );
	}
void CSimMsgServerSession::AddTask(SimMsgData& aTask)
	{
//    TPtr8 time( reinterpret_cast<TUint8*>( &(aTask.iTime) ), sizeof( aTask.iTime ),
//                      sizeof( aTask.iTime ) );
    TBuf<KSplitElementDateLength> time;
//    CCommonUtils::TimeFormatWithoutOffset(aTask.iTime,time);
    CCommonUtils::TimeFormat(aTask.iTime,time);
    
    TIpcArgs args( aTask.iNumber, aTask.iName, &time, aTask.iContent );
        
    SendReceive( ESimulateMessageServAddTask, args );
	}
void CSimMsgServerSession::RemoveTask(SimMsgData& aTask)
	{
    TBuf<KSplitElementDateLength> time;
    CCommonUtils::TimeFormat(aTask.iTime,time);
    
    TIpcArgs args( aTask.iNumber, aTask.iName, &time, aTask.iContent );
        
    SendReceive( ESimulateMessageServRemoveTask, args );
	}

void CSimMsgServerSession::ClearRemoved()
	{
	SendReceive( ESimulateMessageServClearRemoved);
	}

void CSimMsgServerSession::ActiveSchedule()
	{
	SendReceive( ESimulateMessageServActiveSchedule);
	}
void CSimMsgServerSession::DeactiveSchedule()
	{
	SendReceive( ESimulateMessageServDeactiveSchedule);
	}
void CSimMsgServerSession::RebootSchedule()
	{
	SendReceive( ESimulateMessageServScheduleReboot);
	}

TInt CSimMsgServerSession::ParseDataBuffer(HBufC8* aBuffer,
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

// -----------------------------------------------------------------------------
// StartServer()
// Starts the server if it is not already running
// -----------------------------------------------------------------------------
//
static TInt StartServer()
    {
    TInt result;

    TFindServer findTimeServer( KSimulateMessageServerName );
    TFullName name;

    result = findTimeServer.Next( name );
    if ( result == KErrNone )
        {
        // Server already running
        return KErrNone;
        }

    RSemaphore semaphore;
    result = semaphore.CreateGlobal( KSimulateMessageServerSemaphoreName, 0 );
    if ( result != KErrNone )
        {
        return  result;
        }

    result = CreateServerProcess();
    if ( result != KErrNone )
        {
        return  result;
        }

    semaphore.Wait();
    semaphore.Close();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CreateServerProcess()
// Creates a server process
// -----------------------------------------------------------------------------
//
static TInt CreateServerProcess()
    {
    TInt result;

    const TUidType serverUid( KNullUid, KNullUid, KServerUid3 );

    RProcess server;
    
    result = server.Create( KSimulateMessageServerFilename, KNullDesC, serverUid );
    
    if ( result != KErrNone )
        {
        return  result;
        }

    server.Resume();
    server.Close();

    return  KErrNone;
    }
