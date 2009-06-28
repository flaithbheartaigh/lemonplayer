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
#include "bautils.h"
#include "TangFileDefine.h"

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
	DEBUG(iFileLogger = CFileLogger::NewL(_L("c:\\CLemonTangramAppUi.txt")))
	DEBUGLOG(iFileLogger,_L8("constuct start"))
	BaseConstructL(CAknAppUi::EAknEnableSkin);
	
	GlobleInit();
	
	TRect rect = ApplicationRect() ;
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
	DEBUG(SAFE_DELETE(iFileLogger))
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
		case ECommandSetting:
			ActivateLocalViewL(TUid::Uid(ESettingView));
			break;
		case EListboxCmdBack:
			ActivateLocalViewL(TUid::Uid(ELemonViewMain));
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
	else if ( aWidth==176 && aHeight==208)
		iUIMgr = UIFactory::CreateUIMgr(EUIType176x208);
	else	
		iUIMgr = UIFactory::CreateUIMgr(EUIType240x320);
	}

MUIMgr* CLemonTangramAppUi::GetUIMgr()
	{
	if (iUIMgr == NULL)
		ChangeUIMgr(240,320);
	return iUIMgr;
	}

void CLemonTangramAppUi::LTError(const TTLErrInfo& aInfo,const TTLErrState& aState)
{
	switch(aInfo) {
	case ETLErrLoadPicture:
		ShowModalInfoDlgL(R_TEXT_DLG_ERROR,R_TEXT_DLG_ERR_LOAD_PIC);
		break;
	case ETLErrLoadPicFileXml:
		ShowModalInfoDlgL(R_TEXT_DLG_ERROR,R_TEXT_DLG_ERR_LOAD_PIC_FILE_XML);
		break;
	case ETLErrLoadPicDataXml:
		ShowModalInfoDlgL(R_TEXT_DLG_ERROR,R_TEXT_DLG_ERR_LOAD_PIC_DATA_XML);
		break;
	case ETLErrLoadMenu:
		ShowModalInfoDlgL(R_TEXT_DLG_ERROR,R_TEXT_DLG_ERR_LOAD_MENU);
		break;
	case ETLWarnConfigLost:
		ShowInfomationDlgL(R_TEXT_DLG_WARN_CONFIG_LOST);
		break;
	case ETLWarnLoadPicFileNextDefault:
		ShowInfomationDlgL(R_TEXT_DLG_WARN_LOAD_PIC_FILE_NEXT_DEFAULT);
		break;
	case ETLWarnSettingInit:
		ShowInfomationDlgL(R_TEXT_DLG_WARN_SETTING_INIT);
		break;
	case ETLWarnSettingList:
		ShowInfomationDlgL(R_TEXT_DLG_WARN_SETTING_LIST);
		break;
	case ETLWarnSaveProcess:
		ShowInfomationDlgL(R_TEXT_DLG_WARN_FUNC_SAVE_PROCESS);
		break;
	case ETLWarnResetProcess:
		ShowInfomationDlgL(R_TEXT_DLG_WARN_FUNC_RESET_PROCESS);
		break;
	case ETLWarnOpenProcess:
		ShowInfomationDlgL(R_TEXT_DLG_WARN_FUNC_OPEN_PROCESS);
		break;
	case ETLWarnSaveScreen:
		ShowInfomationDlgL(R_TEXT_DLG_WARN_FUNC_SAVE_SCREEN);
		break;
	default:
		break;
	}

	switch(aState) {
	case ETLErrSerious:
		Exit();
		break;
	default:
		break;
	}
}

void CLemonTangramAppUi::GlobleInit()
	{
	BaflUtils::EnsurePathExistsL(CCoeEnv::Static()->FsSession(),KCfgDefaultSkinFolder);
	BaflUtils::EnsurePathExistsL(CCoeEnv::Static()->FsSession(),KCfgDefaultSaveFolder);
	}
// End of File
