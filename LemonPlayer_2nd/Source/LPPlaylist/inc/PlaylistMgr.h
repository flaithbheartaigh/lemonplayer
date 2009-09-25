/*
 ============================================================================
 Name		: PlaylistMgr.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistMgr declaration
 ============================================================================
 */

#ifndef PLAYLISTMGR_H
#define PLAYLISTMGR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <coedef.h>
#include "CustomControlDefine.h"
#include "AnimationEffectDefine.h"
// CLASS DECLARATION
class CPlaylistDataMgr;
class CPlaylistControl;
/**
 *  CPlaylistMgr
 * 
 */
_LIT(KPlaylistXmlFile,"c:\\lemonplayer\\playlist.xml");

class CPlaylistMgr : public CBase
	{
public:
	// Constructors and destructor

	~CPlaylistMgr();
	static CPlaylistMgr* NewL();
	static CPlaylistMgr* NewLC();

private:
	CPlaylistMgr();
	void ConstructL();
	
public:
	void Draw(CBitmapContext& gc);	
	TKeyResponse KeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType,
			EAnimationEffectType& aEffect);
	
	void ChooseIndex(TInt aIndex = 0);
	
private:
	void SelectEvent();
	void EventOpenFile(pListItemStruct aItem);
	void EventOpenNode(pListItemStruct aItem);
	
	void EventOpenDefault();
	void EventOpenFavorite();
	void EventOpenLibrary();
	void EventOpenHistory();
	void EventOpenFolder();
	void EventOpenAblum();
	void EventOpenGenre();
	void EventOpenArtist();
	void EventOpenPlaylist(const TDesC& aFileName);
	void EventOpenCategory(ELibNodesIndex aCate);
	void EventOpenCategory(const TDesC& aCate,TInt aIndex);
	void EventGoBack();

private:
	void AddBackItem();
	
private:
	CPlaylistDataMgr* iDataMgr;
	CPlaylistControl* iControlMgr;

	EPlaylistGoBackState iBackIndex;
	};

#endif // PLAYLISTMGR_H
