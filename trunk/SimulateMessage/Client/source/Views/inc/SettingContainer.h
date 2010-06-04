/*
 ============================================================================
 Name		: SettingContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container control for application.
 ============================================================================
 */

#ifndef SETTINGCONTAINER_H
#define SETTINGCONTAINER_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CSettingContainer  container control class.
 *  
 */
class CSettingContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor		
	~CSettingContainer();
	static CSettingContainer* NewL(const TRect& aRect);
	static CSettingContainer* NewLC(const TRect& aRect);

private:
	// New functions
	void ConstructL(const TRect& aRect);
	CSettingContainer();

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

private:
	//data
	};

#endif

