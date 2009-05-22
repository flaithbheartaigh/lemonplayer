/*
 ============================================================================
 Name		: ImageBitmapReader.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CImageBitmapReader implementation
 ============================================================================
 */

#include <AknUtils.h>

#include "ImageBitmapReader.h"

_LIT(KMBMFILE,"\\system\\apps\\Multi\\Multi.mbm");

CImageBitmapReader::CImageBitmapReader()
	{
	// No implementation required
	}

CImageBitmapReader::~CImageBitmapReader()
	{
	if (iBitmap)
		{
		delete iBitmap;
		iBitmap = NULL;
		}
	}

CImageBitmapReader* CImageBitmapReader::NewLC(const TDesC& aFileName)
	{
	CImageBitmapReader* self = new (ELeave)CImageBitmapReader();
	CleanupStack::PushL(self);
	self->ConstructL(aFileName);
	return self;
	}

CImageBitmapReader* CImageBitmapReader::NewL(const TDesC& aFileName)
	{
	CImageBitmapReader* self=CImageBitmapReader::NewLC(aFileName);
	CleanupStack::Pop(); // self;
	return self;
	}

void CImageBitmapReader::ConstructL(const TDesC& aFileName)
	{
	iBitmap=new (ELeave)CFbsBitmap();
	CreateImage(aFileName);
	}

CFbsBitmap* CImageBitmapReader::GetFbsBitmap()
	{
	return iBitmap;
	}

void CImageBitmapReader::CreateImage(const TDesC& aFileName)
	{
	TFileName file(KMBMFILE);
	User::LeaveIfError(CompleteWithAppPath(file));
	User::LeaveIfError(iBitmap->Load(file, NameToId(aFileName)));
	}

/**
 * 大小写还不能判断
 */
TInt32 CImageBitmapReader::NameToId(const TDesC& aFileName)
	{	
	return -1;
	}

void CImageBitmapReader::DoMyBitmapEffect(CFbsBitmap* aBitmap)
	{
	// Lock heap
	// For series 60 2.0 use:
	aBitmap->LockHeap();
	// For series 60 1.0 use:
	//TBitmapUtil bitmapUtil(aBitmap);
	//bitmapUtil.Begin( TPoint(0,0) );


	// Edit bitmap

	TSize bitmapSize = aBitmap->SizeInPixels();

	// NOTE: TUint16* applies to 16bit bitmaps only; the pointer must

	// correspond the bit depth of the bitmap.

	TUint16* bitmapData = (TUint16*)aBitmap->DataAddress();

	for (TInt y = 0; y < bitmapSize.iHeight; y++)
		{
		for (TInt x = 0; x < bitmapSize.iWidth; x++)
			{
			// Increase colour value of each pixel by one
			*bitmapData = ( *bitmapData & 31 ) | // blue
					( ( *bitmapData >> 5 ) & 63 ) | // green
					( ( *bitmapData >> 11 ) & 31 + 1 ); // red
			bitmapData++;
			}
		}

	// Unlock heap
	// For series 60 1.0 use:
	//bitmapUtil.End();
	// For series 60 2.0 use:
	aBitmap->UnlockHeap();

	}

void CImageBitmapReader::DoMyBitmapEffect()
	{
	// Lock heap
	// For series 60 2.0 use:
	iBitmap->LockHeap();
	// For series 60 1.0 use:
	//TBitmapUtil bitmapUtil(aBitmap);
	//bitmapUtil.Begin( TPoint(0,0) );


	// Edit bitmap
	TSize bitmapSize = iBitmap->SizeInPixels();
	// NOTE: TUint16* applies to 16bit bitmaps only; the pointer must

	// correspond the bit depth of the bitmap.
	TUint16* bitmapData = (TUint16*)iBitmap->DataAddress();
	for (TInt y = 0; y < bitmapSize.iHeight; y++)

		{

		for (TInt x = 0; x < bitmapSize.iWidth; x++)

			{

			// Increase colour value of each pixel by one

			*bitmapData = ( *bitmapData & 31 ) | // blue

					( ( *bitmapData >> 5 ) & 63 ) | // green

					( ( *bitmapData >> 11 ) & 31 + 1 ); // red

			bitmapData++;
			}
		}

	// Unlock heap
	// For series 60 1.0 use:
	//bitmapUtil.End();
	// For series 60 2.0 use:
	iBitmap->UnlockHeap();

	}

void CImageBitmapReader::HeaderInfo()
	{
	SEpocBitmapHeader iHeader = iBitmap->Header();
	}

void CImageBitmapReader::DataInfo()
	{

	TInt width = iBitmap->SizeInPixels().iWidth;
	TInt height = iBitmap->SizeInPixels().iHeight;

	TUint16* src = (TUint16*)iBitmap->DataAddress();
	//	TUint32* src = iBitmap->DataAddress();

	//	iBitmap->LockHeap();
	for (TInt y=0; y<height; y++)
		for (TInt x=0; x<width; x++)
			{
			TRgb col;
			iBitmap->GetPixel(col, TPoint(x, y));			
			}

	//	iBitmap->UnlockHeap();
	}
