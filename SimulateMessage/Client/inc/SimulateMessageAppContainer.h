/*
 ============================================================================
 Name		: SimulateMessageAppContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container class for application.
 ============================================================================
 */

#ifndef __SIMULATEMESSAGEAPPCONTAINER_h__
#define __SIMULATEMESSAGEAPPCONTAINER_h__

// INCLUDES
#include <coecntrl.h>

// CLASS DECLARATION
class CSimulateMessageAppContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor		
	~CSimulateMessageAppContainer();
	static CSimulateMessageAppContainer* NewL(const TRect& aRect);
	static CSimulateMessageAppContainer* NewLC(const TRect& aRect);

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

	CSimulateMessageAppContainer();
	void ConstructL(const TRect& aRect);

private:
	//data

	};

#endif // __SIMULATEMESSAGEAPPVIEW_h__
// End of File
