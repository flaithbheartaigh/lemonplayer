/*
 ============================================================================
 Name		: MainScreenContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Container control implementation
 ============================================================================
 */

// INCLUDE FILES
#include "MainScreenContainer.h"

#include <akniconutils.h> 	//AknIconUtils
#include <aknsutils.h> 		//AknsUtils 
#include <aknlists.h>
#include "SHPlatform.h"
#include "MacroUtil.h"
#include "DetailListBox.h"
#include "UI_Layout.h"
#include "MainScreenView.h"

// ================= MEMBER FUNCTIONS =======================

// -----------------------------------------------------------------------------
// CMainScreenAppContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CMainScreenContainer* CMainScreenContainer::NewL(const TRect& aRect,
		CMainScreenView* aParent)
	{
	CMainScreenContainer* self = CMainScreenContainer::NewLC(aRect, aParent);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CMainScreenAppContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CMainScreenContainer* CMainScreenContainer::NewLC(const TRect& aRect,
		CMainScreenView* aParent)
	{
	CMainScreenContainer* self = new (ELeave) CMainScreenContainer(aParent);
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// C$(baseName)AppContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CMainScreenContainer::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	iPeriodicTimer = CPeriodic::NewL(CActive::EPriorityStandard);
	//InitTest();
	InitButtons();
	InitList();
	
//	SHModel()->GetRuleManager()->AutoLunch();
//	SHModel()->GetRuleManager()->FavLunch();
	//	SHModel()->GetTaskInfoManager()->InitTest();
	UpdateDisplay();

	iBgContext = CAknsBasicBackgroundControlContext::NewL(
			KAknsIIDQsnBgAreaMain, aRect, ETrue);

	SetRect(aRect);
	ActivateL();

	//add your code here ...
	if (SHModel()->GetTaskInfoManager()->ExistTask())
		Start();
	}

// -----------------------------------------------------------------------------
// CMainScreenAppContainer::C$(baseName)AppContainer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CMainScreenContainer::CMainScreenContainer(CMainScreenView* aParent) :
	iParent(aParent), iBtnAdd(NULL)
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CMainScreenAppContainer::~C$(baseName)AppContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
CMainScreenContainer::~CMainScreenContainer()
	{
		// No implementation required
		SAFE_DELETE(iBgContext)

	ReleaseButtons();
	ReleaseList();

		SAFE_DELETE_ACTIVE(iPeriodicTimer)
	}

// ---------------------------------------------------------
// CMainScreenContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CMainScreenContainer::CountComponentControls() const
	{
	TInt count = 0;
	if (iBtnAdd)
		count++;
	if (iBtnRemove)
		count++;
	if (iBtnRules)
		count++;
	if (iBtnAbout)
		count++;
	if (iBtnExit)
		count++;
	if (iListBox)
		count++;
	return count; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CMainScreenContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CMainScreenContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		case ECtrlBtnAdd:
			return iBtnAdd;
		case ECtrlBtnRemove:
			return iBtnRemove;
		case ECtrlBtnRules:
			return iBtnRules;
		case ECtrlBtnAbout:
			return iBtnAbout;
		case ECtrlBtnExit:
			return iBtnExit;
		case ECtrlList:
			return iListBox;
		default:
			return NULL;
		}
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
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	MAknsControlContext* cc = AknsDrawUtils::ControlContext(this);
	AknsDrawUtils::Background(skin, cc, this, gc, drawRect);

	}

// -----------------------------------------------------------------------------
// CMainScreenContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CMainScreenContainer::SizeChanged()
	{
	TRect rect = Rect();
	TSize size = rect.Size();
	if (iBgContext)
		{
		iBgContext->SetRect(Rect());
		if (&Window())
			{
			iBgContext->SetParentPos(PositionRelativeToScreen());
			}
		}
	Layout();

	DrawNow();
	}

