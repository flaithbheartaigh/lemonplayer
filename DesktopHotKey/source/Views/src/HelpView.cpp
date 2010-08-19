/*
 ============================================================================
 Name		: HelpView.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CHelpView implementation
 ============================================================================
 */
#include <aknviewappui.h>
#include "HelpView.h"

#include "SHPlatform.h"

CHelpView::CHelpView()
	{
	// No implementation required
	iContainer = NULL;
	}

CHelpView::~CHelpView()
	{
	DoDeactivate();
	}

CHelpView* CHelpView::NewLC()
	{
	CHelpView* self = new (ELeave) CHelpView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CHelpView* CHelpView::NewL()
	{
	CHelpView* self = CHelpView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CHelpView::ConstructL()
	{
	BaseConstructL(R_VIEW_NULL_BACK);
	}

TUid CHelpView::Id() const
	{
	return TUid::Uid(ESHHelpViewId);
	}

void CHelpView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EAknSoftkeyOk:
			break;
		case EAknSoftkeyBack:
			SHChangeView(EScheduleKillerMainScreenViewId);
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}

void CHelpView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CHelpView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (iContainer == NULL)
		{
		iContainer = CHelpContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void CHelpView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
