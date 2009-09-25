/*
 ============================================================================
 Name		: PlaylistEventMgr.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistEventMgr declaration
 ============================================================================
 */

#ifndef PLAYLISTEVENTMGR_H
#define PLAYLISTEVENTMGR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CPlaylistEventMgr
 * 
 */
class CPlaylistEventMgr : public CBase
	{
public:
	// Constructors and destructor

	~CPlaylistEventMgr();
	static CPlaylistEventMgr* NewL();
	static CPlaylistEventMgr* NewLC();

private:

	CPlaylistEventMgr();
	void ConstructL();

	};

#endif // PLAYLISTEVENTMGR_H
