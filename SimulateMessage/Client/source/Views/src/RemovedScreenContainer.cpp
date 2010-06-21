/*
 ============================================================================
 Name		: RemovedScreenContainer.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRemovedScreenContainer implementation
 ============================================================================
 */
#include "RemovedScreenContainer.h"

#include <coemain.h>
#include <apgtask.h>
#include <eikenv.h>
#include <apgcli.h>
#include <aknlists.h> 
#include <AknIconArray.h> 
#include <eikclbd.h>
#include "SHPlatform.h"

CRemovedScreenContainer::CRemovedScreenContainer()
	{
	// No implementation required
	}

CRemovedScreenContainer::~CRemovedScreenContainer()
	{
	if (iListBox)
		delete iListBox;
	}

CRemovedScreenContainer* CRemovedScreenContainer::NewLC(const TRect& aRect)
	{
	CRemovedScreenContainer* self = new (ELeave) CRemovedScreenContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

CRemovedScreenContainer* CRemovedScreenContainer::NewL(const TRect& aRect)
	{
	CRemovedScreenContainer* self = CRemovedScreenContainer::NewLC(aRect);
	CleanupStack::Pop(); // self;
	return self;
	}

void CRemovedScreenContainer::ConstructL(const TRect& aRect)
	{
	CreateWindowL();

	iListBox = new (ELeave) CAknDoubleGraphicStyleListBox();
	iListBox->ConstructL(this,0);
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
TInt CRemovedScreenContainer::CountComponentControls() const
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
CCoeControl* CRemovedScreenContainer::ComponentControl(TInt aIndex) const
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
void CRemovedScreenContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CRemovedScreenContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CRemovedScreenContainer::OfferKeyEventL(
		const TKeyEvent& aKeyEvent, TEventCode aType)
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
// CRemovedScreenContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CRemovedScreenContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	}

// -----------------------------------------------------------------------------
// CRemovedScreenContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CRemovedScreenContainer::SizeChanged()
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
void CRemovedScreenContainer::SetIconsL()
	{
	CAknIconArray* icons = new (ELeave) CAknIconArray(2);
	CleanupStack::PushL(icons);
	icons->ConstructFromResourceL(R_ICON_MARK);
	iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons);
	CleanupStack::Pop(); // icons
	}

void CRemovedScreenContainer::UpdateDisplay()
	{	
	TInt total;
	HBufC8* buffer;
	RSimMsgDataArray* iTaskArray;

	SHSession().QueryRemovedLength(total);
	if (total > 0)
		{
		iTaskArray = new RSimMsgDataArray();
		 
		buffer = HBufC8::NewL(total);
		TPtr8 ptr = buffer->Des();
		SHSession().QueryRemovedData(ptr);

		CSimMsgServerSession::ParseDataBuffer(buffer, *iTaskArray);

		CTextListBoxModel* model = iListBox->Model();
		CDesCArray* items = static_cast<CDesCArray*> (model->ItemTextArray());

		items->Reset();

		for (TInt i = 0; i < iTaskArray->Count(); i++)
			{
			SimMsgData* task = (*iTaskArray)[i];
			TPtrC number = task->iNumber->Des();
			TBuf<32> time;
			task->iTime.FormatL(time, KDateFormat);

			TBuf<64> item;
			item.Append(_L("0\t"));
			item.Append(number);
			item.Append('\t');
			item.Append(time);

			items->AppendL(item);
			}

		delete buffer;
		
		iTaskArray->ResetAndDestroy();
		delete iTaskArray;

		iListBox->HandleItemAdditionL();
		}
	}

void CRemovedScreenContainer::ClearRemoved()
	{
	SHSession().ClearRemoved();
	UpdateDisplay();
	}
