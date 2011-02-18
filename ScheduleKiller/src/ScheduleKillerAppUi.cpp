/*
 ============================================================================
 Name		: ScheduleKillerAppUi.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CScheduleKillerAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>

#include <CloverTask.rsg>

#include "ScheduleKiller.hrh"
#include "ScheduleKiller.pan"
#include "ScheduleKillerApplication.h"
#include "ScheduleKillerAppUi.h"

#include "Utils.h"
#include "MacroUtil.h"
#include "QueryDlgUtil.h"
#include "SeniorUtils.h"

#include "AppScreenView.h"
#include "MainScreenView.h"
#include "RuleScreenView.h"
#include "SettingScreenView.h"
#include "HelpView.h"
#include "LogoView.h"
// ============================ MEMBER FUNCTIONS ===============================

_LIT(KFeedbackLink,"http://tieba.baidu.com/f?kw=iCloverSoft");

TInt OpenLink(TAny* /*aAny*/)
	{
	CSeniorUtils::StartBroswerApp(KFeedbackLink);
	return EFalse;
	}

// -----------------------------------------------------------------------------
// CScheduleKillerAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CScheduleKillerAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);

	iDataModel = CSHModel::NewL();
	iUIMgr = CUIManager::NewL();
	iKeyManager = COfferKeyManager::NewL();
	
	// Create view object
	iAppView = CAppScreenView::NewL();
	AddViewL(iAppView);
	iMainView = CMainScreenView::NewL();
	AddViewL(iMainView);
	iRuleView = CRuleScreenView::NewL();
	AddViewL(iRuleView);
	iSettingView = CSettingScreenView::NewL();
	AddViewL(iSettingView);
	iHelpView = CHelpView::NewL();
	AddViewL(iHelpView);
	iLogoView = CLogoView::NewL();
	AddViewL(iLogoView);
	
//	SetDefaultViewL(*iLogoView);
	SetDefaultViewL(*iMainView);

	//add your code here...

	}
// -----------------------------------------------------------------------------
// CScheduleKillerAppUi::CScheduleKillerAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CScheduleKillerAppUi::CScheduleKillerAppUi()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CScheduleKillerAppUi::~CScheduleKillerAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CScheduleKillerAppUi::~CScheduleKillerAppUi()
	{
	//add your code here...
	SAFE_DELETE(iKeyManager)
	SAFE_DELETE(iDataModel)
	SAFE_DELETE(iUIMgr)
	}

// -----------------------------------------------------------------------------
// CScheduleKillerAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CScheduleKillerAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			ExitApp();
			break;
		case ECommandAbout:
			About();
			break;
		default:
			Panic(EScheduleKillerUi);
			break;
		}
	}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CScheduleKillerAppUi::HandleStatusPaneSizeChange()
	{
	}

TKeyResponse CScheduleKillerAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	if (iKeyManager)
		return iKeyManager->OfferKeyEventL(aKeyEvent,aType);
	return EKeyWasNotConsumed;
	}

void CScheduleKillerAppUi::SHError(const TSHErrInfo& aInfo,const TSHErrState& aState)
{
	switch(aInfo) {
	case ELAWarnChooseAppNull:
		ShowInfomationDlgL(R_TEXT_WARN_CHOOSE_APP_NULL);
		break;
	case ELAWarnTimeLowerThanNow:
		ShowInfomationDlgL(R_TEXT_WARN_TIME_LOWNER_THAN_NOW);
		break;
	default:
		break;
	}

	switch(aState) {
	case ESHErrSerious:
		Exit();
		break;
	default:
		break;
	}
}

void CScheduleKillerAppUi::About()
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

	TCallBack callback(OpenLink);
	ShowModalAboutLinkDlgL(R_ABOUT_DIALOG_TITLE,iText->Des(),KFeedbackLink,callback);
	
	delete iText;
	}

void CScheduleKillerAppUi::ExitApp()
	{
	if (GetModel()->IsEmputy())
		Exit();
	else if (ShowConfirmationQueryL(R_TEXT_CONFIRM_EXIT_TASK_RUNNING))
		Exit();
	}

// End of File
