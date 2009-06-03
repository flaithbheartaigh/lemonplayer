/*
 ============================================================================
 Name		: TangImageSave.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageSave declaration
 ============================================================================
 */

#ifndef TANGIMAGESAVE_H
#define TANGIMAGESAVE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "ImageConvertorInterface.h"
#include <bitstd.h>
#include <bitdev.h>
#include <gdi.h>
// CLASS DECLARATION
class CImageConvertor;
/**
 *  CTangImageSave
 * 
 */
class CTangImageSave : public CBase , public MWImageConvertorListener
	{
public:
	// Constructors and destructor
	~CTangImageSave();
	static CTangImageSave* NewL(const TDesC& aFileName);
	static CTangImageSave* NewLC(const TDesC& aFileName);

private:
	CTangImageSave();
	void ConstructL(const TDesC& aFileName);
	
public:
	//MWImageConvertorListener
	virtual void OnImageConvertedL(CFbsBitmap &aBitmap);
	virtual void OnImageConvertedL(const TDesC8 &aImgData);
	virtual void OnConvertErrorL(TConvertResult aConvertResult);
	
	CFbsBitGc& CreateBufferBitmapL();
	void StartSave();
	
private:
	CImageConvertor* iConvertor;
	TFileName iFileName;
	
	CFbsBitmap* 			iDoubleBufferBmp;		// λͼ����,owned
	CFbsBitmapDevice*   	iDoubleBufferDevice;	// λͼ���������device,owned,
	CFbsBitGc*  			iDoubleBufferGc;		// λͼ������ƻ���,owned

	};

#endif // TANGIMAGESAVE_H
