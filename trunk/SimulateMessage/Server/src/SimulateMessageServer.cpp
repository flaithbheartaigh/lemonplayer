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

#include "SimulateMessageServer.h"
#include "ClientServerCommon.h"
#include "SimulateMessageSession.h"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CSimulateMessageServer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageServer* CSimulateMessageServer::NewL()
	{
	CSimulateMessageServer* timeServer = CSimulateMessageServer::NewLC();
	CleanupStack::Pop(timeServer);
	return timeServer;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageServer* CSimulateMessageServer::NewLC()
	{
	CSimulateMessageServer* timeServer = new (ELeave) CSimulateMessageServer(
			EPriorityNormal);
	CleanupStack::PushL(timeServer);
	timeServer->ConstructL();
	return timeServer;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSimulateMessageServer::ConstructL()
	{
	StartL(KSimulateMessageServerName);
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::CSimulateMessageServer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSimulateMessageServer::CSimulateMessageServer(TInt aPriority) :
	CServer2(aPriority)
	{
	// Implementation not required
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::NewSessionL()
// Creates a time server session.
// -----------------------------------------------------------------------------
//
CSession2* CSimulateMessageServer::NewSessionL(const TVersion& aVersion,
		const RMessage2& /*aMessage*/) const
	{
	// Check we are the right version
	if (!User::QueryVersionSupported(TVersion(
			KSimulateMessageServMajorVersionNumber,
			KSimulateMessageServMinorVersionNumber,
			KSimulateMessageServBuildVersionNumber), aVersion))
		{
		User::Leave(KErrNotSupported);
		}

	// Make new session        
	return CSimulateMessageServerSession::NewL(
			*const_cast<CSimulateMessageServer*> (this));
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::IncrementSessions()
// Increments the count of the active sessions for this server.
// -----------------------------------------------------------------------------
//
void CSimulateMessageServer::IncrementSessions()
	{
	iSessionCount++;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::DecrementSessions()
// Decrements the count of the active sessions for this server.
// -----------------------------------------------------------------------------
//
void CSimulateMessageServer::DecrementSessions()
	{
	iSessionCount--;
	if (iSessionCount <= 0)
		{
		CActiveScheduler::Stop();
		}
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::RunError()
// Processes any errors.
// -----------------------------------------------------------------------------
//
TInt CSimulateMessageServer::RunError(TInt aError)
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
// CSimulateMessageServer::PanicClient()
// Panics the client.
// -----------------------------------------------------------------------------
//
void CSimulateMessageServer::PanicClient(const RMessage2& aMessage,
		TSimulateMessageServPanic aPanic)
	{
	aMessage.Panic(KSimulateMessageServer, aPanic);
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::PanicServer()
// Panics the server.
// -----------------------------------------------------------------------------
//
void CSimulateMessageServer::PanicServer(TSimulateMessageServPanic aPanic)
	{
	User::Panic(KSimulateMessageServer, aPanic);
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::ThreadFunctionL()
// Second stage startup for the server thread.
// -----------------------------------------------------------------------------
//
void CSimulateMessageServer::ThreadFunctionL()
	{
	// Construct active scheduler
	CActiveScheduler* activeScheduler = new (ELeave) CActiveScheduler;
	CleanupStack::PushL(activeScheduler);

	// Install active scheduler
	// We don't need to check whether an active scheduler is already installed
	// as this is a new thread, so there won't be one
	CActiveScheduler::Install(activeScheduler);

	// Construct our server
	CSimulateMessageServer::NewLC(); // Anonymous

	RSemaphore semaphore;
	User::LeaveIfError(
			semaphore.OpenGlobal(KSimulateMessageServerSemaphoreName));

	// Semaphore opened ok
	semaphore.Signal();
	semaphore.Close();

	// Start handling requests
	CActiveScheduler::Start();

	CleanupStack::PopAndDestroy(2, activeScheduler); //Anonymous CSimulateMessageServer
	}

// -----------------------------------------------------------------------------
// CSimulateMessageServer::ThreadFunction()
// Main function for the server thread.
// -----------------------------------------------------------------------------
//
TInt CSimulateMessageServer::ThreadFunction(TAny* /*aNone*/)
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
	return CSimulateMessageServer::ThreadFunction(NULL);
	}

// End of File