void CMainScreenContainer::Layout()
	{
	TRect rect = Rect();
	TSize size = rect.Size();
	TInt count = 0;
	TInt x, y;
	if (iListBox)
		count = iListBox->Model()->NumberOfItems();

	if (iBtnAdd)
		{
		if (count)
			{
			TInt cw = rect.Width() * LIST_CONTENT_WIDTH_RATE / 100;
			cw += LIST_DELETE_ICON_SIZE.iWidth;

			x = (rect.Width() - cw - FUNCTION_BUTTON_SIZE.iWidth) / 2 + cw;
			y = (size.iHeight - FUNCTION_BUTTON_SIZE.iHeight) / 2;
			iBtnAdd->SetRect(TRect(TPoint(x, y), FUNCTION_BUTTON_SIZE));
			}
		else
			{
			x = (size.iWidth - FUNCTION_BUTTON_SIZE.iWidth) / 2;
			y = (size.iHeight - FUNCTION_BUTTON_SIZE.iHeight) / 2;
			iBtnAdd->SetRect(TRect(TPoint(x, y), FUNCTION_BUTTON_SIZE));
			}
		}

	x = 0;
	y = rect.Height() - BOTTOM_BUTTON_SIZE.iHeight;

	if (iBtnRules)
		iBtnRules->SetRect(TRect(TPoint(x, y), BOTTOM_BUTTON_SIZE));

	x += BOTTOM_BUTTON_SIZE.iWidth;
	if (iBtnAbout)
		iBtnAbout->SetRect(TRect(TPoint(x, y), BOTTOM_BUTTON_SIZE));

	x = rect.Width() - BOTTOM_BUTTON_SIZE.iWidth;
	if (iBtnExit)
		iBtnExit->SetRect(TRect(TPoint(x, y), BOTTOM_BUTTON_SIZE));

	if (iListBox && count)
		{
		//		TInt ih = iListBox->ItemDrawer()->ItemCellSize().iHeight;
		TInt ih = iListBox->ItemHeight();
		TInt cw = rect.Width() * LIST_CONTENT_WIDTH_RATE / 100;
		cw += LIST_DELETE_ICON_SIZE.iWidth;

		TInt chList = (rect.Height()) * LIST_CONTENT_HEIGHT_RATE / 100;
		chList = ((chList / ih) + (chList % ih ? 1 : 0)) * ih;
		TInt chReal = ih * count;

		iListBox->SetShowItems(chList / ih);

		TInt ch = chReal < chList ? chReal : chList;

		x = (rect.Width() - cw - FUNCTION_BUTTON_SIZE.iWidth) / 2;
		y = (rect.Height() - ch) / 2;

		iListBox->SetRect(TRect(TPoint(x, y), TSize(cw, ch)));
		}
	else if (iListBox && count == 0)
		iListBox->SetRect(TRect(TPoint(0, 0), TSize(0, 0)));
	}

// ---------------------------------------------------------
// CMainScreenContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CMainScreenContainer::HandleControlEventL(CCoeControl* aControl,
		TCoeEvent aEventType)
	{
	// TODO: Add your control event handler code here
	switch (aEventType)
		{
		case EEventStateChanged:
			{
			if (aControl == iBtnAdd)
				{
				iParent->HandleCommandL(ECommandAdd);
				}
			else if (aControl == iBtnRemove)
				{
				iParent->HandleCommandL(ECommandRemove);
				}
			else if (aControl == iBtnRules)
				{
				iParent->HandleCommandL(ECommandRule);
				}
			else if (aControl == iBtnAbout)
				{
				iParent->HandleCommandL(ECommandAbout);
				}
			else if (aControl == iBtnExit)
				{
				iParent->HandleCommandL(EAknSoftkeyExit);
				}
			}
			break;

		default:
			break;
		}
	}

void CMainScreenContainer::HandlePointerEventL(
		const TPointerEvent& aPointerEvent)
	{
	TPoint point = aPointerEvent.iPosition;
	if (iListBox == NULL)
		return;

	TInt type = aPointerEvent.iType;
	if (type == TPointerEvent::EButton1Down)
		{
		if (iListBox->Rect().Contains(point))
			{
			if (iListBox->IsFocused() == FALSE)
				iListBox->SetFocus(TRUE);
			}
		else
			{
			if (iListBox->IsFocused())
				iListBox->SetFocus(FALSE);
			}
		}
	
	if (iListBox->IsFocused())
		{
		iListBox->OfferPointerEventL(aPointerEvent);
		DrawNow();
		return;
		}
	
	CCoeControl::HandlePointerEventL(aPointerEvent);
	}
TKeyResponse CMainScreenContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	TInt code = aKeyEvent.iCode;
	switch (code)
		{
		case EKeyBackspace:
			RemoveTask();
			return EKeyWasConsumed;
		default:
			// Let Listbox take care of its key handling           
			break;
		}
	
	if (iListBox)
		{
		if (iListBox->IsFocused() == FALSE)
			iListBox->SetFocus(TRUE);
		return iListBox->OfferKeyEventL(aKeyEvent, aType);
		}		

//	if (iListBox && (aType == EEventKeyUp) && 
//			(aKeyEvent.iCode == EKeyUpArrow || aKeyEvent.iCode == EKeyDownArrow))
//		{
//		iListBox->SetFocus(TRUE);
//		return EKeyWasConsumed;
//		}
	
	return EKeyWasNotConsumed;
	}

