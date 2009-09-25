/*
 ============================================================================
 Name		: PlaylistNodeIndex.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistNodeIndex declaration 索引管理
 ============================================================================
 */

#ifndef PLAYLISTNODEINDEX_H
#define PLAYLISTNODEINDEX_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "PlaylistDefine.h"
// CLASS DECLARATION

/**
 *  CPlaylistNodeIndex
 * 
 */
class CPlaylistNodeIndex : public CBase
	{
public:
	// Constructors and destructor

	~CPlaylistNodeIndex();
	static CPlaylistNodeIndex* NewL();
	static CPlaylistNodeIndex* NewLC();

private:
	CPlaylistNodeIndex();
	void ConstructL();
	
public:
	//把名字转换成索引
//	TInt FindIndexByName(const TDesC& aName);
	TInt FindIndexByName(const TDesC& aName,TInt& aIndex);
//	TInt ConvertNameToIndex(const TDesC& aName);
	void Append(TInt index,const TDesC& aName);
	
	TInt ConvertEventToNumber(const TDesC& aEvent,EPlaylistNodeEvent& aIndex);
	
private:
	RPointerArray<PlaylistNodeIndex> iArray;
	};

#endif // PLAYLISTNODEINDEX_H
