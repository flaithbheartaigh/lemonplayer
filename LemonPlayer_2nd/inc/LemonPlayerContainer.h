/*
 * ============================================================================
 *  Name     : CLemonPlayerContainer from LemonPlayerContainer.h
 *  Part of  : LemonPlayer
 *  Created  : 17.09.2008 by zengcity
 *  Description:
 *     Declares container control for application.
 *  Version  :
 *  Copyright: 
 * ============================================================================
 */

#ifndef LEMONPLAYERCONTAINER_H
#define LEMONPLAYERCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include "AnimationStruct.h"
#include "AnimationEffectAbstract.h"
#include "AnimationEffectDefine.h"
// FORWARD DECLARATIONS
class CAnimationEffectMgr;
class CEikMenuBar;

// CLASS DECLARATION
class CUIManager;
/**
 *  CLemonPlayerContainer  container control class.
 *  
 */
class CLemonPlayerContainer : 	public CCoeControl, MCoeControlObserver,
								public CAnimationStruct,
								public MAnimationEffectNotify
	{
public:
	// Constructors and destructor
	void ConstructL(const TRect& aRect);
	~CLemonPlayerContainer();

public:
	// New functions

public:
	// Functions from base classes
	virtual TBool Tick();
	virtual void Update();
	
public:
	//MAnimationEffectNotify
	virtual TBool UpdateAction();
	virtual void UpdateDisplay(CFbsBitGc& aBitGc);
		
private:
	// Functions from base classes
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
	virtual TKeyResponse OfferKeyEventL(
	                    const TKeyEvent& aKeyEvent,TEventCode aType);

public:
	void StartEffect(EAnimationEffectType aType);
	void DynInitMenuBarL(TInt aResourceId, CEikMenuBar* aMenuBar);
	void HandleCommandL(TInt aCommand);
	
private:
	CUIManager* iUIManager;
	CAnimationEffectMgr* iEffectMgr;
	};

#endif

// End of File
