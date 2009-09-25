/*
 ============================================================================
 Name		: PlaylistDataMgr.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistDataMgr implementation
 ============================================================================
 */

#include "PlaylistDataMgr.h"
#include <LemonPlayer.rsg>
#include <StringLoader.h> 
#include "MacroUtil.h"
#include "PlaylistNodeIndex.h"
#include "PlaylistNodeParser.h"
#include "UIData.h"
#include "MusicInfoBean.h"
#include <libc\stdlib.h>

CPlaylistDataMgr::CPlaylistDataMgr()
	{
	// No implementation required
	}

CPlaylistDataMgr::~CPlaylistDataMgr()
	{
	//	iFileArray.ResetAndDestroy();
	//	iFileArray.Close();
	iHistoryArray->Reset();
	SAFE_DELETE(iHistoryArray);

	SAFE_DELETE_ARRAY(iLibraryNodes,KLibNodeTotal);

	iAllArray->ResetAndDestroy();
	SAFE_DELETE(iAllArray);

	iArray.ResetAndDestroy();
	iArray.Close();

	SAFE_DELETE(iDocHandler);
	SAFE_DELETE(iIndexMgr);
	//	iListShowDesArray->Reset();
	//	SAFE_DELETE(iListShowDesArray);
	iPlaylistArray->Reset();
	SAFE_DELETE(iPlaylistArray);
	}

