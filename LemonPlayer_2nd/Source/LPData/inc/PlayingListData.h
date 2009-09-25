/*
 ============================================================================
 Name		: PlayingListData.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlayingListData declaration
 				��ǰ���ڲ��ŵ��б�
 ============================================================================
 */

#ifndef PLAYINGLISTDATA_H
#define PLAYINGLISTDATA_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION
class CMusicInfoBean;
/**
 *  CPlayingListData
 * 
 */
class CPlayingListData : public CBase
	{
public:
	// Constructors and destructor
	~CPlayingListData();
	static CPlayingListData* NewL();
	static CPlayingListData* NewLC();

private:
	CPlayingListData();
	void ConstructL();
	
public:
	void AddMusic(CMusicInfoBean* aBean);
	void AddMusic(const TDesC8& aFileName);
	void RemoveMusicByIndex(const TInt aIndex);
	void ClearMusic();
	CMusicInfoBean* GetCurrentMusic();
	CMusicInfoBean* GetNextMusic();
	
	RPointerArray<CMusicInfoBean>* GetPlaylistArray();
	
private:
	CMusicInfoBean* GetByIndex(const TInt aIndex);
	
private:
	RPointerArray<CMusicInfoBean>* iPlaylistFileArray;
	TInt iCurSelectFile;
	TInt iNextSelectFile;
	};

#endif // PLAYINGLISTDATA_H
