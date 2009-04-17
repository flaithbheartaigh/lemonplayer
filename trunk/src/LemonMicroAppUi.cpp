/*
 ============================================================================
 Name		: LemonMicroAppUi.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : CLemonMicroAppUi implementation
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

#include <LemonMicro_0xEFE1B7CE.rsg>


#include "LemonMicro.hrh"
#include "LemonMicro.pan"
#include "LemonMicroApplication.h"
#include "LemonMicroAppUi.h"
#include "LemonMicroAppView.h"

#include "FileRecordAdapter.h"
#include "MacroUtil.h"

_LIT(KFileName, "C:\\private\\EFE1B7CE\\LemonMicro.txt");
_LIT(KText, "Hello World!");

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CLemonMicroAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLemonMicroAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);

	// Create view object
	iAppView = CLemonMicroAppView::NewL(ClientRect() );

	// Create a file to write the text to
	TInt err = CCoeEnv::Static()->FsSession().MkDirAll(KFileName);
	if ( (KErrNone != err) && (KErrAlreadyExists != err))
		{
		return;
		}

	RFile file;
	err = file.Replace(CCoeEnv::Static()->FsSession(), KFileName, EFileWrite);
	CleanupClosePushL(file);
	if (KErrNone != err)
		{
		CleanupStack::PopAndDestroy(1); // file
		return;
		}

	RFileWriteStream outputFileStream(file);
	CleanupClosePushL(outputFileStream);
	outputFileStream << KText;

	CleanupStack::PopAndDestroy(2); // outputFileStream, file
	
	iFileRecorder = CFileRecordAdapter::NewL();
	iFileRecorder->SetFileName(_L("c:\\myrecord.wav"));

	}
// -----------------------------------------------------------------------------
// CLemonMicroAppUi::CLemonMicroAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLemonMicroAppUi::CLemonMicroAppUi()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLemonMicroAppUi::~CLemonMicroAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CLemonMicroAppUi::~CLemonMicroAppUi()
	{
	
	SAFE_DELETE(iFileRecorder);
	
	if (iAppView)
		{
		delete iAppView;
		iAppView = NULL;
		}

	}

// -----------------------------------------------------------------------------
// CLemonMicroAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CLemonMicroAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			Exit();
			break;

		case ECommand1:
			{
			iFileRecorder->StartRecordL();
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
			Panic(ELemonMicroUi);
			break;
		}
	}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CLemonMicroAppUi::HandleStatusPaneSizeChange()
	{
	iAppView->SetRect(ClientRect() );
	}

CArrayFix<TCoeHelpContext>* CLemonMicroAppUi::HelpContextL() const
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
	CleanupStack::Pop(array);
	return array;
	}

// End of File
