/*
 ============================================================================
 Name		: ThemeChangeAppContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container class for application.
 ============================================================================
 */

#ifndef __THEMECHANGEAPPCONTAINER_h__
#define __THEMECHANGEAPPCONTAINER_h__

// INCLUDES
#include <coecntrl.h>
#include <eikclb.h> 

class CThemeManager;

class CThemeChangeAppContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor		
	~CThemeChangeAppContainer();
	static CThemeChangeAppContainer* NewL(const TRect& aRect);
	static CThemeChangeAppContainer* NewLC(const TRect& aRect);

public:
	// New functions

public:
	// Functions from base classes
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

private:
	// Functions from base classes
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

	CThemeChangeAppContainer();
	void ConstructL(const TRect& aRect);
	
	void UpdateDisplay();
	void SetIconsL();	
public:
	void Selected();
	void UninstallL();
	void StartServer();
	void StopServer();
	TBool IsServerActive();
	void RefreshServer();
	
private:
	//data
	CEikColumnListBox* iListBox;
	CThemeManager* iThemeManager;
	};

#endif // __THEMECHANGEAPPVIEW_h__
// End of File