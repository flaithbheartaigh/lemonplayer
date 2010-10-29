/*
 ============================================================================
 Name		: NormalSettingContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Container control implementation
 ============================================================================
 */

// INCLUDE FILES
#include "NormalSettingContainer.h"
// INCLUDE FILES
#include <coemain.h>
#include <eikfrlbd.h>
#include <ThemeChange_0xE8EE38C1.rsg>
#include <StringLoader.h> 
#include "ThemeCommonDef.h"
#include "ThemeChangeDef.h"
#include "CommonUtils.h"

// CONSTANTS
// ================= MEMBER FUNCTIONS =======================

// Constructor
CNormalSettingContainer::CNormalSettingContainer()    
:iEnumText(0),iOldEnumText(0),iBinary(EFalse),iOldBinary(EFalse)
    {
    }

// Destructor
CNormalSettingContainer::~CNormalSettingContainer()
    {
    delete iItemList;
    delete iConfig;
    }

// ----------------------------------------------------
// CNormalSettingContainer::ConstructL()
// Symbian OS default constructor can leave.
// ----------------------------------------------------
//
void CNormalSettingContainer::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    TBuf<8> value;
    
    value.FillZ();
    iConfig = CConfiguration::NewL(KConfigFile);
	if (iConfig->Get(KCfgAttFrequency,value))
		{
		iEnumText = CCommonUtils::StrToInt(value);
		iOldEnumText = iEnumText;
		}
	else
		iOldEnumText = -1;
	
	value.FillZ();
	if (iConfig->Get(KCfgAttAutoStart,value))
		{
		iBinary = CCommonUtils::StrToInt(value);
		iOldBinary = iBinary;
		}
	else
		iOldBinary = -1;
    
    iItemList = new (ELeave) CAknSettingItemList;
    iItemList->SetMopParent(this);
    iItemList->ConstructFromResourceL(R_ENTRY_SETTINGS_LIST);

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

// ----------------------------------------------------
// CNormalSettingContainer::Draw()
// This function is used for window server-initiated
// redrawing of controls, and for some
// application-initiated drawing.
// ----------------------------------------------------
//
void CNormalSettingContainer::Draw(const TRect& /*aRect*/) const
    {
    // Get the standard graphics context
    CWindowGc& gc = SystemGc();

    // Gets the control's extent
    TRect rect = Rect();

    // Clears the screen
    gc.Clear(rect);
    }

// ----------------------------------------------------
// CNormalSettingContainer::CountComponentControls()
// Gets the number of controls contained in a compound
// control.
// ----------------------------------------------------
//
TInt CNormalSettingContainer::CountComponentControls() const
    {
    TInt count = 0;
    if (iItemList)
        count++;
    return count;
    }

// ----------------------------------------------------
// CNormalSettingContainer::ComponentControl()
// Gets the specified component of a compound control.
// ----------------------------------------------------
//
CCoeControl* CNormalSettingContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return iItemList;
    }

// ----------------------------------------------------
// CNormalSettingContainer::OfferKeyEventL()
// When a key event occurs, the control framework calls
// this function for each control on the control stack,
// until one of them can process the key event
// (and returns EKeyWasConsumed).
// ----------------------------------------------------
//
TKeyResponse CNormalSettingContainer::OfferKeyEventL(    const TKeyEvent& aKeyEvent,
                                                                TEventCode aType )
    {
    if(iItemList)
        {
        return iItemList->OfferKeyEventL( aKeyEvent, aType );
        }
    else
        {
        return EKeyWasNotConsumed;
        }

    }

