/*
 ============================================================================
 Name		: ImageRotator.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CImageRotator implementation
 ============================================================================
 */
#include <w32std.h>
#include <bitstd.h>
#include <bitdev.h>
#include <libc\math.h>
#include "ImageRotator.h"
#include "MacroUtil.h"

#define PI 3.1415926

CImageRotator::CImageRotator(CFbsBitmap *aSrcBitmap, 
		CFbsBitmap*& aDestBitmap, 
		CFbsBitmap*& aMaskBitmap,
		TInt aDegree, TRgb aBackColor, TBool aFilp) :
	iSrcBitmap(aSrcBitmap), iDestBitmap(aDestBitmap), iMaskBitmap(aMaskBitmap),
	iDegree(aDegree), iBackColor(aBackColor), iFlip(aFilp)
	{
	// No implementation required
	}

CImageRotator::~CImageRotator()
	{
	SAFE_DELETE(iTransparent);
	}

CImageRotator* CImageRotator::NewLC(CFbsBitmap *aSrcBitmap, 
		CFbsBitmap*& aDestBitmap, 
		CFbsBitmap*& aMaskBitmap,
		TInt aDegree, TRgb aBackColor, TBool aFilp)
	{
	CImageRotator* self = new (ELeave)CImageRotator(aSrcBitmap,aDestBitmap,aMaskBitmap,aDegree, aBackColor, aFilp);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CImageRotator* CImageRotator::NewL(CFbsBitmap *aSrcBitmap, 
		CFbsBitmap*& aDestBitmap, 
		CFbsBitmap*& aMaskBitmap,
		TInt aDegree, TRgb aBackColor, TBool aFilp)
	{
	CImageRotator* self=CImageRotator::NewLC(aSrcBitmap, aDestBitmap,aMaskBitmap, aDegree, aBackColor, aFilp);
	CleanupStack::Pop(); // self;
	return self;
	}

void CImageRotator::ConstructL()
	{
	iDestBitmap = new ( ELeave ) CFbsBitmap();
	//	CleanupStack::PushL(iBitmap);

	CalculateSize();
	iRotatePosX = -(iSize.iWidth>>1);
	iRotatePosY = -(iSize.iHeight>>1);

	User::LeaveIfError(iDestBitmap->Create(iSize, iSrcBitmap->DisplayMode()) );

	SetBackColor();
	CopyPixel();
	
	iTransparent = CTransparentBitmap::NewL(iDestBitmap,iMaskBitmap,KRgbMagenta);
	}

void CImageRotator::CalculateSize()
	{
	iRadian = (2* PI *iDegree)/360;

	sine = sin(iRadian);
	cosine = cos(iRadian);
	TInt width = iSrcBitmap->SizeInPixels().iWidth;
	TInt height = iSrcBitmap->SizeInPixels().iHeight;

	TInt x0 = 0;
	TInt y0 = 0;
	TInt x1 = (int)(height * sine);
	TInt y1 = (int)(height * cosine);
	TInt x2 = (int)(width * cosine + height * sine);
	TInt y2 = (int)(height * cosine - width * sine);
	TInt x3 = (int)(width * cosine);
	TInt y3 = (int)(-width * sine);

	minx = Min(x0, Min(x1, Min(x2, x3)));
	miny = Min(y0, Min(y1, Min(y2, y3)));
	maxx = Max(x0, Max(x1, Max(x2, x3)));
	maxy = Max(y0, Max(y1, Max(y2, y3)));

	iSize.iWidth = maxx - minx;
	iSize.iHeight = maxy - miny;

	if (minx < 0)
		{
		iDx = -minx;
		}
	if (miny < 0)
		{
		iDy = -miny;
		}
	}

void CImageRotator::SetBackColor()
	{
	CFbsBitmapDevice *iGD = CFbsBitmapDevice::NewL(iDestBitmap);
	CleanupStack::PushL(iGD);
	CFbsBitGc *iGC;
	User::LeaveIfError(iGD->CreateContext(iGC) );

	iGC->SetPenStyle(CGraphicsContext::ENullPen);
	iGC->SetBrushColor(iBackColor);
	iGC->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iGC->DrawRect(TRect(TPoint(0, 0), iDestBitmap->SizeInPixels()) );
	iGC->SetBrushStyle(CGraphicsContext::ENullBrush);

	delete iGC;
	CleanupStack::PopAndDestroy(iGD);
	}

void CImageRotator::CopyPixel()
	{
	TInt width = iSrcBitmap->SizeInPixels().iWidth;
	TInt height = iSrcBitmap->SizeInPixels().iHeight;

	sine = -sine;
	TBitmapUtil orig_util(iSrcBitmap);
	TBitmapUtil dest_util(iDestBitmap);
	orig_util.Begin(TPoint(0, 0));
	dest_util.Begin(TPoint(0, 0), orig_util);
	for (TInt y=miny; y<maxy; y++)
		for (TInt x=minx; x<maxx; x++)
			{
			TInt srcx = (TInt)(x*cosine + y*sine);
			TInt srcy = (TInt)(y*cosine - x*sine);
			TInt destx = x+iDx;
			TInt desty = y+iDy;
			if (iFlip) {
				desty = iSize.iHeight - desty;
			}

			if (srcx>=width || srcx<0 || srcy>=height || srcy<0)
				{
				}
			else
				{
				orig_util.SetPos(TPoint(srcx, srcy));
				dest_util.SetPos(TPoint(destx, desty));
				dest_util.SetPixel(orig_util);
				}
			}
	orig_util.End();
	dest_util.End();
	sine = -sine;
	}

CFbsBitmap* CImageRotator::Bitmap()
	{
	return iDestBitmap;
	}



void CImageRotator::SetRetatePos(TInt aRotatePosX, TInt aRotatePosY)
	{
	iRotatePosX = (TInt)(aRotatePosX*cosine + aRotatePosY*sine)-aRotatePosX;
	iRotatePosY = (TInt)(aRotatePosY*cosine - aRotatePosX*sine)-aRotatePosY;
	}

void CImageRotator::SetRetateCenter()
	{
	SetRetatePos(iSize.iWidth>>1,iSize.iHeight>>1);
	}

void CImageRotator::Draw(CWindowGc& gc, TInt aX, TInt aY)
	{
//	gc.BitBlt(TPoint(aX-iDx-iRotatePosX, aY-iDy-iRotatePosY), iBitmap);
	iTransparent->Draw(gc,aX-iDx-iRotatePosX,aY-iDy-iRotatePosY);
	}

void CImageRotator::DrawCenter(CWindowGc& gc, TInt aX, TInt aY)
	{
	TInt x = aX-(iSize.iWidth>>1)-iDx;
	TInt y = aY-(iSize.iHeight>>1)-iDy;
//	gc.BitBlt(TPoint(x, y), iBitmap);
	iTransparent->Draw(gc,x,y);
	}

TInt CImageRotator::GetOffsetX()
	{
	return iRotatePosX;
	}
TInt CImageRotator::GetOffsetY()
	{
	return iRotatePosY;
	}
