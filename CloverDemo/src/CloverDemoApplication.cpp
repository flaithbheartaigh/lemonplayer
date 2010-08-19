/*
 ============================================================================
 Name		: CloverDemoApplication.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "CloverDemo.hrh"
#include "CloverDemoDocument.h"
#include "CloverDemoApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CCloverDemoApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CCloverDemoApplication::CreateDocumentL()
	{
	// Create an CloverDemo document, and return a pointer to it
	return CCloverDemoDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CCloverDemoApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CCloverDemoApplication::AppDllUid() const
	{
	// Return the UID for the CloverDemo application
	return KUidCloverDemoApp;
	}

// End of File
