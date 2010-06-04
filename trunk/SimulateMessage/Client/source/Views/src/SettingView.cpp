/*
 ============================================================================
 Name		: SettingView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CSettingView implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "SettingView.h"

//copy from SimulateMessageAppView.cpp
#include "SimulateMessage.hrh"
#include <SimulateMessage_0xE70CE849.rsg>

// ============================ MEMBER FUNCTIONS ===============================
CSettingView::CSettingView()
	{
	// No implementation required
	iContainer = NULL;
	}

CSettingView::~CSettingView()
	{
	DoDeactivate();

	//add your code here ...

	}

CSettingView* CSettingView::NewLC()
	{
	CSettingView* self = new (ELeave) CSettingView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSettingView* CSettingView::NewL()
	{
	CSettingView* self = CSettingView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CSettingView::ConstructL()
	{
	BaseConstructL(R_VIEW_SETTING);

	//add your code here...

	}
/**
 * 
 * */
TUid CSettingView::Id() const
	{
	return TUid::Uid(ESimulateMessageSettingViewId);
	}
void CSettingView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CSettingView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CSettingView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
//		iContainer = CSettingContainer::NewL(ClientRect());
		
		iContainer = CSettingList::NewL();
		iContainer->SetMopParent(this);
		iContainer->ConstructFromResourceL( R_LISTBOX_SETTING_ITEM_LIST );
		AppUi()->AddToStackL(*this, iContainer);
		
	    iContainer->MakeVisible( ETrue );
	    iContainer->SetRect( ClientRect() );
	    iContainer->ActivateL();

		//add your init code ...

		}
	}
void CSettingView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
