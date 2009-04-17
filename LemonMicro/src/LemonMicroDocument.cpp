/*
 ============================================================================
 Name		: LemonMicroDocument.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : CLemonMicroDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "LemonMicroAppUi.h"
#include "LemonMicroDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLemonMicroDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLemonMicroDocument* CLemonMicroDocument::NewL(CEikApplication& aApp)
	{
	CLemonMicroDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CLemonMicroDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLemonMicroDocument* CLemonMicroDocument::NewLC(CEikApplication& aApp)
	{
	CLemonMicroDocument* self = new ( ELeave ) CLemonMicroDocument( aApp );

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CLemonMicroDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLemonMicroDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLemonMicroDocument::CLemonMicroDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLemonMicroDocument::CLemonMicroDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CLemonMicroDocument::~CLemonMicroDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CLemonMicroDocument::~CLemonMicroDocument()
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CLemonMicroDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CLemonMicroDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new ( ELeave )CLemonMicroAppUi;
	}

// End of File
