/*
 ============================================================================
 Name		: NormalSettingContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container control for application.
 ============================================================================
 */

#ifndef NORMALSETTINGCONTAINER_H
#define NORMALSETTINGCONTAINER_H

// INCLUDE FILES
#include <coecntrl.h>
#include <aknsettingitemlist.h> 
#include "Configuration.h"
// CLASS DECLARATION

/**
* A view class for a dynamic setting list.
*/
class CNormalSettingContainer : public CCoeControl
    {
public: // Constructor and destructor
	enum TSettingItems
		{
		EItemFreqency = 0,
		EItemAutoStart
		};
    /**
    * Symbian OS default constructor.
    */      
	void ConstructL(const TRect& aRect);
	
	/**
	* Constructor
	*/
	CNormalSettingContainer();
	
	/**
	* Destructor
	*/
     ~CNormalSettingContainer();
          
private: // Functions from base classes

	/**
    * From CCoeControl,Draw.
    */
    void Draw(const TRect& aRect) const;

	/**
    * From CoeControl,CountComponentControls.
    */        
    TInt CountComponentControls() const;

	/**
    * From CCoeControl,ComponentControl.
    */
    CCoeControl* ComponentControl(TInt aIndex) const;

	/**
    * From CCoeControl,OfferKeyEventL.
    */
	TKeyResponse OfferKeyEventL(	const TKeyEvent& aKeyEvent, TEventCode aType );
	
	
	
private: // New Functions

	/**
	* Loads the setting list dynamically.
	*/	
	void LoadListL();

	/**
	* Stores the settings of the setting list.
	*/	
public:
	
	void StoreSettingsL();
	TBool IsChange();
	TInt SaveConfig();

private: // Data members

	CAknSettingItemList* iItemList;
	CConfiguration* iConfig;

	TInt						iEnumText;
	TBool						iBinary;
	TInt						iOldEnumText;
	TBool						iOldBinary;
	
    };


#endif

