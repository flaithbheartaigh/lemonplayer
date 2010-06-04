/*
 ============================================================================
 Name		: SimulateMessageAppView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "SimulateMessageAppView.h"

#include <SimulateMessage_0xE70CE849.rsg>
#include "SimulateMessage.hrh"

// ============================ MEMBER FUNCTIONS ===============================
CSimulateMessageAppView::CSimulateMessageAppView()
	{
	// No implementation required
	iContainer = NULL;
	}

CSimulateMessageAppView::~CSimulateMessageAppView()
	{
	DoDeactivate();
	}

CSimulateMessageAppView* CSimulateMessageAppView::NewLC()
	{
	CSimulateMessageAppView* self = new (ELeave) CSimulateMessageAppView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSimulateMessageAppView* CSimulateMessageAppView::NewL()
	{
	CSimulateMessageAppView* self = CSimulateMessageAppView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CSimulateMessageAppView::ConstructL()
	{
	BaseConstructL(R_VIEW_APP);

	//add your code here...

	}
/**
 * 
 * */
TUid CSimulateMessageAppView::Id() const
	{
	return TUid::Uid(ESimulateMessageAppViewId);
	}
void CSimulateMessageAppView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CSimulateMessageAppView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CSimulateMessageAppView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
		iContainer = CSimulateMessageAppContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void CSimulateMessageAppView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
