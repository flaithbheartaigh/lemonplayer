/*
 ============================================================================
 Name		: OpenGLParticlesDocument.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : COpenGLParticlesDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "OpenGLParticlesAppUi.h"
#include "OpenGLParticlesDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// COpenGLParticlesDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
COpenGLParticlesDocument* COpenGLParticlesDocument::NewL(CEikApplication& aApp)
	{
	COpenGLParticlesDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
COpenGLParticlesDocument* COpenGLParticlesDocument::NewLC(CEikApplication& aApp)
	{
	COpenGLParticlesDocument* self =
			new (ELeave) COpenGLParticlesDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void COpenGLParticlesDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesDocument::COpenGLParticlesDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
COpenGLParticlesDocument::COpenGLParticlesDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// COpenGLParticlesDocument::~COpenGLParticlesDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
COpenGLParticlesDocument::~COpenGLParticlesDocument()
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// COpenGLParticlesDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* COpenGLParticlesDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) COpenGLParticlesAppUi;
	}

// End of File
