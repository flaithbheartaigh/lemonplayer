/*
 ============================================================================
 Name		: MainScreenContainer.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMainScreenContainer implementation
 ============================================================================
 */
#include "MainScreenContainer.h"

#include <coemain.h>
#include <apgtask.h>
#include <eikenv.h>
#include <apgcli.h>
#include <aknlists.h> 
#include <AknIconArray.h> 
#include <eikclbd.h>
#include "SHPlatform.h"

CMainScreenContainer::CMainScreenContainer()
	{
	// No implementation required
	}

CMainScreenContainer::~CMainScreenContainer()
	{
	if (iListBox)
		delete iListBox;

	if (iTaskArray)
		{
		iTaskArray->ResetAndDestroy();
		delete iTaskArray;
		}
	}

CMainScreenContainer* CMainScreenContainer::NewLC(const TRect& aRect)
	{
	CMainScreenContainer* self = new (ELeave) CMainScreenContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

CMainScreenContainer* CMainScreenContainer::NewL(const TRect& aRect)
	{
	CMainScreenContainer* self = CMainScreenContainer::NewLC(aRect);
	CleanupStack::Pop(); // self;
	return self;
	}

void CMainScreenContainer::ConstructL(const TRect& aRect)
	{
	CreateWindowL();

	iTaskArray = new RSimMsgDataArray();

	iListBox = new (ELeave) CAknDoubleGraphicStyleListBox();
	iListBox->ConstructL(this, 0);
	iListBox->SetContainerWindowL(*this);

	// Creates scrollbar.
	iListBox->CreateScrollBarFrameL(ETrue);
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
			CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
	// Enable marquee
	iListBox->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);

	SetIconsL();
	UpdateDisplay();

	SetRect(aRect);
	ActivateL();
	}

// ---------------------------------------------------------
// CThemeChangeContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CMainScreenContainer::CountComponentControls() const
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
CCoeControl* CMainScreenContainer::ComponentControl(TInt aIndex) const
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
void CMainScreenContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CMainScreenContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CMainScreenContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
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
// CMainScreenContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CMainScreenContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	}

// -----------------------------------------------------------------------------
// CMainScreenContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CMainScreenContainer::SizeChanged()
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
void CMainScreenContainer::SetIconsL()
	{
	CAknIconArray* icons = new (ELeave) CAknIconArray(2);
	CleanupStack::PushL(icons);
	icons->ConstructFromResourceL(R_ICON_MARK);
	iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons);
	CleanupStack::Pop(); // icons
	}

//const TInt MAX_TASK_DATA_BUFFER_SIZE = 1024;

void CMainScreenContainer::UpdateDisplay()
	{
	TInt total;
	HBufC8* buffer;

	SHSession().QueryAllLength(total);
	if (total > 0)
		{
		buffer = HBufC8::NewL(total);
		TPtr8 ptr = buffer->Des();
		SHSession().QueryAllData(ptr);

		CSimMsgServerSession::ParseDataBuffer(buffer, *iTaskArray);

		CTextListBoxModel* model = iListBox->Model();
		CDesCArray* items = static_cast<CDesCArray*> (model->ItemTextArray());

		items->Reset();

		for (TInt i = 0; i < iTaskArray->Count(); i++)
			{
			SimMsgData* task = (*iTaskArray)[i];
			TPtrC name = task->iName->Des();
			
			//剔除末尾三个特殊字符 e2 80 a9
//			TInt cl = task->iContent->Length() - 3;
//			if (cl<0)
//				cl = 0;
//			cl = cl < KMessageBriefLength ? cl : KMessageBriefLength;
				
			TPtrC content = task->iContent->Des().Left(KMessageBriefLength);
			TBuf<32> time;
			task->iTime.FormatL(time, KDateFormat);

			//格式 名字 - 时间 - 
			HBufC* item;
			TInt len = name.Length() + time.Length() + content.Length() + KListItemFormat().Length() + 4;
			
			item = HBufC::NewL(len);
			item->Des().Format(KListItemFormat, &name, &time, &content);
//			TBuf<64> item;
//			item->Des().Append(_L("0\t"));
//			item->Des().Append(number);
//			item->Des().Append('\t');
//			item->Des().Append(time);

			items->AppendL(item->Des());
			delete item;
			}

		delete buffer;

		iListBox->HandleItemAdditionL();
		}
	}

void CMainScreenContainer::RemoveSelectedTask()
	{
	TInt index = iListBox->CurrentItemIndex();
	
	if (index >=0 )
		{
		SimMsgData* task = (*iTaskArray)[index];
		SHSession().RemoveTask(*task);
	
		CTextListBoxModel* model = iListBox->Model();
		CDesCArray* items = static_cast<CDesCArray*> (model->ItemTextArray());
	
		items->Delete(index);
	
		iListBox->HandleItemAdditionL();
		}
	}

void CMainScreenContainer::EditSelectedTask()
	{
	TInt index = iListBox->CurrentItemIndex();
	
	if (index >= 0)
		{
		SimMsgData* task = (*iTaskArray)[index];
		SHSession().RemoveTask(*task);
	
		SHModel()->SetEditMessage(task);
		SHModel()->SetEditModel(CSHModel::EEditmodelModify);
	
		SHChangeViewParam(ESimulateMessageEditViewId, KViewChangeFromModify);
		}
	}
