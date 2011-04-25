/*
 ============================================================================
 Name		: AppScreenContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Container control implementation
 ============================================================================
 */

// INCLUDE FILES
#include "AppScreenContainer.h"

#include <coemain.h>
#include <apgcli.h>
#include <apgwgnam.h>
#include <apgtask.h>
#include <eikenv.h>
#include <apgcli.h>
#include <aknlists.h> 
#include <AknIconArray.h> 
#include <eikclbd.h>
#include <w32std.h>
#include <GULICON.H>
#include <stringloader.h> 
#include "SHPlatform.h"
#include "MacroUtil.h"
#include "SHDebug.h"
#include "LmSvgUtil.h"
#include "AppDefine.h"

const TInt KAknExListFindBoxTextLength = 20;
const TInt MAX_APP_REFRESH_NUMBER = 10;

CAppScreenContainer::CAppScreenContainer()
:iAppRefresh(0)
	{
	// No implementation required
	}

CAppScreenContainer::~CAppScreenContainer()
	{
		SAFE_DELETE_ACTIVE(iAppEngine)

	iUids.Close();

		SAFE_DELETE(iListBox)
		SAFE_DELETE(iFindBox)
	}

CAppScreenContainer* CAppScreenContainer::NewLC(const TRect& aRect)
	{
	CAppScreenContainer* self = new (ELeave) CAppScreenContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

CAppScreenContainer* CAppScreenContainer::NewL(const TRect& aRect)
	{
	CAppScreenContainer* self = CAppScreenContainer::NewLC(aRect);
	CleanupStack::Pop(); // self;
	return self;
	}

void CAppScreenContainer::ConstructL(const TRect& aRect)
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

	iFindBox = CreateFindBoxL(iListBox, iListBox->Model(),
			CAknSearchField::ESearch);
	//	UpdateDisplay();

	CGulIcon* icon = LMSvgUtil::GetIconFormResourceL(EMbmSchedulekillerShutdown,
			EMbmSchedulekillerShutdown_mask);
	HBufC* name = StringLoader::LoadL(R_TEXT_SHUTDOWN);
	TBuf<16> info;
	info.AppendNum(ICON_INDEX_SHUTDOWN);
	info.Append('\t');
	info.Append(name->Des());
	delete name;
	GetAppInfo(icon,info,UID_SHUTDOWN);
	
	iAppEngine = CLoadAppEngine::NewL(this);
	iAppEngine->StartL(1000);

	SetRect(aRect);
	ActivateL();
	}

// ---------------------------------------------------------
// CThemeChangeContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CAppScreenContainer::CountComponentControls() const
	{
	TInt count(0);
	if (iListBox)
		count++;
	if (iFindBox)
		count++;
	return count; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CThemeChangeContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CAppScreenContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		case 0:
			return iListBox; // Returns the pointer to listbox object.
		case 1:
			return iFindBox;
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CThemeChangeContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CAppScreenContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

void CAppScreenContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if  ( aType == KEikDynamicLayoutVariantSwitch )
    	{
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
        SetRect(rect);
        }
    }

//------------------------------------------------------------------
//CAppList::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CAppScreenContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
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
		case EKeyDevice3:
			if (aType == EEventKey)
				{
				Selected();
				return EKeyWasConsumed;
				}
			break;
		default:
			if (iListBox)
				{
				if (iFindBox)
					{
					TBool needRefresh(EFalse);

					// Offers the key event to find box.
					if (AknFind::HandleFindOfferKeyEventL(aKeyEvent, aType,
							this, iListBox, iFindBox, EFalse, needRefresh)
							== EKeyWasConsumed)
						{
						if (needRefresh)
							{
							//							SizeChanged();
							DrawNow();
							}

						return EKeyWasConsumed;
						}
					}
				}
			break;
		}
	return EKeyWasNotConsumed;
	}
// -----------------------------------------------------------------------------
// CAppList::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CAppScreenContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	}

// -----------------------------------------------------------------------------
// CAppList::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CAppScreenContainer::SizeChanged()
	{
	if (iListBox)
		{
		iListBox->SetRect(Rect());
		if (iFindBox)
			{
			CAknColumnListBox* aknListBox = STATIC_CAST(CAknColumnListBox*,
					iListBox);
			AknFind::HandleFixedFindSizeChanged(this, aknListBox, iFindBox);
			}
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
void CAppScreenContainer::SetIconsL()
	{
	CAknIconArray* icons = new (ELeave) CAknIconArray(10);
	//	CleanupStack::PushL(icons);
	//	icons->ConstructFromResourceL(R_ICON_MARK);
	iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons);
	//	CleanupStack::Pop(); // icons
	}

void CAppScreenContainer::UpdateDisplay()
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

void CAppScreenContainer::GetAppInfo(CGulIcon* aIcon, const TDesC& aInfo,
		const TUid aUid)
	{
	CTextListBoxModel* model = iListBox->Model();
	CDesCArray* items = static_cast<CDesCArray*> (model->ItemTextArray());

	CArrayPtr<CGulIcon>* icons =
			iListBox->ItemDrawer()->ColumnData()->IconArray();

	icons->AppendL(aIcon);
//	__LOGDES_TOFILE(aInfo);
	items->AppendL(aInfo);
	iUids.Append(aUid);

	if (++iAppRefresh > MAX_APP_REFRESH_NUMBER)
		{
		iAppRefresh = 0;
		iListBox->HandleItemAdditionL();
		}
	}

void CAppScreenContainer::Selected()
	{
	CListBoxView* view = iListBox->View();
	CAknFilteredTextListBoxModel* model = STATIC_CAST (CAknFilteredTextListBoxModel*, iListBox->Model ());
	CAknListBoxFilterItems* filter = model->Filter();

	TInt index = view->CurrentItemIndex();
	TInt fIndex = filter->FilteredItemIndex(index);

	//TInt index = iListBox->CurrentItemIndex();

	TUid uid = iUids[fIndex];
	TPtrC name = iListBox->Model()->ItemText(index);
	SHModel()->SetTransUid(uid);
	TInt pos = name.Locate('\t');
	if (pos != KErrNotFound)
		SHModel()->SetTransName(name.Mid(pos + 1));

	SHChangeViewParam(EScheduleKillerSettingScreenViewId, KViewChangeFromApp);
	}

CAknSearchField* CAppScreenContainer::CreateFindBoxL(CEikListBox* aListBox,
		CTextListBoxModel* aModel, CAknSearchField::TSearchFieldStyle aStyle)
	{
	CAknSearchField* findbox = NULL;

	if (aListBox && aModel)
		{
		// Gets pointer of CAknFilteredTextListBoxModel.
		CAknFilteredTextListBoxModel* model = STATIC_CAST( CAknFilteredTextListBoxModel*, aModel );
		// Creates FindBox.
		findbox = CAknSearchField::NewL(*this, aStyle, NULL,
		KAknExListFindBoxTextLength);
		CleanupStack::PushL(findbox);
		// Creates CAknListBoxFilterItems class.
		model->CreateFilterL(aListBox, findbox);
		//Filter can get by model->Filter();
		CleanupStack::Pop(findbox); // findbox
		}

	return findbox;
	}
