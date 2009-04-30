/*
 ============================================================================
 Name		: StreamPlayer.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CStreamPlayer implementation
 ============================================================================
 */

#include "StreamPlayerdapter.h"

CStreamPlayer::CStreamPlayer(void) :
	iVolume(10), iReadSize(0), iPlayError(KErrNone)
	{
	}

CStreamPlayer::~CStreamPlayer()
	{
	Stop();

	delete iStream;
	iStream = NULL;

	delete iPlayBuffer;
	iPlayBuffer = NULL;

	iBuffer.ResetAndDestroy();
	}

void CStreamPlayer::PlayL(const TDesC8& aPlayBuffer)
	{
	Stop();
	iReadSize = 0;

	delete iPlayBuffer;
	iPlayBuffer = NULL;

	delete iStream;
	iStream = NULL;

	iBuffer.ResetAndDestroy();

	iPlayBuffer = HBufC8::NewL(aPlayBuffer.Length());
	iPlayBuffer->Des().Copy(aPlayBuffer);

	TDes8* buffer = new(ELeave) TBuf8<KPcmBufferSize>;
	buffer->SetMax();
	CleanupStack::PushL(buffer);
	User::LeaveIfError(iBuffer.Append(buffer));
	CleanupStack::Pop(buffer);

	buffer = new(ELeave) TBuf8<KPcmBufferSize>;
	buffer->SetMax();
	CleanupStack::PushL(buffer);
	User::LeaveIfError(iBuffer.Append(buffer));
	CleanupStack::Pop(buffer);

	iReadSize = 0;
	iCurrIndex = 0;
	for (TInt index = 0; index < iBuffer.Count(); index++)
		{
		ReadFromFromL(index);
		}

	iStream = CMdaAudioOutputStream::NewL(*this);
	iStream->Open(&iSettings);
	}

void CStreamPlayer::Stop()
	{
	if (iStream)
		iStream->Stop();
	}

void CStreamPlayer::SetVolume(TInt aVol)
	{
	iVolume = aVol;

	if (iVolume < 0)
		iVolume = 0;
	else
		if (iVolume > 10)
			iVolume = 10;

	if (iStream)
		{
		iStream->SetVolume(((iStream->MaxVolume() * iVolume) / 10));
		}
	}

void CStreamPlayer::MaoscOpenComplete(TInt aError)
	{
	iPlayError = aError;

	if (aError==KErrNone && iStream)
		{
		iSettings.iSampleRate = TMdaAudioDataSettings::ESampleRate8000Hz;
		iSettings.iChannels = TMdaAudioDataSettings::EChannelsMono;
		//iSettings.iVolume = ((iStream->MaxVolume() * iVolume) / 10);

		iStream->SetAudioPropertiesL(iSettings.iSampleRate, iSettings.iChannels);
		SetVolume(iVolume);
		iStream->SetPriority(EPriorityNormal, EMdaPriorityPreferenceNone);

		iStream->WriteL(*iBuffer[0]);
		}
	}

void CStreamPlayer::MaoscBufferCopied(TInt aError, const TDesC8& aBuffer)
	{
	iPlayError = aError;

	if (aError == KErrNone && iStream)
		{
		if (&aBuffer == iBuffer[0])
			{
			iCurrIndex = 0;

			if ((*iBuffer[1]).Length())
				{
				iStream->WriteL(*iBuffer[1]);
				ReadFromFromL(0);
				}
			}
		else// if (&aBuffer == iBuffer[1])
			{
			iCurrIndex = 1;

			if ((*iBuffer[0]).Length())
				{
				iStream->WriteL(*iBuffer[0]);
				ReadFromFromL(1);
				}
			}
		}
	}

void CStreamPlayer::MaoscPlayComplete(TInt aError)
	{
	iPlayError = aError;

	if (aError == KErrUnderflow)
		{
		if (iPlayBuffer->Des().Length() > iReadSize)
			{
			iCurrIndex = 0;
			for (TInt index = 0; index < iBuffer.Count(); index++)
				{
				ReadFromFromL(index);
				}

			iStream->WriteL(*iBuffer[0]);
			}
		}
	}

void CStreamPlayer::ReadFromFromL(TInt aBufferIndex)
	{
	if (aBufferIndex ==0 || aBufferIndex == 1 && iPlayBuffer)
		{
		(*iBuffer[aBufferIndex]).FillZ();
		(*iBuffer[aBufferIndex]).Zero();

		if (iPlayBuffer->Des().Length() > iReadSize)
			{
			TInt ReadFor(KPcmBufferSize);
			if (iPlayBuffer->Des().Length() < (iReadSize + ReadFor))
				{
				ReadFor = iPlayBuffer->Des().Length() - iReadSize;
				}
			(*iBuffer[aBufferIndex]).Copy(iPlayBuffer->Des().Mid(iReadSize, ReadFor));
			iReadSize = iReadSize + ReadFor;
			}
		}
	}
