/*
 * ==============================================================================
 *  Name        : timeserver.cpp
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
#include <eikstart.h>
#include <e32svr.h>
#include <e32math.h>

#include "DesktopHotKeyServer.h"
#include "ClientServerCommon.h"
#include "DesktopHotKeySession.h"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyServer* CDesktopHotKeyServer::NewL()
	{
	CDesktopHotKeyServer* timeServer = CDesktopHotKeyServer::NewLC();
	CleanupStack::Pop(timeServer);
	return timeServer;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyServer* CDesktopHotKeyServer::NewLC()
	{
	CDesktopHotKeyServer* timeServer = new (ELeave) CDesktopHotKeyServer(
			EPriorityNormal);
	CleanupStack::PushL(timeServer);
	timeServer->ConstructL();
	return timeServer;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyServer::ConstructL()
	{
	StartL(KDesktopHotKeyServerName);
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::CDesktopHotKeyServer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyServer::CDesktopHotKeyServer(TInt aPriority) :
	CServer2(aPriority)
	{
	// Implementation not required
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::NewSessionL()
// Creates a time server session.
// -----------------------------------------------------------------------------
//
CSession2* CDesktopHotKeyServer::NewSessionL(const TVersion& aVersion,
		const RMessage2& /*aMessage*/) const
	{
	// Check we are the right version
	if (!User::QueryVersionSupported(TVersion(
			KDesktopHotKeyServMajorVersionNumber,
			KDesktopHotKeyServMinorVersionNumber,
			KDesktopHotKeyServBuildVersionNumber), aVersion))
		{
		User::Leave(KErrNotSupported);
		}

	// Make new session        
	return CDesktopHotKeyServerSession::NewL(
			*const_cast<CDesktopHotKeyServer*> (this));
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::IncrementSessions()
// Increments the count of the active sessions for this server.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyServer::IncrementSessions()
	{
	iSessionCount++;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::DecrementSessions()
// Decrements the count of the active sessions for this server.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyServer::DecrementSessions()
	{
	iSessionCount--;
	if (iSessionCount <= 0)
		{
		CActiveScheduler::Stop();
		}
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::RunError()
// Processes any errors.
// -----------------------------------------------------------------------------
//
TInt CDesktopHotKeyServer::RunError(TInt aError)
	{
	if (aError == KErrBadDescriptor)
		{
		// A bad descriptor error implies a badly programmed client,
		// so panic it; otherwise report the error to the client
		PanicClient(Message(), EBadDescriptor);
		}
	else
		{
		Message().Complete(aError);
		}

	// The leave will result in an early return from CServer::RunL(), skipping
	// the call to request another message. So do that now in order to keep the
	// server running.
	ReStart();

	return KErrNone; // Handled the error fully
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::PanicClient()
// Panics the client.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyServer::PanicClient(const RMessage2& aMessage,
		TDesktopHotKeyServPanic aPanic)
	{
	aMessage.Panic(KDesktopHotKeyServer, aPanic);
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::PanicServer()
// Panics the server.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyServer::PanicServer(TDesktopHotKeyServPanic aPanic)
	{
	User::Panic(KDesktopHotKeyServer, aPanic);
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::ThreadFunctionL()
// Second stage startup for the server thread.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyServer::ThreadFunctionL()
	{
	// Construct active scheduler
	CActiveScheduler* activeScheduler = new (ELeave) CActiveScheduler;
	CleanupStack::PushL(activeScheduler);

	// Install active scheduler
	// We don't need to check whether an active scheduler is already installed
	// as this is a new thread, so there won't be one
	CActiveScheduler::Install(activeScheduler);

	// Construct our server
	CDesktopHotKeyServer::NewLC(); // Anonymous

	RSemaphore semaphore;
	User::LeaveIfError(semaphore.OpenGlobal(KDesktopHotKeyServerSemaphoreName));

	// Semaphore opened ok
	semaphore.Signal();
	semaphore.Close();

	// Start handling requests
	CActiveScheduler::Start();

	CleanupStack::PopAndDestroy(2, activeScheduler); //Anonymous CDesktopHotKeyServer
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServer::ThreadFunction()
// Main function for the server thread.
// -----------------------------------------------------------------------------
//
TInt CDesktopHotKeyServer::ThreadFunction(TAny* /*aNone*/)
	{
	CTrapCleanup* cleanupStack = CTrapCleanup::New();
	if (!(cleanupStack))
		{
		PanicServer(ECreateTrapCleanup);
		}

	TRAPD(err, ThreadFunctionL());
	if (err != KErrNone)
		{
		PanicServer(ESrvCreateServer);
		}

	delete cleanupStack;
	cleanupStack = NULL;

	return KErrNone;
	}

// -----------------------------------------------------------------------------
// E32Main()
// Provides the API for the operating system to start the executable.
// Returns the address of the function to be called.
// -----------------------------------------------------------------------------
//
TInt E32Main()
	{
	return CDesktopHotKeyServer::ThreadFunction(NULL);
	}

// End of File
