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
iState(KImageStateNone),iDegree(0),iSelected(EFalse),iFlip(EFalse)
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
	if (iBitmapRotate && iBitmapMask)
		{
		TInt x,y;
		x = iCenterX + iOffsetX;
		y = iCenterY + iOffsetY;
		TRect rect( TPoint( 0,0 ),iBitmapRotate->SizeInPixels() );
		aGc.BitBltMasked(TPoint(x,y),iBitmapRotate,
				rect,iBitmapMask,ETrue);
		}
	}

void CImageElement::Draw(CBitmapContext& aGc, TInt aScrollX, TInt aScrollY)
	{
	if (iBitmapRotate && iBitmapMask)
		{
		TInt x,y;
		x = iCenterX + iOffsetX + aScrollX;
		y = iCenterY + iOffsetY + aScrollY;
		TRect rect( TPoint( 0,0 ),iBitmapRotate->SizeInPixels() );
		aGc.BitBltMasked(TPoint(x,y),iBitmapRotate,
				rect,iBitmapMask,ETrue);
		}
	}

void CImageElement::SetDegree(TInt aDegree)
	{
	iDegree = aDegree;
	if (iDegree > 360)
		iDegree -= 360;
	};
