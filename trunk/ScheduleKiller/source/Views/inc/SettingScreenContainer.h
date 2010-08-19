/*
 ============================================================================
 Name		: SettingScreenContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container control for application.
 ============================================================================
 */

#ifndef SETTINGSCREENCONTAINER_H
#define SETTINGSCREENCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <aknsettingitemlist.h> 
// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CSettingScreenContainer  container control class.
 *  
 */
class CSettingScreenContainer : public CAknSettingItemList
	{
public:
	// Constructors and destructor		
	~CSettingScreenContainer();
	static CSettingScreenContainer* NewL(const TRect& aRect);
	static CSettingScreenContainer* NewLC(const TRect& aRect);

//private:
	// New functions
	void ConstructL(const TRect& aRect);
	CSettingScreenContainer();

public:
	// Functions from base classes
	CAknSettingItem* CreateSettingItemL(TInt aSettingId);
	void EditItemL(TBool aCalledFromMenu);
	void EditItemL(TInt aIndex, TBool aCalledFromMenu);
	
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	
	//new fuction	
	TBool Save();
	
	void InitDataFromMain();
	void InitDataFromApp();

private:	
	void ModifyItemL(TInt aIndex);
	
private:	
	TBuf<0x100>		iText;
	TFileName		iRule;
	TInt						iNumber;
	TTime						iDate;
	TBool						iBinary;
	
	};

#endif

