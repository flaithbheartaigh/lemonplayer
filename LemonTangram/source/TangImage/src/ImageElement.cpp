/*
 ============================================================================
 Name		: ImageElement.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CImageElement implementation
 ============================================================================
 */

#include "ImageElement.h"
#include "MacroUtil.h"
#include <eikenv.h>

CImageElement::CImageElement()
:iCenterX(0),iCenterY(0),iBitmapLoad(NULL),iBitmapRotate(NULL),iBitmapMask(NULL),
iState(KImageStateNone),iDegree(0),iSelected(EFalse)
	{
	// No implementation required
	}

CImageElement::~CImageElement()
	{
	SAFE_DELETE(iBitmapLoad);
	SAFE_DELETE(iBitmapRotate);
	SAFE_DELETE(iBitmapMask);
	}

CImageElement* CImageElement::NewLC()
	{
	CImageElement* self = new (ELeave)CImageElement();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CImageElement* CImageElement::NewL()
	{
	CImageElement* self=CImageElement::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CImageElement::ConstructL()
	{

	}

void CImageElement::SetPoistion(const TPoint& aPoint)
	{
	iCenterX = aPoint.iX;
	iCenterY = aPoint.iY;
	}
void CImageElement::SetPointion(TInt aX,TInt aY)
	{
	iCenterX = aX;
	iCenterY = aY;
	}

void CImageElement::Draw(CBitmapContext& aGc)
	{
//	if(iBitmapLoad)
//		aGc.BitBlt(TPoint(iCenterX,iCenterY),iBitmapLoad);
	if (iBitmapRotate && iBitmapMask)
		{
//		aGc.BitBlt(TPoint(iCenterX+iOffsetX,iCenterY+iOffsetY),iBitmapRotate);
		TInt x,y;
		x = iCenterX + iOffsetX;
		y = iCenterY + iOffsetY;
		TRect rect( TPoint( 0,0 ),iBitmapRotate->SizeInPixels() );
//		if (!iSelected)
		aGc.BitBltMasked(TPoint(x,y),iBitmapRotate,
				rect,iBitmapMask,ETrue);
//		if (iSelected)
//			{
//			aGc.SetPenStyle( CGraphicsContext::ESolidPen );
//			aGc.SetPenColor(KRgbRed);	
////			aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
////			aGc.SetBrushColor( KRgbGray );
//			aGc.UseFont(CEikonEnv::Static()->LegendFont());
//			aGc.DrawText(_L("Hell,world"),TPoint(x,y));
//			aGc.DiscardFont();
//			aGc.DrawRect(TRect(x,y,x+10,y+10));
//			}
		}
	}

void CImageElement::SetDegree(TInt aDegree)
	{
	iDegree = aDegree;
	if (iDegree > 360)
		iDegree -= 360;
	};
