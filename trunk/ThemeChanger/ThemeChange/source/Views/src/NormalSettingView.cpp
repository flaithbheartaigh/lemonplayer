/*
 ============================================================================
 Name		: NormalSettingView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CNormalSettingView implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "NormalSettingView.h"

//copy from ThemeChangeAppView.cpp
#include "ThemeChange.hrh"
#include "ThemeChangeAppUi.h"
#include <ThemeChange_0xE8EE38C1.rsg>
#include "QueryDlgUtil.h"
#include "ThemeChangeDef.h"

// ============================ MEMBER FUNCTIONS ===============================
CNormalSettingView::CNormalSettingView()
	{
	// No implementation required
	iContainer = NULL;
	}

CNormalSettingView::~CNormalSettingView()
	{
	DoDeactivate();

	//add your code here ...

	}

CNormalSettingView* CNormalSettingView::NewLC()
	{
	CNormalSettingView* self = new (ELeave) CNormalSettingView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CNormalSettingView* CNormalSettingView::NewL()
	{
	CNormalSettingView* self = CNormalSettingView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CNormalSettingView::ConstructL()
	{
	BaseConstructL(R_VIEW_OK_BACK);

	//add your code here...

	}
/**
 * 
 * */
TUid CNormalSettingView::Id() const
	{
	return TUid::Uid(EThemeChangeSettingView);
	}
void CNormalSettingView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EAknSoftkeyOk:
			if (iContainer)
				{
				iContainer->StoreSettingsL();
				if (iContainer->IsChange())
					{
					//¶Ô»°¿ò 
					if (ShowConfirmationQueryL(R_CONFIRM_SAVE_CONFIG))
						{
						TInt result = iContainer->SaveConfig();
						if ( (result & KCfgChangeFrequency) != 0)
							OKCChangeView(EThemeChangeAppViewId,EThemeChangeSettingView,KMsgCfgChange);
						else
							OKCChangeView(EThemeChangeAppViewId);
						}
					}
				else
					OKCChangeView(EThemeChangeAppViewId);
				}
			break;
		case EAknSoftkeyBack:
			OKCChangeView(EThemeChangeAppViewId);
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CNormalSettingView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CNormalSettingView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
		iContainer = new (ELeave) CNormalSettingContainer ;
		CleanupStack::PushL(iContainer);
		iContainer->ConstructL(ClientRect());
		CleanupStack::Pop();
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void CNormalSettingView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
