/*
 ============================================================================
 Name		: ImageArrayReader.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CImageArrayReader declaration
 ============================================================================
 */

#ifndef IMAGEARRAYREADER_H
#define IMAGEARRAYREADER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "ImageConvertorInterface.h"
#include "DefaultDocHandler.h"
#include "ImageArrayReaderDef.h"
// CLASS DECLARATION
class CImageConvertor;
/**
 *  CImageArrayReader
 * 
 */
class MImageArrayNotify
	{
public:
	virtual void ConvertError() = 0;
	virtual void ConvertedOne() = 0;
	virtual void ConvertComplete() = 0;
	};

class CImageArrayReader : 	public CBase, public CDefaultDocHandler,
							public MWImageConvertorListener
	{
public:
	// Constructors and destructor

	~CImageArrayReader();
	static CImageArrayReader* NewL();
	static CImageArrayReader* NewLC();

private:
	CImageArrayReader();
	void ConstructL();

public:
	//MWImageConvertorListener
	virtual void OnImageConvertedL(CFbsBitmap &aBitmap);
	virtual void OnImageConvertedL(const TDesC8 &aImgData);
	virtual void OnConvertErrorL(TConvertResult aConvertResult);

	//CDefaultDocHandler
	virtual void StartElement(const TQualified& aName,
			const RArray<TAttribute>& aAttributes);
	virtual void EndElement(const TQualified& aName);

public:
	void LoadDataFromFile(const TDesC& aFileName);
	
	//	void SetBitmap(TInt index,CFbsBitmap*& aBitmap);
	
private:
	TInt ConvertNameToNumber(const TDesC& aName);	
	
	void ParseImage(const RArray<TAttribute>& aAttributes);
	void ParseImg(const RArray<TAttribute>& aAttributes);
	
	void ConvertImage();
	void ConvertNext();
	
	void ConstructBitmapL(const TInt aNumber);
	
public:
	CFbsBitmap** GetBitmapArray() const;
	const TInt GetBitmapCount() const;
	
public:
	void SetNotify(MImageArrayNotify* aNotify){iNotify = aNotify;};

private:
	CFbsBitmap** iBitmap;
	TInt iBitmapCount;
	//TInt iCurBitmapIndex;
	TInt iAdjustErr;  //初始为0 ,正确一位 | 1;
	
	CImageConvertor* iConvertor;
	RPointerArray<ImageArrayConvertStruct>  iArray; //把要转换的数据先放入到数组中.
	
	MImageArrayNotify* iNotify;
	};

#endif // IMAGEARRAYREADER_H
