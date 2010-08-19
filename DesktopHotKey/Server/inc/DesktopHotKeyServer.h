/*
 * ==============================================================================
 *  Name        : timeserver.h
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

#ifndef __DESKTOPHOTKEYSERVER_H__
#define __DESKTOPHOTKEYSERVER_H__

// INCLUDE FILES
#include <e32base.h>
#include "DesktopHotKeyServer.pan"

// CLASS DECLARATION
/**
 * CTimeServer.
 *  An instance of class CTimeServer is the main server class
 *  for the ClientServerSync example application
 */
class CDesktopHotKeyServer : public CServer2
	{
public:
	// Constructors and destructors

	/**
	 * NewL.
	 * Two-phased constructor.
	 * @return Pointer to created CDesktopHotKeyServer object.
	 */
	static CDesktopHotKeyServer* NewL();

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * @return Pointer to created CDesktopHotKeyServer object.
	 */
	static CDesktopHotKeyServer* NewLC();

public:
	// New functions

	/**
	 * ThreadFunction.
	 * Main function for the server thread.
	 * @param aNone Not used.
	 * @return Error code.
	 */
	static TInt ThreadFunction(TAny* aNone);

	/**
	 * IncrementSessions.
	 * Increments the count of the active sessions for this server.
	 */
	void IncrementSessions();

	/**
	 * DecrementSessions.
	 * Decrements the count of the active sessions for this server.
	 * If no more sessions are in use the server terminates.
	 */
	void DecrementSessions();

protected:
	// Functions from base classes

	/**
	 * From CActive, RunError.
	 * Processes any errors.
	 * @param aError The leave code reported.
	 * @result return KErrNone if leave is handled.
	 */
	TInt RunError(TInt aError);

private:
	// Constructors and destructors

	/**
	 * CDesktopHotKeyServer.
	 * C++ default constructor.
	 * @param aPriority priority for this thread.
	 */
	CDesktopHotKeyServer(TInt aPriority);

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

private:
	// New methods

	/**
	 * PanicClient.
	 * Panics the client.
	 * @param aMessage The message channel to the client.
	 * @param aReason The reason code for the panic.
	 */
	static void PanicClient(const RMessage2& aMessage,
			TDesktopHotKeyServPanic aReason);

	/**
	 * PanicServer.
	 * Panics the server.
	 * @param aReason the reason code for the panic.
	 */
	static void PanicServer(TDesktopHotKeyServPanic aReason);

	/**
	 * ThreadFunctionL.
	 * Second stage startup for the server thread.
	 */
	static void ThreadFunctionL();

private:
	// Functions from base classes

	/**
	 * From CServer, NewSessionL.
	 * Create a time server session.
	 * @param aVersion The client version.
	 * @param aMessage Message from client.
	 * @return Pointer to new session.
	 */
	CSession2
			* NewSessionL(const TVersion& aVersion, const RMessage2& aMessage) const;

private:
	// Data

	/**
	 * iSessionCount, the number of open sessions.
	 */
	TInt iSessionCount;
	};

#endif // __DESKTOPHOTKEYSERVER_H__

// End of File
