/*
============================================================================
 Name        : BWImageConvertor.h
 Author      : hts
 Version     :
 Copyright   : focus
 Description : MBWImageConvertor - header file
============================================================================
*/

#ifndef BWIMAGECONVERTORINTERFACE_H
#define BWIMAGECONVERTORINTERFACE_H


// INCLUDES
#include <fbs.h>
#include <e32std.h>

// FORWARD DECLARATIONS
//class MyClass;

// CLASS DECLARATION
class MWImageConvertorListener
{
	public:
		enum TConvertResult
		{
			EConvertSucceed,
			EConvertError
		};
	public:
		virtual void OnImageConvertedL(CFbsBitmap &aBitmap) = 0;
		virtual void OnImageConvertedL(const TDesC8 &aImgData) = 0;
		virtual	void OnConvertErrorL(TConvertResult aConvertResult) = 0;
};

class MBWImageConvertor
{
	public:
		virtual void DecodeFromDataL(const TDesC8 &aSourceData) = 0;
		virtual void DecodeFromFileL(const TDesC &aSourceFileName) = 0;
		virtual void EncodeToDesL(CFbsBitmap &aBitmap) = 0;
		virtual void CancelConvertL(void) = 0;
		virtual void SetListener(MWImageConvertorListener *aListener) = 0;
		virtual ~MBWImageConvertor(){}// = 0;
};

#endif // BWIMAGECONVERTORINTERFACE_H

// End of File
