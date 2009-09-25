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

CImageRotator::CImageRotator(CFbsBitmap *aSrcBitmap, TInt aDegree,
		TRgb aBackColor) :
	iSrcBitmap(aSrcBitmap), iDegree(aDegree), iBackColor(aBackColor)
	{
	// No implementation required
	}

CImageRotator::~CImageRotator()
	{
	SAFE_DELETE(iTransparent);
	SAFE_DELETE(iBitmap);
	}

CImageRotator* CImageRotator::NewLC(CFbsBitmap *aSrcBitmap, TInt aDegree,
		TRgb aBackColor)
	{
	CImageRotator* self = new (ELeave)CImageRotator(aSrcBitmap,aDegree, aBackColor);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CImageRotator* CImageRotator::NewL(CFbsBitmap *aSrcBitmap, TInt aDegree,
		TRgb aBackColor)
	{
	CImageRotator* self=CImageRotator::NewLC(aSrcBitmap, aDegree, aBackColor);
	CleanupStack::Pop(); // self;
	return self;
	}

void CImageRotator::ConstructL()
	{
	iBitmap = new ( ELeave ) CFbsBitmap();
	//	CleanupStack::PushL(iBitmap);

	CalculateSize();

	User::LeaveIfError(iBitmap->Create(iSize, iSrcBitmap->DisplayMode()) );

	//	SetBackColor();
	CopyPixel();
	
	iTransparent = CTransparentBitmap::NewL(iBitmap,KRgbMagenta);
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
	CFbsBitmapDevice *iGD = CFbsBitmapDevice::NewL(iBitmap);
	CleanupStack::PushL(iGD);
	CFbsBitGc *iGC;
	User::LeaveIfError(iGD->CreateContext(iGC) );

	iGC->SetPenStyle(CGraphicsContext::ENullPen);
	iGC->SetBrushColor(iBackColor);
	iGC->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iGC->DrawRect(TRect(TPoint(0, 0), iBitmap->SizeInPixels()) );
	iGC->SetBrushStyle(CGraphicsContext::ENullBrush);

	delete iGC;
	CleanupStack::PopAndDestroy(iGD);
	}

void CImageRotator::CopyPixel()
	{
	TInt width = iSrcBitmap->SizeInPixels().iWidth;
	TInt height = iSrcBitmap->SizeInPixels().iHeight;
	TUint16* src = (TUint16*)iSrcBitmap->DataAddress();
	TUint16* dest = (TUint16*)iBitmap->DataAddress();

	sine = -sine;
	TBitmapUtil orig_util(iSrcBitmap);
	TBitmapUtil dest_util(iBitmap);
	orig_util.Begin(TPoint(0, 0));
	dest_util.Begin(TPoint(0, 0), orig_util);
	for (TInt y=miny; y<maxy; y++)
		for (TInt x=minx; x<maxx; x++)
			{
			TInt srcx = (TInt)(x*cosine + y*sine);
			TInt srcy = (TInt)(y*cosine - x*sine);
			TInt destx = x+iDx;
			TInt desty = y+iDy;

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
	return iBitmap;
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

void CImageRotator::Draw(CFbsBitGc& gc, TInt aX, TInt aY)
	{
//	gc.BitBlt(TPoint(aX-iDx-iRotatePosX, aY-iDy-iRotatePosY), iBitmap);
	iTransparent->Draw(gc,aX-iDx-iRotatePosX,aY-iDy-iRotatePosY);
	}

void CImageRotator::DrawCenter(CFbsBitGc& gc, TInt aX, TInt aY)
	{
	TInt x = aX-(iSize.iWidth>>1);
	TInt y = aY-(iSize.iHeight>>1);
//	gc.BitBlt(TPoint(x, y), iBitmap);
	iTransparent->Draw(gc,x,y);
	}
