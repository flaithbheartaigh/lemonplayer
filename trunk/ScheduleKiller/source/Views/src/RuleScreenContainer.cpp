/*
 ============================================================================
 Name		: RuleScreenContainer.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRuleScreenContainer implementation
 ============================================================================
 */
#include "RuleScreenContainer.h"

#include <coemain.h>
#include <apgtask.h>
#include <eikenv.h>
#include <apgcli.h>
#include <aknlists.h> 
#include <AknIconArray.h> 
#include <eikclbd.h>
#include <StringLoader.h> 

#include "ShPlatform.h"

CRuleScreenContainer::CRuleScreenContainer()
	{
	// No implementation required
	}

CRuleScreenContainer::~CRuleScreenContainer()
	{
	if (iListBox)
		delete iListBox;
	}

CRuleScreenContainer* CRuleScreenContainer::NewLC(const TRect& aRect)
	{
	CRuleScreenContainer* self = new (ELeave) CRuleScreenContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

CRuleScreenContainer* CRuleScreenContainer::NewL(const TRect& aRect)
	{
	CRuleScreenContainer* self = CRuleScreenContainer::NewLC(aRect);
	CleanupStack::Pop(); // self;
	return self;
	}

void CRuleScreenContainer::ConstructL(const TRect& aRect)
	{
	CreateWindowL();

	iListBox = new (ELeave) CAknDoubleStyleListBox ();
	iListBox->ConstructL(this,EAknListBoxSelectionList);
	iListBox->SetContainerWindowL(*this);

	// Creates scrollbar.
	iListBox->CreateScrollBarFrameL(ETrue);
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
			CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);

	//SetIconsL();
	UpdateDisplay();

	SetRect(aRect);
	ActivateL();
	}

// ---------------------------------------------------------
// CThemeChangeContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CRuleScreenContainer::CountComponentControls() const
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
CCoeControl* CRuleScreenContainer::ComponentControl(TInt aIndex) const
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
void CRuleScreenContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CRuleScreenContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CRuleScreenContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
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
			Select();
			return EKeyWasConsumed;
			break;
		default:
			break;
		}
	return EKeyWasNotConsumed;
	}
// -----------------------------------------------------------------------------
// CRuleScreenContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CRuleScreenContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	}

// -----------------------------------------------------------------------------
// CRuleScreenContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CRuleScreenContainer::SizeChanged()
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
void CRuleScreenContainer::SetIconsL()
	{
//	CAknIconArray* icons = new (ELeave) CAknIconArray(2);
//	CleanupStack::PushL(icons);
//	icons->ConstructFromResourceL(R_ICON_MARK);
//	iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons);
//	CleanupStack::Pop(); // icons
	}
//格式:\t名字\程序 倒计时/定时 %d分钟/时间
void CRuleScreenContainer::UpdateDisplay()
	{

	CTextListBoxModel* model = iListBox->Model();
	CDesCArray* items = static_cast<CDesCArray*> (model->ItemTextArray());
	
	RPointerArray<CRule>* rules = SHModel()->GetRuleManager()->Rules();

	items->Reset();
	_LIT(KItemFormat, "\tItem\titem");

	if (rules)
		{
		for (TInt i = 0; i < rules->Count(); i++)
			{
			CRule* rule = (*rules)[i];
			TPtrC rulename 	= rule->GetRuleName();
			TPtrC appname  	= rule->GetName();
			TInt type 		= rule->GetType();
			TInt countdown 	= rule->GetCountDown();
			TTime time 		= rule->GetClock();
			
			TInt len = rulename.Length() + appname.Length() + 16;
			HBufC* record = HBufC::NewL(len);
			TPtr ptr = record->Des();
			ptr.Append('\t');
			ptr.Append(rulename);
			ptr.Append('\t');
			ptr.Append(appname);
			ptr.Append(' ');
			if (type == 0)
				{
				HBufC* txt = StringLoader::LoadL(R_TEXT_TYPE_COUNTDOWN);
				TBuf<16> app;
				app.Format(txt->Des(),countdown);
				ptr.Append(app);
				delete txt;
				}
			else
				{
				HBufC* txt = StringLoader::LoadL(R_TEXT_TYPE_CLOCKING);
				TBuf<16> app;
				TBuf8<8> timetxt8;
				TBuf<8> timetxt;
				CRuleManager::TimeFormat(time,timetxt8);
				timetxt.Copy(timetxt8);
				app.Format(txt->Des(),&timetxt);
				ptr.Append(app);
				delete txt;
				}
			
			items->AppendL(ptr);
			delete record;
			}
		}

	iListBox->HandleItemAdditionL();

	}

TBool CRuleScreenContainer::Select()
	{
	TInt index = iListBox->CurrentItemIndex();
	return SHModel()->GetRuleManager()->Select(index);
	}
