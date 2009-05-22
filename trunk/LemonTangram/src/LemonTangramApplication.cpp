/*
 ============================================================================
 Name		: LemonTangramApplication.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "LemonTangram.hrh"
#include "LemonTangramDocument.h"
#include "LemonTangramApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLemonTangramApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CLemonTangramApplication::CreateDocumentL()
	{
	// Create an LemonTangram document, and return a pointer to it
	return CLemonTangramDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CLemonTangramApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CLemonTangramApplication::AppDllUid() const
	{
	// Return the UID for the LemonTangram application
	return KUidLemonTangramApp;
	}

// End of File
