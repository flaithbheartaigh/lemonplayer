/*
 ============================================================================
 Name		: SimulateMessageAppContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "SimulateMessageAppContainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSimulateMessageAppContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageAppContainer* CSimulateMessageAppContainer::NewL(
		const TRect& aRect)
	{
	CSimulateMessageAppContainer* self = CSimulateMessageAppContainer::NewLC(
			aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageAppContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageAppContainer* CSimulateMessageAppContainer::NewLC(
		const TRect& aRect)
	{
	CSimulateMessageAppContainer* self =
			new (ELeave) CSimulateMessageAppContainer;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageAppContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSimulateMessageAppContainer::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();
	SetRect(aRect);
	ActivateL();

	//add your code here ...
	}

// -----------------------------------------------------------------------------
// CSimulateMessageAppContainer::CSimulateMessageAppContainer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSimulateMessageAppContainer::CSimulateMessageAppContainer()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CSimulateMessageAppContainer::~CSimulateMessageAppContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageAppContainer::~CSimulateMessageAppContainer()
	{
	// No implementation required
	}

// ---------------------------------------------------------
// CSimulateMessageContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CSimulateMessageAppContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CSimulateMessageContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CSimulateMessageAppContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CSimulateMessageContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CSimulateMessageAppContainer::HandleControlEventL(
		CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CSimulateMessageAppContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CSimulateMessageAppContainer::OfferKeyEventL(
		const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	// See if we have a selection
	TInt code = aKeyEvent.iCode;
	switch (code)
		{
		//add your code here...

		default:
			break;
		}
	return EKeyWasNotConsumed;
	}
// -----------------------------------------------------------------------------
// CSimulateMessageAppContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CSimulateMessageAppContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	}

// -----------------------------------------------------------------------------
// CSimulateMessageAppContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CSimulateMessageAppContainer::SizeChanged()
	{
	DrawNow();
	}
// End of File
