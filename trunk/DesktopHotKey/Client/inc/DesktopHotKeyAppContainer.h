/*
 ============================================================================
 Name		: DesktopHotKeyAppContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container class for application.
 ============================================================================
 */

#ifndef __DESKTOPHOTKEYAPPCONTAINER_h__
#define __DESKTOPHOTKEYAPPCONTAINER_h__

// INCLUDES
#include <coecntrl.h>

// CLASS DECLARATION
class CDesktopHotKeyAppContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor		
	~CDesktopHotKeyAppContainer();
	static CDesktopHotKeyAppContainer* NewL(const TRect& aRect);
	static CDesktopHotKeyAppContainer* NewLC(const TRect& aRect);

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

	CDesktopHotKeyAppContainer();
	void ConstructL(const TRect& aRect);

private:
	//data

	};

#endif // __DESKTOPHOTKEYAPPVIEW_h__
// End of File
