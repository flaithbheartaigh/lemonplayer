/*
 ============================================================================
 Name		: UIOperateImplement.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIOperateImplement implementation
 ============================================================================
 */

#include "UIOperateImplement.h"
#include "SoundManager.h"
#include "UIData.h"

CUIOperateImplement::CUIOperateImplement(CUIViewData *aData) :
	iData(aData)
	{
	// No implementation required
	}

CUIOperateImplement::~CUIOperateImplement()
	{
	}

CUIOperateImplement* CUIOperateImplement::NewLC(CUIViewData *aData)
	{
	CUIOperateImplement* self = new (ELeave)CUIOperateImplement(aData);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIOperateImplement* CUIOperateImplement::NewL(CUIViewData *aData)
	{
	CUIOperateImplement* self=CUIOperateImplement::NewLC(aData);
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIOperateImplement::ConstructL()
	{
	iSoundManager = CSoundManager::NewL(iData);
	}

void CUIOperateImplement::PlayFile()
	{
	StateChange();
	iSoundManager->StateChange();
	}

void CUIOperateImplement::PlayFile(const TDesC& aFileName)
	{
	}

void CUIOperateImplement::VolumeChange(TInt aVolume)
	{
	iData->SetVolume(aVolume);
	iSoundManager->VolumeChange();
	}

void CUIOperateImplement::AddVolumeOneBlock()
	{
	iData->AddVolumeOneBlock();
	iSoundManager->VolumeChange();
	}

void CUIOperateImplement::DecVolumeOneBlock()
	{
	iData->DecVolumeOneBlock();
	iSoundManager->VolumeChange();
	}

void CUIOperateImplement::StateChange()
	{
	if (iData->GetPlayerState() == KPlayerStateStop)
		{
		iData->SetPlayerState(KPlayerStatePlay);
		}
	else if (iData->GetPlayerState() == KPlayerStatePlay)
		{
		iData->SetPlayerState(KPlayerStatePause);
		}
	else if (iData->GetPlayerState() == KPlayerStatePause)
		{
		iData->SetPlayerState(KPlayerStatePlay);
		}
	}