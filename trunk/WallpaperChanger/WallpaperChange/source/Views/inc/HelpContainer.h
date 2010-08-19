/*
 ============================================================================
 Name		: HelpContainer.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CHelpContainer declaration
 ============================================================================
 */

#ifndef HELPCONTAINER_H
#define HELPCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <eiklabel.h> 
#include <eikrted.h> 
#include <AknsBasicBackgroundControlContext.h> 
#include <aknsdrawutils.h>
#include <aknscontrolcontext.h>
#include <AknsSkinInstance.h>
#include <aknsutils.h>
// CLASS DECLARATION

/**
 *  CHelpContainer
 * 
 */
class CHelpContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CHelpContainer();

	/**
	 * Two-phased constructor.
	 */
	static CHelpContainer* NewL(const TRect& aRect);

	/**
	 * Two-phased constructor.
	 */
	static CHelpContainer* NewLC(const TRect& aRect);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CHelpContainer();

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
	
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

	TBool ReadTextL();
	
	void Prepare();
	void SetupL();
	void IntroL();
	void SetAlignment(CParaFormat::TAlignment aAlignment);
	void SetColor(TRgb aColor);
	void SetFontAndColor(const CFont* aFont,TRgb aColor);
	
private:
	//data
	HBufC* 		iText;
//	CEikLabel*  iCaption ;
	CEikRichTextEditor* iRtEd; // Rich Text Editor
	
	CAknsBasicBackgroundControlContext* iBgContext;
	};

#endif // HELPCONTAINER_H
