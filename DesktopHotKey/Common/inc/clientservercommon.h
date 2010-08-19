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

// CONSTANTS
_LIT( KDesktopHotKeyServerName,"DesktopHotKeyServer" ); // Server name
_LIT( KDesktopHotKeyServerSemaphoreName, "DesktopHotKeySemaphore" );

// The server version. A version must be specified when
// creating a session with the server.
const TUint KDesktopHotKeyServMajorVersionNumber = 0;
const TUint KDesktopHotKeyServMinorVersionNumber = 1;
const TUint KDesktopHotKeyServBuildVersionNumber = 1;

// DATA TYPES
// Opcodes used in message passing between client and server
enum TDesktopHotKeyServRqst
	{
	EDesktopHotKeyServRequestTime
	};

#endif // __CLIENTSERVERCOMMON_H__
// End of File