CPlaylistDataMgr* CPlaylistDataMgr::NewLC()
	{
	CPlaylistDataMgr* self = new (ELeave)CPlaylistDataMgr();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CPlaylistDataMgr* CPlaylistDataMgr::NewL()
	{
	CPlaylistDataMgr* self=CPlaylistDataMgr::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CPlaylistDataMgr::ConstructL()
	{
	iPlaylistArray = new (ELeave)CDesCArrayFlat(5);

	iFileArray = CUIViewData::GetInstance()->GetPlaylistArray();
	//	iListShowDesArray = new (ELeave)CDesCArrayFlat(5);

	iIndexMgr = CPlaylistNodeIndex::NewL();

	iDocHandler = CPlaylistNodeParser::NewL();
	iDocHandler->SetNodeNotify(this);

	iAllArray = new (ELeave) RPointerArray<CMusicInfoBean>;

	iLibraryNodes
			= (PlayListLibNodeArray**) malloc(sizeof(PlayListLibNodeArray*)
					*KLibNodeTotal);
	for (TInt i=0; i<KLibNodeTotal; i++)
		{
		iLibraryNodes[i] = new (ELeave) PlayListLibNodeArray;
		}
	iHistoryArray = new (ELeave) RArray<TInt>;
	AddToHistory(0);

	LoadAll();
	CateAll(); //·ÖÀà
	//	iListShowDesArray.
	}

void CPlaylistDataMgr::Init()
	{
	}

RPointerArray<ListItemStruct>* CPlaylistDataMgr::GetShowDesArray(TInt index)
	{
	RPointerArray<ListItemStruct>* list = new (ELeave)RPointerArray<ListItemStruct>;

	RArray<TInt>& children = iArray[index]->iChildren;
	for (TInt i=0; i<children.Count(); i++)
		{
		TInt index = children[i];
		TPtr ptr = iArray[index]->iName->Des();

		pListItemStruct item = new (ELeave) ListItemStruct;

		item->iIconIndex = 0;
		item->iHideIndex = index;
		item->iShowName = ptr.AllocL();
		item->iHideInfo = NULL;
		item->iType = KPlaylistItemTypeNode;

		list->AppendL(item);
		}

	return list;
	}

TInt CPlaylistDataMgr::GetCurrentIndex()
	{
	TInt index = iArray.Count();
	return index;
	}

TInt CPlaylistDataMgr::GetCurrentMaxFreeIndex()
	{
	TInt index = iArray.Count();
	return index;
	}

TInt CPlaylistDataMgr::ConvertNameToIndex(const TDesC& aName)
	{
	TInt index;
	iIndexMgr->FindIndexByName(aName, index);
	return index;
	}

EPlaylistNodeEvent CPlaylistDataMgr::ConvertEventToIndex(const TDesC& aName)
	{
	EPlaylistNodeEvent index;
	iIndexMgr->ConvertEventToNumber(aName, index);
	return index;
	}

void CPlaylistDataMgr::AddPlaylistNode(pPlaylistTreeNode node)
	{
	TInt index = node->iIndex;
	TPtr ptr = node->iName->Des();
	iIndexMgr->Append(index, ptr);
	iArray.Insert(node, index);
	//	iArray.AppendL(node);
	}

pPlaylistTreeNode CPlaylistDataMgr::GetPlaylistNodeByIndex(TInt index)
	{
	if (index < iArray.Count() && index>-1)
		{
		return iArray[index];
		}
	else
		return NULL;
	}

TInt CPlaylistDataMgr::LoadStructFromXmlFile(const TDesC& aFileName)
	{
	CPlaylistDecHandler *decl = CPlaylistDecHandler::NewLC();

	CSyParser *syParser = CSyParser::NewLC(TPtrC());
	syParser->SetHandler(iDocHandler);
	syParser->SetHandler(decl);

	RFile file;
	TInt err = file.Open(CCoeEnv::Static()->FsSession(), aFileName, EFileRead);

	if (KErrNone == err)
		{
		CleanupClosePushL(file);
		//²Ù×÷
		TBuf8<1024> ptr;
		file.Read(ptr);
		syParser->Parse(ptr, ETrue);
		CleanupStack::PopAndDestroy(1);
		}
	CleanupStack::PopAndDestroy(2);
	}

RPointerArray<CMusicInfoBean>* CPlaylistDataMgr::GetCleanList()
	{
	iFileArray->ResetAndDestroy();
	return iFileArray;
	}

void CPlaylistDataMgr::AddPlaylistFile(const TDesC& aFileName)
	{
	iPlaylistArray->AppendL(aFileName);
	}

CDesCArrayFlat* CPlaylistDataMgr::GetPlaylistFiles()
	{
	return iPlaylistArray;
	}

void CPlaylistDataMgr::LoadAll()
	{
	CMusicInfoBean* bean = CMusicInfoBean::NewL();
	bean->setAblumL(_L8("Oly"));
	bean->setArtistL(_L8("L"));
	bean->setFileFolderL(_L8("c:\\lemonplayer\\"));
	bean->setFileNameL(_L8("music.mp3"));
	bean->setGenre(0);
	bean->setTitleL(_L8("You"));

	AddToAll(bean);
	}

void CPlaylistDataMgr::AddToAll(CMusicInfoBean* aBean)
	{
	iAllArray->AppendL(aBean);
	}

CMusicInfoBean* CPlaylistDataMgr::GetMusicByIndexForAll(TInt aIndex)
	{
	return (*iAllArray)[aIndex];
	}

void CPlaylistDataMgr::CateAll()
	{
	for (TInt i=0; i<iAllArray->Count(); i++)
		{
		CMusicInfoBean* bean = (*iAllArray)[i];

		AddToCate(bean->getFileFolder(), i, KLibNodeFolder);
		AddToCate(bean->getAblum(), i, KLibNodeAblum);
		//		AddToCate(bean->getGenre(),i,KLibNodeGenre);
		AddToCate(bean->getArtist(), i, KLibNodeArtist);
		}
	}

void CPlaylistDataMgr::AddToCate(const TDesC8& aName, TInt index,
		ELibNodesIndex aCate)
	{
	PlayListLibNodeArray *node = iLibraryNodes[aCate];
	for (TInt i=0; i<node->Count(); i++)
		{
		PlaylistLibNode *entry = (*node)[i];
		if (entry->iName->Compare(aName)== 0)
			{
			entry->iLinks.Append(index);
			return;
			}
		}
	PlaylistLibNode *entry = new (ELeave)PlaylistLibNode;
	entry->iName = aName.AllocL();
	entry->iLinks.AppendL(index);
	node->Append(entry);
	}

PlayListLibNodeArray* CPlaylistDataMgr::GetNodesByCate(TInt aIndex)
	{
	return iLibraryNodes[aIndex];
	}

void CPlaylistDataMgr::AddToHistory(TInt aIndex)
	{
	for(TInt i=0; i<iHistoryArray->Count(); i++)
		{
		if ((*iHistoryArray)[i] == aIndex)
			{
			return;
			}
		}
	iHistoryArray->Append(aIndex);
	}

RArray<TInt>* CPlaylistDataMgr::GetHistoryArray()
	{
	return iHistoryArray;
	}