/*
 ============================================================================
 Name		: DesktopHotKeyDocument.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CDesktopHotKeyDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "DesktopHotKeyAppUi.h"
#include "DesktopHotKeyDocument.h"
#include "MacroUtil.h"
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CDesktopHotKeyDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyDocument* CDesktopHotKeyDocument::NewL(CEikApplication& aApp)
	{
	CDesktopHotKeyDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyDocument* CDesktopHotKeyDocument::NewLC(CEikApplication& aApp)
	{
	CDesktopHotKeyDocument* self = new (ELeave) CDesktopHotKeyDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyDocument::CDesktopHotKeyDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyDocument::CDesktopHotKeyDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CDesktopHotKeyDocument::~CDesktopHotKeyDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CDesktopHotKeyDocument::~CDesktopHotKeyDocument()
	{
	// No implementation required
#ifdef EKA2
	SAFE_DELETE(iIconProvider);
#endif
	}

// ---------------------------------------------------------------------------
// CDesktopHotKeyDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CDesktopHotKeyDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CDesktopHotKeyAppUi;
	}

// End of File
