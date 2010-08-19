/*
 * ==============================================================================
 *  Name        : timesession.h
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

#ifndef ___DESKTOPHOTKEYSESSION_H__
#define ___DESKTOPHOTKEYSESSION_H__

// INCLUDE FILES
#include <e32base.h>

// FORWARD DECLARATIONS
class CDesktopHotKeyServer;

// CLASS DECLARATION
/**
 * CDesktopHotKeyServerSession.
 *  An instance of class CDesktopHotKeyServerSession is created for each client.
 */
class CDesktopHotKeyServerSession : public CSession2
	{
public:
	// Constructors and destructors

	/**
	 * NewL.
	 * Two-phased constructor.
	 * @param aServer The server.
	 * @return Pointer to created CDesktopHotKeyServerSession object.
	 */
	static CDesktopHotKeyServerSession* NewL(CDesktopHotKeyServer& aServer);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * @param aServer The server.
	 * @return Pointer to created CDesktopHotKeyServerSession object.
	 */
	static CDesktopHotKeyServerSession* NewLC(CDesktopHotKeyServer& aServer);

	/**
	 * ~CDesktopHotKeyServerSession.
	 * Destructor.
	 */
	virtual ~CDesktopHotKeyServerSession();

public:
	// Functions from base classes

	/**
	 * From CSession, ServiceL.
	 * Service request from client.
	 * @param aMessage Message from client
	 *                 (containing requested operation and any data).
	 */
	void ServiceL(const RMessage2& aMessage);

private:
	// Constructors and destructors

	/**
	 * CDesktopHotKeyServerSession.
	 * C++ default constructor.
	 * @param aServer The server.
	 */
	CDesktopHotKeyServerSession(CDesktopHotKeyServer& aServer);

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

private:
	// New methods

	/**
	 * PanicClient.
	 * Causes the client thread to panic.
	 * @param aMessage Message from client.
	 * @param aPanic Panic code.
	 */
	void PanicClient(const RMessagePtr2& aMessage, TInt aPanic) const;

	/**
	 * RequestTimeL.
	 * Handle the result of the client requesting the time.
	 * Gets the time and writes it back to the client synchronously.
	 * @param aMessage Message from client.
	 */
	void RequestTimeL(const RMessage2& aMessage);

private:
	// Data

	/**
	 * iServer, reference to the server.
	 */
	CDesktopHotKeyServer& iServer;
	};

#endif // ___DESKTOPHOTKEYSESSION_H__

// End of File
