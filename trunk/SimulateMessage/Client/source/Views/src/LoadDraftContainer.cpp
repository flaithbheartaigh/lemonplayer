/*
 ============================================================================
 Name		: LoadDraftContainer.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLoadDraftContainer implementation
 ============================================================================
 */
#include "LoadDraftContainer.h"

#include <coemain.h>
#include <apgtask.h>
#include <eikenv.h>
#include <apgcli.h>
#include <aknlists.h> 
#include <AknIconArray.h> 
#include <eikclbd.h>
#include <SimulateMessage_0xE70CE849.rsg>

CLoadDraftContainer::CLoadDraftContainer()
	{
	// No implementation required
	}

CLoadDraftContainer::~CLoadDraftContainer()
	{
	if (iListBox)
		delete iListBox;
	}

CLoadDraftContainer* CLoadDraftContainer::NewLC(const TRect& aRect)
	{
	CLoadDraftContainer* self = new (ELeave) CLoadDraftContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

CLoadDraftContainer* CLoadDraftContainer::NewL(const TRect& aRect)
	{
	CLoadDraftContainer* self = CLoadDraftContainer::NewLC(aRect);
	CleanupStack::Pop(); // self;
	return self;
	}

void CLoadDraftContainer::ConstructL(const TRect& aRect)
	{
	CreateWindowL();

	iListBox = new (ELeave) CAknSingleGraphicStyleListBox();
	iListBox->ConstructL(this);
	iListBox->SetContainerWindowL(*this);

	// Creates scrollbar.
	iListBox->CreateScrollBarFrameL(ETrue);
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
			CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
	
	SetIconsL();
	UpdateDisplay();

	SetRect(aRect);
	ActivateL();
	}

// ---------------------------------------------------------
// CThemeChangeContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CLoadDraftContainer::CountComponentControls() const
	{
	TInt count(0);
	if (iListBox)
		count++;

	return count; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CThemeChangeContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CLoadDraftContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		case 0:
			return iListBox; // Returns the pointer to listbox object.
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CThemeChangeContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CLoadDraftContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CLoadDraftContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CLoadDraftContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	// See if we have a selection
	TInt code = aKeyEvent.iCode;
	switch (code)
		{
		//add your code here...
		case EKeyDownArrow:
		case EKeyUpArrow:
			return iListBox->OfferKeyEventL(aKeyEvent, aType);
		default:
			break;
		}
	return EKeyWasNotConsumed;
	}
// -----------------------------------------------------------------------------
// CLoadDraftContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CLoadDraftContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	}

// -----------------------------------------------------------------------------
// CLoadDraftContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CLoadDraftContainer::SizeChanged()
	{
	if (iListBox)
		{
		iListBox->SetRect(Rect());
		}
	DrawNow();
	}

/*

 #include <avkon.mbg>
 #include <avkonicons.hrh>

 RESOURCE AKN_ICON_ARRAY r_icon_mark
 {
 type = EAknIconArraySimple;
 bmpfile = AVKON_ICON_FILE;
 icons =
 {
 AKN_ICON
 {
 iconId = EMbmAvkonQgn_prop_radiobutt_on;
 maskId = EMbmAvkonQgn_prop_radiobutt_on_mask;
 },
 AKN_ICON
 {
 iconId = EMbmAvkonQgn_prop_radiobutt_off;
 maskId = EMbmAvkonQgn_prop_radiobutt_off_mask;
 },
 AKN_ICON
 {
 iconId = EMbmAvkonQgn_prop_mmc_memc_large;
 maskId = EMbmAvkonQgn_prop_mmc_memc_large_mask;
 }            
 };
 }
 */
void CLoadDraftContainer::SetIconsL()
	{
	CAknIconArray* icons = new (ELeave) CAknIconArray(2);
	CleanupStack::PushL(icons);
	icons->ConstructFromResourceL(R_ICON_MARK);
	iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons);
	CleanupStack::Pop(); // icons
	}

void CLoadDraftContainer::UpdateDisplay()
	{

	CTextListBoxModel* model = iListBox->Model();
	CDesCArray* items = static_cast<CDesCArray*> (model->ItemTextArray());

	items->Reset();
	_LIT(KItemFormat, "0\tItem");

	for (TInt i = 0; i < 10; i++)
		{
		TBuf<32> record;
		record.Format(KItemFormat);
		items->AppendL(record);
		}

	iListBox->HandleItemAdditionL();

	}
