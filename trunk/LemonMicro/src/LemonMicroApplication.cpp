/*
 ============================================================================
 Name		: LemonMicroApplication.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "LemonMicro.hrh"
#include "LemonMicroDocument.h"
#include "LemonMicroApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLemonMicroApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CLemonMicroApplication::CreateDocumentL()
	{
	// Create an LemonMicro document, and return a pointer to it
	return CLemonMicroDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CLemonMicroApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CLemonMicroApplication::AppDllUid() const
	{
	// Return the UID for the LemonMicro application
	return KUidLemonMicroApp;
	}

// End of File
