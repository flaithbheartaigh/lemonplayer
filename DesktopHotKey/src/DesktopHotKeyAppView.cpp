/*
 ============================================================================
 Name		: DesktopHotKeyAppView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "DesktopHotKeyAppView.h"

#include <DesktopHotKey_0xE4ED7F71.rsg>
#include "DesktopHotKey.hrh"

// ============================ MEMBER FUNCTIONS ===============================
CDesktopHotKeyAppView::CDesktopHotKeyAppView()
	{
	// No implementation required
	iContainer = NULL;
	}

CDesktopHotKeyAppView::~CDesktopHotKeyAppView()
	{
	DoDeactivate();
	}

CDesktopHotKeyAppView* CDesktopHotKeyAppView::NewLC()
	{
	CDesktopHotKeyAppView* self = new (ELeave) CDesktopHotKeyAppView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CDesktopHotKeyAppView* CDesktopHotKeyAppView::NewL()
	{
	CDesktopHotKeyAppView* self = CDesktopHotKeyAppView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CDesktopHotKeyAppView::ConstructL()
	{
	BaseConstructL(R_VIEW_APP);

	//add your code here...

	}
/**
 * 
 * */
TUid CDesktopHotKeyAppView::Id() const
	{
	return TUid::Uid(EDesktopHotKeyAppViewId);
	}
void CDesktopHotKeyAppView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CDesktopHotKeyAppView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CDesktopHotKeyAppView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
		iContainer = CDesktopHotKeyAppContainer::NewL(ClientRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void CDesktopHotKeyAppView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
