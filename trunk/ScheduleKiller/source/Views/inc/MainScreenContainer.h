/*
 ============================================================================
 Name		: MainScreenContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container control for application.
 ============================================================================
 */

#ifndef MAINSCREENCONTAINER_H
#define MAINSCREENCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <GULICON.H>	//CGulIcon

#include <AknsBasicBackgroundControlContext.h> 
#include <aknsdrawutils.h>
#include <aknscontrolcontext.h>
#include <AknsSkinInstance.h>
#include <aknsutils.h>
// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CMainScreenContainer  container control class.
 *  
 */
class CMainScreenContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor		
	~CMainScreenContainer();
	static CMainScreenContainer* NewL(const TRect& aRect);
	static CMainScreenContainer* NewLC(const TRect& aRect);

private:
	// New functions
	void ConstructL(const TRect& aRect);
	CMainScreenContainer();

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
	
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

	void DrawClock() const;
	void DrawApp() const;
	void DrawClockDigital(TInt& aNumber,const TPoint& aPoint) const;
	
	TInt ParseLeftTime(TInt aSecend,RArray<TInt>& aArray ) const;
	TInt ParseNumber(TInt aNumber,RArray<TInt>& aArray) const;
	
	void InitClockDigital();
	void InitIcon();
	void InitTest();
	
	void KillProcess();
	
	void Start();
	void Stop();
	static TInt Period( TAny* aPtr );
	void DoPeriodTask();	
	void Update();
private:
	//data
	RPointerArray<CGulIcon> *iClock;
	CGulIcon* iIcon;
	CPeriodic* iPeriodicTimer;
	
	TBool	iInitIcon;
	
	CAknsBasicBackgroundControlContext* iBgContext;
	};

#endif

