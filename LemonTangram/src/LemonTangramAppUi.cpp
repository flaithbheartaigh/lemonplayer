/*
 ============================================================================
 Name		: LemonTangramAppUi.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CLemonTangramAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>
#include <hlplch.h>

#include <LemonTangram.rsg>
#include "LemonTangram.hlp.hrh"

#include "LemonTangram.hrh"
#include "LemonTangram.pan"
#include "LemonTangramApplication.h"
#include "LemonTangramAppUi.h"
#include "LemonTangramAppView.h"
#include "MacroUtil.h"
#include "YCSettingView.h"
#include "QueryDlgUtil.h"

const TUid KUidHelpFile = { HELPFILE_UID };


// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CLemonTangramAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLemonTangramAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);
	
	TRect rect = ClientRect() ;
	ChangeUIMgr(rect.Width(),rect.Height());
	
	// Create view object
	iAppView = CLemonTangramAppView::NewL(rect);
	AddViewL(iAppView);
	iSettingView = CYCSettingView::NewL();
	AddViewL(iSettingView);
		
	ActivateLocalViewL(iAppView->Id());

	}
// -----------------------------------------------------------------------------
// CLemonTangramAppUi::CLemonTangramAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLemonTangramAppUi::CLemonTangramAppUi()
:iUIMgr(NULL)
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLemonTangramAppUi::~CLemonTangramAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CLemonTangramAppUi::~CLemonTangramAppUi()
	{
	SAFE_DELETE(iUIMgr);
	}

// -----------------------------------------------------------------------------
// CLemonTangramAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CLemonTangramAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
		case ECommandExit:
			if (ShowConfirmationQueryL(R_TEXT_DLG_EXIT_CONFIRM))
				Exit();
			break;
		case EHelp:
		case ECommandHelp:
			{
			CArrayFix<TCoeHelpContext>* buf = CCoeAppUi::AppHelpContextL();
			HlpLauncher::LaunchHelpApplicationL(iEikonEnv->WsSession(), buf);
			}
			break;
		case EAbout:
			{
			CAknMessageQueryDialog* dlg = new (ELeave)CAknMessageQueryDialog();
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
		case EListboxCmdBack:
			STATIC_CAST(CLemonTangramAppUi*,iEikonEnv->AppUi())->ActivateLocalViewL(TUid::Uid(ELemonViewMain));
			break;
		default:
			//Panic(ELemonTangramUi);
			break;
		}
	}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CLemonTangramAppUi::HandleStatusPaneSizeChange()
	{
//	iAppView->SetRect(ClientRect() );
	}

CArrayFix<TCoeHelpContext>* CLemonTangramAppUi::HelpContextL() const
	{
	// Note: Help will not work if the application uid3 is not in the
	// protected range.  The default uid3 range for projects created
	// from this template (0xE0000000 - 0xEFFFFFFF) are not in the protected range so that they
	// can be self signed and installed on the device during testing.
	// Once you get your official uid3 from Symbian Ltd. and find/replace
	// all occurrences of uid3 in your project, the context help will
	// work.
	CArrayFixFlat<TCoeHelpContext>* array = new(ELeave)CArrayFixFlat<TCoeHelpContext>(1);
	CleanupStack::PushL(array);
	array->AppendL( TCoeHelpContext( KUidHelpFile, KGeneral_Information ) );
	//array->AppendL( TCoeHelpContext( KUidHelpFile, KContextApplication ) );
	CleanupStack::Pop(array);
	return array;
	}

void CLemonTangramAppUi::ChangeUIMgr(TInt aWidth,TInt aHeight)
	{
	SAFE_DELETE(iUIMgr);
	
	TPixelsAndRotation nPR;
	CEikonEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(nPR);
		
	if ( aWidth==240 && aHeight==320 )
		iUIMgr = UIFactory::CreateUIMgr(EUIType240x320);
	else if ( aWidth==320 && aHeight==240 )
		{
		if (nPR.iRotation == CFbsBitGc::EGraphicsOrientationNormal)	
			iUIMgr = UIFactory::CreateUIMgr(EUIType320x240orig);
		else
			iUIMgr = UIFactory::CreateUIMgr(EUIType320x240);
		}
	else if ( aWidth==352 && aHeight==416 )
		iUIMgr = UIFactory::CreateUIMgr(EUIType352x416);
	else if ( aWidth==416 && aHeight==352 )
		iUIMgr = UIFactory::CreateUIMgr(EUIType416x352);
	else if ( aWidth==208 && aHeight==208 )
		iUIMgr = UIFactory::CreateUIMgr(EUIType208x208);
	else	
		iUIMgr = UIFactory::CreateUIMgr(EUIType176x208);
	}

MUIMgr* CLemonTangramAppUi::GetUIMgr()
	{
	if (iUIMgr == NULL)
		ChangeUIMgr(176,208);
	return iUIMgr;
	}
// End of File
