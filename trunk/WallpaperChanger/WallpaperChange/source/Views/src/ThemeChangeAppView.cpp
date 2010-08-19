/*
 ============================================================================
 Name		: ThemeChangeAppView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "ThemeChangeAppView.h"

#include <eikmenup.h>
#include <ThemeChange_0xEAC842A2.rsg>
#include "ThemeChange.hrh"
#include "ThemeChangeDef.h"

// ============================ MEMBER FUNCTIONS ===============================
CThemeChangeAppView::CThemeChangeAppView()
	{
	// No implementation required
	iContainer = NULL;
	}

CThemeChangeAppView::~CThemeChangeAppView()
	{
	DoDeactivate();
	}

CThemeChangeAppView* CThemeChangeAppView::NewLC()
	{
	CThemeChangeAppView* self = new (ELeave) CThemeChangeAppView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CThemeChangeAppView* CThemeChangeAppView::NewL()
	{
	CThemeChangeAppView* self = CThemeChangeAppView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CThemeChangeAppView::ConstructL()
	{
	BaseConstructL(R_VIEW_APP);

	//add your code here...

	}
/**
 * 
 * */
TUid CThemeChangeAppView::Id() const
	{
	return TUid::Uid(EThemeChangeAppViewId);
	}
void CThemeChangeAppView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ECommandChoose:
			if (iContainer)
				iContainer->Selected();
			break;
		case ECommandRemove:
			if (iContainer)
				iContainer->UninstallL();
			break;
		case ECommandStart:
			if (iContainer)
				iContainer->StartServer();
			break;
		case ECommandStop:
			if (iContainer)
				iContainer->StopServer();
			break;		
		case ECommandSettingTheme:
		case ECommandSettingService:
			break;
		case ECommandRegister:
			if (iContainer)
				iContainer->StartPaymentWaitDlg();
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CThemeChangeAppView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CThemeChangeAppView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid /*aCustomMessageId*/, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
		iContainer = CThemeChangeAppContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...
		if (aCustomMessage.Length() > 0)
			{
			if (aCustomMessage.Compare(KMsgCfgChange))
				{
				iContainer->RefreshServer();
				}
			}
		}
	}
void CThemeChangeAppView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}

void CThemeChangeAppView::DynInitMenuPaneL( TInt aResourceId, 
                                               CEikMenuPane* aMenuPane )
	{
	if (aResourceId == R_MENU_SERVICE)
		{
		if (iContainer->IsServerActive())
			{
			aMenuPane->SetItemDimmed(ECommandStart, ETrue);
			aMenuPane->SetItemDimmed(ECommandStop, EFalse);
			}
		else
			{
			aMenuPane->SetItemDimmed(ECommandStart, EFalse);
			aMenuPane->SetItemDimmed(ECommandStop, ETrue);			
			}
		}
	else if (aResourceId == R_MENU_THEME)
		{
		if (iContainer->IsCurrentDeletable())
			{
			aMenuPane->SetItemDimmed(ECommandRemove, EFalse);
			}
		else
			{
			aMenuPane->SetItemDimmed(ECommandRemove, ETrue);	
			}		
		}
	}

void CThemeChangeAppView::StopWaitDlg()
	{
	if (iContainer)
		iContainer->StopWaitDlg();
	}
// End of File
