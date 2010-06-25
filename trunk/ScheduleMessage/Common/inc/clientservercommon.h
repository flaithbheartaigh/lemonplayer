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

// Server UID
const TUid KServerUid3 =
	{
	0xEF4ABCDD
	};

_LIT( KSimulateMessageServerFilename, "ScheduleMessageServer.exe" );

#ifdef __WINS__
static const TUint KServerMinHeapSize = 0x1000; //  4K
static const TUint KServerMaxHeapSize = 0x10000; // 64K
#endif

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
	ESimulateMessageServSendDriver,
	ESimulateMessageServQueryState,
	ESimulateMessageServQueryAllLength,
	ESimulateMessageServQueryAllData,
	ESimulateMessageServQueryRemovedLength,
	ESimulateMessageServQueryRemovedData,
	ESimulateMessageServQueryAllTasks,
	ESimulateMessageServAddTask,
	ESimulateMessageServRemoveTask,
	ESimulateMessageServClearRemoved,
	ESimulateMessageServActiveSchedule,
	ESimulateMessageServDeactiveSchedule,
	ESimulateMessageServScheduleReboot
	};

#endif // __CLIENTSERVERCOMMON_H__
// End of File
