/*
 ============================================================================
 Name		: YCSettingContainer.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CYCSettingContainer declaration
 ============================================================================
 */

#ifndef YCSETTINGCONTAINER_H
#define YCSETTINGCONTAINER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <aknsettingitemlist.h> 

#include "LemonTangram.hrh"

// CLASS DECLARATION
class CSkinImageScan;
class CConfiguration;
/**
 *  CYCSettingContainer
 * 
 */
class CYCSettingContainer : public CCoeControl
	{
public:
	// Constructors and destructor
	~CYCSettingContainer();
	CYCSettingContainer();
	void ConstructL(const TRect& aRect);
	
private: // Functions from base classes
    //* From CCoeControl	
    void Draw(const TRect& aRect) const;
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
	TKeyResponse OfferKeyEventL(	const TKeyEvent& aKeyEvent, TEventCode aType );	

private: // New Functions
	void LoadListL();
    void StoreSettingsL();
    
	void CreateSkinFolderItem(TInt aSettingId);
	void CreateSkinChooseItem(TInt aSettingId);
	void CreateSaveFolderItem(TInt aSettingId);
	
	void LoadConfigL();
	void SaveL();
    
private: // Data members
	CAknSettingItemList* iItemList;
	
    TFileName iSkinFolder;    
    TInt iSkinChoose;
    TFileName iFileSkinChoose;    
    TFileName iSaveFolder;
    
    CSkinImageScan* iScaner;
    CConfiguration* iConfig;
    
	};

#endif // YCSETTINGCONTAINER_H
