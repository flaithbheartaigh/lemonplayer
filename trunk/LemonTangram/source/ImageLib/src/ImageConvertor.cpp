/*
 ============================================================================
 Name        : BWImageConvertor.cpp
 Author      : hts
 Version     :
 Copyright   : focus
 Description : CBWImageConvertor implementation
 ============================================================================
 */
#include <ImageConversion.h>
#include <eikenv.h>

#include <s32mem.h>
#include <BitmapTransforms.h>

#include "CommonUtils.h"
#include "ImageConvertor.h"
#include "MacroUtil.h"

CImageConvertor::CImageConvertor() :
	CActive(EPriorityStandard), iImgDecoder(NULL), iImgEncoder(NULL),
			iImgDecodeListener(NULL), iBitmapBuffer(NULL),
			iEncoderBuffer(NULL), iDecoderBuffer(NULL), iJpgImgData(NULL),
			iScaler(NULL)
	{
	}

void CImageConvertor::ConstructL()
	{
	iScaler = CBitmapScaler::NewL();
	User::LeaveIfError(iFileSystem.Connect() );
	CActiveScheduler::Add(this); // Add to scheduler
	}

CImageConvertor::~CImageConvertor()
	{
	Cancel();

	delete iImgDecoder;
	iImgDecoder = NULL;

	delete iImgEncoder;
	iImgEncoder = NULL;

	delete iBitmapBuffer;
	iBitmapBuffer = NULL;

	delete iEncoderBuffer;
	iEncoderBuffer = NULL;

	delete iDecoderBuffer;
	iDecoderBuffer = NULL;

	delete iJpgImgData;
	iJpgImgData = NULL;

	if (iScaler)
		{
		delete iScaler;
		iScaler = NULL;
		}

	iFileSystem.Close();
	}

