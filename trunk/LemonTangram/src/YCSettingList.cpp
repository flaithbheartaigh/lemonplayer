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
	}

// ---------------------------------------------------------------------------
// CListboxSettingList::CreateSettingItemL()
// Creates setting item
// ---------------------------------------------------------------------------
//  	
CAknSettingItem* CYCSettingList::CreateSettingItemL(TInt aSettingId)
	{
	CAknSettingItem* settingItem= NULL;

	switch (aSettingId)
		{
		case EYCSettingFont:
			iFontSizeOld = iFontSize;
			settingItem = new ( ELeave )
				CAknEnumeratedTextPopupSettingItem( aSettingId, iFontSize );
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

void CYCSettingList::SaveData()
{
	if (iFontSize != iFontSizeOld)
	{
	}
}
