/*
 ============================================================================
 Name		: CloverDemoAppContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container class for application.
 ============================================================================
 */

#ifndef __CLOVERDEMOAPPCONTAINER_h__
#define __CLOVERDEMOAPPCONTAINER_h__

// INCLUDES
#include <coecntrl.h>
#include <fbs.h>
#include "AnimationFrame.h"
class CCLBitmap;
class QEasingCurve;
class CCLListBox;

// CLASS DECLARATION
class CCloverDemoAppContainer : public CCoeControl, MCoeControlObserver , MAnimationNofity
	{
public:
	// Constructors and destructor		
	~CCloverDemoAppContainer();
	static CCloverDemoAppContainer* NewL(const TRect& aRect);
	static CCloverDemoAppContainer* NewLC(const TRect& aRect);

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
	void HandleResourceChange( TInt aType );

	CCloverDemoAppContainer();
	void ConstructL(const TRect& aRect);
	
	void AnimationCallback();
	
	void InitImgs();
	void DrawImgs() const;
	
	void Start();
	void Stop();
	static TInt Period( TAny* aPtr );
	void DoPeriodTask();	
	void Update();

private:
	//data
	CFbsBitmap* iBitmap;
	CCLBitmap** iImgs;
	CPeriodic* iPeriodicTimer;
	QEasingCurve* iCurve;
	TInt iFrame;
	
	CCLListBox* iListBox;
	};

#endif // __CLOVERDEMOAPPVIEW_h__
// End of File
