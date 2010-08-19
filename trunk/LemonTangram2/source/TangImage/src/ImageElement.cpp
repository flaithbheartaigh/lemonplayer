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
:iCenterX(0),iCenterY(0),
iState(KImageStateNone),iDegree(0),iSelected(EFalse),iFlip(EFalse)
	{
	// No implementation required
	}

CImageElement::~CImageElement()
	{
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

void CImageElement::SetDegree(TInt aDegree)
	{
	iDegree = aDegree;
	if (iDegree > 360)
		iDegree -= 360;
	else if(iDegree < 0)
		iDegree += 360;
	}
