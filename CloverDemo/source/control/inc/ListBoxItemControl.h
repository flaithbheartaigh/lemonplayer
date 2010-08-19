/*
 ============================================================================
 Name		: ListBoxItemControl.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxItemControl declaration
 ============================================================================
 */

#ifndef LISTBOXITEMCONTROL_H
#define LISTBOXITEMCONTROL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "BaseControl.h"
#include "ListBoxPainter.h"
// CLASS DECLARATION

/**
 *  CListBoxItemControl
 * 
 */
class CListBoxItemControl : public CBaseControl
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CListBoxItemControl();

	/**
	 * Two-phased constructor.
	 */
	static CListBoxItemControl* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CListBoxItemControl* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CListBoxItemControl();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	//from base
	virtual void Draw(CBitmapContext& gc) const;
	
	//new func
	void SetText(const TDesC& aText);
	void SetPainter(CListBoxPainter* aPainter) {iPainter = aPainter;};
	
	void StartAnimationMarquee();	
	void StopAnimationMarquee();	
	TInt AnimationMarquee();	
	static TInt CallbackAnimationMarquee( TAny* aThis );
	
private:
	CListBoxPainter* iPainter;		//not own
	HBufC* iText;
	
	TInt iItemScrollFrame;
	TInt iItemScrollAnimationIndex;
	TInt iMarqueeOffset;
	
	TCallBack* iCallFunc;		//not own
	};

#endif // LISTBOXITEMCONTROL_H
