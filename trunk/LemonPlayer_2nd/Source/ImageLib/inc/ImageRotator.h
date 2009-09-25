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
	static CImageRotator* NewL(CFbsBitmap *aSrcBitmap, TInt aDegree,
			TRgb aBackColor);
	static CImageRotator* NewLC(CFbsBitmap *aSrcBitmap, TInt aDegree,
			TRgb aBackColor);

	void SetRetatePos(TInt aRotatePosX, TInt aRotatePosY);
	void SetRetateCenter();
	CFbsBitmap* Bitmap();


	void Draw(CFbsBitGc& gc, TInt aX, TInt aY);
	void DrawCenter(CFbsBitGc& gc, TInt aX, TInt aY);

private:

	CImageRotator(CFbsBitmap *aSrcBitmap, TInt aDegree, TRgb aBackColor);
	void ConstructL();

	void CalculateSize();
	void SetBackColor();
	void CopyPixel();

private:
	CFbsBitmap *iSrcBitmap;
	TInt iDegree;
	TRgb iBackColor;

	CFbsBitmap *iBitmap;
	TSize iSize;

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

	};

#endif // IMAGEROTATOR_H
