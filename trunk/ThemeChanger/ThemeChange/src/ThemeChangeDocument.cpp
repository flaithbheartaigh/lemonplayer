/*
 ============================================================================
 Name		: ThemeChangeDocument.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CThemeChangeDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "ThemeChangeAppUi.h"
#include "ThemeChangeDocument.h"
#include "MacroUtil.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CThemeChangeDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CThemeChangeDocument* CThemeChangeDocument::NewL(CEikApplication& aApp)
	{
	CThemeChangeDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CThemeChangeDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CThemeChangeDocument* CThemeChangeDocument::NewLC(CEikApplication& aApp)
	{
	CThemeChangeDocument* self = new (ELeave) CThemeChangeDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CThemeChangeDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CThemeChangeDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CThemeChangeDocument::CThemeChangeDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CThemeChangeDocument::CThemeChangeDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CThemeChangeDocument::~CThemeChangeDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CThemeChangeDocument::~CThemeChangeDocument()
	{
	// No implementation required
#ifdef EKA2
	SAFE_DELETE(iIconProvider);
#endif
	}

// ---------------------------------------------------------------------------
// CThemeChangeDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CThemeChangeDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CThemeChangeAppUi;
	}

// End of File
