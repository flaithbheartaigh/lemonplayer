/*
 ============================================================================
 Name		: LoadDraftContainer.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLoadDraftContainer declaration
 ============================================================================
 */

#ifndef LOADDRAFTCONTAINER_H
#define LOADDRAFTCONTAINER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <eikclb.h> 

// CLASS DECLARATION

/**
 *  CLoadDraftContainer
 * 
 */
class CLoadDraftContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CLoadDraftContainer();

	/**
	 * Two-phased constructor.
	 */
	static CLoadDraftContainer* NewL(const TRect& aRect);

	/**
	 * Two-phased constructor.
	 */
	static CLoadDraftContainer* NewLC(const TRect& aRect);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CLoadDraftContainer();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL(const TRect& aRect);

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

	void UpdateDisplay();
	void SetIconsL();

private:
	//data
	CEikColumnListBox* iListBox;
	};

#endif // LOADDRAFTCONTAINER_H
