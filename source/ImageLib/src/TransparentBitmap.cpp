/*
 ============================================================================
 Name		: TransparentBitmap.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTransparentBitmap implementation
 ============================================================================
 */

#include "TransparentBitmap.h"

CTransparentBitmap::CTransparentBitmap(CFbsBitmap *aSrcBitmap,CFbsBitmap*& aMaskBitmap,TRgb& aColor)
:iSrcBitmap(aSrcBitmap),iMaskBitmap(aMaskBitmap),iColor(aColor)
{
	// No implementation required
	}

CTransparentBitmap::~CTransparentBitmap()
	{
	}

CTransparentBitmap* CTransparentBitmap::NewLC(CFbsBitmap *aSrcBitmap,
		CFbsBitmap*& aMaskBitmap, TRgb aColor)
	{
	CTransparentBitmap* self = new (ELeave)CTransparentBitmap(aSrcBitmap,aMaskBitmap,aColor);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTransparentBitmap* CTransparentBitmap::NewL(CFbsBitmap *aSrcBitmap,
		CFbsBitmap*& aMaskBitmap, TRgb aColor)
	{
	CTransparentBitmap* self=CTransparentBitmap::NewLC(aSrcBitmap,aMaskBitmap,aColor);
	CleanupStack::Pop(); // self;
	return self;
	}

void CTransparentBitmap::ConstructL()
	{
	iMaskBitmap = new (ELeave) CFbsBitmap;
	User::LeaveIfError(iMaskBitmap->Create(iSrcBitmap->SizeInPixels(), 
			EGray2 ));
	
	TInt width  = iSrcBitmap->SizeInPixels().iWidth;
	TInt height = iSrcBitmap->SizeInPixels().iHeight;
	
	TBitmapUtil butil(iMaskBitmap);
	butil.Begin(TPoint(0,0));
	for(TInt y=0; y<height; y++)
		for(TInt x=0; x<width; x++)
			{
			TRgb col;
			iSrcBitmap->GetPixel(col,TPoint(x,y));
			butil.SetPos(TPoint(x,y));
			if(col == iColor)
				{butil.SetPixel(KRgbWhite.Value());}
			else
				{butil.SetPixel(KRgbBlack.Value());}
			}
	butil.End();
	}

void CTransparentBitmap::Draw(CWindowGc& gc,TInt aX, TInt aY)
	{
//	gc.BitBlt(TPoint(aX,aY),iMaskBitmap);
	TRect sourceRect( TPoint( 0,0 ),iSrcBitmap->SizeInPixels() );
	gc.BitBltMasked(TPoint(aX,aY),iSrcBitmap,sourceRect,iMaskBitmap,ETrue);
	}
