#ifndef PLAYLISTDEFINE_H
#define PLAYLISTDEFINE_H

#include "MacroUtil.h"

//节点属性
enum EPlaylistNodeProp
	{
	KPlaylistNodePropUninit = 0,
	KPlaylistNodePropRoot
	};

//节点点击事件
enum EPlaylistNodeEvent
	{
	KPlaylistEventNone = 0,
	KPlaylistEventOpenDefault,
	KPlaylistEventOpenFavorite,
	KPlaylistEventOpenLibrary,
	KPlaylistEventOpenHistory,
	KPlaylistEventOpenFolder,
	KPlaylistEventOpenAblum,
	KPlaylistEventOpenGenre,
	KPlaylistEventOpenArtist,
	KPlaylistEventGoBack
	};

//点击事件
_LIT(KPlaylistEventStrOpenDefault, "open_default");
_LIT(KPlaylistEventStrOpenFavorite, "open_favorite");
_LIT(KPlaylistEventStrOpenLibrary, "open_library");
_LIT(KPlaylistEventStrOpenHistory, "open_history");
_LIT(KPlaylistEventStrOpenFolder, "open_folder");
_LIT(KPlaylistEventStrOpenAblum, "open_ablum");
_LIT(KPlaylistEventStrOpenGenre, "open_genre");
_LIT(KPlaylistEventStrOpenArtist, "open_artist");
_LIT(KPlaylistEventStrGoBack, "go_back");

//界面显示节点
typedef struct _PlaylistTreeNode
	{
	TInt iIndex;
	HBufC* iName;
	EPlaylistNodeProp iProperty;
	EPlaylistNodeEvent iEvent;
	RArray<TInt> iChildren;
	TInt iParent;

	_PlaylistTreeNode()
		{
		iIndex = -1;
		iName = NULL;
		iProperty = KPlaylistNodePropUninit;
		iEvent = KPlaylistEventNone;
		iParent = -1;
		}

	~_PlaylistTreeNode()
		{
		SAFE_DELETE(iName);
		iChildren.Close();
		}

	} PlaylistTreeNode, *pPlaylistTreeNode;

//_LIT(KPlaylistNode,"")
_LIT(KPlaylistNodeRoot, "root");
_LIT(KPlaylistNodeDefault, "default");
_LIT(KPlaylistNodeFavorite, "favorite");
_LIT(KPlaylistNodeLibrary, "library");
_LIT(KPlaylistNodeHistroy, "history");

_LIT(KPlaylistNodeBack, "back");

enum EPlaylistNodeIndex
	{
	KPlaylistNodeIndexRoot = 0,
	KPlaylistNodeIndexDefault,
	KPlaylistNodeIndexFavorite,
	KPlaylistNodeIndexLibrary
	};

//节点索引对照关系
typedef struct _PlaylistNodeIndex
	{
	TInt iIndex;
	HBufC* iName;

	_PlaylistNodeIndex()
		{
		iIndex = KErrNotFound;
		}

	~_PlaylistNodeIndex()
		{
		SAFE_DELETE(iName);
		}

	} PlaylistNodeIndex, *pPlaylistNodeIndex;

enum EPlaylistItemType
	{
	KPlaylistItemTypeNode = 0,
	KPlaylistItemTypeFile,
	KPlaylistItemTypePlaylist,
	KPlaylistItemTypeCategory
	};

enum EPlaylistGoBackState
	{
	KPlaylistBackStateRoot = 0,
	KPlaylistBackStateFavorite,
	KPlaylistBackStateLibrary,
	KPlaylistBackStateFolder,
	KPlaylistBackStateAblum,
	KPlaylistBackStateGenre,
	KPlaylistBackStateArtist
	};

typedef struct _PlaylistLibNode
	{
	HBufC8* iName;
	RArray<TInt> iLinks;
	} PlaylistLibNode, *pPlaylistLibNode;

enum ELibNodesIndex
	{
	KLibNodeFolder = 0,
	KLibNodeAblum,
	KLibNodeGenre,
	KLibNodeArtist,
	KLibNodeTotal
	};

typedef RPointerArray<PlaylistLibNode> PlayListLibNodeArray;
#endif /*PLAYLISTDEFINE_H*/

