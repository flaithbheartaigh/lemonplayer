/*
 * ==============================================================================
 *  Name        : ListboxSettingList.h
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

#ifndef __LISTBOXSETTINGLIST_H__
#define __LISTBOXSETTINGLIST_H__

#include <AknSettingItemList.h>
#include <aknsettingpage.h> 

class CSkinImageScan;
class CConfiguration;

/**
 *  CListboxSettingList class
 *  This class is a container for CListboxSettingView. It implements functionality
 *  for setting list. 
 */
class CYCSettingList : public CAknSettingItemList
	{
public:

	/**
	 * C++ default constructor.
	 */
	CYCSettingList();
	~CYCSettingList();
	static CYCSettingList* NewL();

public:
	// From CAknSettingItemList

	/**
	 * From CAknSettingItemList.
	 * Creates setting item.
	 *
	 * @param aSettingId Type of the setting item.
	 * @return  Pointer to CAknSettingItem object.
	 */
	CAknSettingItem* CreateSettingItemL(TInt aSettingId);

	/**
	 * From CAknSettingItemList.
	 * Edits setting item data.
	 *
	 * @param aIndex Setting item index.
	 * @param aCalledFromMenu is called from menu.
	 */
	void EditItemL(TInt aIndex, TBool aCalledFromMenu);

private:

	/**
	 * By default Symbian 2nd phase constructor is private.
	 */
	void ConstructL();
	
public:
	void LoadListL();
	
private:
	CAknSettingItem* CreateSkinFolderItem(TInt aSettingId);
	CAknSettingItem* CreateSkinChooseItem(TInt aSettingId);
	CAknSettingItem* CreateSaveFolderItem(TInt aSettingId);
	
	void LoadConfigL();	
	void SaveL();
	
	void AdjustSkinChoose();
	void ResetSkinChooseItem();
	
	void ModifyItemL(TInt aIndex);
	
	void ModifySkinFolderItem();

private:
	// Data        
    TFileName iSkinFolder;    
    TFileName iSkinFolderOld;    
    TInt iSkinChoose;
    TFileName iFileSkinChoose;    
    TFileName iSaveFolder;
    
    CSkinImageScan* iScaner;
    CConfiguration* iConfig;

	};

#endif // __LISTBOXSETTINGLIST_H__    
