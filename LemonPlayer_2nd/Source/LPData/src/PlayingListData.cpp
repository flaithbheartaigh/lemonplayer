/*
 ============================================================================
 Name		: PlayingListData.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlayingListData implementation
 ============================================================================
 */

#include "PlayingListData.h"
#include "MusicInfoBean.h"
#include "MacroUtil.h"

CPlayingListData::CPlayingListData()
	{
	// No implementation required
	}

CPlayingListData::~CPlayingListData()
	{
	ClearMusic();
	SAFE_DELETE_R(iPlaylistFileArray);
	}

CPlayingListData* CPlayingListData::NewLC()
	{
	CPlayingListData* self = new (ELeave)CPlayingListData();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CPlayingListData* CPlayingListData::NewL()
	{
	CPlayingListData* self=CPlayingListData::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CPlayingListData::ConstructL()
	{
	iPlaylistFileArray = new (ELeave) RPointerArray<CMusicInfoBean>;
	}

void CPlayingListData::AddMusic(CMusicInfoBean* aBean)
	{
	iPlaylistFileArray->AppendL(aBean);
	}

void CPlayingListData::AddMusic(const TDesC8& aFileName)
	{
	CMusicInfoBean* music = CMusicInfoBean::NewL();
	music->setFullNameL(aFileName);
	music->setInfoState(CMusicInfoBean::KInfoInit);
	AddMusic(music);
	}

void CPlayingListData::RemoveMusicByIndex(const TInt aIndex)
	{
	
	}

void CPlayingListData::ClearMusic()
	{
	iPlaylistFileArray->ResetAndDestroy();
	}

CMusicInfoBean* CPlayingListData::GetCurrentMusic()
	{
	}

CMusicInfoBean* CPlayingListData::GetNextMusic()
	{
	}

RPointerArray<CMusicInfoBean>* CPlayingListData::GetPlaylistArray()
	{
	return iPlaylistFileArray;
	}