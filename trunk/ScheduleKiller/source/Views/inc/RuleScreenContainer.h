/*
 ============================================================================
 Name		: RuleScreenContainer.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRuleScreenContainer declaration
 ============================================================================
 */

#ifndef RULESCREENCONTAINER_H
#define RULESCREENCONTAINER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <eikclb.h> 
#include <aknlists.h> 

// CLASS DECLARATION

/**
 *  CRuleScreenContainer
 * 
 */
class CRuleScreenContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CRuleScreenContainer();

	/**
	 * Two-phased constructor.
	 */
	static CRuleScreenContainer* NewL(const TRect& aRect);

	/**
	 * Two-phased constructor.
	 */
	static CRuleScreenContainer* NewLC(const TRect& aRect);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CRuleScreenContainer();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL(const TRect& aRect);

public:
	// Functions from base classes
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

	TBool Select();
private:
	// Functions from base classes
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

	void UpdateDisplay();
	void SetIconsL();

private:
	//data
	CAknDoubleStyleListBox* iListBox;
	};

#endif // RULESCREENCONTAINER_H
