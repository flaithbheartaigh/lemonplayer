/*
 ============================================================================
 Name		: MainCommand.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMainCommand implementation
 ============================================================================
 */

#include "MainCommand.h"
#include "UIData.h"
#include "PlayingListData.h"
#include "LUDynamicWait.h"
#include "MacroUtil.h"
#include <LemonPlayer.rsg>
#include <StringLoader.h> 
#include <eikenv.h>
#include <CAknMemorySelectionDialog.h> 
#include <CAknFileSelectionDialog.h> 
#include "FormatCheck.h"
#include "CommonUtils.h"

const TInt KInfoSize = 40;

CMainCommand::CMainCommand()
:iWaitDlg(NULL),iFileScaner(NULL)
	{
	// No implementation required
	}

CMainCommand::~CMainCommand()
	{
	SAFE_DELETE_ACTIVE(iFileScaner);
	SAFE_DELETE(iWaitDlg);
	}

CMainCommand* CMainCommand::NewLC()
	{
	CMainCommand* self = new (ELeave)CMainCommand();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMainCommand* CMainCommand::NewL()
	{
	CMainCommand* self=CMainCommand::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CMainCommand::ConstructL()
	{
	}

void CMainCommand::OpenAll()
	{
	StartOpenAll();
	}

void CMainCommand::OpenOne()
	{
	ShowSelectFile(ETrue);
	}

void CMainCommand::AddOne()
	{
	ShowSelectFile(EFalse);
	}

void CMainCommand::StartOpenAll()
	{
	if (iWaitDlg)
		iWaitDlg = CLUDynamicWait::NewL();
	if (iFileScaner)
		iFileScaner = CScanFile::NewL(this);
	//清理播放列表
	CUIViewData::GetInstance()->GetPlayList()->ClearMusic();
	//打开等待对话框
	if (iWaitDlg)
		iWaitDlg->OpenWaitNoteL(R_CE_WAIT_NOTE);
	//打开文件遍历活动对象
	if (iFileScaner)
		iFileScaner->StartL();
	}

void CMainCommand::UpdateScan(const TDesC& aInfo)
	{
	TBuf<KInfoSize> info;
	CreateInfo(aInfo,info);
	if (iWaitDlg)
		iWaitDlg->UpdateTextL(info);
	}

void CMainCommand::FinishScan(const TDesC& aInfo)
	{
	TBuf<KInfoSize> info;
	CreateInfo(aInfo,info);
	if (iWaitDlg)
		iWaitDlg->CloseWaitNoteL();
	CEikonEnv::Static()->InfoWinL(_L("note:"), info);
	}

void CMainCommand::CreateInfo(const TDesC& aMsg,TDes& aInfo)
	{
	TInt pos = aMsg.Find(KScanInfoSplit);
	if (pos == KErrNotFound)
		return;
	TPtrC folder = aMsg.Left(pos);
	TPtrC file   = aMsg.Mid(pos+1);
	HBufC* textResource = StringLoader::LoadLC(R_TEXT_SCAN_INFO);
	aInfo.Format(textResource->Des(),folder,file);
	CleanupStack::PopAndDestroy(textResource);
	}

TBool CMainCommand::OkToExitL(const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/)
	{
	// Return ETrue if it is OK to close the CAknFileSelectionDialog.
	return ETrue;
	}

void CMainCommand::ShowSelectFile(TBool aOpen)
	{
	TFileName folder;

	// Create select memory dialog
	CAknMemorySelectionDialog* memDlg = CAknMemorySelectionDialog::NewL(
			ECFDDialogTypeNormal, ETrue);
	CAknMemorySelectionDialog::TMemory memory =
			CAknMemorySelectionDialog::EPhoneMemory;
	_LIT(KDialogTitle, "Browse files");
	_LIT(KCDrive,"C:\\");
	_LIT(KEDrive,"E:\\");

	TBool result = EFalse;
	TFileName filename;

	for (;;)
		{
		if (memDlg->ExecuteL(memory) == CAknFileSelectionDialog::ERightSoftkey)
			{
			// cancel selection
			break;
			}

		if (memory==CAknMemorySelectionDialog::EMemoryCard)
			{
			filename.Copy(KCDrive);
			folder.Copy(KCDrive);
			}
		else
			{
			filename.Copy(KEDrive);
			folder.Copy(KEDrive);
			}

		TBool ret = CAknFileSelectionDialog::RunDlgLD(filename, // on return, contains the selected file's name
				folder,
//				KDialogTitle,
				this 
				);
		if (ret)
			{
			// we got our folder and finish loop
			if (FormatCheck::GetInstance()->IsAllowedFormat(filename))
			{
			if (aOpen)
				{
				CUIViewData::GetInstance()->GetPlayList()->ClearMusic();
				}
			HBufC8* file = CCommonUtils::ConvertToUTF8FromUnicode(filename);
			CUIViewData::GetInstance()->GetPlayList()->AddMusic(file->Des());
			delete file;
			}
			result = ETrue;
			break;
			}
		}
	delete memDlg;
	}