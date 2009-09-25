/*
 ============================================================================
 Name		: PlaylistDataMgr.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistDataMgr declaration
 ============================================================================
 */

#ifndef PLAYLISTDATAMGR_H
#define PLAYLISTDATAMGR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "PlaylistDefine.h"
#include <badesca.h>
#include "CustomControlDefine.h"
// CLASS DECLARATION
class CPlaylistNodeIndex;
class CPlaylistNodeParser;
class CMusicInfoBean;
/**
 *  CPlaylistDataMgr
 * 
 */
class MPlaylistNodeNotify
	{
public:
	virtual TInt ConvertNameToIndex(const TDesC& aName) = 0;
	virtual EPlaylistNodeEvent ConvertEventToIndex(const TDesC& aName) = 0;
	virtual void AddPlaylistNode(pPlaylistTreeNode node) = 0;
	virtual pPlaylistTreeNode GetPlaylistNodeByIndex(TInt index) = 0;
	};

class CPlaylistDataMgr : public CBase,
						 public MPlaylistNodeNotify
	{
public:
	// Constructors and destructor

	~CPlaylistDataMgr();
	static CPlaylistDataMgr* NewL();
	static CPlaylistDataMgr* NewLC();

private:
	CPlaylistDataMgr();
	void ConstructL();
	
public: //MPlaylistNodeNotify	
	virtual TInt ConvertNameToIndex(const TDesC& aName);
	virtual EPlaylistNodeEvent ConvertEventToIndex(const TDesC& aName);
	virtual void AddPlaylistNode(pPlaylistTreeNode node) ;
	virtual pPlaylistTreeNode GetPlaylistNodeByIndex(TInt index);
		
public:
	void Init();
	RPointerArray<ListItemStruct>* GetShowDesArray(TInt index = 0);
	
private:
	TInt GetCurrentIndex();
	TInt GetCurrentMaxFreeIndex();
//	void GetCurrentDesArray(TInt index);
	
public:
	TInt LoadStructFromXmlFile(const TDesC& aFileName);
	
public:
//	void SetList(RPointerArray<CMusicInfoBean>* aList)
//			{iFileArray = aList;};
	RPointerArray<CMusicInfoBean>* GetList()
			{return iFileArray;};
	RPointerArray<CMusicInfoBean>* GetCleanList();
	
public:
	void AddPlaylistFile(const TDesC& aFileName);
	CDesCArrayFlat* GetPlaylistFiles();
	
	
	/********ȫ���б����********************/
private:
	void LoadAll();
	void CateAll();	//����
	
	void AddToCate(const TDesC8& aName,TInt index,ELibNodesIndex aCate);
public:
	void AddToAll(CMusicInfoBean* aBean);	
	CMusicInfoBean* GetMusicByIndexForAll(TInt aIndex);
	PlayListLibNodeArray* GetNodesByCate(TInt aIndex);
	
	/********��ʷ�����б�*********************/
public:
	void AddToHistory(TInt aIndex);
	RArray<TInt>* GetHistoryArray();
	
private:
	RPointerArray<PlaylistTreeNode> iArray;
//	CDesCArrayFlat* iListShowDesArray;
	
	CPlaylistNodeIndex* iIndexMgr;	
	CPlaylistNodeParser* iDocHandler;
	
	RPointerArray<CMusicInfoBean>* iFileArray; //��ǰ����
	
	RPointerArray<CMusicInfoBean>* iAllArray; //ȫ���ļ�
	
	CDesCArrayFlat* iPlaylistArray;  //�����б�
	
	PlayListLibNodeArray** iLibraryNodes;  //���������
	
	RArray<TInt>* iHistoryArray;		//��ʷ����,������ȫ���ļ��������������
	};

#endif // PLAYLISTDATAMGR_H
