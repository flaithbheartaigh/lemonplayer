/*
 ============================================================================
 Name		: ScheduleKillerDocument.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CScheduleKillerDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "ScheduleKillerAppUi.h"
#include "ScheduleKillerDocument.h"
#include "MacroUtil.h"
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CScheduleKillerDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CScheduleKillerDocument* CScheduleKillerDocument::NewL(CEikApplication& aApp)
	{
	CScheduleKillerDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CScheduleKillerDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CScheduleKillerDocument* CScheduleKillerDocument::NewLC(CEikApplication& aApp)
	{
	CScheduleKillerDocument* self = new (ELeave) CScheduleKillerDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CScheduleKillerDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CScheduleKillerDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CScheduleKillerDocument::CScheduleKillerDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CScheduleKillerDocument::CScheduleKillerDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CScheduleKillerDocument::~CScheduleKillerDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CScheduleKillerDocument::~CScheduleKillerDocument()
	{
	// No implementation required
#ifdef EKA2
	SAFE_DELETE(iIconProvider);
#endif
	}

// ---------------------------------------------------------------------------
// CScheduleKillerDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CScheduleKillerDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CScheduleKillerAppUi;
	}

// End of File
