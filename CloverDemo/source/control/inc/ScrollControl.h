/*
 ============================================================================
 Name		: ScrollControl.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CScrollControl declaration
 ============================================================================
 */

#ifndef SCROLLCONTROL_H
#define SCROLLCONTROL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "BaseControl.h"
// CLASS DECLARATION
class CListBoxPainter;

/**
 *  CScrollControl
 * 
 */
class CScrollControl : public CBaseControl
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CScrollControl();

	/**
	 * Two-phased constructor.
	 */
	static CScrollControl* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CScrollControl* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CScrollControl();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	//from base
	virtual void Draw(CBitmapContext& gc) const;
	
	//new func
	TBool CheckScroll() const;
	
	void SetPainter(CListBoxPainter* aPainter) {iPainter = aPainter;}
	
	void SetPosition(const TInt& aTotal,const TInt& aStart,const TInt& aEnd)
		{
		iTotal 	= aTotal;
		iStart 	= aStart;
		iEnd	= aEnd;
		}
	
	void StartAnimationScroll();	
	TInt AnimationScroll();	
	static TInt CallbackAnimationScroll( TAny* aThis );
	
private:
	TInt 	iTotal;
	TInt 	iStart;
	TInt 	iEnd;
	
	CListBoxPainter* iPainter;	//not own 
	
	TInt iAlpha;
	
	TInt iItemScrollFrame;
	
	TCallBack* iCallFunc;		//not own
	};

#endif // SCROLLCONTROL_H
