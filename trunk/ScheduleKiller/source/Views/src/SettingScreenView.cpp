/*
 ============================================================================
 Name		: SettingScreenView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CSettingScreenView implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "SettingScreenView.h"

#include "SHPlatform.h"
//copy from ScheduleKillerAppView.cpp
//#include "ScheduleKiller.hrh"
//#include <ScheduleKiller_UID3.rsg>

// ============================ MEMBER FUNCTIONS ===============================
CSettingScreenView::CSettingScreenView()
	{
	// No implementation required
	iContainer = NULL;
	}

CSettingScreenView::~CSettingScreenView()
	{
	DoDeactivate();

	//add your code here ...

	}

CSettingScreenView* CSettingScreenView::NewLC()
	{
	CSettingScreenView* self = new (ELeave) CSettingScreenView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSettingScreenView* CSettingScreenView::NewL()
	{
	CSettingScreenView* self = CSettingScreenView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CSettingScreenView::ConstructL()
	{
	BaseConstructL(R_VIEW_SETTINGSCREEN);

	//add your code here...

	}
/**
 * 
 * */
TUid CSettingScreenView::Id() const
	{
	return TUid::Uid(EScheduleKillerSettingScreenViewId);
	}
void CSettingScreenView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
//		case EAknSoftkeySave:
		case EAknSoftkeyOk:
			if (iContainer)
				if (!iContainer->Save())
					break;
			//可以不用break,因为也需要返回的
		case EAknSoftkeyBack:
			SHChangeView(EScheduleKillerMainScreenViewId);
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CSettingScreenView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CSettingScreenView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
		iContainer = new (ELeave) CSettingScreenContainer;
		if (aCustomMessage.Length())
			{
			if (aCustomMessage.Compare(KViewChangeFromMain) == 0)
				iContainer->InitDataFromMain();
			else if (aCustomMessage.Compare(KViewChangeFromApp) == 0)
				iContainer->InitDataFromApp();
			}
		iContainer->ConstructL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);
		//add your init code ...
		}
	}
void CSettingScreenView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
