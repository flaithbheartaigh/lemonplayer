/*
 ============================================================================
 Name		: SettingScreenContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Container control implementation
 ============================================================================
 */

// INCLUDE FILES
#include <eikfrlbd.h> 
#include <stringloader.h> 

#include "SettingScreenContainer.h"
#include "SHPlatform.h"
// ================= MEMBER FUNCTIONS =======================

// -----------------------------------------------------------------------------
// CSettingScreenAppContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSettingScreenContainer* CSettingScreenContainer::NewL(const TRect& aRect)
	{
	CSettingScreenContainer* self = CSettingScreenContainer::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CSettingScreenAppContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSettingScreenContainer* CSettingScreenContainer::NewLC(const TRect& aRect)
	{
	CSettingScreenContainer* self = new (ELeave) CSettingScreenContainer;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// C$(baseName)AppContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSettingScreenContainer::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	ConstructFromResourceL(R_ENTRY_SETTINGS_LIST);

	ModifyItemL(EListboxSettingType);
	
	SetRect(aRect);
	ActivateL();

	//add your code here ...
	}

// -----------------------------------------------------------------------------
// CSettingScreenAppContainer::C$(baseName)AppContainer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSettingScreenContainer::CSettingScreenContainer()
:iNumber(30)
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CSettingScreenAppContainer::~C$(baseName)AppContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
CSettingScreenContainer::~CSettingScreenContainer()
	{
	// No implementation required
	}

CAknSettingItem* CSettingScreenContainer::CreateSettingItemL(TInt aSettingId)
	{
	CAknSettingItem* settingItem = NULL;

	switch (aSettingId)
		{
		case EListboxSettingName:
			settingItem = new (ELeave) CAknTextSettingItem(EListboxSettingName,
					iText);
			break;
		case EListboxSettingType:
			settingItem = new (ELeave) CAknBinaryPopupSettingItem(
					EListboxSettingType, iBinary);
			break;
		case EListboxSettingCountdown:
			settingItem = new (ELeave) CAknIntegerEdwinSettingItem(
					EListboxSettingCountdown, iNumber);
			break;
		case EListboxSettingClocking:
			settingItem = new (ELeave) CAknTimeOrDateSettingItem(
					EListboxSettingClocking, CAknTimeOrDateSettingItem::ETime,
					iDate);
			break;
		case EListboxSettingRule:
			settingItem = new (ELeave) CAknTextSettingItem(EListboxSettingRule,
					iRule);
			break;
		default:
			break;
		}

	return settingItem;
	}

void CSettingScreenContainer::EditItemL(TBool aCalledFromMenu)
	{
	TInt currentItem =
					((CAknSettingItemList*) this)->ListBox()->View()->CurrentItemIndex();
	if (currentItem == 0)
		{
		JumpToAppView();
		return;
		}
	CAknSettingItemList::EditItemL(currentItem, aCalledFromMenu);
	(*SettingItemArray())[currentItem]->UpdateListBoxTextL();
	(*SettingItemArray())[currentItem]->StoreL();
	ModifyItemL(currentItem);
	}
// ---------------------------------------------------------------------------
// CListboxSettingList::EditItemL()
// Edits setting item data.
// ---------------------------------------------------------------------------
//    
void CSettingScreenContainer::EditItemL(TInt aIndex, TBool aCalledFromMenu)
	{
	if (aIndex == 0)
		{
		JumpToAppView();
		return;
		}
	CAknSettingItemList::EditItemL(aIndex, aCalledFromMenu);
	(*SettingItemArray())[aIndex]->UpdateListBoxTextL();
	(*SettingItemArray())[aIndex]->StoreL();
	ModifyItemL(aIndex);
	}

TKeyResponse CSettingScreenContainer::OfferKeyEventL(
		const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	if (aType != EEventKey)
		return EKeyWasNotConsumed;

	TInt index = ListBox()->CurrentItemIndex();

	if (aKeyEvent.iCode == EKeyDevice3 && index == EListboxSettingName)
		{
		JumpToAppView();
		return EKeyWasConsumed;
		}
	else
		return ListBox()->OfferKeyEventL(aKeyEvent, aType);

	}

void CSettingScreenContainer::ModifyItemL(TInt aIndex)
	{
	if (aIndex == EListboxSettingType)
		{
		CAknSettingItemArray* array = SettingItemArray();
		if (iBinary == 0)
			{
			(*array)[EListboxSettingCountdown]->SetHidden(EFalse);
			(*array)[EListboxSettingClocking]->SetHidden(ETrue);
			}
		else
			{
			(*array)[EListboxSettingCountdown]->SetHidden(ETrue);
			(*array)[EListboxSettingClocking]->SetHidden(EFalse);
			}
		array->RecalculateVisibleIndicesL();
		HandleChangeInItemArrayOrVisibilityL();		
		}
	}

void CSettingScreenContainer::InitDataFromMain()
	{
	SHModel()->SetTransName(KNullDesC);
	iBinary = 0;
	iDate.HomeTime();
	}

void CSettingScreenContainer::InitDataFromApp()
	{
	const TDesC& name = SHModel()->GetTransName();
	if (name.Length())
		iText.Copy(name);
	iBinary = SHModel()->GetRule()->GetType();
	iNumber = SHModel()->GetRule()->GetCountDown();
	iDate = SHModel()->GetRule()->GetClock();
	}

TBool CSettingScreenContainer::Save()
	{
	CSHModel* model = SHModel();

	//检查数据
	if (iText.Length() == 0)
		{
		SHErrFun(ELAWarnChooseAppNull,ESHErrWarning);
		return EFalse;
		}
	
	//拷贝数据
	TTime time;
	if (iBinary == 0)
		{
		time.HomeTime();
		time += TTimeIntervalMinutes(iNumber);
		}
	else
		{
		time.HomeTime();
		
		//iDate会被重置,丢失年月日等数据,因此需要重新赋值.
		TDateTime dt;
		dt.SetYear(time.DateTime().Year());
		dt.SetMonth(time.DateTime().Month());
		dt.SetDay(time.DateTime().Day());
		dt.SetHour(iDate.DateTime().Hour());
		dt.SetMinute(iDate.DateTime().Minute());
		dt.SetSecond(0);
		
		iDate = dt;
		if (iDate <= time)
			{
			SHErrFun(ELAWarnTimeLowerThanNow,ESHErrWarning);
			return EFalse;
			}
		}
//	re = model->GetTaskInfoManager()->AppendTask(model->GetTransUid(),model->GetTransName(),time);
//	
//	//已存在
//	if (re == EFalse)
//		{
//		SHErrFun(ELAWarnTimeLowerThanNow,ESHErrWarning);
//		return EFalse;
//		}
	
	TInt err = model->GetTaskInfoManager()->AppendTask(model->GetTransName(),model->GetTransUid(),iBinary,
			iNumber,iDate);
	
	if (err == CTaskInfoManager::ETaskErrDuplicate)
		{
		SHErrFun(ELAWarnDuplicateTask,ESHErrWarning);
		return EFalse;
		}
	if (err == CTaskInfoManager::ETaskErrTimeOut)
		{
		SHErrFun(ELAWarnTimeLowerThanNow,ESHErrWarning);
		return EFalse;
		}
	
	//保存规则
	if (iRule.Length())
		{
		SHModel()->GetRuleManager()->AppendRule(iText,model->GetTransUid(),iBinary,iNumber,iDate,iRule);
		}
	//重启定时器
//	SHModel()->GetTimeWorkManager()->StartL(1000);
	
	return ETrue;
	}

void CSettingScreenContainer::JumpToAppView()
	{
	SHModel()->SetRule(iBinary,iNumber,iDate);
	SHChangeView(EScheduleKillerAppScreenViewId);
	}
// End of File

