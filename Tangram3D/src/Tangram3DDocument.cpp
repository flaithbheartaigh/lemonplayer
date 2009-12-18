/*
 ============================================================================
 Name		: Tangram3DDocument.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : CTangram3DDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "Tangram3DAppUi.h"
#include "Tangram3DDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTangram3DDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTangram3DDocument* CTangram3DDocument::NewL(CEikApplication& aApp)
	{
	CTangram3DDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CTangram3DDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTangram3DDocument* CTangram3DDocument::NewLC(CEikApplication& aApp)
	{
	CTangram3DDocument* self = new (ELeave) CTangram3DDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CTangram3DDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTangram3DDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CTangram3DDocument::CTangram3DDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CTangram3DDocument::CTangram3DDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CTangram3DDocument::~CTangram3DDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CTangram3DDocument::~CTangram3DDocument()
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CTangram3DDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CTangram3DDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CTangram3DAppUi;
	}

// End of File
