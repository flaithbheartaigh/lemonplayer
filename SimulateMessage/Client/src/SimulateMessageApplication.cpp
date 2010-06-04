/*
 ============================================================================
 Name		: SimulateMessageApplication.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "SimulateMessage.hrh"
#include "SimulateMessageDocument.h"
#include "SimulateMessageApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSimulateMessageApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CSimulateMessageApplication::CreateDocumentL()
	{
	// Create an SimulateMessage document, and return a pointer to it
	return CSimulateMessageDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CSimulateMessageApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CSimulateMessageApplication::AppDllUid() const
	{
	// Return the UID for the SimulateMessage application
	return KUidSimulateMessageApp;
	}

// End of File
