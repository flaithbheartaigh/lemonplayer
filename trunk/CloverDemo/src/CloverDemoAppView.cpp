/*
 ============================================================================
 Name		: CloverDemoAppView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "CloverDemoAppView.h"

#include <CloverDemo_0xECDEBC61.rsg>
#include "CloverDemo.hrh"

// ============================ MEMBER FUNCTIONS ===============================
CCloverDemoAppView::CCloverDemoAppView()
	{
	// No implementation required
	iContainer = NULL;
	}

CCloverDemoAppView::~CCloverDemoAppView()
	{
	DoDeactivate();
	}

CCloverDemoAppView* CCloverDemoAppView::NewLC()
	{
	CCloverDemoAppView* self = new (ELeave) CCloverDemoAppView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CCloverDemoAppView* CCloverDemoAppView::NewL()
	{
	CCloverDemoAppView* self = CCloverDemoAppView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CCloverDemoAppView::ConstructL()
	{
	BaseConstructL(R_VIEW_APP);

	//add your code here...

	}
/**
 * 
 * */
TUid CCloverDemoAppView::Id() const
	{
	return TUid::Uid(ECloverDemoAppViewId);
	}
void CCloverDemoAppView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CCloverDemoAppView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
//		iContainer->SetRect(ClientRect());
		iContainer->SetRect(AppUi()->ApplicationRect());
	}

/**
 * 
 * */
void CCloverDemoAppView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
//		iContainer = CCloverDemoAppContainer::NewL(ClientRect());
		iContainer = CCloverDemoAppContainer::NewL(AppUi()->ApplicationRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void CCloverDemoAppView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
