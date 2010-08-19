/*
 * ==============================================================================
 *  Name        : timesession.cpp
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
#include <e32svr.h>

#include "DesktopHotKeySession.h"
#include "ClientServerCommon.h"
#include "DesktopHotKeyServer.h"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CTimeServerSession::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyServerSession* CDesktopHotKeyServerSession::NewL(
		CDesktopHotKeyServer& aServer)
	{
	CDesktopHotKeyServerSession* self = CDesktopHotKeyServerSession::NewLC(
			aServer);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServerSession::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyServerSession* CDesktopHotKeyServerSession::NewLC(
		CDesktopHotKeyServer& aServer)
	{
	CDesktopHotKeyServerSession* self =
			new (ELeave) CDesktopHotKeyServerSession(aServer);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServerSession::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyServerSession::ConstructL()
	{
	iServer.IncrementSessions();
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServerSession::CDesktopHotKeyServerSession()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyServerSession::CDesktopHotKeyServerSession(
		CDesktopHotKeyServer& aServer) :
	iServer(aServer)
	{
	// Implementation not required
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServerSession::~CDesktopHotKeyServerSession()
// Destructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyServerSession::~CDesktopHotKeyServerSession()
	{
	iServer.DecrementSessions();
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServerSession::ServiceL()
// Service request from client.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyServerSession::ServiceL(const RMessage2& aMessage)
	{
	switch (aMessage.Function())
		{
		case EDesktopHotKeyServRequestTime:
			RequestTimeL(aMessage);
			break;

		default:
			PanicClient(aMessage, EBadRequest);
			break;
		}
	aMessage.Complete(KErrNone);
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServerSession::RequestTimeL()
// Called as a result of the client requesting the time.
// -----------------------------------------------------------------------------
//

void CDesktopHotKeyServerSession::RequestTimeL(const RMessage2& aMessage)
	{
	TTime time;
	time.HomeTime();

	TPtr8 ptr(reinterpret_cast<TUint8*> (&time), sizeof(time), sizeof(time));

	// Write time data to the descriptor which is the first message argument
	aMessage.WriteL(0, ptr, 0);
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyServerSession::PanicClient()
// Causes the client thread to panic.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyServerSession::PanicClient(const RMessagePtr2& aMessage,
		TInt aPanic) const
	{
	aMessage.Panic(KDesktopHotKeyServer, aPanic); // Note: this panics the client thread,
	// not server
	}

// End of File
