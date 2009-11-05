/*
 ============================================================================
 Name		: ImageRotator.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CImageRotator declaration
 ============================================================================
 */

#ifndef IMAGEROTATOR_H
#define IMAGEROTATOR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <fbs.h>
#include "TransparentBitmap.h"

// CLASS DECLARATION

/**
 *  CImageRotator
 * 
 */
class CImageRotator : public CBase
	{
public:
	// Constructors and destructor

	~CImageRotator();
	static CImageRotator* NewL(CFbsBitmap *aSrcBitmap, 
			CFbsBitmap*& aDestBitmap,
			CFbsBitmap*& aMaskBitmap,
			TInt aDegree, TRgb aBackColor, TBool aFilp = EFalse);
	static CImageRotator* NewLC(CFbsBitmap *aSrcBitmap, 
			CFbsBitmap*& aDestBitmap, 
			CFbsBitmap*& aMaskBitmap,
			TInt aDegree, TRgb aBackColor, TBool aFilp = EFalse);
	CImageRotator(CFbsBitmap *aSrcBitmap, 
			CFbsBitmap*& aDestBitmap, 
			CFbsBitmap*& aMaskBitmap, 
			TInt aDegree, TRgb aBackColor,TBool aFilp);

	void SetRetatePos(TInt aRotatePosX, TInt aRotatePosY);
	void SetRetateCenter();
	CFbsBitmap* Bitmap();
	TInt GetOffsetX();
	TInt GetOffsetY();


	void Draw(CWindowGc& gc, TInt aX, TInt aY);
	void DrawCenter(CWindowGc& gc, TInt aX, TInt aY);

private:

	
	void ConstructL();

	void CalculateSize();
	void SetBackColor();
	void CopyPixel();

private:
	CFbsBitmap* iSrcBitmap;
	TInt iDegree;
	TRgb iBackColor;

	CFbsBitmap*& iDestBitmap;
	TSize iSize;
	
	CFbsBitmap*& iMaskBitmap;

	TReal64 iRadian;
	TReal64 sine;
	TReal64 cosine;

	TInt minx;
	TInt miny;
	TInt maxx;
	TInt maxy;
	TInt iDx;
	TInt iDy;

	TInt iRotatePosX;
	TInt iRotatePosY;
	
	CTransparentBitmap *iTransparent;

	TInt iFlip;

	};

#endif // IMAGEROTATOR_H
