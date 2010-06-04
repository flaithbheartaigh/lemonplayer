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

#include "MainScreenView.h"

#include "SHPlatform.h"

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

	}
/**
 * 
 * */
TUid CMainScreenView::Id() const
	{
	return TUid::Uid(ESimulateMessageMainScreenViewId);
	}

void CMainScreenView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ECommandCreate:
		case ECommandCreateNew:
			SHChangeView(ESimulateMessageEditViewId);
			break;
		case ECommandCreateFrom:
			SHChangeView(ESimulateMessageLoadDraftViewId);
			break;
		case ECommandManage:
		case ECommandManageEdit:
			SHChangeView(ESimulateMessageEditViewId);
			break;
		case ECommandmanageRemove:
		case ECommandActiveServer:
		case ECommandDeactiveServer:
		case ECommandSetting:
			SHChangeView(ESimulateMessageSettingViewId);
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

/**
 * 
 * */
void CMainScreenView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (iContainer == NULL)
		{
		iContainer = CMainScreenContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
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
