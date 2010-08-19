/*
 ============================================================================
 Name		: ThemeChangeApplication.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "ThemeChange.hrh"
#include "ThemeChangeDocument.h"
#include "ThemeChangeApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CThemeChangeApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CThemeChangeApplication::CreateDocumentL()
	{
	// Create an ThemeChange document, and return a pointer to it
	return CThemeChangeDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CThemeChangeApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CThemeChangeApplication::AppDllUid() const
	{
	// Return the UID for the ThemeChange application
	return KUidThemeChangeApp;
	}

// End of File
