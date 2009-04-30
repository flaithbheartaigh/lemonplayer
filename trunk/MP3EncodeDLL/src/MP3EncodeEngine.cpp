/*
 ============================================================================
 Name		: MP3EncodeEngine.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMP3EncodeEngine implementation
 ============================================================================
 */

#include "MP3EncodeEngine.h"
#include "MP3Encode.h"

CMP3EncodeEngine::CMP3EncodeEngine()
	{
	// No implementation required
	}

CMP3EncodeEngine::~CMP3EncodeEngine()
	{
	delete iMp3Encoder;
	}

EXPORT_C CMP3EncodeEngine* CMP3EncodeEngine::NewLC()
	{
	CMP3EncodeEngine* self = new (ELeave)CMP3EncodeEngine();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

EXPORT_C CMP3EncodeEngine* CMP3EncodeEngine::NewL()
	{
	CMP3EncodeEngine* self=CMP3EncodeEngine::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CMP3EncodeEngine::ConstructL()
	{
	iMp3Encoder = CMP3Encode::NewL();
	}

EXPORT_C TInt CMP3EncodeEngine::Open(const TDesC& aFileWav, const TDesC& aFileMp3)
	{
	if (iMp3Encoder)
		return iMp3Encoder->Open(aFileWav,aFileMp3);
	return KErrNone;
	}

EXPORT_C TInt CMP3EncodeEngine::Open(MMP3EncodeNotifier* aNotifier,const TDesC& aFileMp3)
	{
	if (iMp3Encoder)
		return iMp3Encoder->Open(aNotifier,aFileMp3);
	return KErrNone;
	}

EXPORT_C TInt CMP3EncodeEngine::Close()
	{
	if (iMp3Encoder)
		return iMp3Encoder->Close();
	return KErrNone;
	}
	
EXPORT_C TInt CMP3EncodeEngine::EncodeOneFrame()
	{
	if (iMp3Encoder)
		return iMp3Encoder->EncodeOneFrame();
	return KErrNone;
	}

EXPORT_C TInt CMP3EncodeEngine::GetFileLength()
	{
	if (iMp3Encoder)
		return iMp3Encoder->GetFileLength();
	return -1;
	}

EXPORT_C TInt CMP3EncodeEngine::GetFilePosition()
	{
	if (iMp3Encoder)
		return iMp3Encoder->GetFilePosition();
	return -1;
	}