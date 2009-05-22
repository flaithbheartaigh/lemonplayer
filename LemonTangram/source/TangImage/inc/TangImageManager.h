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
#include "TangImageDefine.h"
#include "ImageArrayReader.h"
// CLASS DECLARATION
class CImageElement;
class CTangImageDataReader;

/**
 *  CTangImageManager
 * 
 */
class CTangImageManager : public CBase , public MImageArrayNotify
	{
public:
	// Constructors and destructor

	~CTangImageManager();
	static CTangImageManager* NewL();
	static CTangImageManager* NewLC();
	
	//MImageArrayNotify
	virtual void ConvertedOne();
	virtual void ConvertComplete();
	
	void LoadImageFromFileL(const TDesC& aFileName);
	void LoadImageDataFileL(const TDesC& aFileName);
	void Draw(CBitmapContext& aGc);
	void Rotate(TInt aIndex,TInt aDegree);
	
	TInt GetConvertedNum(){return iConverted;};
	TInt GetConvertDown(){return iConvertDown;};

private:
	CTangImageManager();
	void ConstructL();
	
private:
	CImageElement** iElements;
	CImageArrayReader* iBitmapArray;
	CTangImageDataReader* iDataArray;

	TInt iConverted;
	TInt iConvertDown;
	
	};

#endif // TANGIMAGEMANAGER_H
