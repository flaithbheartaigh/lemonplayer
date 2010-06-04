/*
 * ==============================================================================
 *  Name        : clientservercommon.h
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

#ifndef __CLIENTSERVERCOMMON_H__
#define __CLIENTSERVERCOMMON_H__

// INCLUDE FILES
#include <e32base.h>

static const TUint KDefaultMessageSlots = 0;

// CONSTANTS
_LIT( KSimulateMessageServerName,"SimulateMessageServer" ); // Server name
_LIT( KSimulateMessageServerSemaphoreName, "SimulateMessageSemaphore" );

// The server version. A version must be specified when
// creating a session with the server.
const TUint KSimulateMessageServMajorVersionNumber = 0;
const TUint KSimulateMessageServMinorVersionNumber = 1;
const TUint KSimulateMessageServBuildVersionNumber = 1;

// DATA TYPES
// Opcodes used in message passing between client and server
enum TSimulateMessageServRqst
	{
	ESimulateMessageServRequestTime = 0,
	ESimulateMessageServQueryState,
	ESimulateMessageServQueryAllTasks,
	ESimulateMessageServAddTask,
	ESimulateMessageServRemoveTask,
	ESimulateMessageServActiveSchedule,
	ESimulateMessageServDeactiveSchedule
	};

#endif // __CLIENTSERVERCOMMON_H__
// End of File
