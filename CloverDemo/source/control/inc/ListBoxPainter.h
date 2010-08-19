/*
 ============================================================================
 Name		: ListBoxPainter.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxPainter declaration
 ============================================================================
 */

#ifndef LISTBOXPAINTER_H
#define LISTBOXPAINTER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <GDI.H>
// CLASS DECLARATION

/**
 *  CListBoxPainter
 * 
 */

const TInt KItemAnimationFrame = 4;

class CListBoxPainter : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CListBoxPainter();

	/**
	 * Two-phased constructor.
	 */
	static CListBoxPainter* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CListBoxPainter* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CListBoxPainter();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

public:
	const CFont* GetFont() ;
	
	void SetWidth (const TInt& aWidth) {iWidth = aWidth; }
	TInt GetWidth() const {return iWidth;};
	
	TInt GetItemHeight();
	
	TRgb GetHightLightClock() {return KRgbGray;}
	TRgb GetTextColor() {return KRgbRed;};
	
	TInt GetAnimationItemScrollFrame() const {return KItemAnimationFrame;}
	
	TInt GetAnimationScrollStartFadeFrame() const {return KItemAnimationFrame * 6;}
	TInt GetAnimationScrollFrame() const {return KItemAnimationFrame * 10;}
	TInt GetScrollWidth() const {return 8;}
	
	TInt GetAnimationMarqueeStartFrame() const {return KItemAnimationFrame * 4;}
private:
	TInt iWidth;
	TInt iItemHeight;
	TInt iItemPadding;
	};

#endif // LISTBOXPAINTER_H
