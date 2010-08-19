/*
 ============================================================================
 Name		: TangImageManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageManager declaration
 				TangramÕº∆¨π‹¿Ì.
 ============================================================================
 */

#ifndef TANGIMAGEMANAGER_H
#define TANGIMAGEMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <coedef.h>
#include "TangImageDefine.h"
#include "ImageArrayReader.h"
#include "MSaveScreenNotify.h"
// CLASS DECLARATION
class CImageElement;
class CTangImageDataReader;
class CTangImageSave;
class CAlphaBackground;
class CSlideshow;
class CTangImageData;

/**
 *  CTangImageManager
 * 
 */
class CTangImageManager : public CBase ,
							public MSaveScreenNotify
	{
public:
	// Constructors and destructor

	~CTangImageManager();
	static CTangImageManager* NewL();
	static CTangImageManager* NewLC();
	
	//MSaveScreenNotify
	virtual void SaveComplete();
	
	void InitOpenGL(CCoeControl* aParentControl, RWindow* aParentWindow);
	
	void LoadImageDataFileL(const TDesC& aFileName);
	void Draw(CBitmapContext& aGc) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void Rotate(TInt aIndex,TInt aDegree);
	void Flip(TInt aIndex);
	
	
	TInt GetConvertDown();
	
	void SaveProcessL();
	void ResetProcessL();
	void OpenProcessL();
	void SaveScreenL();
	void SaveScreenL(CFbsBitmap *aBitmap);

private:
	CTangImageManager();
	void ConstructL();
	
	TKeyResponse KeyChoose(const TKeyEvent& aKeyEvent,TEventCode aType);
	TKeyResponse KeyMove(const TKeyEvent& aKeyEvent,TEventCode aType);
	TKeyResponse KeyScroll(const TKeyEvent& aKeyEvent);
	


	TInt OffsetAccel(/*EImageElementState aDirection*/);
	void ResetAccel();
	TInt OffsetDegreeAccel();
	void ResetDegreeAccel();
	
	enum TSelectedState
		{
		ESelectedStateMove,
		ESelectedStateChoose
		};	
	
private:
	CTangImageData* iImageData;
	CImageElement** iElements;
	CTangImageDataReader* iDataArray;
	CTangImageSave* iScreenSave;
	
//	TInt iSelectedIndex;
	TSelectedState iSelectedState;
	
	TInt iWaitDlgId;

	TInt iAcceleration;
	TInt iDegreeAcceleration;

	TInt iScrollX;
	TInt iScrollY;
	
	CSlideshow* iRender;
	
	};

#endif // TANGIMAGEMANAGER_H
