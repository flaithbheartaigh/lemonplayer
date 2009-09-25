/*
 ============================================================================
 Name		: TransparentBitmap.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTransparentBitmap declaration
 ============================================================================
 */

#ifndef TRANSPARENTBITMAP_H
#define TRANSPARENTBITMAP_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <fbs.h>
// CLASS DECLARATION

/**
 *  CTransparentBitmap
 * 
 */
class CTransparentBitmap : public CBase
	{
public:
	// Constructors and destructor

	~CTransparentBitmap();
	static CTransparentBitmap* NewL(CFbsBitmap *aSrcBitmap,TRgb aColor);
	static CTransparentBitmap* NewLC(CFbsBitmap *aSrcBitmap,TRgb aColor);
	
	void Draw(CFbsBitGc& gc,TInt aX, TInt aY);

private:

	CTransparentBitmap();
	void ConstructL(CFbsBitmap *aSrcBitmap,TRgb& aColor);
	
private:
	TRgb iColor;
	CFbsBitmap *iSrcBitmap;
	CFbsBitmap *iMaskBitmap;

	};

#endif // TRANSPARENTBITMAP_H
