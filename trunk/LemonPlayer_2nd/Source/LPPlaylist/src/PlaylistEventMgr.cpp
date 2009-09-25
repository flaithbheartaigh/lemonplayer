/*
 ============================================================================
 Name		: PlaylistEventMgr.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistEventMgr implementation
 ============================================================================
 */

#include "PlaylistEventMgr.h"

CPlaylistEventMgr::CPlaylistEventMgr()
	{
	// No implementation required
	}

CPlaylistEventMgr::~CPlaylistEventMgr()
	{
	}

CPlaylistEventMgr* CPlaylistEventMgr::NewLC()
	{
	CPlaylistEventMgr* self = new (ELeave)CPlaylistEventMgr();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CPlaylistEventMgr* CPlaylistEventMgr::NewL()
	{
	CPlaylistEventMgr* self=CPlaylistEventMgr::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CPlaylistEventMgr::ConstructL()
	{

	}
