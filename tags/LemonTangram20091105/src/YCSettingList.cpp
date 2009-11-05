/*
 * ==============================================================================
 *  Name        : ListboxSettingList.cpp
 *  Part of     : Listbox example
 *  Interface   :
 *  Description :
 *  Version     :
 *
 *  Copyright (c) 2007 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

#include "LemonTangram.hrh"
#include "YCSettingList.h"
#include <eikfrlbd.h>
#include <akntitle.h>
#include <eikspane.h>
#include <akncontext.h>
#include <StringLoader.h>
#include <LemonTangram.rsg>
#include <BAUTILS.H>
#include <COEMAIN.H>

#include "SkinImageScan.h"
#include "TangFileDefine.h"
#include "ConfigDefine.h"
#include "Configuration.h"
#include "Utils.h"
#include "QueryDlgUtil.h"
#include "MacroUtil.h"

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CListboxSettingList::CListboxSettingList()
// C++ default constructor
// ---------------------------------------------------------------------------
//
CYCSettingList::CYCSettingList()
:iScaner(NULL),iConfig(NULL)
	{
	}

// ---------------------------------------------------------------------------
// CListboxSettingList::~CListboxSettingList()
// Destructor
// ---------------------------------------------------------------------------
//      
CYCSettingList::~CYCSettingList()
	{
	SaveL();
	SAFE_DELETE(iScaner);
	SAFE_DELETE(iConfig);
	}

// ---------------------------------------------------------------------------
// CListboxSettingList::NewL()
// Two-phased constructor.
// ---------------------------------------------------------------------------
//      
CYCSettingList* CYCSettingList::NewL()
	{
	CYCSettingList* self = new ( ELeave ) CYCSettingList;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

// ---------------------------------------------------------------------------
// CListboxSettingList::ConstructL()
// 2nd phase constructor
// ---------------------------------------------------------------------------
//      
void CYCSettingList::ConstructL()
	{
	LoadConfigL();
	}

// ---------------------------------------------------------------------------
// CListboxSettingList::CreateSettingItemL()
// Creates setting item
// ---------------------------------------------------------------------------
//    
CAknSettingItem* CYCSettingList::CreateSettingItemL(TInt aSettingId)
	{
	CAknSettingItem* settingItem= NULL;

//	switch (aSettingId)
//		{
//		case ELTSettingSkinFolder:
//			settingItem = CreateSkinFolderItem(aSettingId);
//			break;
//		case ELTSettingSkinChosse:
//			settingItem = CreateSkinChooseItem(aSettingId);
//			break;
//		case ELTSettingSaveFolder:
//			settingItem = CreateSaveFolderItem(aSettingId);
//			break;
//		default:
//			break;
// 		}

	return settingItem;
	}

// ---------------------------------------------------------------------------
// CListboxSettingList::EditItemL()
// Edits setting item data.
// ---------------------------------------------------------------------------
//    
void CYCSettingList::EditItemL(TInt aIndex, TBool aCalledFromMenu)
	{
	BeforeEditItem(aIndex);
	TInt currentItem = ((CAknSettingItemList*)this)->ListBox()->View()->CurrentItemIndex();
	CAknSettingItemList::EditItemL(currentItem, aCalledFromMenu);
	( *SettingItemArray() )[aIndex]->UpdateListBoxTextL();
	( *SettingItemArray() )[aIndex]->StoreL();
	ModifyItemL(aIndex);
	}

CAknSettingItem* CYCSettingList::CreateSkinChooseItem(TInt aSettingId)
	{
	TBool isNumberedStyle = this->IsNumberedStyle();
	CArrayPtr<CGulIcon>* icons = this->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();

	CAknEnumeratedTextPopupSettingItem* item = new (ELeave) CAknEnumeratedTextPopupSettingItem(aSettingId, iSkinChoose);
	CleanupStack::PushL(item);

	HBufC* textResource= NULL;
	textResource = StringLoader::LoadLC(R_TEXT_SETTING_SKIN_CHOOSE);
	// The same resource id can be used for multiple enumerated text setting pages.
	item->ConstructL(isNumberedStyle, aSettingId, textResource->Des(), icons, 
	R_ENUMERATEDTEXT_SETTING_PAGE, -1, 0, R_POPUP_SETTING_TEXTS);

	// Load texts dynamically.
	CArrayPtr<CAknEnumeratedText>* texts = item->EnumeratedTextArray();
	texts->ResetAndDestroy();

	HBufC* textDef = StringLoader::LoadLC(R_TEXT_DEFAULT);
	CAknEnumeratedText* enumTextDef = new (ELeave) CAknEnumeratedText(0, textDef);
	CleanupStack::Pop(textDef);
	CleanupStack::PushL(enumTextDef);
	texts->AppendL(enumTextDef);
	CleanupStack::Pop(enumTextDef);

	RPointerArray<SkinImageStruct>& skins = iScaner->GetSkins();
	for (TInt i=0; i<skins.Count(); i++)
		{
		pSkinImageStruct sk = skins[i];
		CAknEnumeratedText* enumText;

		HBufC* text = sk->iShortName.AllocLC();
		enumText = new (ELeave) CAknEnumeratedText(sk->iIndex+1, text);
		CleanupStack::Pop(text);
		CleanupStack::PushL(enumText);
		texts->AppendL(enumText);
		CleanupStack::Pop(enumText);
		}

	this->SettingItemArray()->AppendL(item);

	CleanupStack::PopAndDestroy(textResource);

	CleanupStack::Pop(item);

	return item;
	}

CAknSettingItem* CYCSettingList::CreateSkinFolderItem(TInt aSettingId)
	{
	TBool isNumberedStyle = this->IsNumberedStyle();
	CArrayPtr<CGulIcon>* icons = this->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();
	HBufC* textResource = StringLoader::LoadLC(R_TEXT_SETTING_SKIN_FOLDER);

	CAknTextSettingItem* item = new (ELeave) CAknTextSettingItem(aSettingId, iSkinFolder);
	CleanupStack::PushL(item);
	item->SetEmptyItemTextL(KEmptyFolder);
	// The same resource id can be used for multiple text setting pages.
	item->ConstructL(isNumberedStyle, aSettingId, textResource->Des(), icons,
			R_TEXT_SETTING_PAGE, -1);
	//item->ConstructL(isNumberedStyle, aSettingId, KName, icons, R_TEXT_SETTING_PAGE, -1);

	this->SettingItemArray()->AppendL(item);

	CleanupStack::Pop(item);
	CleanupStack::PopAndDestroy(textResource);

	return item;
	}
CAknSettingItem* CYCSettingList::CreateSaveFolderItem(TInt aSettingId)
	{
	TBool isNumberedStyle = this->IsNumberedStyle();
	CArrayPtr<CGulIcon>* icons = this->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();
	HBufC* textResource = StringLoader::LoadLC(R_TEXT_SETTING_SAVE_FOLDER);

	CAknTextSettingItem* item = new (ELeave) CAknTextSettingItem(aSettingId, iSaveFolder);
	CleanupStack::PushL(item);
	item->SetEmptyItemTextL(KEmptyFolder);
	// The same resource id can be used for multiple text setting pages.
	item->ConstructL(isNumberedStyle, aSettingId, textResource->Des(), icons,
			R_TEXT_SETTING_PAGE, -1);
	this->SettingItemArray()->AppendL(item);
	CleanupStack::Pop(item);

	CleanupStack::PopAndDestroy(textResource);

	return item;
	}

void CYCSettingList::LoadConfigL()
	{
	TFileName setup;
	GetAppPath(setup);
	setup.Append(KSetupSaveFile);

	iConfig = CConfiguration::NewL(setup);

	if(!iConfig->Get(KCfgSkinFolder, iSkinFolder))	
		iSkinFolder.Copy(KCfgDefaultSkinFolder);

	if (!iConfig->Get(KCfgSkinChoose, iFileSkinChoose))
		iFileSkinChoose.Zero();

	if(!iConfig->Get(KCfgSaveFolder, iSaveFolder))
		iSaveFolder.Copy(KCfgDefaultSaveFolder);

	iSkinFolderOld.Copy(iSkinFolder);
	iSaveFolderOld.Copy(iSaveFolder);
	//adjust iSkinChoose
	AdjustSkinChoose();
	}

void CYCSettingList::AdjustSkinChoose()
	{
	if (!iScaner)
		iScaner = CSkinImageScan::NewL();
	iScaner->ScanFolder(iSkinFolder, KXmlFormat);

	iSkinChoose = 0; //0为默认
	RPointerArray<SkinImageStruct>& skins = iScaner->GetSkins();
	for (TInt i=0; i<skins.Count(); i++)
		{
		pSkinImageStruct sk = skins[i];
		if (sk->iFileName.Compare(iFileSkinChoose) == 0)
			{
			iSkinChoose = i+1;
			break;
			}
		}	
	}
void CYCSettingList::ResetSkinFolderItem()
{
	CAknTextSettingItem* item = (CAknTextSettingItem*)(this->SettingItemArray()->At(ELTSettingSkinFolder));
}

void CYCSettingList::ResetSaveFolderItem()
{
	CAknTextSettingItem* item = (CAknTextSettingItem*)(this->SettingItemArray()->At(ELTSettingSaveFolder));
}

void CYCSettingList::ResetSkinChooseItem()
	{
	CAknEnumeratedTextPopupSettingItem* item = (CAknEnumeratedTextPopupSettingItem*)(this->SettingItemArray()->At(ELTSettingSkinChosse));
	CArrayPtr<CAknEnumeratedText>* texts = item->EnumeratedTextArray();
	texts->ResetAndDestroy();

	HBufC* textDef = StringLoader::LoadLC(R_TEXT_DEFAULT);
	CAknEnumeratedText* enumTextDef = new (ELeave) CAknEnumeratedText(0, textDef);
	CleanupStack::Pop(textDef);
	CleanupStack::PushL(enumTextDef);
	texts->AppendL(enumTextDef);
	CleanupStack::Pop(enumTextDef);

	RPointerArray<SkinImageStruct>& skins = iScaner->GetSkins();
	for (TInt i=0; i<skins.Count(); i++)
		{
		pSkinImageStruct sk = skins[i];
		CAknEnumeratedText* enumText;

		HBufC* text = sk->iShortName.AllocLC();
		enumText = new (ELeave) CAknEnumeratedText(sk->iIndex+1, text);
		CleanupStack::Pop(text);
		CleanupStack::PushL(enumText);
		texts->AppendL(enumText);
		CleanupStack::Pop(enumText);
		}
	}

void CYCSettingList::SaveL()
	{
	iConfig->Set(KCfgSkinFolder, iSkinFolder);
	iConfig->Set(KCfgSaveFolder, iSaveFolder);

	iFileSkinChoose.Zero();
	if (iSkinChoose == 0)
		{
		GetAppPath(iFileSkinChoose);
		iFileSkinChoose.Copy(KFileTangImageDefault);
		}
	else
		{
		RPointerArray<SkinImageStruct>& skins = iScaner->GetSkins();
		for (TInt i=0; i<skins.Count(); i++)
			{
			if (iSkinChoose == (i+1))
				{
				iFileSkinChoose.Copy(skins[i]->iFileName);
				}
			}
		}
	iConfig->Set(KCfgSkinChoose, iFileSkinChoose);
	}

void CYCSettingList::LoadListL()
	{
	CreateSkinFolderItem(ELTSettingSkinFolder);
	CreateSkinChooseItem(ELTSettingSkinChosse);
	CreateSaveFolderItem(ELTSettingSaveFolder);
	
    this->SettingItemArray()->RecalculateVisibleIndicesL();

    this->HandleChangeInItemArrayOrVisibilityL();
	}

void CYCSettingList::BeforeEditItem(TInt aIndex)
	{
	switch (aIndex)
		{
		case ELTSettingSkinFolder:
			iSkinFolderOld.Copy(iSkinFolder);
			break;
		case ELTSettingSaveFolder:
			iSaveFolderOld.Copy(iSaveFolder);
			break;
		default:
			break;
		}	
	}
void CYCSettingList::ModifyItemL(TInt aIndex)
	{
	switch (aIndex)
		{
		case ELTSettingSkinFolder:
			ModifySkinFolderItem();
			break;
		case ELTSettingSaveFolder:
			ModifySaveFolderItem();
			break;
		default:
			break;
		}
	}

void CYCSettingList::ModifySkinFolderItem()
	{
	if (AdjustFolder(iSkinFolder) == EFalse)
		{
		iSkinFolder.Copy(iSkinFolderOld);
		return;
		}
	if (iSkinFolder.Compare(iSkinFolderOld))
		{
		AdjustSkinChoose();
		ResetSkinChooseItem();
		}
	}

void CYCSettingList::ModifySaveFolderItem()
	{
	if (AdjustFolder(iSaveFolder) == EFalse)
		{
		iSaveFolder.Copy(iSaveFolderOld);
		}	
	}

TBool CYCSettingList::AdjustFolder(TDes& aDes)
	{
	//是否'/'结尾.
	TInt pos = aDes.LocateReverse('\\');
	if (pos != aDes.Length() - 1)
		aDes.Append('\\');
	
	//是否存在文件夹
	if (BaflUtils::PathExists(CCoeEnv::Static()->FsSession(),aDes))
		{
		return ETrue;
		}
	else
		{
		ShowInfomationDlgL(R_TEXT_DLG_INPUT_FOLDER_ERROR);
		return EFalse;
		}	
	}