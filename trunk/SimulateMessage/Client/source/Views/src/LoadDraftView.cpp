/*
 ============================================================================
 Name		: LoadDraftView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CLoadDraftView implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "LoadDraftView.h"

//copy from SimulateMessageAppView.cpp
#include "SimulateMessage.hrh"
#include <SimulateMessage_0xE70CE849.rsg>

// ============================ MEMBER FUNCTIONS ===============================
CLoadDraftView::CLoadDraftView()
	{
	// No implementation required
	iContainer = NULL;
	}

CLoadDraftView::~CLoadDraftView()
	{
	DoDeactivate();

	//add your code here ...

	}

CLoadDraftView* CLoadDraftView::NewLC()
	{
	CLoadDraftView* self = new (ELeave) CLoadDraftView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLoadDraftView* CLoadDraftView::NewL()
	{
	CLoadDraftView* self = CLoadDraftView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CLoadDraftView::ConstructL()
	{
	BaseConstructL(R_VIEW_LOADDRAFT);

	//add your code here...

	}
/**
 * 
 * */
TUid CLoadDraftView::Id() const
	{
	return TUid::Uid(ESimulateMessageLoadDraftViewId);
	}
void CLoadDraftView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CLoadDraftView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CLoadDraftView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
		iContainer = CLoadDraftContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void CLoadDraftView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
