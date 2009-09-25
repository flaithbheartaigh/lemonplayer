/*
 ============================================================================
 Name		: ScanFile.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CScanFile implementation
 ============================================================================
 */

#include "ScanFile.h"
#include "MacroUtil.h"
#include <coemain.h>
#include "UIData.h"
#include "PlayingListData.h"
#include "CommonUtils.h"
#include <LemonPlayer.rsg>

_LIT(KDriveC,"c:\\");
_LIT(KDriveE,"e:\\");

CScanFile::CScanFile(ScanFileNotify* aNotifier) :
	CActive(EPriorityStandard), iNotifier(aNotifier)
	{
	// No implementation required
	}

CScanFile::~CScanFile()
	{
	iFormatArray->Reset();
	SAFE_DELETE(iFormatArray);
	SAFE_DELETE(iDirScan);
	Cancel();
	iTimeWaster.Close();
	}

CScanFile* CScanFile::NewLC(ScanFileNotify* aNotifier)
	{
	CScanFile* self = new (ELeave)CScanFile(aNotifier);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CScanFile* CScanFile::NewL(ScanFileNotify* aNotifier)
	{
	CScanFile* self=CScanFile::NewLC(aNotifier);
	CleanupStack::Pop(); // self;
	return self;
	}

void CScanFile::ConstructL()
	{
	iFormatArray = CCoeEnv::Static()->ReadDesCArrayResourceL(R_ACCEPTED_SOUND_FORMAT);
	User::LeaveIfError(iTimeWaster.CreateLocal());
	CActiveScheduler::Add(this);
	}

void CScanFile::RunL()
	{
	if (Scaning())
		SetActive();
	}

void CScanFile::DoCancel()
	{
	iTimeWaster.Cancel();
	}

void CScanFile::StartL()
	{
	iTimeWaster.After(iStatus, 1000);
	SetActive();
	}

TBool CScanFile::Scaning()
	{
	TBool re = ETrue;
	switch (iScanState)
		{
		case KScanInit:
			iScanState = KScanDriveC;
			ScanFromRoot(KDriveC);
			break;
		case KScanDriveC:
			if (ScanNext())
				{
				}
			else
				{
				iScanState = KScanDriveCDone;
				SAFE_DELETE(iDirScan);
				}
			break;
		case KScanDriveCDone:
			iScanState = KScanDriveE;
			ScanFromRoot(KDriveE);
			break;
		case KScanDriveE:
			if (ScanNext())
				{
				}
			else
				{
				iScanState = KScanDriveEDone;
				re = EFalse;
				TBuf<10> info;
				CreateInfo(info);
				iNotifier->FinishScan(info);
				SAFE_DELETE(iDirScan);
				}
			break;
		default:
			break;
		}
	return re;
	}
void CScanFile::ScanFromRoot(const TDesC& aDrive)
	{
	SAFE_DELETE(iDirScan);
	iDirScan = CDirScan::NewLC(CCoeEnv::Static()->FsSession());
	iDirScan->SetScanDataL(aDrive, KEntryAttNormal, ESortNone);
	}

//扫描目录,当遇见有文件时,中断,进行界面显示.
TBool CScanFile::ScanNext()
	{
	TInt num = 0;
	CDir* dirs= NULL;
	iDirScan->NextL(dirs);

	while (dirs!=NULL)
		{
		iTotalFolder++;
		for (TInt i=0; i < dirs->Count(); i++)
			{

			TParse fullentry;
			fullentry.Set((*dirs)[i].iName, &iDirScan->FullPath(), NULL);
			if (IsAllowedFormat(fullentry.Ext()))
				{
				num++;
				iTotalFile++;
				HBufC8
						* file =
								CCommonUtils::ConvertToUTF8FromUnicode(fullentry.FullName());
				CUIViewData::GetInstance()->GetPlayList()->AddMusic(file->Des());
				delete file;
				TBuf<10> info;
				CreateInfo(info);
				iNotifier->UpdateScan(info);
				}
			}
		delete dirs;
		dirs = NULL;
		if (num==0)
			iDirScan->NextL(dirs);
		else
			{
			return ETrue;
			}
		}
	return EFalse;
	}

TBool CScanFile::IsAllowedFormat(const TDesC& aExt)
	{
	for (TInt i=0; i<iFormatArray->Count(); i++)
		{
		TPtrC str = (*iFormatArray)[i];
		TInt pos = aExt.Find(str);
		if (pos!=KErrNotFound)
			{
			return ETrue;
			}
		}
	return EFalse;
	}

void CScanFile::CreateInfo(TDes& aInfo)
	{
	aInfo.AppendNum(iTotalFolder);
	aInfo.Append(KScanInfoSplit);
	aInfo.AppendNum(iTotalFile);
	}