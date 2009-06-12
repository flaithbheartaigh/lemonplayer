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

/**
 *  CTangImageManager
 * 
 */
class CTangImageManager : public CBase , public MImageArrayNotify , 
							public MSaveScreenNotify
	{
public:
	// Constructors and destructor

	~CTangImageManager();
	static CTangImageManager* NewL();
	static CTangImageManager* NewLC();
	
	//MImageArrayNotify
	virtual void ConvertedOne();
	virtual void ConvertComplete();
	
	//MSaveScreenNotify
	virtual void SaveComplete();
	
	void LoadImageFromFileL(const TDesC& aFileName);
	void LoadImageDataFileL(const TDesC& aFileName);
	void Draw(CBitmapContext& aGc);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void Rotate(TInt aIndex,TInt aDegree);
	
	TInt GetConvertedNum(){return iConverted;};
	TInt GetConvertDown(){return iConvertDown;};
	
	void SaveProcess();
	void ResetProcess();
	void OpenProcess();
	void SaveScreen();

private:
	CTangImageManager();
	void ConstructL();
	
	TKeyResponse KeyChoose(const TKeyEvent& aKeyEvent,TEventCode aType);
	TKeyResponse KeyMove(const TKeyEvent& aKeyEvent,TEventCode aType);
	
	void ChangeLayer();
	
	enum TSelectedState
		{
		ESelectedStateMove,
		ESelectedStateChoose
		};
	enum TBitmapFocus
		{		
		EBitmapActive = 0,
		EBitmapActiveMask,
		EBitmapFocus,
		EBitmapFocusMask,
		EBitmapFocusTotal
		};
	
private:
	CImageElement** iElements;
	CImageArrayReader* iBitmapArray;
	CTangImageDataReader* iDataArray;
	CTangImageSave* iScreenSave;

	TInt iConverted;
	TInt iConvertDown;
	
	TInt iSelectedIndex;
	TSelectedState iSelectedState;
	
	CFbsBitmap** iBitmapFocus;
	
	RArray<TInt> iLayer;
	
	TInt iWaitDlgId;
	
	};

#endif // TANGIMAGEMANAGER_H
