/*
 ============================================================================
 Name		: BasicSound.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CBasicSound implementation
 ============================================================================
 */

#include "BasicSound.h"

CBasicSound::CBasicSound():
	iState(ENotReady)
	{
	// No implementation required
	}

CBasicSound::~CBasicSound()
	{
	if (iMdaPlayer)
		{
		delete iMdaPlayer;
		iMdaPlayer = NULL;
		}
	}

CBasicSound* CBasicSound::NewLC()
	{
	CBasicSound* self = new (ELeave)CBasicSound();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CBasicSound* CBasicSound::NewL()
	{
	CBasicSound* self=CBasicSound::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CBasicSound::ConstructL()
	{

	}

TInt CBasicSound::LoadFile(const TDesC& aFileName)
	{
	if (iMdaPlayer)
		{
		delete iMdaPlayer;
		}
	iState = ENotReady;
	TRAPD(error,iMdaPlayer = CMdaAudioPlayerUtility::NewFilePlayerL(aFileName,*this))
	;
	return error;
	}

void CBasicSound::MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/)
{
   iState = aError ? ENotReady : EReady;
   iMaxVolume = iMdaPlayer->MaxVolume();
   if (iNotify)
	   {
	   iNotify->InitComplete();
	   }
}

void CBasicSound::MapcPlayComplete(TInt aError)
{
   iState = aError ? ENotReady : EReady;
   if (iNotify)
	   {
	   iNotify->PlayComplete();
	   }
}

void CBasicSound::SetListerner(MSoundCallBack *aNotify)
	{
	iNotify = aNotify;
	}

TInt CBasicSound::Play()
{
   if(iState==EReady || iState==EPause)
   {
       iState=EPlaying;
       iMdaPlayer->Play();
   }
   return KErrNone;
}

TInt CBasicSound::Stop()
{
   if(iState==EPlaying)
   {
       iState=EReady;
       iMdaPlayer->Stop();
   }
   return KErrNone;
}

TInt CBasicSound::Pause()
{
   if(iState==EPlaying)
   {
       iState=EPause;
       iMdaPlayer->Pause();
   }
   return KErrNone;
}

void CBasicSound::SetVolume(TInt aVolume)
	{
	iMdaPlayer->SetVolume(aVolume);
	}

TInt CBasicSound::GetVolume(TInt& aVolume)
	{
	return iMdaPlayer->GetVolume(aVolume);
	}

TInt CBasicSound::MaxVolume()
	{
	return iMaxVolume;
	}