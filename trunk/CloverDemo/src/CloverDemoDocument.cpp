/*
 ============================================================================
 Name		: CloverDemoDocument.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CCloverDemoDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "CloverDemoAppUi.h"
#include "CloverDemoDocument.h"
#include "MacroUtil.h"
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CCloverDemoDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCloverDemoDocument* CCloverDemoDocument::NewL(CEikApplication& aApp)
	{
	CCloverDemoDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CCloverDemoDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCloverDemoDocument* CCloverDemoDocument::NewLC(CEikApplication& aApp)
	{
	CCloverDemoDocument* self = new (ELeave) CCloverDemoDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CCloverDemoDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CCloverDemoDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CCloverDemoDocument::CCloverDemoDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CCloverDemoDocument::CCloverDemoDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CCloverDemoDocument::~CCloverDemoDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CCloverDemoDocument::~CCloverDemoDocument()
	{
	// No implementation required
#ifdef EKA2
	SAFE_DELETE(iIconProvider)
#endif
	}

// ---------------------------------------------------------------------------
// CCloverDemoDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CCloverDemoDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CCloverDemoAppUi;
	}

// End of File
