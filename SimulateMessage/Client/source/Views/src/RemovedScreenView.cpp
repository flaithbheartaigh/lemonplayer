/*
 ============================================================================
 Name		: RemovedScreenView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CRemovedScreenView implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "RemovedScreenView.h"

#include "SHPlatform.h"

// ============================ MEMBER FUNCTIONS ===============================
CRemovedScreenView::CRemovedScreenView()
	{
	// No implementation required
	iContainer = NULL;
	}

CRemovedScreenView::~CRemovedScreenView()
	{
	DoDeactivate();

	//add your code here ...

	}

CRemovedScreenView* CRemovedScreenView::NewLC()
	{
	CRemovedScreenView* self = new (ELeave) CRemovedScreenView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CRemovedScreenView* CRemovedScreenView::NewL()
	{
	CRemovedScreenView* self = CRemovedScreenView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CRemovedScreenView::ConstructL()
	{
	BaseConstructL(R_VIEW_REMOVEDSCREEN);

	//add your code here...
	}
/**
 * 
 * */
TUid CRemovedScreenView::Id() const
	{
	return TUid::Uid(ESimulateMessageRemovedScreenViewId);
	}
void CRemovedScreenView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EAknSoftkeyBack:
			SHChangeView(ESimulateMessageMainScreenViewId);
			break;
		case ECommandRemovedClear:
			iContainer->ClearRemoved();
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CRemovedScreenView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CRemovedScreenView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
		iContainer = CRemovedScreenContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void CRemovedScreenView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
