/*
 ============================================================================
 Name		: CloverDemoAppUi.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CCloverDemoAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>

#include <CloverDemo_0xECDEBC61.rsg>

#include "CloverDemo.hrh"
#include "CloverDemo.pan"
#include "CloverDemoApplication.h"
#include "CloverDemoAppUi.h"
#include "CloverDemoAppView.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CCloverDemoAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CCloverDemoAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);

	// Create view object
	iAppView = CCloverDemoAppView::NewL();
	AddViewL(iAppView);
	SetDefaultViewL(*iAppView);

	//add your code here...

	}
// -----------------------------------------------------------------------------
// CCloverDemoAppUi::CCloverDemoAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CCloverDemoAppUi::CCloverDemoAppUi()
	{
	// No implementation required
	iAppView = NULL;
	}

// -----------------------------------------------------------------------------
// CCloverDemoAppUi::~CCloverDemoAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CCloverDemoAppUi::~CCloverDemoAppUi()
	{
	//add your code here...

	}

// -----------------------------------------------------------------------------
// CCloverDemoAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CCloverDemoAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			Exit();
			break;
		case EAbout:
			{

			CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
			dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
			HBufC* title = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TITLE);
			dlg->QueryHeading()->SetTextL(*title);
			CleanupStack::PopAndDestroy(); //title
			HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
			dlg->SetMessageTextL(*msg);
			CleanupStack::PopAndDestroy(); //msg
			dlg->RunLD();
			}
			break;
		default:
			Panic(ECloverDemoUi);
			break;
		}
	}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CCloverDemoAppUi::HandleStatusPaneSizeChange()
	{
	if (iAppView != NULL)
		iAppView->HandleStatusPaneSizeChange();
	}

// End of File
