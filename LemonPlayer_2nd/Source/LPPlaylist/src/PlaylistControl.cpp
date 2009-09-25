/*
 ============================================================================
 Name		: PlaylistControl.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistControl implementation
 ============================================================================
 */

#include "PlaylistControl.h"
#include "CustomControlList.h"

#include "MacroUtil.h"

CPlaylistControl::CPlaylistControl()
	{
	// No implementation required
	}

CPlaylistControl::~CPlaylistControl()
	{
	SAFE_DELETE(iList);
	}

CPlaylistControl* CPlaylistControl::NewLC()
	{
	CPlaylistControl* self = new (ELeave)CPlaylistControl();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CPlaylistControl* CPlaylistControl::NewL()
	{
	CPlaylistControl* self=CPlaylistControl::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CPlaylistControl::ConstructL()
	{
	iList = CCustomControlList::NewL();

	TPoint point(0, 0);
	TSize size(100, 100);
	iList->InitData(point, size, size);
	}

void CPlaylistControl::SetShowDesArray(CDesCArrayFlat& aDesArray)
	{
	iList->ClearItem();
	for (TInt i=0; i<aDesArray.Count(); i++)
		{
		iList->AddItem(aDesArray[i]);
		}
	}

void CPlaylistControl::SetShowDesArray(RPointerArray<ListItemStruct>* aList)
	{
	iList->ResetItem(aList);
	}

void CPlaylistControl::Draw(CBitmapContext& gc)
	{
	iList->Draw(gc);
	}

TInt CPlaylistControl::Update(ECustomControlDirection aDirection)
	{
	return iList->Update(aDirection);
	}

void CPlaylistControl::CleanList()
	{
	iList->ClearItem();
	}

void CPlaylistControl::AddListItem(const TDesC& aName, TInt aIndex)
	{
	iList->AddItem(aName, aIndex);
	}

void CPlaylistControl::AddListItem(pListItemStruct aItem)
	{
	iList->AddItem(aItem);
	}

void CPlaylistControl::SelectEvent()
	{
	
	}

pListItemStruct CPlaylistControl::GetCurrentItem()
	{
	return iList->GetCurrentItem();
	}