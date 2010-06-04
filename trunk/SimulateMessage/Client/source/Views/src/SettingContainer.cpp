/*
 ============================================================================
 Name		: SettingContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Container control implementation
 ============================================================================
 */

// INCLUDE FILES
#include "SettingContainer.h"

// ================= MEMBER FUNCTIONS =======================

// -----------------------------------------------------------------------------
// CSettingAppContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSettingContainer* CSettingContainer::NewL(const TRect& aRect)
	{
	CSettingContainer* self = CSettingContainer::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CSettingAppContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSettingContainer* CSettingContainer::NewLC(const TRect& aRect)
	{
	CSettingContainer* self = new (ELeave) CSettingContainer;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// C$(baseName)AppContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSettingContainer::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();
	SetRect(aRect);
	ActivateL();

	//add your code here ...
	}

// -----------------------------------------------------------------------------
// CSettingAppContainer::C$(baseName)AppContainer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSettingContainer::CSettingContainer()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CSettingAppContainer::~C$(baseName)AppContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
CSettingContainer::~CSettingContainer()
	{
	// No implementation required
	}

// ---------------------------------------------------------
// CSettingContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CSettingContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CSettingContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CSettingContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		default:
			return NULL;
		}
	}

// -----------------------------------------------------------------------------
// CSettingContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CSettingContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	}

// -----------------------------------------------------------------------------
// CSettingContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CSettingContainer::SizeChanged()
	{
	DrawNow();
	}

// ---------------------------------------------------------
// CSettingContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CSettingContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}
TKeyResponse CSettingContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	// See if we have a selection
	TInt code = aKeyEvent.iCode;
	switch (code)
		{
		default:
			// Let Listbox take care of its key handling           
			break;
		}
	return EKeyWasNotConsumed;
	}
// End of File

