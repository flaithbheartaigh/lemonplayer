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
#include <LemonTangram_0xEAE107BA.rsg>

// Listbox class name is shown on navigation pane
_LIT(KNaviPaneText, "CAknSettingItemList");

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CListboxSettingList::CListboxSettingList()
// C++ default constructor
// ---------------------------------------------------------------------------
//
CYCSettingList::CYCSettingList()
	{
	}

// ---------------------------------------------------------------------------
// CListboxSettingList::~CListboxSettingList()
// Destructor
// ---------------------------------------------------------------------------
// 	
CYCSettingList::~CYCSettingList()
	{
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
	CreateList();
	}
/*
 // ---------------------------------------------------------------------------
 // CListboxSettingList::CreateSettingItemL()
 // Creates setting item
 // ---------------------------------------------------------------------------
 //  	
 CAknSettingItem* CYCSettingList::CreateSettingItemL(TInt aSettingId)
 {
 TBool isNumberedStyle = this->IsNumberedStyle();
 CArrayPtr<CGulIcon>* icons = this->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();

 HBufC* textResource = NULL;
 CAknSettingItem* settingItem= NULL;

 switch (aSettingId)
 {
 //		case EYCSettingFont:
 //			iFontSizeOld = iFontSize;
 //			settingItem = new ( ELeave )
 //				CAknEnumeratedTextPopupSettingItem( aSettingId, iFontSize );
 //			break;
 case ELTSettingSkinFolder:
 textResource = StringLoader::LoadLC(R_TEXT_SETTING_SKIN_FOLDER);
 settingItem = new (ELeave) CAknTextSettingItem(aSettingId, iSkinFolder);
 //STATIC_CAST(CAknTextSettingItem*,settingItem)->ConstructL(isNumberedStyle, 
 //		aSettingId, textResource->Des(), icons, R_TEXT_SETTING_PAGE, -1);
 //CleanupStack::PopAndDestroy(textResource);
 break;
 case ELTSettingSkinChosse:
 settingItem = CreateSkinChooseItem(aSettingId);
 break;
 case ELTSettingSaveFolder:
 textResource = StringLoader::LoadLC(R_TEXT_SETTING_SAVE_FOLDER);
 settingItem = new (ELeave) CAknTextSettingItem(aSettingId, iSaveFolder);
 //STATIC_CAST(CAknTextSettingItem*,settingItem)->ConstructL(isNumberedStyle, 
 //		aSettingId, textResource->Des(), icons, R_TEXT_SETTING_PAGE, -1);
 //CleanupStack::PopAndDestroy(textResource);
 break;
 default:
 break;
 }
 
 return settingItem;
 }

 // ---------------------------------------------------------------------------
 // CListboxSettingList::EditItemL()
 // Edits setting item data.
 // ---------------------------------------------------------------------------
 //    
 void CYCSettingList::EditItemL(TInt aIndex, TBool aCalledFromMenu)
 {	
 TInt currentItem = ((CAknSettingItemList*)this)->ListBox()->View()->CurrentItemIndex();
 CAknSettingItemList::EditItemL(currentItem, aCalledFromMenu);
 ( *SettingItemArray() )[aIndex]->UpdateListBoxTextL();
 ( *SettingItemArray() )[aIndex]->StoreL();
 }
 */
void CYCSettingList::SaveData()
	{
	if (iFontSize != iFontSizeOld)
		{
		}
	}

_LIT(KEnumText1, "Enum text 1");
_LIT(KEnumText2, "Enum text 2");
void CYCSettingList::CreateSkinChooseItem(TInt aSettingId)
	{
	TBool isNumberedStyle = this->IsNumberedStyle();
	CArrayPtr<CGulIcon>* icons = NULL;//this->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();

	CAknEnumeratedTextPopupSettingItem* item9 = new (ELeave) CAknEnumeratedTextPopupSettingItem(aSettingId, iSkinChoose);
	CleanupStack::PushL(item9);

	HBufC* textResource= NULL;
	textResource = StringLoader::LoadLC(R_TEXT_SETTING_SKIN_CHOOSE);
	// The same resource id can be used for multiple enumerated text setting pages.
	item9->ConstructL(isNumberedStyle, aSettingId, textResource->Des(), icons,
			R_ENUMERATEDTEXT_SETTING_PAGE, -1, 0, R_POPUP_SETTING_TEXTS);

	// Load texts dynamically.
	CArrayPtr<CAknEnumeratedText>* texts = item9->EnumeratedTextArray();
	texts->ResetAndDestroy();
	CAknEnumeratedText* enumText;
	// Text 1
	HBufC* text = KEnumText1().AllocLC();
	enumText = new (ELeave) CAknEnumeratedText(0, text);
	CleanupStack::Pop(text);
	CleanupStack::PushL(enumText);
	texts->AppendL(enumText);
	CleanupStack::Pop(enumText);
	// Text 2
	text = KEnumText2().AllocLC();
	enumText = new (ELeave) CAknEnumeratedText(1, text);
	CleanupStack::Pop(text);
	CleanupStack::PushL(enumText);
	texts->AppendL(enumText);
	CleanupStack::Pop(enumText);

	this->SettingItemArray()->AppendL(item9);

	CleanupStack::PopAndDestroy(textResource);

	CleanupStack::Pop(item9);
	}

void CYCSettingList::CreateList()
	{
	CreateSkinFolderItem(ELTSettingSkinFolder);
	CreateSkinChooseItem(ELTSettingSkinChosse);
	CreateSaveFolderItem(ELTSettingSaveFolder);
	}
void CYCSettingList::CreateSkinFolderItem(TInt aSettingId)
	{
	TBool isNumberedStyle = this->IsNumberedStyle();
	CArrayPtr<CGulIcon>* icons = this->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();
	HBufC* textResource = StringLoader::LoadLC(R_TEXT_SETTING_SKIN_FOLDER);
		
	CAknTextSettingItem* item = new (ELeave) CAknTextSettingItem(aSettingId, iSkinFolder);
	CleanupStack::PushL(item);
	// The same resource id can be used for multiple text setting pages.
	item->ConstructL(isNumberedStyle, aSettingId, textResource->Des(), icons, R_TEXT_SETTING_PAGE, -1);
	this->SettingItemArray()->AppendL(item);
	CleanupStack::PopAndDestroy(textResource);
	CleanupStack::Pop(item);
	}
void CYCSettingList::CreateSaveFolderItem(TInt aSettingId)
	{
	TBool isNumberedStyle = this->IsNumberedStyle();
	CArrayPtr<CGulIcon>* icons = NULL;//this->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();
	HBufC* textResource = StringLoader::LoadLC(R_TEXT_SETTING_SAVE_FOLDER);
	
	CAknTextSettingItem* item = new (ELeave) CAknTextSettingItem(aSettingId, iSaveFolder);
	CleanupStack::PushL(item);
	// The same resource id can be used for multiple text setting pages.
	item->ConstructL(isNumberedStyle, aSettingId, textResource->Des(), icons, R_TEXT_SETTING_PAGE, -1);
	this->SettingItemArray()->AppendL(item);
	CleanupStack::PopAndDestroy(textResource);
	CleanupStack::Pop(item);
	}
