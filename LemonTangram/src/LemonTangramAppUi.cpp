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

#include <LemonTangram_0xEAE107BA.rsg>
#include "LemonTangram.hlp.hrh"

#include "LemonTangram.hrh"
#include "LemonTangram.pan"
#include "LemonTangramApplication.h"
#include "LemonTangramAppUi.h"
#include "LemonTangramAppView.h"
#include "MacroUtil.h"
#include "YCSettingView.h"

const TUid KUidHelpFile = { HELPFILE_UID };

_LIT(KFileName, "C:\\private\\EAE107BA\\LemonTangram.txt");
_LIT(KText, "Hello World!");


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
//	if (iAppView)
//		{
//		delete iAppView;
//		iAppView = NULL;
//		}

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
			Exit();
			break;

		case ECommand1:
			{

			// Load a string from the resource file and display it
			HBufC* textResource = StringLoader::LoadLC(R_COMMAND1_TEXT);
			CAknInformationNote* informationNote;

			informationNote = new ( ELeave ) CAknInformationNote;

			// Show the information Note with
			// textResource loaded with StringLoader.
			informationNote->ExecuteLD( *textResource);

			// Pop HBuf from CleanUpStack and Destroy it.
			CleanupStack::PopAndDestroy(textResource);
			}
			break;
		case ECommand2:
			{
			RFile rFile;

			//Open file where the stream text is
			User::LeaveIfError(rFile.Open(CCoeEnv::Static()->FsSession(), KFileName, EFileStreamText));//EFileShareReadersOnly));// EFileStreamText));
			CleanupClosePushL(rFile);

			// copy stream from file to RFileStream object
			RFileReadStream inputFileStream(rFile);
			CleanupClosePushL(inputFileStream);

			// HBufC descriptor is created from the RFileStream object.
			HBufC* fileData = HBufC::NewLC(inputFileStream, 32);

			CAknInformationNote* informationNote;

			informationNote = new ( ELeave ) CAknInformationNote;
			// Show the information Note
			informationNote->ExecuteLD( *fileData);

			// Pop loaded resources from the cleanup stack
			CleanupStack::PopAndDestroy(3); // filedata, inputFileStream, rFile
			}
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
		default:
			Panic(ELemonTangramUi);
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
