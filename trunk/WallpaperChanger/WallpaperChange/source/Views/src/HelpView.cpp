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
#include "ThemeChange.hrh"
#include "ThemeChangeAppUi.h"
#include <ThemeChange_0xEAC842A2.rsg>

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
	BaseConstructL(R_VIEW_OK_BACK);
	}

TUid CHelpView::Id() const
	{
	return TUid::Uid(EThemeChangeHelpView);
	}

void CHelpView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EAknSoftkeyOk:
		case EAknSoftkeyBack:
			OKCChangeView(EThemeChangeAppViewId);
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
