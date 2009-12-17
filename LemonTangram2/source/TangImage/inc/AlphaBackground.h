/*
 ============================================================================
 Name		: AlphaBackground.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAlphaBackground declaration
 ============================================================================
 */

#ifndef ALPHABACKGROUND_H
#define ALPHABACKGROUND_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <fbs.h>
#include <gdi.h>

// CLASS DECLARATION

/**
 *  CAlphaBackground
 * 
 */
class CAlphaBackground : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CAlphaBackground();

	/**
	 * Two-phased constructor.
	 */
	static CAlphaBackground* NewL(const TSize& aSize);

	/**
	 * Two-phased constructor.
	 */
	static CAlphaBackground* NewLC(const TSize& aSize);

	void Draw(CBitmapContext& aGc);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CAlphaBackground(const TSize& aSize);

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

	void AlphaBackWithColor();
	void BltGrayTexture();
	void BltAlphaTexture();

	TRgb	AlphaColorToRgb(const TRgb& aColor1,const TRgb& aColor2,const TUint8& aAlpha);
	TUint32 AlphaColor(const TRgb& aColor1,const TRgb& aColor2,const TUint8& aAlpha,TDisplayMode aMode);

	TUint32 ColorToInt(const TRgb& aColor,TDisplayMode aMode);
	TRgb    IntToColor(const TUint32& aColor,TDisplayMode aMode);
private:
	CFbsBitmap* iBackground;
	CFbsBitmap* iTexture;

	TSize iScreenSize;
	TRgb iColorBack;

	};

#endif // ALPHABACKGROUND_H
