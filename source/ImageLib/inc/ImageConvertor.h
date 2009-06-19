/*
============================================================================
 Name        : BWImageConvertor.h
 Author      : hts
 Version     :
 Copyright   : BlueWhale
 Description : CBWImageConvertor declaration
============================================================================
*/

#ifndef BWIMAGECONVERTOR_H
#define BWIMAGECONVERTOR_H

#include <f32file.h>
#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib

#include "ImageConvertorInterface.h"

class CImageDecoder;
class CImageEncoder;
class CFrameImageData;
class CBitmapScaler;

const TInt KJpgQuality = 100;

class CImageConvertor : 	public CActive,
						  	public MBWImageConvertor
{
	public:
		~CImageConvertor();
		static CImageConvertor* NewLC();
		static CImageConvertor* NewL();
	private:
		CImageConvertor();
		void ConstructL();
	public: // from MBlueWhaleImageConvertor
		virtual void DecodeFromDataL(const TDesC8 &aSourceData);
		virtual void DecodeFromFileL(const TDesC &aSourceFileName);
		virtual void EncodeToDesL(CFbsBitmap &aBitmap);
		virtual void CancelConvertL(void);
		virtual void SetListener(MWImageConvertorListener *aListener);
		virtual CBase* GetPointer() { return this; };
		
	private: // From CActive
		// Handle completion
		void RunL();
		
		// How to cancel me
		void DoCancel();
		
		// Override to handle leaves from RunL(). Default implementation causes
		// the active scheduler to panic.
		//void RunError(TInt aError);
		
	public:
		//����+����
		void DecodeFromDataL(const TDesC8 &aSourceData,TInt width,TInt height);		
		void DecodeFromFileL(const TDesC &aSourceFileName,CFbsBitmap*& aBitmap);

	private:
		enum TBlueWhaleImageConvertorS602xState
		{
			EDecode = 1,
			EEncode,
			EDecodeScale,
			EError			// Error condition
		};
	private:
		TInt iConvertorState;		// State of the active object
		RFs iFileSystem;

		CImageDecoder *iImgDecoder;	// ����ͼ����� owned
		CImageEncoder *iImgEncoder; // ����ͼ����� owned
		MWImageConvertorListener *iImgDecodeListener;	// ������ 
		CFbsBitmap *iBitmapBuffer;	// ���������λͼ���� owned
		HBufC8 *iEncoderBuffer; // ������������� ĿǰĬ��jpg owned
		HBufC8 *iDecoderBuffer;  //owned
		CFrameImageData *iJpgImgData;//owend
		
		CBitmapScaler *iScaler;		//ͼƬ���� owned
		TInt iScalerWidth;
		TInt iScalerHeight;
};

#endif//BWIMAGECONVERTOR_H
