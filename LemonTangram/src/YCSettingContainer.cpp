/*
 ============================================================================
 Name		: YCSettingContainer.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CYCSettingContainer implementation
 ============================================================================
 */

#include "YCSettingContainer.h"
#include <eikfrlbd.h>
#include <StringLoader.h>
#include <LemonTangram_0xEAE107BA.rsg>
#include "SkinImageScan.h"

#include "TangFileDefine.h"
#include "ConfigDefine.h"
#include "Configuration.h"
#include "Utils.h"

CYCSettingContainer::CYCSettingContainer()
	{
	// No implementation required
	}

CYCSettingContainer::~CYCSettingContainer()
	{
	SaveL();
    delete iItemList;
    delete iScaner;
	}

void CYCSettingContainer::ConstructL(const TRect& aRect)
	{
	LoadConfigL();
	
    CreateWindowL();

    iItemList = new (ELeave) CAknSettingItemList;
    iItemList->SetMopParent(this);
    iItemList->ConstructFromResourceL(R_LISTBOX_SETTINGS_VIEW);

    LoadListL();

    iItemList->MakeVisible(ETrue);
    iItemList->SetRect(aRect);
    iItemList->ActivateL();
    iItemList->ListBox()->UpdateScrollBarsL();
    iItemList->DrawNow();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
	}

void CYCSettingContainer::LoadConfigL()
	{
	TFileName setup;
	GetAppPath(setup);
	setup.Append(KSetupSaveFile);
	
	iConfig = CConfiguration::NewL(setup);
	
	iConfig->Get(KCfgSkinFolder,iSkinFolder);
	iConfig->Get(KCfgSkinChoose,iFileSkinChoose);
	iConfig->Get(KCfgSaveFolder,iSaveFolder);	
	
	//adjust iSkinChoose
	iScaner = CSkinImageScan::NewL();
	iScaner->ScanFolder(iSkinFolder,KXmlFormat);
	
	iSkinChoose = 0;  //0ÎªÄ¬ÈÏ
	RPointerArray<SkinImageStruct>& skins = iScaner->GetSkins();
	for(TInt i=0; i<skins.Count(); i++)
		{
		pSkinImageStruct sk = skins[i];
		if (sk->iFileName.Compare(iFileSkinChoose) == 0)
			{
			iSkinChoose = i+1;
			break;
			}
		}
	}

void CYCSettingContainer::Draw(const TRect& /*aRect*/) const
    {
    // Get the standard graphics context
    CWindowGc& gc = SystemGc();

    // Gets the control's extent
    TRect rect = Rect();

    // Clears the screen
    gc.Clear(rect);
    }

// ----------------------------------------------------
// CYCSettingContainer::CountComponentControls()
// Gets the number of controls contained in a compound
// control.
// ----------------------------------------------------
//
TInt CYCSettingContainer::CountComponentControls() const
    {
    TInt count = 0;
    if (iItemList)
        count++;
    return count;
    }

// ----------------------------------------------------
// CYCSettingContainer::ComponentControl()
// Gets the specified component of a compound control.
// ----------------------------------------------------
//
CCoeControl* CYCSettingContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return iItemList;
    }

// ----------------------------------------------------
// CYCSettingContainer::OfferKeyEventL()
// When a key event occurs, the control framework calls
// this function for each control on the control stack,
// until one of them can process the key event
// (and returns EKeyWasConsumed).
// ----------------------------------------------------
//
TKeyResponse CYCSettingContainer::OfferKeyEventL(    const TKeyEvent& aKeyEvent,
                                                                TEventCode aType )
    {
    if(aType != EEventKey)
        {
        return EKeyWasNotConsumed;
        }
    else if(iItemList)
        {
        return iItemList->OfferKeyEventL( aKeyEvent, aType );
        }
    else
        {
        return EKeyWasNotConsumed;
        }
    }


void CYCSettingContainer::LoadListL()
	{
	CreateSkinFolderItem(ELTSettingSkinFolder);
	CreateSkinChooseItem(ELTSettingSkinChosse);
	CreateSaveFolderItem(ELTSettingSaveFolder);
	
    iItemList->SettingItemArray()->RecalculateVisibleIndicesL();

    iItemList->HandleChangeInItemArrayOrVisibilityL();
	}
