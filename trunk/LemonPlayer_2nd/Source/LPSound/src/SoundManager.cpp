/*
 ============================================================================
 Name		: SoundManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSoundManager implementation
 ============================================================================
 */

#include "SoundManager.h"
#include "BasicSound.h"
#include "UIData.h"


CSoundManager::CSoundManager(CUIViewData *aData)
	{
	// No implementation required
	iData = aData;
	iIsLoad = EFalse;
	}

CSoundManager::~CSoundManager()
	{
	}

CSoundManager* CSoundManager::NewLC(CUIViewData *aData)
	{
	CSoundManager* self = new (ELeave)CSoundManager(aData);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSoundManager* CSoundManager::NewL(CUIViewData *aData)
	{
	CSoundManager* self=CSoundManager::NewLC(aData);
	CleanupStack::Pop(); // self;
	return self;
	}

void CSoundManager::ConstructL()
	{
	iPlayer = CBasicSound::NewL();
	iPlayer->SetListerner(this);
	}

void CSoundManager::InitComplete()
	{
	iIsLoad = ETrue;
	iData->InitVolume(iPlayer->MaxVolume());
	
	iData->SetPlayerState(KPlayerStatePlay);
	StateChange();
	VolumeChange();
	
	if (iSoundCallBack)
		{
		iSoundCallBack->InitComplete();
		}
	}

void CSoundManager::PlayComplete()
	{
	iIsLoad = EFalse;
	iData->SetPlayerState(KPlayerStateStop);
	
//	TInt result = PlayFile();
	
	if (iSoundCallBack)
		{
		iSoundCallBack->PlayComplete();
		}
	}	



void CSoundManager::StateChange()
	{
		if (iData->GetPlayerState() == KPlayerStateStop)
			{
			iPlayer->Stop();
			}
		else if (iData->GetPlayerState() == KPlayerStatePlay)
			{
			if (iIsLoad)
				{
				iPlayer->Play();
				}
			else
				{
				PlayFile();
				}
			
			}
		else if (iData->GetPlayerState() == KPlayerStatePause)
			{
			iPlayer->Pause();
			}
	}

void CSoundManager::VolumeChange()
	{
	if (iIsLoad)
		iPlayer->SetVolume(iData->GetVolume());
	}

TInt CSoundManager::LoadFile(const TDesC& aFileName)
	{
	return iPlayer->LoadFile(aFileName);
	}

TInt CSoundManager::PlayFile()
	{
	TPtrC file = iData->GetSelectFile();
	if (file.Compare(KNullDesC)== 0)
		return KErrNotFound;
	else
		return LoadFile(file);
	}