/*
 ============================================================================
 Name		: SettingList.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSettingList implementation
 ============================================================================
 */

#include "SettingList.h"
#include "SHPlatform.h"

CSettingList::CSettingList()
	{
	// No implementation required
	}

CSettingList::~CSettingList()
	{
	}

CSettingList* CSettingList::NewLC()
	{
	CSettingList* self = new (ELeave) CSettingList();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSettingList* CSettingList::NewL()
	{
	CSettingList* self = CSettingList::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CSettingList::ConstructL()
	{

	}

// ---------------------------------------------------------------------------
// CSettingList::CreateSettingItemL()
// Creates setting item
// ---------------------------------------------------------------------------
//  	
CAknSettingItem* CSettingList::CreateSettingItemL( TInt aSettingId )
    {
    CAknSettingItem* settingItem = NULL;
    
    switch( aSettingId )
        {
        case EListboxSettingAutoStart:
            settingItem = new ( ELeave ) CAknBinaryPopupSettingItem( 
							aSettingId, iSelected );
            break;
        default:
            break;    
        }    
     
    return settingItem;
    }   

// ---------------------------------------------------------------------------
// CSettingList::EditItemL()
// Edits setting item data.
// ---------------------------------------------------------------------------
//    
void CSettingList::EditItemL( TInt aIndex, TBool aCalledFromMenu )
    {
    TInt currentItem = ((CAknSettingItemList*)this)->ListBox()->View()->CurrentItemIndex();
    CAknSettingItemList::EditItemL( currentItem, aCalledFromMenu );
  ( *SettingItemArray() )[aIndex]->UpdateListBoxTextL();
  ( *SettingItemArray() )[aIndex]->StoreL();    
    
    }
