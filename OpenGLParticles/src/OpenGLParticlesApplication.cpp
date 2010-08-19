/*
 ============================================================================
 Name		: OpenGLParticlesApplication.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "OpenGLParticles.hrh"
#include "OpenGLParticlesDocument.h"
#include "OpenGLParticlesApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// COpenGLParticlesApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* COpenGLParticlesApplication::CreateDocumentL()
	{
	// Create an OpenGLParticles document, and return a pointer to it
	return COpenGLParticlesDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid COpenGLParticlesApplication::AppDllUid() const
	{
	// Return the UID for the OpenGLParticles application
	return KUidOpenGLParticlesApp;
	}

// End of File
