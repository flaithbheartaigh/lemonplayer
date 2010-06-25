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
#include "SHPlatform.h"
#include "LoadMessageEngine.h"
#include "MacroUtil.h"

CLoadDraftContainer::CLoadDraftContainer()
:iInfoArray(NULL),iListBox(NULL)
	{
	// No implementation required
	}

CLoadDraftContainer::~CLoadDraftContainer()
	{
	if (iInfoArray)
		{
		iInfoArray->ResetAndDestroy();
		delete iInfoArray;
		}
	
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

	iListBox = new (ELeave) CAknDoubleGraphicStyleListBox ();
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
		case EKeyDevice3:
			if (aType == EEventKey)
				{
				Selected();
				return EKeyWasConsumed;
				}
			break;
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
	
	CLoadMessageEngine* engine = CLoadMessageEngine::NewL();
	iInfoArray = new CSMSInfoListArray(4);
#ifdef __WINS__
	_LIT(KContent,"Hello");
	_LIT(KNumber,"1358008000");
	CSMSInfoList* temp = new (ELeave) CSMSInfoList;
	temp->iContent = KContent().AllocL();
	temp->iNumber = KNumber().AllocL();
	temp->iMsgId = 1048584;
	iInfoArray->Append(temp);
//	engine->LoadSMSFromFolder(iInfoArray,0x1003);
#else
	engine->LoadSMSDraft(iInfoArray);
#endif
	
	_LIT(KItemFormat, "0\t");
	for(TInt i=0; i<iInfoArray->Count(); i++)
		{
		CSMSInfoList* info = (*iInfoArray)[i];
		TPtrC content = info->iContent->Des();
		TPtrC number = info->iNumber->Des();
		TInt length = content.Length() + number.Length() + KItemFormat().Length() + 4;
		
		HBufC* record;
		record = HBufC::NewL(length);
		record->Des().Copy(KItemFormat);
		record->Des().Append(info->iNumber->Des());
		record->Des().Append('\t');		
		record->Des().Append(info->iContent->Des());
		
		items->AppendL(record->Des());
		delete record;
		}
	delete engine;

	iListBox->HandleItemAdditionL();

	}

void CLoadDraftContainer::Selected()
	{
	TInt index = iListBox->CurrentItemIndex();
	
	TInt count = 0;
	if (iInfoArray)
		count = iInfoArray->Count();
	if (index >=0 && index < count)
		{
		CSMSInfoList* info = (*iInfoArray)[index];
		TMsvId msg = info->iMsgId;
		
		SHModel()->SetDraftMsg(msg);
		SHModel()->SetEditModel(CSHModel::EEditModelLoadDraft);
		
		SHChangeViewParam(ESimulateMessageEditViewId,KViewChangeFromLoadDraft);
		}
	}
