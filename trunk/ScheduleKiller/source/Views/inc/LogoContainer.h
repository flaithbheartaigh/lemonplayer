/*
 ============================================================================
 Name		: LogoContainer.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLogoContainer declaration
 ============================================================================
 */

#ifndef LOGOCONTAINER_H
#define LOGOCONTAINER_H

// INCLUDES
#include <coecntrl.h>

// CLASS DECLARATION
class CFbsBitmap;

/**
 *  CLogoContainer
 * 
 */
class CLogoContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CLogoContainer();

	/**
	 * Two-phased constructor.
	 */
	static CLogoContainer* NewL(const TRect& aRect);

	/**
	 * Two-phased constructor.
	 */
	static CLogoContainer* NewLC(const TRect& aRect);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CLogoContainer();

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
	void HandleResourceChange( TInt aType );

private:
	//data
	CFbsBitmap* iLogo;
	};

#endif // LOGOCONTAINER_H
