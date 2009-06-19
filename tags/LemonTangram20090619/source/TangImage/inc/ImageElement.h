/*
 ============================================================================
 Name		: ImageElement.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CImageElement declaration
 			   TangramÍ¼Æ¬»ù´¡.
 ============================================================================
 */

#ifndef IMAGEELEMENT_H
#define IMAGEELEMENT_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <fbs.h>
#include <w32std.h>

#include "TangImageDefine.h"

// CLASS DECLARATION

/**
 *  CImageElement
 * 
 */
class CImageElement : public CBase
	{
public:
	// Constructors and destructor
	~CImageElement();
	static CImageElement* NewL();
	static CImageElement* NewLC();
	
	
	void SetPoistion(const TPoint& aPoint);
	void SetPointion(TInt aX,TInt aY);
	TInt GetPositionX() const {return iCenterX;};
	TInt GetPositionY() const {return iCenterY;};
	
	void SetState(EImageElementState aState){iState = aState;};
	
	void SetBitmapLoad(CFbsBitmap* aBitmap){iBitmapLoad = aBitmap;};
	void SetBitmapRotate(CFbsBitmap* aBitmap){iBitmapRotate = aBitmap;};
	void SetBitmapMask(CFbsBitmap* aBitmap){iBitmapMask = aBitmap;};
	CFbsBitmap* GetBitmapLoad(){return iBitmapLoad;};	
	CFbsBitmap* GetBitmapRotate() {return iBitmapRotate;};
	CFbsBitmap* GetBitmapMask() {return iBitmapMask;};
	CFbsBitmap*& GetBitmapLoadAdd(){return iBitmapLoad;};
	CFbsBitmap*& GetBitmapRotateAdd() {return iBitmapRotate;};
	CFbsBitmap*& GetBitmapMaskAdd() {return iBitmapMask;};
	
	void SetImageState(EImageElementState aState){iState = aState;};
	EImageElementState GetImageState(){return iState;};
	
	void SetDegree(TInt aDegree);
	TInt GetDegree(){return iDegree;};
	
	void SetOffsetX(TInt aOffset){iOffsetX = aOffset;};
	void SetOffsetY(TInt aOffset){iOffsetY = aOffset;};
	
	void SetIndex(TInt aIndex){iIndex = aIndex;};
	TInt GetIndex(){return iIndex;};
	
	void SetSelected(TBool aSelected){iSelected = aSelected;};
	TBool GetSelected(){return iSelected;};
	
	void Draw(CBitmapContext& aGc);

public:
	CImageElement();
	void ConstructL();
	
private:
	TInt iCenterX;
	TInt iCenterY;
	TInt iOffsetX;
	TInt iOffsetY;
	CFbsBitmap* iBitmapLoad;
	CFbsBitmap* iBitmapRotate;
	CFbsBitmap* iBitmapMask;
	EImageElementState iState;
	TInt iDegree;
	TInt iIndex;
	TBool iSelected;

	};

#endif // IMAGEELEMENT_H
