/*
 ============================================================================
 Name		: ThemeChangeAppContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "ThemeChangeAppContainer.h"
#include <apgtask.h>
#include <eikenv.h>
#include <apgcli.h>
#include <aknlists.h> 
#include "ThemeManager.h"
#include "ThemeCommonDef.h"
#include <AknIconArray.h> 
#include <ThemeChange_0xEAC842A2.rsg>
#include <eikclbd.h>
#include <swinstapi.h> // RSWInstLauncher
#include <swi\sisregistrysession.h> // RSisRegistrySession
#include <swi\sisregistrypackage.h> // CSisRegistryPackage

#include "OKCDebug.h"
#include "QueryDlgUtil.h"
#include "PaymentManager.h"
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CThemeChangeAppContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CThemeChangeAppContainer* CThemeChangeAppContainer::NewL(const TRect& aRect)
	{
	CThemeChangeAppContainer* self = CThemeChangeAppContainer::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CThemeChangeAppContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CThemeChangeAppContainer* CThemeChangeAppContainer::NewLC(const TRect& aRect)
	{
	CThemeChangeAppContainer* self = new (ELeave) CThemeChangeAppContainer;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CThemeChangeAppContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CThemeChangeAppContainer::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	iThemeManager = CThemeManager::NewL();

	iListBox = new (ELeave) CAknSingleGraphicStyleListBox();
	iListBox->ConstructL(this);
	iListBox->SetContainerWindowL(*this);

	// Creates scrollbar.
	iListBox->CreateScrollBarFrameL(ETrue);
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
			CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);

	SetIconsL();
	UpdateDisplay();

	SetRect(aRect);
	ActivateL();

	//add your code here ...
	}

// -----------------------------------------------------------------------------
// CThemeChangeAppContainer::CThemeChangeAppContainer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CThemeChangeAppContainer::CThemeChangeAppContainer() :
	iListBox(NULL),iPayment(NULL),iPaymentWaitDlg(NULL)
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CThemeChangeAppContainer::~CThemeChangeAppContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
CThemeChangeAppContainer::~CThemeChangeAppContainer()
	{
	// No implementation required
	
	StopPaymentWaitDlg();
	
	if (iListBox)
		delete iListBox;

	if (iThemeManager)
		delete iThemeManager;
	
	if (iPayment)
		delete iPayment;
	
	iThemeArray.Close();
	}

// ---------------------------------------------------------
// CThemeChangeContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CThemeChangeAppContainer::CountComponentControls() const
	{
	TInt count(0);
	if (iListBox)
		count++;

	return count; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CThemeChangeContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CThemeChangeAppContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		case 0:
			return iListBox; // Returns the pointer to listbox object.
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CThemeChangeContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CThemeChangeAppContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CThemeChangeAppContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CThemeChangeAppContainer::OfferKeyEventL(
		const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	// See if we have a selection
	TInt code = aKeyEvent.iCode;
	switch (code)
		{
		//add your code here...
		case EKeyDownArrow:
		case EKeyUpArrow:
			return iListBox->OfferKeyEventL(aKeyEvent, aType);
		case EKeyDevice3:
			if (aType == EEventKey)
				{
				Selected();
				return EKeyWasConsumed;
				}
			break;
		case EKeyBackspace:
			if (aType == EEventKey)
				{
				UninstallL();
				return EKeyWasConsumed;
				}
			break;
		default:
			break;
		}
	return EKeyWasNotConsumed;
	}
// -----------------------------------------------------------------------------
// CThemeChangeAppContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CThemeChangeAppContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	}

// -----------------------------------------------------------------------------
// CThemeChangeAppContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CThemeChangeAppContainer::SizeChanged()
	{
	if (iListBox)
		{
		iListBox->SetRect(Rect());
		}
	DrawNow();
	}

void CThemeChangeAppContainer::StartServer()
	{
	if (!IsServerActive())
		{
		RApaLsSession ras;
		User::LeaveIfError(ras.Connect());
		CleanupClosePushL(ras);
		TApaAppInfo appInfo;
		ras.GetAppInfo(appInfo, KUidServer);
		CApaCommandLine *cmd = CApaCommandLine::NewLC();
		//cmd->SetExecutableNameL(appInfo.iFullName);
		cmd->SetExecutableNameL(KServerFileName);
		cmd->SetCommandL(EApaCommandRun);
		ras.StartApp(*cmd);
		CleanupStack::PopAndDestroy(cmd);
		CleanupStack::Pop();
		ras.Close();
		}
	}

void CThemeChangeAppContainer::StopServer()
	{
	TFullName fullName;
	TInt err = KErrNone;
	TFindProcess findprocess;
	while (err = findprocess.Next(fullName), err == KErrNone)
		{
		if (err = fullName.FindF(KProcessToSearch), err != KErrNotFound)
			{
			RProcess process;
			TInt processopenerr = process.Open(findprocess);
			if (processopenerr == KErrNone)
				{
				process.Kill(KErrNone);
				process.Close();
				}
			break;
			}
		}
	}

TBool CThemeChangeAppContainer::IsServerActive()
	{
	TFullName fullName;
	TInt err = KErrNone;
	TFindProcess findprocess;
	TBool result = EFalse;
	while (err = findprocess.Next(fullName), err == KErrNone)
		{
		if (err = fullName.FindF(KProcessToSearch), err != KErrNotFound)
			{
			result = ETrue;
			break;
			}
		}
	return result;
	}

TBool CThemeChangeAppContainer::IsCurrentDeletable()
	{
//	RArray<TThemeInfo> array;
//	iThemeManager->DisplayAll(array);
	TBool deletable = EFalse;

	TInt index = iListBox->CurrentItemIndex();
	if (index >=0 && index <iThemeArray.Count())
		{
		const TThemeInfo& info = iThemeArray[index];
	
		deletable = info.iDeletable;
		}
//	array.Close();
	
	return deletable;
	}

void CThemeChangeAppContainer::RefreshServer()
	{
	StopServer();
	StartServer();
	}

void CThemeChangeAppContainer::UpdateDisplay()
	{
//	RArray<TThemeInfo> array;
	iThemeArray.Reset();
	
	iThemeManager->DisplayAll(iThemeArray);
	TAknsPkgID current;
	iThemeManager->GetCurrentTheme(current);
	TInt uid = current.iNumber;
	TInt index = -1;

	CTextListBoxModel* model = iListBox->Model();
	CDesCArray* items = static_cast<CDesCArray*> (model->ItemTextArray());

	items->Reset();
	_LIT(KItemFormat, "\t%S");
	TBuf<32> record;

	for (TInt i = 0; i < iThemeArray.Count(); i++)
		{
		const TThemeInfo& info = iThemeArray[i];
		record.Format(KItemFormat(), &(info.iName));
		TInt unum = info.iPID.iNumber;
		if (unum == uid)
			{
			record.Insert(0, _L("0"));
			index = i;
			}
		else
			{
			record.Insert(0, _L("1"));
			}
//		if (info.iLoacation == ESknLoactionMMC)
//			record.Append(_L("\t2"));
		items->AppendL(record);
		}

	iListBox->HandleItemAdditionL();
	
	if (index >= 0)
		iListBox->SetCurrentItemIndex(index);

//	array.Close();
	}

void CThemeChangeAppContainer::Selected()
	{
//	RArray<TThemeInfo> array;
//	iThemeManager->DisplayAll(array);

	TAknsPkgID current;
	iThemeManager->GetCurrentTheme(current);
	
	TInt index = iListBox->CurrentItemIndex();
	if (index >=0 && index <iThemeArray.Count())
		{
		const TThemeInfo& info = iThemeArray[index];
	
		if (info.iPID != current)
			{
			iThemeManager->SetTheme(info.iPID);
			StartWaitDlg();
			}
		}

//	array.Close();

	UpdateDisplay();
	}

void CThemeChangeAppContainer::UninstallL()
	{
	User::LeaveIfNull(iListBox);
	TInt index = iListBox->CurrentItemIndex();
	
	if (index >=0 && index <iThemeArray.Count())
		{
		const TThemeInfo& info = iThemeArray[index];	
		if (info.iDeletable == EFalse)
			return;
		}
	else
		return;
	
	TPtrC text = iListBox->Model()->ItemText(index);
	TPtrC name = text.Mid(2); //ÌÞ³ýÇ°Ãæ "1\t"

	TUid uid = KNullUid;
	Swi::RSisRegistrySession session;
	TInt err = session.Connect();
	User::LeaveIfError(err);
	CleanupClosePushL(session);
	RPointerArray<Swi::CSisRegistryPackage> sisPkgs;
	session.InstalledPackagesL(sisPkgs); // ReadUserData
	TInt count = sisPkgs.Count();
	for (TInt i = 0; i < count; i++)
		{
		Swi::CSisRegistryPackage& sisPkg = *(sisPkgs[i]);
		// is it the sis package for the theme?
		if (sisPkg.Name() == name)
			{
			uid = sisPkg.Uid();
			index = sisPkg.Index();
			break;
			}
		}
	sisPkgs.ResetAndDestroy();
	sisPkgs.Close();
	CleanupStack::PopAndDestroy(&session);

	if (uid == KNullUid)
		{
		User::Leave(KErrNotFound);
		}

	SwiUI::RSWInstLauncher installer;
	User::LeaveIfError(installer.Connect());
	CleanupClosePushL(installer);
	
	if (uid.iUid < 0)
		{	
		SwiUI::TOpUninstallIndexParam params;
		params.iUid = uid;
		params.iIndex = index;
		SwiUI::TOpUninstallIndexParamPckg pckg(params);
		SwiUI::TOperation operation(SwiUI::EOperationUninstallIndex);
		SwiUI::TUninstallOptions uninstallOptions;
		SwiUI::TUninstallOptionsPckg optPckg(uninstallOptions);
		err = installer.CustomUninstall(operation, pckg, SwiUI::KSisxMimeType());
	// silent uninstall can also be used.
	//		err = installer.SilentCustomUninstall( operation, optPckg, pckg,SwiUI::KSisxMimeType() );
		}
	else
		{
		err = installer.Uninstall(uid,SwiUI::KSisxMimeType());
		}
	if (err != SwiUI::KSWInstErrUserCancel)
		{
		User::LeaveIfError(err);
		}
	CleanupStack::PopAndDestroy(&installer);
	
	UpdateDisplay();
	}

void CThemeChangeAppContainer::SetIconsL()
	{
	CAknIconArray* icons = new (ELeave) CAknIconArray(2);
	CleanupStack::PushL(icons);
	icons->ConstructFromResourceL(R_ICON_MARK);
	iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons);
	CleanupStack::Pop(); // icons
	}

void CThemeChangeAppContainer::StartWaitDlg()
	{
	iChangeWaitDlg = StartWaitingDlg(R_TEXT_CHANGE_WAITING);
	}
void CThemeChangeAppContainer::StopWaitDlg()
	{
	EndWaitingDlg(iChangeWaitDlg);
	}

void CThemeChangeAppContainer::StartPaymentWaitDlg()
	{
	if (iPaymentWaitDlg)
		{
		delete iPaymentWaitDlg;
		iPaymentWaitDlg = NULL;
		}

	// For the wait dialog
	iPaymentWaitDlg = new (ELeave) CAknWaitDialog(REINTERPRET_CAST(CEikDialog**, &iPaymentWaitDlg));


	//    iWaitDialog->SetTextL(aLabel);
	iPaymentWaitDlg->ExecuteLD(R_PROCESS_WAIT_NOTE);//R_TEST_WAITNOTE);
	
	iPayment = CPaymentManager::NewL(*this);
	iPayment->Register();
	}
void CThemeChangeAppContainer::StopPaymentWaitDlg()
	{
	if (iPaymentWaitDlg)
		{
		iPaymentWaitDlg->ProcessFinishedL(); // deletes the dialog
		delete iPaymentWaitDlg;
		iPaymentWaitDlg = NULL;
		}
	}

void CThemeChangeAppContainer::PaymentErr(const TInt& aError)
	{
	StopPaymentWaitDlg();
	TBuf<32> info;
	info.Append(_L("Error:"));
	info.AppendNum(aError);
	ShowInfomationDlgL(info);
	}

void CThemeChangeAppContainer::PaymentState(const TInt& aState)
	{
	switch (aState)
		{
		default:
			StopPaymentWaitDlg();
			break;
		}
	}
// End of File
