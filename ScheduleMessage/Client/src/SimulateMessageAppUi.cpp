/*
 ============================================================================
 Name		: SimulateMessageAppUi.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CSimulateMessageAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>

#include "SHPlatform.h"
#include "SimulateMessage.pan"
#include "SimulateMessageApplication.h"
#include "SimulateMessageAppUi.h"

#include "SimulateMessageAppView.h"
#include "LogoView.h"
#include "HelpView.h"
#include "LoadDraftView.h"
#include "MainScreenView.h"
#include "SettingView.h"
#include "EditorAppView.h"
#include "RemovedScreenView.h"

#include "MacroUtil.h"
#include "Utils.h"
#include "QueryDlgUtil.h"



// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CSimulateMessageAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSimulateMessageAppUi::ConstructL()
	{
	User::LeaveIfError( iSession.Connect() );
	TFileName fn = this->Application()->AppFullName();
	TPtrC driver = fn.Left(2);
	iSession.SendDriver(driver);
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);
//	BaseConstructL();

	iDataModel = CSHModel::NewL();
	iUIMgr = CUIManager::NewL();
	
	// Create view object
//	iAppView = CSimulateMessageAppView::NewL();
//	AddViewL(iAppView);
	iLogoView = CLogoView::NewL();
	AddViewL(iLogoView);
	iHelpView = CHelpView::NewL();
	AddViewL(iHelpView);
	iDraftView = CLoadDraftView::NewL();
	AddViewL(iDraftView);
	iMainView = CMainScreenView::NewL();
	AddViewL(iMainView);
	iSettingView = CSettingView::NewL();
	AddViewL(iSettingView);
	iRemovedView = CRemovedScreenView::NewL();
	AddViewL(iRemovedView);
	iEditView = CEditorAppView::NewL();
	AddViewL(iEditView);
	
	SetDefaultViewL(*iLogoView);

	//add your code here...

	}
// -----------------------------------------------------------------------------
// CSimulateMessageAppUi::CSimulateMessageAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSimulateMessageAppUi::CSimulateMessageAppUi()
	{
	// No implementation required
	iAppView = NULL;
	}

// -----------------------------------------------------------------------------
// CSimulateMessageAppUi::~CSimulateMessageAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CSimulateMessageAppUi::~CSimulateMessageAppUi()
	{
	//add your code here...
	SAFE_DELETE(iDataModel)
	SAFE_DELETE(iUIMgr)
	
	iSession.Close();
	}

// -----------------------------------------------------------------------------
// CSimulateMessageAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CSimulateMessageAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			Exit();
			break;
		case ECommandExit:
			if (ShowConfirmationQueryL(R_TEXT_DLG_EXIT_CONFIRM))
				Exit();
			break;
		case ECommandSetting:
			SHChangeView(ESimulateMessageSettingViewId);
			break;
		case ECommandHelp:
			SHChangeView(ESimulateMessageHelpViewId);
			break;
		case ECommandAbout:
			About();
			break;
		default:
			Panic(ESimulateMessageUi);
			break;
		}
	}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
//void CSimulateMessageAppUi::HandleStatusPaneSizeChange()
//	{
//	}

void CSimulateMessageAppUi::About()
	{
	TFileName filename;
	GetAppPath(filename);
	HBufC* textResource = StringLoader::LoadLC(R_ABOUT_FILE);
	filename.Append(textResource->Des());
	CleanupStack::PopAndDestroy(textResource);

	RFile file;
	TInt nErr = file.Open(CEikonEnv::Static()->FsSession(), filename, EFileRead
			| EFileShareAny);
	if (nErr != KErrNone)
		return;

	TFileText fileText;
	fileText.Set(file);
	TBuf<128> linePtr;
	HBufC* iText = NULL;

	while (fileText.Read(linePtr) == KErrNone)
		{
		if (iText!=NULL)
			{
			iText = iText->ReAllocL(iText->Length() + linePtr.Length() + 2);
			iText->Des().Append(linePtr);
			}
		else
			{
			iText = HBufC::NewL(linePtr.Length() + 2);
			iText->Des().Append(linePtr);
			}
		iText->Des().Append(CEditableText::ELineBreak);
		}
	file.Close();

	ShowModalAboutDlgL(R_ABOUT_DIALOG_TITLE,iText->Des());
	
	delete iText;
	}
// End of File
