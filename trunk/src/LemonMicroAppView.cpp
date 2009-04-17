/*
 ============================================================================
 Name		: LemonMicroAppView.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "LemonMicroAppView.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLemonMicroAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLemonMicroAppView* CLemonMicroAppView::NewL(const TRect& aRect)
	{
	CLemonMicroAppView* self = CLemonMicroAppView::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CLemonMicroAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLemonMicroAppView* CLemonMicroAppView::NewLC(const TRect& aRect)
	{
	CLemonMicroAppView* self = new ( ELeave ) CLemonMicroAppView;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CLemonMicroAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLemonMicroAppView::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	// Set the windows size
	SetRect(aRect);

	// Activate the window, which makes it ready to be drawn
	ActivateL();
	}

// -----------------------------------------------------------------------------
// CLemonMicroAppView::CLemonMicroAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLemonMicroAppView::CLemonMicroAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLemonMicroAppView::~CLemonMicroAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CLemonMicroAppView::~CLemonMicroAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLemonMicroAppView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CLemonMicroAppView::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();

	// Gets the control's extent
	TRect drawRect(Rect());

	// Clears the screen
	gc.Clear(drawRect);

	}

// -----------------------------------------------------------------------------
// CLemonMicroAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CLemonMicroAppView::SizeChanged()
	{
	DrawNow();
	}
// End of File