void CMainScreenContainer::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	if (aType == KEikDynamicLayoutVariantSwitch)
		{
		TRect rect;
		AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
		//        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EScreen, rect);
		SetRect(rect);
		}
	}

CAknButton* CMainScreenContainer::CreateButton(const TInt aResourceId)
	{
	CAknButton* button = CAknButton::NewL();
	button->ConstructFromResourceL(aResourceId);
	button->SetContainerWindowL(*this);
	button->SetObserver(this);
	button->MakeVisible(ETrue);
	//	button->ActivateL();

	return button;
	}

void CMainScreenContainer::InitButtons()
	{
	iBtnAdd = CreateButton(R_BUTTON_ADD);
	iBtnRemove = CreateButton(R_BUTTON_REMOVE);
	iBtnRules = CreateButton(R_BUTTON_RULES);
	iBtnAbout = CreateButton(R_BUTTON_ABOUT);
	iBtnExit = CreateButton(R_BUTTON_EXIT);
	}

void CMainScreenContainer::ReleaseButtons()
	{
		SAFE_DELETE(iBtnAdd)
		SAFE_DELETE(iBtnRemove)
		SAFE_DELETE(iBtnRules)
		SAFE_DELETE(iBtnAbout)
		SAFE_DELETE(iBtnExit)
	}

void CMainScreenContainer::InitList()
	{
	iListBox = new (ELeave) CDetailListBox();
	iListBox->ConstructL(this);
	iListBox->SetContainerWindowL(*this);

	iListBox->SetItemHeightL(LIST_DELETE_AREA_SIZE.iHeight);
	// Creates scrollbar.
	iListBox->CreateScrollBarFrameL(ETrue);
	
	if (SHModel()->GetTaskInfoManager()->GetTaskList().Count() <=4)
		iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
				CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOff);
	else
		iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
				CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
	iListBox->SetNotify(this);

	}

void CMainScreenContainer::UpdateDisplay()
	{
	CTextListBoxModel* model = iListBox->Model();
	CDesCArray* items = static_cast<CDesCArray*> (model->ItemTextArray());

	items->Reset();

	RPointerArray<TaskInfo>& array =
			SHModel()->GetTaskInfoManager()->GetTaskList();

	for (TInt i = 0; i < array.Count(); i++)
		{
		items->AppendL(KNullDesC);
		}

	//	if (array.Count())
	//		iListBox->SetCurrentItemIndex(0);

	iListBox->HandleItemAdditionL();
	}

void CMainScreenContainer::ReleaseList()
	{
		SAFE_DELETE(iListBox)
	}

void CMainScreenContainer::Start()
	{
	if (iPeriodicTimer && !iPeriodicTimer->IsActive())
		{
		iPeriodicTimer->Start(1, 1000000, TCallBack(
				CMainScreenContainer::Period, this));
		}
	SHModel()->GetTimeWorkManager()->StartL(1000);
	}
void CMainScreenContainer::Stop()
	{
	if (iPeriodicTimer && iPeriodicTimer->IsActive())
		{
		iPeriodicTimer->Cancel();
		}
	}

TInt CMainScreenContainer::Period(TAny* aPtr)
	{
	(static_cast<CMainScreenContainer*> (aPtr))->DoPeriodTask();
	// Returning a value of TRUE indicates the callback should be done again
	return ETrue;
	}

void CMainScreenContainer::DoPeriodTask()
	{
	Update();

	DrawNow();
	}

void CMainScreenContainer::Update()
	{
	SHModel()->GetTaskInfoManager()->ConvertClockNumber();
	}

TTypeUid::Ptr CMainScreenContainer::MopSupplyObject(TTypeUid aId)
	{
	if (iBgContext)
		{
		return MAknsControlContext::SupplyMopObject(aId, iBgContext);
		}
	return CCoeControl::MopSupplyObject(aId);
	}

void CMainScreenContainer::TimeOut()
	{
	if (SHModel()->GetTaskInfoManager()->ExistTask())
		{
		//Ë¢ÐÂ½çÃæ
		UpdateDisplay();
		}
	}

void CMainScreenContainer::HandleListEvent(
		MDetailListBoxNotify::TEventType aEvent)
	{
	switch (aEvent)
		{
		case MDetailListBoxNotify::EEventRemove:
			{
			RemoveTask();
			}
			break;
		default:
			break;
		}
	}

void CMainScreenContainer::RemoveTask()
	{
	if (!iListBox->IsFocused())
		return;
	
	TInt index = iListBox->CurrentItemIndex();
	SHModel()->GetTaskInfoManager()->RemoveTask(index);
	UpdateDisplay();
	Layout();
	iListBox->SetFocus(FALSE);
	iParent->UpdateCBA();
	}
// End of File

