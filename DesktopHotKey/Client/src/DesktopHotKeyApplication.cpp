/*
 ============================================================================
 Name		: DesktopHotKeyApplication.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "DesktopHotKey.hrh"
#include "DesktopHotKeyDocument.h"
#include "DesktopHotKeyApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CDesktopHotKeyApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CDesktopHotKeyApplication::CreateDocumentL()
	{
	// Create an DesktopHotKey document, and return a pointer to it
	return CDesktopHotKeyDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CDesktopHotKeyApplication::AppDllUid() const
	{
	// Return the UID for the DesktopHotKey application
	return KUidDesktopHotKeyApp;
	}

// End of File
