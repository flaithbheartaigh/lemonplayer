/*
 ============================================================================
 Name		: PlaylistMgr.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistMgr implementation
 ============================================================================
 */

#include "PlaylistMgr.h"
#include "PlaylistDataMgr.h"
#include "PlaylistControl.h"
#include "MacroUtil.h"
#include "CustomControlDefine.h"
#include "UIData.h"
#include "CommonUtils.h"
#include "MusicListMgr.h"
#include "MusicInfoBean.h"

CPlaylistMgr::CPlaylistMgr()
	{
	// No implementation required
	}

CPlaylistMgr::~CPlaylistMgr()
	{
	SAFE_DELETE(iControlMgr);
	SAFE_DELETE(iDataMgr);
	}

CPlaylistMgr* CPlaylistMgr::NewLC()
	{
	CPlaylistMgr* self = new (ELeave)CPlaylistMgr();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CPlaylistMgr* CPlaylistMgr::NewL()
	{
	CPlaylistMgr* self=CPlaylistMgr::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CPlaylistMgr::ConstructL()
	{
	iDataMgr = CPlaylistDataMgr::NewL();
	//	iDataMgr->Init();
	iDataMgr->LoadStructFromXmlFile(KPlaylistXmlFile);
	iDataMgr->AddPlaylistFile(_L("c:\\lemonplayer\\my.m3u"));

	iControlMgr = CPlaylistControl::NewL();

	ChooseIndex();
	}

void CPlaylistMgr::ChooseIndex(TInt aIndex)
	{
	iControlMgr->SetShowDesArray(iDataMgr->GetShowDesArray(aIndex));
	}

void CPlaylistMgr::Draw(CBitmapContext& gc)
	{
	iControlMgr->Draw(gc);
	}

TKeyResponse CPlaylistMgr::KeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType, EAnimationEffectType& aEffect)
	{
	TInt update;
	switch (aType)
		{
		case EEventKey:
			switch (aKeyEvent.iScanCode)
				{
				case EStdKeyUpArrow:
					update = iControlMgr->Update(KCustomControlDirectionUp);
					if (update == EKeyWasConsumed)
						{
						aEffect = KAnimationEffectNone;
						}
					return EKeyWasConsumed;
				case EStdKeyDownArrow:
					update = iControlMgr->Update(KCustomControlDirectionDown);
					if (update == EKeyWasConsumed)
						{
						aEffect = KAnimationEffectNone;
						}
					return EKeyWasConsumed;
				case EStdKeyDevice3:
					SelectEvent();
					aEffect = KAnimationEffectSwap;
					return EKeyWasConsumed;
				}
			break;
		}
	return EKeyWasNotConsumed;
	}

void CPlaylistMgr::SelectEvent()
	{
	//得到当前选择
	pListItemStruct item = iControlMgr->GetCurrentItem();
	TInt index;

	EPlaylistItemType type = item->iType;
	switch (type)
		{
		case KPlaylistItemTypeNode:
			EventOpenNode(item);
			break;
		case KPlaylistItemTypeFile:
			EventOpenFile(item);
			break;
		case KPlaylistItemTypePlaylist:
			//			TPtr file = item->iHideInfo->Des();
			EventOpenPlaylist(*(item->iHideInfo));
			break;
		case KPlaylistItemTypeCategory:
			//			file = item->iHideInfo->Des();
			index = item->iHideIndex;
			//			EventOpenCategory(file, index);
			EventOpenCategory(*(item->iHideInfo), index);
		default:
			break;
		}
	}

void CPlaylistMgr::EventOpenNode(pListItemStruct aItem)
	{
	TInt index = aItem->iHideIndex;

	//事件相应
	pPlaylistTreeNode node = iDataMgr->GetPlaylistNodeByIndex(index);

	switch (node->iEvent)
		{
		case KPlaylistEventOpenDefault:
			EventOpenDefault();
			break;
		case KPlaylistEventOpenFavorite:
			EventOpenFavorite();
			break;
		case KPlaylistEventOpenLibrary:
			EventOpenLibrary();
			break;
		case KPlaylistEventOpenHistory:
			EventOpenHistory();
			break;
		case KPlaylistEventOpenFolder:
			EventOpenFolder();
			break;
		case KPlaylistEventOpenAblum:
			EventOpenAblum();
			break;
		case KPlaylistEventOpenGenre:
			EventOpenGenre();
			break;
		case KPlaylistEventOpenArtist:
			EventOpenArtist();
			break;
		case KPlaylistEventGoBack:
			EventGoBack();
			break;
		default:
			break;
		}
	}

void CPlaylistMgr::EventGoBack()
	{
	switch (iBackIndex)
		{
		case KPlaylistBackStateRoot:
			TInt index = iDataMgr->ConvertNameToIndex(KPlaylistNodeRoot);
			ChooseIndex(index);
			break;
		case KPlaylistBackStateFavorite:
			EventOpenFavorite();
			break;
		case KPlaylistBackStateLibrary:
			EventOpenLibrary();
			break;
		case KPlaylistBackStateFolder:
			EventOpenFolder();
			break;
		case KPlaylistBackStateAblum:
			EventOpenAblum();
			break;
		case KPlaylistBackStateGenre:
			EventOpenGenre();
			break;
		case KPlaylistBackStateArtist:
			EventOpenArtist();
			break;
		}
	}

void CPlaylistMgr::EventOpenFile(pListItemStruct aItem)
	{
	}

void CPlaylistMgr::EventOpenDefault()
	{
	iControlMgr->CleanList();

	//返回
	iBackIndex = KPlaylistBackStateRoot;
	AddBackItem();

	CDesCArrayFlat* files = CUIViewData::GetInstance()->GetSelectFileList();

	for (TInt i=0; i<files->Count(); i++)
		{
		pListItemStruct back = new (ELeave) ListItemStruct;
		back->iIconIndex = 0;
		back->iShowName = (*files)[i].AllocL();
		back->iType = KPlaylistItemTypeNode;
		iControlMgr->AddListItem(back);
		}
	}

void CPlaylistMgr::AddBackItem()
	{
	TInt index = iDataMgr->ConvertNameToIndex(KPlaylistNodeBack);
	pPlaylistTreeNode node = iDataMgr->GetPlaylistNodeByIndex(index);

	pListItemStruct back = new (ELeave) ListItemStruct;
	back->iHideIndex = index;
	back->iIconIndex = 0;
	back->iShowName = node->iName->AllocL();
	back->iType = KPlaylistItemTypeNode;
	iControlMgr->AddListItem(back);

	}

void CPlaylistMgr::EventOpenFavorite()
	{
	iControlMgr->CleanList();

	//返回
	iBackIndex = KPlaylistBackStateRoot;
	AddBackItem();

	CDesCArrayFlat* files = iDataMgr->GetPlaylistFiles();

	for (TInt i=0; i<files->Count(); i++)
		{
		pListItemStruct back = new (ELeave) ListItemStruct;
		back->iIconIndex = 0;
		back->iHideInfo = (*files)[i].AllocL();
		back->iShowName = (*files)[i].AllocL();
		back->iType = KPlaylistItemTypePlaylist;
		iControlMgr->AddListItem(back);
		}
	}

void CPlaylistMgr::EventOpenPlaylist(const TDesC& aFileName)
	{
	CMusicListMgr* mgr = CMusicListMgr::NewL();
	mgr->SetList(iDataMgr->GetCleanList());
	mgr->ReadFile(aFileName);
	delete mgr;

	iControlMgr->CleanList();

	//返回
	iBackIndex = KPlaylistBackStateFavorite;
	AddBackItem();

	RPointerArray<CMusicInfoBean>* files = iDataMgr->GetList();

	for (TInt i=0; i<files->Count(); i++)
		{
		CMusicInfoBean* info = (*files)[i];

		pListItemStruct back = new (ELeave) ListItemStruct;
		back->iIconIndex = 0;
		back->iShowName
				= CCommonUtils::ConvertToUnicodeFromUTF8(info->getFileName());
		back->iHideInfo
				= CCommonUtils::ConvertToUnicodeFromUTF8(info->getFileName());
		back->iType = KPlaylistItemTypeFile;
		iControlMgr->AddListItem(back);
		}
	}

void CPlaylistMgr::EventOpenLibrary()
	{
	iBackIndex = KPlaylistBackStateRoot;
	TInt index = iDataMgr->ConvertNameToIndex(KPlaylistNodeLibrary);
	ChooseIndex(index);
	}

void CPlaylistMgr::EventOpenHistory()
	{
	iControlMgr->CleanList();

	//返回
	iBackIndex = KPlaylistBackStateRoot;
	AddBackItem();

	RArray<TInt>* array = iDataMgr->GetHistoryArray();

	for (TInt i=0; i<array->Count(); i++)
		{
		TInt index = (*array)[i];
		CMusicInfoBean* info = iDataMgr->GetMusicByIndexForAll(index);

		pListItemStruct back = new (ELeave) ListItemStruct;
		back->iIconIndex = 0;
		back->iShowName
				= CCommonUtils::ConvertToUnicodeFromUTF8(info->getFileName());
		back->iHideInfo
				= CCommonUtils::ConvertToUnicodeFromUTF8(info->getFileName());
		back->iType = KPlaylistItemTypeFile;
		iControlMgr->AddListItem(back);
		}
	}

void CPlaylistMgr::EventOpenFolder()
	{
	EventOpenCategory(KLibNodeFolder);
	}

void CPlaylistMgr::EventOpenAblum()
	{
	EventOpenCategory(KLibNodeAblum);
	}

void CPlaylistMgr::EventOpenGenre()
	{
	EventOpenCategory(KLibNodeGenre);
	}

void CPlaylistMgr::EventOpenArtist()
	{
	EventOpenCategory(KLibNodeArtist);
	}

void CPlaylistMgr::EventOpenCategory(ELibNodesIndex aCate)
	{
	iControlMgr->CleanList();

	//返回
	iBackIndex = KPlaylistBackStateLibrary;
	AddBackItem();

	PlayListLibNodeArray* nodes = iDataMgr->GetNodesByCate(aCate);
	for (TInt i=0; i<nodes->Count(); i++)
		{
		pPlaylistLibNode node = (*nodes)[i];
		pListItemStruct back = new (ELeave) ListItemStruct;
		back->iIconIndex = 0;
		back->iShowName
				= CCommonUtils::ConvertToUnicodeFromUTF8(*(node->iName));
		back->iHideInfo = HBufC::NewL(2);
		back->iHideInfo->Des().AppendNum(aCate);
		back->iHideIndex = i;
		back->iType = KPlaylistItemTypeCategory;
		iControlMgr->AddListItem(back);
		}
	}

void CPlaylistMgr::EventOpenCategory(const TDesC& aCate, TInt aIndex)
	{
	TInt cate = CCommonUtils::StrToInt(aCate);

	iControlMgr->CleanList();

	//返回
	switch (cate)
		{
		case KLibNodeFolder:
			iBackIndex = KPlaylistBackStateFolder;
			break;
		case KLibNodeAblum:
			iBackIndex = KPlaylistBackStateAblum;
			break;
		case KLibNodeGenre:
			iBackIndex = KPlaylistBackStateGenre;
			break;
		case KLibNodeArtist:
			iBackIndex = KPlaylistBackStateArtist;
			break;
		}
	AddBackItem();

	PlayListLibNodeArray* nodes = iDataMgr->GetNodesByCate(cate);
	pPlaylistLibNode node = (*nodes)[aIndex];
	RArray<TInt>& links = node->iLinks;
	for (TInt i=0; i<links.Count(); i++)
		{
		TInt index = links[i];
		CMusicInfoBean* info = iDataMgr->GetMusicByIndexForAll(index);

		pListItemStruct back = new (ELeave) ListItemStruct;
		back->iIconIndex = 0;
		back->iShowName
				= CCommonUtils::ConvertToUnicodeFromUTF8(info->getFileName());
		back->iHideInfo
				= CCommonUtils::ConvertToUnicodeFromUTF8(info->getFileName());
		back->iType = KPlaylistItemTypeFile;
		iControlMgr->AddListItem(back);
		}
	}