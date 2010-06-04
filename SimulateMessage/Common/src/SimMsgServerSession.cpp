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

TBool CSimMsgServerSession::IsScheduleActive()
	{
    // Create descriptor to enable copying data between client and server.
    // Note: This can be local since this is a synchronous call.
    // Note : Using TPtr8 since this is binary information.
	TBool result;
    TPtr8 descriptor( reinterpret_cast<TUint8*>( &result ), sizeof( result ),
                      sizeof( result ) );
    
    // Package message arguments before sending to the server
    TIpcArgs args( &descriptor );
        
    // This call waits for the server to complete the request before
    // proceeding. When it returns, the new time will be in aTime.
    SendReceive( ESimulateMessageServRequestTime, args );
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
    TPtr8 descriptor( reinterpret_cast<TUint8*>( &aTask ), sizeof( aTask ),
                      sizeof( aTask ) );
    
    TIpcArgs args( &descriptor );
        
    SendReceive( ESimulateMessageServAddTask, args );
	}
void CSimMsgServerSession::RemoveTask(SimMsgData& aTask)
	{
    TPtr8 descriptor( reinterpret_cast<TUint8*>( &aTask ), sizeof( aTask ),
                      sizeof( aTask ) );
    
    TIpcArgs args( &descriptor );
        
    SendReceive( ESimulateMessageServRemoveTask, args );
	}

void CSimMsgServerSession::ActiveSchedule()
	{}
void CSimMsgServerSession::DeactiveSchedule()
	{}
