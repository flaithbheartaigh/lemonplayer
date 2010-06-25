/*
 ============================================================================
 Name		: RemovedScreenContainer.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRemovedScreenContainer declaration
 ============================================================================
 */

#ifndef REMOVEDSCREENCONTAINER_H
#define REMOVEDSCREENCONTAINER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <eikclb.h> 
#include <eikfrlb.h> 
// CLASS DECLARATION

/**
 *  CRemovedScreenContainer
 * 
 */
class CRemovedScreenContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CRemovedScreenContainer();

	/**
	 * Two-phased constructor.
	 */
	static CRemovedScreenContainer* NewL(const TRect& aRect);

	/**
	 * Two-phased constructor.
	 */
	static CRemovedScreenContainer* NewLC(const TRect& aRect);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CRemovedScreenContainer();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL(const TRect& aRect);

public:
	// Functions from base classes
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void ClearRemoved();

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
	CEikFormattedCellListBox* iListBox;
	};

#endif // REMOVEDSCREENCONTAINER_H
