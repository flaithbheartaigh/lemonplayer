/*
 ============================================================================
 Name		: PlaylistNodeIndex.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistNodeIndex implementation
 ============================================================================
 */

#include "PlaylistNodeIndex.h"

CPlaylistNodeIndex::CPlaylistNodeIndex()
	{
	// No implementation required
	}

CPlaylistNodeIndex::~CPlaylistNodeIndex()
	{
	iArray.ResetAndDestroy();
	}

CPlaylistNodeIndex* CPlaylistNodeIndex::NewLC()
	{
	CPlaylistNodeIndex* self = new (ELeave)CPlaylistNodeIndex();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CPlaylistNodeIndex* CPlaylistNodeIndex::NewL()
	{
	CPlaylistNodeIndex* self=CPlaylistNodeIndex::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CPlaylistNodeIndex::ConstructL()
	{

	}

//TInt CPlaylistNodeIndex::FindIndexByName(const TDesC& aName)
//	{
//	for(TInt i=0; i<iArray.Count(); i++)
//		{
//		TPtr ptr = iArray[i].iName->Des();
//		if (ptr.Compare(aName) == 0)
//			{
//			return i;
//			}
//		}
//	return KErrNotFound;
//	}

TInt CPlaylistNodeIndex::FindIndexByName(const TDesC& aName, TInt& aIndex)
	{
	for (TInt i=0; i<iArray.Count(); i++)
		{
		TPtr ptr = iArray[i]->iName->Des();
		if (ptr.Compare(aName) == 0)
			{
			aIndex = iArray[i]->iIndex;
			return KErrNone;
			}
		}
	aIndex = iArray.Count();
	return KErrNotFound;
	}

//TInt CPlaylistNodeIndex::ConvertNameToIndex(const TDesC& aName)
//	{
//	for(TInt i=0; i<iArray.Count(); i++)
//		{
//		TPtr ptr = iArray[i].iName->Des();
//		if (ptr.Compare(aName) == 0)
//			{
//			return i;
//			}
//		}
//	return iArray.Count();
//	}

void CPlaylistNodeIndex::Append(TInt index, const TDesC& aName)
	{
	pPlaylistNodeIndex node = new (ELeave)PlaylistNodeIndex;
	node->iIndex = index;
	node->iName = aName.AllocL();
	iArray.Append(node);
	}

TInt CPlaylistNodeIndex::ConvertEventToNumber(const TDesC& aEvent,
		EPlaylistNodeEvent& aIndex)
	{
	TInt err = KErrNone;
	if (aEvent.Compare(KPlaylistEventStrOpenDefault) == 0)
		{
		aIndex = KPlaylistEventOpenDefault;
		return err;
		}
	if (aEvent.Compare(KPlaylistEventStrOpenFavorite) == 0)
		{
		aIndex = KPlaylistEventOpenFavorite;
		return err;
		}
	if (aEvent.Compare(KPlaylistEventStrOpenLibrary) == 0)
		{
		aIndex = KPlaylistEventOpenLibrary;
		return err;
		}
	if (aEvent.Compare(KPlaylistEventStrOpenHistory) == 0)
		{
		aIndex = KPlaylistEventOpenHistory;
		return err;
		}
	if (aEvent.Compare(KPlaylistEventStrOpenFolder) == 0)
		{
		aIndex = KPlaylistEventOpenFolder;
		return err;
		}
	if (aEvent.Compare(KPlaylistEventStrOpenAblum) == 0)
		{
		aIndex = KPlaylistEventOpenAblum;
		return err;
		}
	if (aEvent.Compare(KPlaylistEventStrOpenGenre) == 0)
		{
		aIndex = KPlaylistEventOpenGenre;
		return err;
		}
	if (aEvent.Compare(KPlaylistEventStrOpenArtist) == 0)
		{
		aIndex = KPlaylistEventOpenArtist;
		return err;
		}
	if (aEvent.Compare(KPlaylistEventStrGoBack) == 0)
		{
		aIndex = KPlaylistEventGoBack;
		return err;
		}
	aIndex = KPlaylistEventNone;
	return KErrNotFound;
	}