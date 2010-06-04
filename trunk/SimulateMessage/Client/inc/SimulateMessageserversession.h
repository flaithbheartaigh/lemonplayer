/*
 * ==============================================================================
 *  Name        : timeserversession.h
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

#ifndef __SIMULATEMESSAGESERVERSESSION_H__
#define __SIMULATEMESSAGESERVERSESSION_H__

// INCLUDE FILES
#include <e32base.h>

// CONSTANTS
// Number of message slots to reserve for this client server session.
// Since we only communicate synchronously here, we never have any
// outstanding asynchronous requests.
static const TUint KDefaultMessageSlots = 0;

// Server UID
const TUid KServerUid3 =
	{
	0xEF4ABCDC
	};

_LIT( KSimulateMessageServerFilename, "SimulateMessageServer.exe" );

#ifdef __WINS__
static const TUint KServerMinHeapSize = 0x1000; //  4K
static const TUint KServerMaxHeapSize = 0x10000; // 64K
#endif

// CLASS DECLARATION
/**
 * RTimeServerSession
 *  This class provides the client-side interface to the server session
 */
class RSimulateMessageServerSession : public RSessionBase
	{
public:
	// Constructors and destructors

	/**
	 * RSimulateMessageServerSession.
	 * Constructs the object.
	 */
	RSimulateMessageServerSession();

public:
	// New functions

	/**
	 * Connect.
	 * Connects to the server and create a session.
	 * @return Error code.
	 */
	TInt Connect();

	/**
	 * Version.
	 * Gets the version number.
	 * @return The version.
	 */
	TVersion Version() const;

	/**
	 * RequestTime.
	 * Issues a request for the time to the server.
	 * @param aTime The location for the server to write data into.
	 */
	void RequestTime(TTime& aTime) const;

	};

#endif // __SIMULATEMESSAGESERVERSESSION_H__

// End of File
