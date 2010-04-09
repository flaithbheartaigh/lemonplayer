/*
 ============================================================================
 Name		: ThemeChangeAppUi.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CThemeChangeAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>
#include <apgcli.h>

#include <ThemeChange_0xE8EE38C1.rsg>

#include "ThemeChange.hrh"
#include "ThemeChange.pan"
#include "ThemeChangeApplication.h"
#include "ThemeChangeAppUi.h"

#include "ThemeChangeAppView.h"
#include "HelpView.h"
#include "NormalSettingView.h"

#include "MacroUtil.h"
#include "QueryDlgUtil.h"
#include "Utils.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CThemeChangeAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CThemeChangeAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);

	iDataModel = COKCModel::NewL();
	iUIMgr = CUIManager::NewL();
	// Create view object
	CThemeChangeAppView* appView= CThemeChangeAppView::NewL();
	AddViewL(appView);
	CHelpView* helpView = CHelpView::NewL();
	AddViewL(helpView);
	CNormalSettingView* settingView = CNormalSettingView::NewL();
	AddViewL(settingView);
	
	SetDefaultViewL(*appView);

	//add your code here...

	}
// -----------------------------------------------------------------------------
// CThemeChangeAppUi::CThemeChangeAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CThemeChangeAppUi::CThemeChangeAppUi()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CThemeChangeAppUi::~CThemeChangeAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CThemeChangeAppUi::~CThemeChangeAppUi()
	{
	//add your code here...
	SAFE_DELETE(iDataModel);
	SAFE_DELETE(iUIMgr);
	}

// -----------------------------------------------------------------------------
// CThemeChangeAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CThemeChangeAppUi::HandleCommandL(TInt aCommand)
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
		case EAbout:
			About();
			break;

		case ECommandHelp:
			ActivateLocalViewL(TUid::Uid(EThemeChangeHelpView));
			break;
		case ECommandSetting:
			ActivateLocalViewL(TUid::Uid(EThemeChangeSettingView));
			break;
		default:
			Panic(EThemeChangeUi);
			break;
		}
	}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CThemeChangeAppUi::HandleStatusPaneSizeChange()
	{
	}

COKCModel* CThemeChangeAppUi::GetModel()
	{
	return iDataModel;
	}

CUIManager* CThemeChangeAppUi::GetUI()
	{
	return iUIMgr;
	}

void CThemeChangeAppUi::About()
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
