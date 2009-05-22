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

CImageElement::CImageElement()
:iCenterX(0),iCenterY(0),iBitmapLoad(NULL),iBitmapRotate(NULL),iBitmapMask(NULL),
iState(KImageStateNone),iDegree(0)
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
		TRect rect( TPoint( 0,0 ),iBitmapRotate->SizeInPixels() );
		aGc.BitBltMasked(TPoint(iCenterX+iOffsetX,iCenterY+iOffsetY),iBitmapRotate,
				rect,iBitmapMask,ETrue);
		}
	}

void CImageElement::SetDegree(TInt aDegree)
	{
	iDegree = aDegree;
	if (iDegree > 360)
		iDegree -= 360;
	};
