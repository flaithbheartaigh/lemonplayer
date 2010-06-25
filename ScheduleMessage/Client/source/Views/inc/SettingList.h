/*
 ============================================================================
 Name		: SettingList.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSettingList declaration
 ============================================================================
 */

#ifndef SETTINGLIST_H
#define SETTINGLIST_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <AknSettingItemList.h>
#include <aknsettingpage.h> 
// CLASS DECLARATION

/**
 *  CSettingList
 * 
 */
class CSettingList : public CAknSettingItemList 
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CSettingList();

	/**
	 * Two-phased constructor.
	 */
	static CSettingList* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CSettingList* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CSettingList();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public: // From CAknSettingItemList
        
    /**
    * From CAknSettingItemList.
    * Creates setting item.
    *
    * @param aSettingId Type of the setting item.
    * @return  Pointer to CAknSettingItem object.
    */
    CAknSettingItem* CreateSettingItemL( TInt aSettingId );
        
    /**
    * From CAknSettingItemList.
    * Edits setting item data.
    *
    * @param aIndex Setting item index.
    * @param aCalledFromMenu is called from menu.
    */
    void EditItemL( TInt aIndex, TBool aCalledFromMenu );
    
    void EditItemL( TBool aCalledFromMenu );
    
    void SaveConfig();
    
private: // Data
    
    /**
    * Integer representing the selected index from "Connection mode" 
    * setting page.
    */
    TInt iSelected;

	};

#endif // SETTINGLIST_H