void CYCSettingContainer::StoreSettingsL()
	{
	iItemList->StoreSettingsL();
	}


void CYCSettingContainer::CreateSkinChooseItem(TInt aSettingId)
	{
	TBool isNumberedStyle = iItemList->IsNumberedStyle();
	CArrayPtr<CGulIcon>* icons = iItemList->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();

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
	
	HBufC* textDef = StringLoader::LoadLC(R_TEXT_DEFAULT);
	CAknEnumeratedText* enumTextDef = new (ELeave) CAknEnumeratedText(0, textDef);
	CleanupStack::Pop(textDef);
	CleanupStack::PushL(enumTextDef);
	texts->AppendL(enumTextDef);
	CleanupStack::Pop(enumTextDef);
	
	RPointerArray<SkinImageStruct>& skins = iScaner->GetSkins();
	for(TInt i=0; i<skins.Count(); i++)
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

	iItemList->SettingItemArray()->AppendL(item9);

	CleanupStack::PopAndDestroy(textResource);

	CleanupStack::Pop(item9);
	}


void CYCSettingContainer::CreateSkinFolderItem(TInt aSettingId)
	{
	TBool isNumberedStyle = iItemList->IsNumberedStyle();
	CArrayPtr<CGulIcon>* icons = iItemList->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();
	HBufC* textResource = StringLoader::LoadLC(R_TEXT_SETTING_SKIN_FOLDER);
		
	CAknTextSettingItem* item = new (ELeave) CAknTextSettingItem(aSettingId, iSkinFolder);
	CleanupStack::PushL(item);
	item->SetEmptyItemTextL( KEmptyFolder );
	// The same resource id can be used for multiple text setting pages.
	item->ConstructL(isNumberedStyle, aSettingId, textResource->Des(), icons, R_TEXT_SETTING_PAGE, -1);
	//item->ConstructL(isNumberedStyle, aSettingId, KName, icons, R_TEXT_SETTING_PAGE, -1);
		
	iItemList->SettingItemArray()->AppendL(item);
	
	CleanupStack::Pop(item);
	CleanupStack::PopAndDestroy(textResource);
	}
void CYCSettingContainer::CreateSaveFolderItem(TInt aSettingId)
	{
	TBool isNumberedStyle = iItemList->IsNumberedStyle();
	CArrayPtr<CGulIcon>* icons = iItemList->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();
	HBufC* textResource = StringLoader::LoadLC(R_TEXT_SETTING_SAVE_FOLDER);
	
	CAknTextSettingItem* item = new (ELeave) CAknTextSettingItem(aSettingId, iSaveFolder);
	CleanupStack::PushL(item);
	item->SetEmptyItemTextL( KEmptyFolder );
	// The same resource id can be used for multiple text setting pages.
	item->ConstructL(isNumberedStyle, aSettingId, textResource->Des(), icons, R_TEXT_SETTING_PAGE, -1);
	iItemList->SettingItemArray()->AppendL(item);
	CleanupStack::Pop(item);
	
	CleanupStack::PopAndDestroy(textResource);
	}

void CYCSettingContainer::SaveL()
	{
	iConfig->Set(KCfgSkinFolder,iSkinFolder);
	iConfig->Set(KCfgSaveFolder,iSaveFolder);	
	
	iFileSkinChoose.Zero();
	if (iSkinChoose == 0)
		{
		GetAppPath(iFileSkinChoose);
		iFileSkinChoose.Copy(KFileTangImageDefault);
		}
	else
		{
		RPointerArray<SkinImageStruct>& skins = iScaner->GetSkins();
		for(TInt i=0; i<skins.Count(); i++)
			{
			if (iSkinChoose == (i+1))
				{
				iFileSkinChoose.Copy(skins[i]->iFileName);
				}
			}
		}
	iConfig->Set(KCfgSkinChoose,iFileSkinChoose);
	}