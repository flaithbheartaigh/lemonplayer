/*
 ============================================================================
 Name		: LemonTangramDocument.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CLemonTangramDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "LemonTangramAppUi.h"
#include "LemonTangramDocument.h"
#include "MacroUtil.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLemonTangramDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLemonTangramDocument* CLemonTangramDocument::NewL(CEikApplication& aApp)
	{
	CLemonTangramDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CLemonTangramDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLemonTangramDocument* CLemonTangramDocument::NewLC(CEikApplication& aApp)
	{
	CLemonTangramDocument* self = new ( ELeave ) CLemonTangramDocument( aApp );

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CLemonTangramDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLemonTangramDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLemonTangramDocument::CLemonTangramDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLemonTangramDocument::CLemonTangramDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CLemonTangramDocument::~CLemonTangramDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CLemonTangramDocument::~CLemonTangramDocument()
	{
	SAFE_DELETE(iIconProvider);
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CLemonTangramDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CLemonTangramDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new ( ELeave )CLemonTangramAppUi;
	}

// End of File
