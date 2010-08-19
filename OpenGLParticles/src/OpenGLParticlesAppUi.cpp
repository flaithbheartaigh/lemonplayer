/*
 ============================================================================
 Name		: OpenGLParticlesAppUi.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : COpenGLParticlesAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>

#include <OpenGLParticles_0xEC9DD319.rsg>

#include "OpenGLParticles.hrh"
#include "OpenGLParticles.pan"
#include "OpenGLParticlesApplication.h"
#include "OpenGLParticlesAppUi.h"
#include "OpenGLParticlesAppView.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// COpenGLParticlesAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void COpenGLParticlesAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);

	// Create view object
	iAppView = COpenGLParticlesAppView::NewL();
	AddViewL(iAppView);
	SetDefaultViewL(*iAppView);

	//add your code here...

	}
// -----------------------------------------------------------------------------
// COpenGLParticlesAppUi::COpenGLParticlesAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
COpenGLParticlesAppUi::COpenGLParticlesAppUi()
	{
	// No implementation required
	iAppView = NULL;
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesAppUi::~COpenGLParticlesAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
COpenGLParticlesAppUi::~COpenGLParticlesAppUi()
	{
	//add your code here...

	}

// -----------------------------------------------------------------------------
// COpenGLParticlesAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void COpenGLParticlesAppUi::HandleCommandL(TInt aCommand)
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
			Panic(EOpenGLParticlesUi);
			break;
		}
	}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void COpenGLParticlesAppUi::HandleStatusPaneSizeChange()
	{
	if (iAppView != NULL)
		iAppView->HandleStatusPaneSizeChange();
	}

// End of File
