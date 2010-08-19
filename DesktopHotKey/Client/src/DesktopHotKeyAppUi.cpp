/*
 ============================================================================
 Name		: DesktopHotKeyAppUi.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CDesktopHotKeyAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>

#include <DesktopHotKey_0xE4ED7F71.rsg>

#include "DesktopHotKey.hrh"
#include "DesktopHotKey.pan"
#include "DesktopHotKeyApplication.h"
#include "DesktopHotKeyAppUi.h"
#include "DesktopHotKeyAppView.h"

#include "Utils.h"
#include "MacroUtil.h"
#include "QueryDlgUtil.h"

#include "HelpView.h"
#include "LogoView.h"
// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CDesktopHotKeyAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);

	// Create view object
	iAppView = CDesktopHotKeyAppView::NewL();
	AddViewL(iAppView);
	
	iHelpView = CHelpView::NewL();
	AddViewL(iHelpView);
	iLogoView = CLogoView::NewL();
	AddViewL(iLogoView);
	
	SetDefaultViewL(*iAppView);

	//add your code here...

	}
// -----------------------------------------------------------------------------
// CDesktopHotKeyAppUi::CDesktopHotKeyAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyAppUi::CDesktopHotKeyAppUi()
	{
	// No implementation required
	iAppView = NULL;
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyAppUi::~CDesktopHotKeyAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CDesktopHotKeyAppUi::~CDesktopHotKeyAppUi()
	{
	//add your code here...
	SAFE_DELETE(iDataModel)
	SAFE_DELETE(iUIMgr)
	}

// -----------------------------------------------------------------------------
// CDesktopHotKeyAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			Exit();
			break;
		case ECommandAbout:
			About();
			break;
		default:
			Panic(EDesktopHotKeyUi);
			break;
		}
	}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CDesktopHotKeyAppUi::HandleStatusPaneSizeChange()
	{
	if (iAppView != NULL)
		iAppView->HandleStatusPaneSizeChange();
	}

void CDesktopHotKeyAppUi::SHError(const TSHErrInfo& aInfo,const TSHErrState& aState)
{
	switch(aInfo) {
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

void CDesktopHotKeyAppUi::About()
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
