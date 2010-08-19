/*
 ============================================================================
 Name		: DesktopHotKeyAppContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "DesktopHotKeyAppContainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CDesktopHotKeyAppContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyAppContainer* CDesktopHotKeyAppContainer::NewL(const TRect& aRect)
	{
	CDesktopHotKeyAppContainer* self = CDesktopHotKeyAppContainer::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyAppContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyAppContainer* CDesktopHotKeyAppContainer::NewLC(
		const TRect& aRect)
	{
	CDesktopHotKeyAppContainer* self = new (ELeave) CDesktopHotKeyAppContainer;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyAppContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyAppContainer::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();
	SetRect(aRect);
	ActivateL();

	//add your code here ...
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyAppContainer::CDesktopHotKeyAppContainer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyAppContainer::CDesktopHotKeyAppContainer()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyAppContainer::~CDesktopHotKeyAppContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyAppContainer::~CDesktopHotKeyAppContainer()
	{
	// No implementation required
	}

// ---------------------------------------------------------
// CDesktopHotKeyContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CDesktopHotKeyAppContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CDesktopHotKeyContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CDesktopHotKeyAppContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CDesktopHotKeyContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CDesktopHotKeyAppContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CDesktopHotKeyAppContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CDesktopHotKeyAppContainer::OfferKeyEventL(
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
// CDesktopHotKeyAppContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyAppContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyAppContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyAppContainer::SizeChanged()
	{
	DrawNow();
	}
// End of File