// ----------------------------------------------------
// CNormalSettingContainer::LoadListL()
// Loads the setting item list dynamically.
// ----------------------------------------------------
//
void CNormalSettingContainer::LoadListL()
    {
    TBool isNumberedStyle = iItemList->IsNumberedStyle();
    CArrayPtr<CGulIcon>* icons = iItemList->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();
    CArrayPtr<CAknEnumeratedText>* texts;
    CAknEnumeratedText* enumText;
    HBufC* text;

    /* Text setting item */
//    CAknTextSettingItem* item = new (ELeave) CAknTextSettingItem(1, iText);
//    CleanupStack::PushL(item);
//    item->SetEmptyItemTextL( KEmptyText );
//    // The same resource id can be used for multiple text setting pages.
//    item->ConstructL(isNumberedStyle, 1, KName, icons, R_TEXT_SETTING_PAGE, -1);
//    iItemList->SettingItemArray()->AppendL(item);
//    CleanupStack::Pop(item);
//
//
//    /* Integer setting item */
//    CAknIntegerEdwinSettingItem* item2 = new (ELeave) CAknIntegerEdwinSettingItem(2, iNumber);
//    CleanupStack::PushL(item2);
//    // The same resource id can be used for multiple integer setting pages.
//    item2->ConstructL(isNumberedStyle, 2, KName2, icons, R_INTEGER_SETTING_PAGE, -1);
//    iItemList->SettingItemArray()->AppendL(item2);
//    CleanupStack::Pop(item2);
//
//
//    /* Password setting item */
//    CAknPasswordSettingItem* item3 = new (ELeave) CAknPasswordSettingItem(  3,
//                                                                            CAknPasswordSettingItem::EAlpha,
//                                                                            iPassword);
//    CleanupStack::PushL(item3);
//    item3->SetEmptyItemTextL( KEmptyText );
//    // The same resource id can be used for multiple password setting pages.
//    item3->ConstructL(isNumberedStyle, 3, KName3, icons, R_PASSWORD_SETTING_PAGE, -1);
//    iItemList->SettingItemArray()->AppendL(item3);
//    CleanupStack::Pop(item3);
//
//
//    /* Volume setting item */
//    CAknVolumeSettingItem* item4 = new (ELeave) CAknVolumeSettingItem(4, iVolume);
//    CleanupStack::PushL(item4);
//    // The same resource id can be used for multiple volume setting pages.
//    item4->ConstructL(isNumberedStyle, 4, KName4, icons, R_VOLUME_SETTING_PAGE, -1);
//    iItemList->SettingItemArray()->AppendL(item4);
//    CleanupStack::Pop(item4);
//
//
//   /* Slider setting item. Read comments in CDynamicSettingListSlider, why
//    * a derived class is used instead of CAknSliderSettingItem
//    */
//    CDynamicSettingListSlider* item5 = new (ELeave) CDynamicSettingListSlider(5, iSlider);
//    CleanupStack::PushL(item5);
//    // The same resource id can be used for multiple slider setting pages.
//    item5->ConstructL(isNumberedStyle, 5, KName5, icons, R_SLIDER_SETTING_PAGE, -1);
//    iItemList->SettingItemArray()->AppendL(item5);
//    CleanupStack::Pop(item5);
//
//
//    /* Date setting item */
//    CAknTimeOrDateSettingItem* item6 = new (ELeave) CAknTimeOrDateSettingItem(  6,
//                                                                                CAknTimeOrDateSettingItem::EDate,
//                                                                                iDate);
//    CleanupStack::PushL(item6);
//    // The same resource id can be used for multiple date setting pages.
//    item6->ConstructL(isNumberedStyle, 6, KName6, icons, R_DATE_SETTING_PAGE, -1);
//    iItemList->SettingItemArray()->AppendL(item6);
//    CleanupStack::Pop(item6);
//
//
//    /* Time offset setting item */
//    CAknTimeOffsetSettingItem* item7 = new (ELeave) CAknTimeOffsetSettingItem(7, iTime);
//    CleanupStack::PushL(item7);
//    // The same resource id can be used for multiple time offset setting pages.
//    item7->ConstructL(isNumberedStyle, 7, KName7, icons, R_TIMEOFFSET_SETTING_PAGE, -1);
//    iItemList->SettingItemArray()->AppendL(item7);
//    CleanupStack::Pop(item7);
//
//
//    /* Ip field setting item */
//    CAknIpFieldSettingItem* item8 = new (ELeave) CAknIpFieldSettingItem(8, iIp);
//    CleanupStack::PushL(item8);
//    // The same resource id can be used for multiple ip field setting pages.
//    item8->ConstructL(isNumberedStyle, 8, KName8, icons, R_IPFIELD_SETTING_PAGE, -1);
//    iItemList->SettingItemArray()->AppendL(item8);
//    CleanupStack::Pop(item8);
//
//
//    /* Enumerated text setting item */  ����Ƶ��
    CAknEnumeratedTextPopupSettingItem* item9 = new (ELeave) CAknEnumeratedTextPopupSettingItem(EItemFreqency, iEnumText);
    CleanupStack::PushL(item9);
    // The same resource id can be used for multiple enumerated text setting pages.
    text = StringLoader::LoadLC(R_SETTING_FREQUENCY_TITLE);
    item9->ConstructL(isNumberedStyle, EItemFreqency, text->Des(), icons, R_ENUMERATEDTEXT_SETTING_PAGE, -1, 0, R_POPUP_SETTING_TEXTS);
    CleanupStack::PopAndDestroy();
    
    // Load texts dynamically.
    texts = item9->EnumeratedTextArray();
    texts->ResetAndDestroy();    
    // 1 hour
    text = StringLoader::LoadLC(R_TEXT_FREQUENCY_ONE_HOUR);
    enumText = new (ELeave) CAknEnumeratedText(EFrequencyOneHour, text);
    CleanupStack::Pop(text);
    CleanupStack::PushL(enumText);
    texts->AppendL(enumText);
    CleanupStack::Pop(enumText);
    // 8 hours
    text = StringLoader::LoadLC(R_TEXT_FREQUENCY_EIGHT_HOURS);
    enumText = new (ELeave) CAknEnumeratedText(EFrequencyEightHours, text);
    CleanupStack::Pop(text);
    CleanupStack::PushL(enumText);
    texts->AppendL(enumText);
    CleanupStack::Pop(enumText);
    // 1 day
    text = StringLoader::LoadLC(R_TEXT_FREQUENCY_ONE_DAY);
    enumText = new (ELeave) CAknEnumeratedText(EFrequencyOneDay, text);
    CleanupStack::Pop(text);
    CleanupStack::PushL(enumText);
    texts->AppendL(enumText);
    CleanupStack::Pop(enumText);
    // 3 days
    text = StringLoader::LoadLC(R_TEXT_FREQUENCY_THREE_DAYS);
    enumText = new (ELeave) CAknEnumeratedText(EFrequencyThreeDays, text);
    CleanupStack::Pop(text);
    CleanupStack::PushL(enumText);
    texts->AppendL(enumText);
    CleanupStack::Pop(enumText);
    // 1 week
    text = StringLoader::LoadLC(R_TEXT_FREQUENCY_ONE_WEEK);
    enumText = new (ELeave) CAknEnumeratedText(EFrequencyOneWeek, text);
    CleanupStack::Pop(text);
    CleanupStack::PushL(enumText);
    texts->AppendL(enumText);
    CleanupStack::Pop(enumText);

    iItemList->SettingItemArray()->AppendL(item9);
    CleanupStack::Pop(item9);


//  /* Binary popup setting item */	��������
//    CAknBinaryPopupSettingItem* item10 = new (ELeave) CAknBinaryPopupSettingItem(EItemAutoStart, iBinary);
//    CleanupStack::PushL(item10);
//    // The same resource id can be used for multiple binary setting pages.
//    text = StringLoader::LoadLC(R_SETTING_AUTOSTART_TITLE);
//    item10->ConstructL(isNumberedStyle, EItemAutoStart, text->Des(), icons, R_BINARY_SETTING_PAGE, -1, 0, R_BINARY_TEXTS);
//    CleanupStack::PopAndDestroy();
//    
//    // Load texts dynamically.
//    texts = item10->EnumeratedTextArray();
//    texts->ResetAndDestroy();
//    // Text 1
//    text = StringLoader::LoadLC(R_TEXT_NO);
//    enumText = new (ELeave) CAknEnumeratedText(0, text);
//    CleanupStack::Pop(text);
//    CleanupStack::PushL(enumText);
//    texts->AppendL(enumText);
//    CleanupStack::Pop(enumText);
//    // Text 2
//    text = StringLoader::LoadLC(R_TEXT_YES);
//    enumText = new (ELeave) CAknEnumeratedText(1, text);
//    CleanupStack::Pop(text);
//    CleanupStack::PushL(enumText);
//    texts->AppendL(enumText);
//    CleanupStack::Pop(enumText);
//
//    // Sets the correct text visible
//    item10->LoadL();
//
//    iItemList->SettingItemArray()->AppendL(item10);
//    CleanupStack::Pop(item10);

    // Required when there is only one setting item.
    iItemList->SettingItemArray()->RecalculateVisibleIndicesL();

    iItemList->HandleChangeInItemArrayOrVisibilityL();
    }

// ----------------------------------------------------
// CNormalSettingContainer::StoreSettingsL()
// Stores the settings of the setting list.
// ----------------------------------------------------
//
void CNormalSettingContainer::StoreSettingsL()
    {
    iItemList->StoreSettingsL();
    }

TBool CNormalSettingContainer::IsChange()
	{
	TBool a1 = (iEnumText != iOldEnumText);
	TBool a2 = (iBinary != iOldBinary);
	
	return (a1 || a2);
	}
TInt CNormalSettingContainer::SaveConfig()
	{
	TBuf<8> value;
	TInt result = 0;
	if (iEnumText != iOldEnumText)
		{
		value.FillZ();
		value.AppendNum(iEnumText);
		iConfig->Set(KCfgAttFrequency,value);
		result |= KCfgChangeFrequency;
		}
	
	if (iBinary != iOldBinary)
		{
		value.FillZ();
		value.AppendNum(iBinary);
		iConfig->Set(KCfgAttAutoStart,value);
		result |= KCfgChangeAutoStart;
		}
	return result;
	}
// End of File

