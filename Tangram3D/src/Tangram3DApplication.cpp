/*
 ============================================================================
 Name		: Tangram3DApplication.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "Tangram3D.hrh"
#include "Tangram3DDocument.h"
#include "Tangram3DApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTangram3DApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CTangram3DApplication::CreateDocumentL()
	{
	// Create an Tangram3D document, and return a pointer to it
	return CTangram3DDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CTangram3DApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CTangram3DApplication::AppDllUid() const
	{
	// Return the UID for the Tangram3D application
	return KUidTangram3DApp;
	}

// End of File