CImageConvertor* CImageConvertor::NewLC()
	{
	CImageConvertor *self = new(ELeave) CImageConvertor();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CImageConvertor* CImageConvertor::NewL()
	{
	CImageConvertor *self = CImageConvertor::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CImageConvertor::DecodeFromDataL(const TDesC8 &aSourceData)
	{
	delete iDecoderBuffer;
	iDecoderBuffer = NULL;
	iDecoderBuffer = aSourceData.AllocL();

	delete iImgDecoder;
	iImgDecoder = NULL;
	iImgDecoder = CImageDecoder::DataNewL(iFileSystem, *iDecoderBuffer);

	TFrameInfo frameInfo = iImgDecoder->FrameInfo();
	TRect rectOfImg = frameInfo.iFrameCoordsInPixels;

	//TDisplayMode displayMode = CEikonEnv::Static()->ScreenDevice()->DisplayMode();
	TDisplayMode displayMode = frameInfo.iFrameDisplayMode;
	delete iBitmapBuffer;
	iBitmapBuffer = NULL;
	iBitmapBuffer = new(ELeave) CFbsBitmap();
	iBitmapBuffer->Create(rectOfImg.Size(), displayMode);

	iImgDecoder->Convert(&iStatus, *iBitmapBuffer);
	iConvertorState = EDecode;
	SetActive();
	}

void CImageConvertor::DecodeFromDataL(const TDesC8 &aSourceData, TInt width,
		TInt height)
	{
	iScalerWidth = width;
	iScalerHeight = height;

	delete iDecoderBuffer;
	iDecoderBuffer = NULL;
	iDecoderBuffer = aSourceData.AllocL();

	delete iImgDecoder;
	iImgDecoder = NULL;
	iImgDecoder = CImageDecoder::DataNewL(iFileSystem, *iDecoderBuffer);

	TFrameInfo frameInfo = iImgDecoder->FrameInfo();
	TRect rectOfImg = frameInfo.iFrameCoordsInPixels;

	//TDisplayMode displayMode = CEikonEnv::Static()->ScreenDevice()->DisplayMode();
	TDisplayMode displayMode = frameInfo.iFrameDisplayMode;
	delete iBitmapBuffer;
	iBitmapBuffer = NULL;
	iBitmapBuffer = new(ELeave) CFbsBitmap();
	iBitmapBuffer->Create(rectOfImg.Size(), displayMode);

	iImgDecoder->Convert(&iStatus, *iBitmapBuffer);
	iConvertorState = EDecodeScale;
	SetActive();
	}

void CImageConvertor::DecodeFromFileL(const TDesC &aSourceFileName)
	{
	if (iImgDecoder)
		{
		delete iImgDecoder;
		iImgDecoder = NULL;
		}
	//	iImgDecoder = CImageDecoder::FileNewL(iFileSystem, aSourceFileName);
	TRAPD(err,iImgDecoder =
			CImageDecoder::FileNewL(CCoeEnv::Static()->FsSession(), aSourceFileName))

	if (err!= KErrNone)
		{
		return;
		}

	TFrameInfo frameInfo = iImgDecoder->FrameInfo();
	TRect rectOfImg = frameInfo.iFrameCoordsInPixels;

	TDisplayMode displayMode = CEikonEnv::Static()->ScreenDevice()->DisplayMode();
	delete iBitmapBuffer;
	iBitmapBuffer = NULL;
	iBitmapBuffer = new(ELeave) CFbsBitmap();
	iBitmapBuffer->Create(rectOfImg.Size(), displayMode);

	iImgDecoder->Convert(&iStatus, *iBitmapBuffer);
	iConvertorState = EDecode;
	SetActive();
	}

void CImageConvertor::EncodeToDesL(CFbsBitmap &aBitmap)
	{
	delete iImgEncoder;
	iImgEncoder = NULL;

	delete iEncoderBuffer;
	iEncoderBuffer = NULL;

	delete iJpgImgData;
	iJpgImgData = NULL;

	iImgEncoder = CImageEncoder::DataNewL(iEncoderBuffer,
			CImageEncoder::EOptionNone, KImageTypeJPGUid);

	TJpegImageData *jpgData = new(ELeave) TJpegImageData();
	CleanupStack::PushL(jpgData);
	jpgData->iQualityFactor = KJpgQuality;
	jpgData->iSampleScheme = TJpegImageData::EColor420;

	iJpgImgData = CFrameImageData::NewL();
	User::LeaveIfError(iJpgImgData->AppendImageData(jpgData) );
	CleanupStack::Pop(jpgData);

	iImgEncoder->Convert(&iStatus, aBitmap, iJpgImgData);
	iConvertorState = EEncode;
	SetActive();
	}

void CImageConvertor::CancelConvertL(void)
	{
	Cancel();
	}

void CImageConvertor::SetListener(MWImageConvertorListener *aListener)
	{
	iImgDecodeListener = aListener;
	}

void CImageConvertor::DoCancel()
	{
	if (iImgDecoder)
		{
		iImgDecoder->Cancel();
		}

	if (iImgEncoder)
		{
		iImgEncoder->Cancel();
		}
	}

void CImageConvertor::RunL()
	{
	if (iStatus.Int() == KErrNone)
		{
		switch (iConvertorState)
			{
			case EDecode:
				{
				if (iImgDecodeListener)
					{
					iImgDecodeListener->OnConvertErrorL(MWImageConvertorListener::EConvertSucceed);
					iImgDecodeListener->OnImageConvertedL(*iBitmapBuffer);
					}
				}
				break;
			case EEncode:
				{
				if (iImgDecodeListener)
					{
					iImgDecodeListener->OnConvertErrorL(MWImageConvertorListener::EConvertSucceed);
					iImgDecodeListener->OnImageConvertedL(*iEncoderBuffer);
					}
				}
				break;
			case EDecodeScale:
				break;
			default:
				;
			}
		}
	else
		if (iStatus.Int() == KErrUnderflow)
			{
			switch (iConvertorState)
				{
				case EDecode:
					{
					if (iImgDecoder)
						{
						iImgDecoder->ContinueConvert(&iStatus);
						iConvertorState = EDecode;
						SetActive();
						}
					//if (iImgDecodeListener)
					//{
					//	iImgDecodeListener->OnConvertErrorL(MWImageConvertorListener::EConvertSucceed);
					//	iImgDecodeListener->OnImageConvertedL(*iBitmapBuffer);
					//}
					}
					break;
				default:
					if (iImgDecodeListener)
						{
						iImgDecodeListener->OnConvertErrorL(MWImageConvertorListener::EConvertError);
						}
				}
			}
		else
			{
			if (iImgDecodeListener)
				{
				iImgDecodeListener->OnConvertErrorL(MWImageConvertorListener::EConvertError);
				}
			}
	}

void CImageConvertor::DecodeFromFileL(const TDesC &aSourceFileName,
		CFbsBitmap*& aBitmap)
	{
	SAFE_DELETE(iImgDecoder);

	//	iImgDecoder = CImageDecoder::FileNewL(iFileSystem, aSourceFileName);
	TRAPD(err,iImgDecoder =
			CImageDecoder::FileNewL(CCoeEnv::Static()->FsSession(), aSourceFileName));

	if (err != KErrNone)
		{
		return;
		}
//	RETURN_ERROR(err);

	TFrameInfo frameInfo = iImgDecoder->FrameInfo();
	TRect rectOfImg = frameInfo.iFrameCoordsInPixels;
	TDisplayMode displayMode = CEikonEnv::Static()->ScreenDevice()->DisplayMode();
	
	SAFE_DELETE(aBitmap);
	aBitmap = new(ELeave) CFbsBitmap();
	aBitmap->Create(rectOfImg.Size(), displayMode);

	iImgDecoder->Convert(&iStatus, *aBitmap);
	iConvertorState = EDecode;
	SetActive();
	}