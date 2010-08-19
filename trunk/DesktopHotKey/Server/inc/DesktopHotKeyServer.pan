/*
 * ==============================================================================
 *  Name        : syncserver.pan
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

#ifndef __DESKTOPHOTKEYSERVER_PAN__
#define __DESKTOPHOTKEYSERVER_PAN__

/** Panic Category */
_LIT( KDesktopHotKeyServer, "DesktopHotKeyServer" );

/** SyncServer panic codes */
enum TDesktopHotKeyServPanic
	{
	EBadRequest, EBadDescriptor, ESrvCreateServer, ECreateTrapCleanup
	};

#endif // __SYNCSERVER_PAN__
// End of File