/*
 ============================================================================
 Name		: CLBitmap.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCLBitmap declaration
 ============================================================================
 */

#ifndef CLBITMAP_H
#define CLBITMAP_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <fbs.h>		//CFbsBitmap
#include <gdi.h>		//TDisplayMode 

// CLASS DECLARATION

/**
 *  CCLBitmap
 * 
 */
class CCLBitmap : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CCLBitmap();

	/**
	 * Two-phased constructor.
	 */
	static CCLBitmap* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CCLBitmap* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CCLBitmap();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	TInt Create(const TSize &aSizeInPixels, TDisplayMode aDispMode);
	
	void Scale(CFbsBitmap* aSource);
	
	static CFbsBitmap* Scale(CFbsBitmap* aSource,const TSize &aSizeInPixels, TDisplayMode aDispMode);
	
	CFbsBitmap* Bitmap() const {return iBitmap;};
	
	TBool IsEmputy() const {return iEmputy;};
private:
	CFbsBitmap* iBitmap;
	TBool iEmputy;
	};

#endif // CLBITMAP_H
