/*
 ============================================================================
 Name		: MainScreenView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CMainScreenView implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>
#include <eikmenup.h> 
#include <eikbtgpc.h> 
#include "MainScreenView.h"

#include "SHPlatform.h"
#include "SeniorUtils.h"
//copy from ScheduleKillerAppView.cpp
//#include "ScheduleKiller.hrh"
//#include <ScheduleKiller_UID3.rsg>

// ============================ MEMBER FUNCTIONS ===============================
CMainScreenView::CMainScreenView()
	{
	// No implementation required
	iContainer = NULL;
	}

CMainScreenView::~CMainScreenView()
	{
	DoDeactivate();

	//add your code here ...

	}

CMainScreenView* CMainScreenView::NewLC()
	{
	CMainScreenView* self = new (ELeave) CMainScreenView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMainScreenView* CMainScreenView::NewL()
	{
	CMainScreenView* self = CMainScreenView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CMainScreenView::ConstructL()
	{
	BaseConstructL(R_VIEW_MAINSCREEN);
	//add your code here...

	SHModel()->GetRuleManager()->Init();
	}
/**
 * 
 * */
TUid CMainScreenView::Id() const
	{
	return TUid::Uid(EScheduleKillerMainScreenViewId);
	}
void CMainScreenView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ECommandAdd:
			SHChangeViewParam(EScheduleKillerSettingScreenViewId,KViewChangeFromMain);
			break;
		case ECommandRemove:
			SHModel()->SetEmputy(ETrue);
			SHModel()->GetTimeWorkManager()->Cancel();
			UpdateCBA();
			break;
		case ECommandRule:
			SHChangeView(EScheduleKillerRuleScreenViewId);
			break;
		case ECommandHelp:
			SHChangeView(ESHHelpViewId);
			break;
		case ECommandHidden:
			CSeniorUtils::HideApplication();
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CMainScreenView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

void CMainScreenView::DynInitMenuPaneL( TInt aResourceId, 
                                               CEikMenuPane* aMenuPane )
	{
	if (aResourceId == R_MENUPANE_MAINSCREEN)
		{
		if (SHModel()->IsEmputy())
			{
				aMenuPane->SetItemDimmed(ECommandAdd,  EFalse);
				aMenuPane->SetItemDimmed(ECommandRemove, ETrue);	
			}
		else
			{
				aMenuPane->SetItemDimmed(ECommandAdd,  ETrue);
				aMenuPane->SetItemDimmed(ECommandRemove, EFalse);	
			}
		}
	}

/**
 * 
 * */
void CMainScreenView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (iContainer == NULL)
		{
		iContainer = CMainScreenContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	UpdateCBA();
	}

void CMainScreenView::UpdateCBA()
	{
	CEikButtonGroupContainer* cba = CEikButtonGroupContainer::Current();         
	if (SHModel()->IsEmputy())
		cba-> SetCommandSetL(R_CBA_MAINSCREEN_OPTIONS_ADD); 
	else
		cba-> SetCommandSetL(R_CBA_MAINSCREEN_OPTIONS_TASK_RUNNING); 
	cba-> DrawNow();
	}

void CMainScreenView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
