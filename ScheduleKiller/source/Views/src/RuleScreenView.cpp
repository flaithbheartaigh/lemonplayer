/*
 ============================================================================
 Name		: RuleScreenView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CRuleScreenView implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "RuleScreenView.h"

#include "SHPlatform.h"
//copy from ScheduleKillerAppView.cpp
//#include "ScheduleKiller.hrh"
//#include <ScheduleKiller_UID3.rsg>

// ============================ MEMBER FUNCTIONS ===============================
CRuleScreenView::CRuleScreenView()
	{
	// No implementation required
	iContainer = NULL;
	}

CRuleScreenView::~CRuleScreenView()
	{
	DoDeactivate();

	//add your code here ...

	}

CRuleScreenView* CRuleScreenView::NewLC()
	{
	CRuleScreenView* self = new (ELeave) CRuleScreenView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CRuleScreenView* CRuleScreenView::NewL()
	{
	CRuleScreenView* self = CRuleScreenView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CRuleScreenView::ConstructL()
	{
	BaseConstructL(R_VIEW_RULESCREEN);

	//add your code here...

	}
/**
 * 
 * */
TUid CRuleScreenView::Id() const
	{
	return TUid::Uid(EScheduleKillerRuleScreenViewId);
	}
void CRuleScreenView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ECommandRemove:
			if (iContainer)
				iContainer->Delete();
			break;
		case ECommandOpen:
			if (iContainer)
				if (!iContainer->Select())
					break;
			//需要返回,不用break
		case EAknSoftkeyBack:
			SHChangeView(EScheduleKillerMainScreenViewId);
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CRuleScreenView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CRuleScreenView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (iContainer == NULL)
		{
		iContainer = CRuleScreenContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void CRuleScreenView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
