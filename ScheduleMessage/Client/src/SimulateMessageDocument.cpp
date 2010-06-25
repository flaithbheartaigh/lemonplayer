/*
 ============================================================================
 Name		: SimulateMessageDocument.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CSimulateMessageDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "SimulateMessageAppUi.h"
#include "SimulateMessageDocument.h"
#include "MacroUtil.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSimulateMessageDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageDocument* CSimulateMessageDocument::NewL(CEikApplication& aApp)
	{
	CSimulateMessageDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageDocument* CSimulateMessageDocument::NewLC(CEikApplication& aApp)
	{
	CSimulateMessageDocument* self =
			new (ELeave) CSimulateMessageDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSimulateMessageDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CSimulateMessageDocument::CSimulateMessageDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSimulateMessageDocument::CSimulateMessageDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CSimulateMessageDocument::~CSimulateMessageDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CSimulateMessageDocument::~CSimulateMessageDocument()
	{
	// No implementation required
#ifdef EKA2
	SAFE_DELETE(iIconProvider);
#endif
	}

// ---------------------------------------------------------------------------
// CSimulateMessageDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CSimulateMessageDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CSimulateMessageAppUi;
	}

// End of File
