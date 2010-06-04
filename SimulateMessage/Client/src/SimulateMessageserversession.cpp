/*
 * ==============================================================================
 *  Name        : timeserversession.cpp
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
#include <e32math.h>

#include "ClientServerCommon.h"
#include "SimulateMessageServerSession.h"

// FUNCTION PROTOTYPES
static TInt StartServer();
static TInt CreateServerProcess();

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// RSimulateMessageServerSession::RSimulateMessageServerSession()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
RSimulateMessageServerSession::RSimulateMessageServerSession() :
	RSessionBase()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// RSimulateMessageServerSession::Connect()
// Connects to the server and create a session.
// -----------------------------------------------------------------------------
//
TInt RSimulateMessageServerSession::Connect()
	{
	TInt error = ::StartServer();

	if (KErrNone == error)
		{
		error = CreateSession(KSimulateMessageServerName, Version(),
				KDefaultMessageSlots);
		}
	return error;
	}

// -----------------------------------------------------------------------------
// RSimulateMessageServerSession::Version()
// Gets the version number.
// -----------------------------------------------------------------------------
//
TVersion RSimulateMessageServerSession::Version() const
	{
	return (TVersion(KSimulateMessageServMajorVersionNumber,
			KSimulateMessageServMinorVersionNumber,
			KSimulateMessageServBuildVersionNumber));
	}

// -----------------------------------------------------------------------------
// RSimulateMessageServerSession::RequestTime()
// Issues a request for the time to the server.
// -----------------------------------------------------------------------------
//
void RSimulateMessageServerSession::RequestTime(TTime& aTime) const
	{
	// Create descriptor to enable copying data between client and server.
	// Note: This can be local since this is a synchronous call.
	// Note : Using TPtr8 since this is binary information.
	TPtr8 descriptor(reinterpret_cast<TUint8*> (&aTime), sizeof(aTime),
			sizeof(aTime));

	// Package message arguments before sending to the server
	TIpcArgs args(&descriptor);

	// This call waits for the server to complete the request before
	// proceeding. When it returns, the new time will be in aTime.
	SendReceive(ESimulateMessageServRequestTime, args);
	}

// ============================= OTHER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// StartServer()
// Starts the server if it is not already running
// -----------------------------------------------------------------------------
//
static TInt StartServer()
	{
	TInt result;

	TFindServer findTimeServer(KSimulateMessageServerName);
	TFullName name;

	result = findTimeServer.Next(name);
	if (result == KErrNone)
		{
		// Server already running
		return KErrNone;
		}

	RSemaphore semaphore;
	result = semaphore.CreateGlobal(KSimulateMessageServerSemaphoreName, 0);
	if (result != KErrNone)
		{
		return result;
		}

	result = CreateServerProcess();
	if (result != KErrNone)
		{
		return result;
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

	const TUidType serverUid(KNullUid, KNullUid, KServerUid3);

	RProcess server;

	result
			= server.Create(KSimulateMessageServerFilename, KNullDesC,
					serverUid);

	if (result != KErrNone)
		{
		return result;
		}

	server.Resume();
	server.Close();

	return KErrNone;
	}

// End of File
