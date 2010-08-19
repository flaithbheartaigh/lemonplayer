/*
 ============================================================================
 Name		: AppScreenView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CAppScreenView implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "AppScreenView.h"

#include "SHPlatform.h"
//copy from ScheduleKillerAppView.cpp
//#include "ScheduleKiller.hrh"
//#include <ScheduleKiller_UID3.rsg>

// ============================ MEMBER FUNCTIONS ===============================
CAppScreenView::CAppScreenView()
	{
	// No implementation required
	iContainer = NULL;
	}

CAppScreenView::~CAppScreenView()
	{
	DoDeactivate();

	//add your code here ...

	}

CAppScreenView* CAppScreenView::NewLC()
	{
	CAppScreenView* self = new (ELeave) CAppScreenView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CAppScreenView* CAppScreenView::NewL()
	{
	CAppScreenView* self = CAppScreenView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CAppScreenView::ConstructL()
	{
	BaseConstructL(R_VIEW_APPSCREEN);

	//add your code here...

	}
/**
 * 
 * */
TUid CAppScreenView::Id() const
	{
	return TUid::Uid(EScheduleKillerAppScreenViewId);
	}
void CAppScreenView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EAknSoftkeySelect:
			if (iContainer)
				iContainer->Selected();
			break;
			//可以不用break,因为也需要返回的
		case EAknSoftkeyCancel:
			SHChangeViewParam(EScheduleKillerSettingScreenViewId,KViewChangeFromApp);
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CAppScreenView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CAppScreenView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (iContainer == NULL)
		{
		iContainer = CAppScreenContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void CAppScreenView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
