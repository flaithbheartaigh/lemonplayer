/*
 ============================================================================
 Name		: ScheduleKillerApplication.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "ScheduleKiller.hrh"
#include "ScheduleKillerDocument.h"
#include "ScheduleKillerApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CScheduleKillerApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CScheduleKillerApplication::CreateDocumentL()
	{
	// Create an ScheduleKiller document, and return a pointer to it
	return CScheduleKillerDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CScheduleKillerApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CScheduleKillerApplication::AppDllUid() const
	{
	// Return the UID for the ScheduleKiller application
	return KUidScheduleKillerApp;
	}

// End of File
