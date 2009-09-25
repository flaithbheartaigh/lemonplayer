/*
 ============================================================================
 Name		: UIList.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIList implementation
 ============================================================================
 */

#include "UIList.h"
#include "PlaylistMgr.h"
#include "MacroUtil.h"
#include <eikmenub.h>
#include <LemonPlayer.rsg>

CUIList::CUIList()
	{
	// No implementation required
	}

CUIList::~CUIList()
	{
	SAFE_DELETE(iList);
	}

CUIList* CUIList::NewL(CUIViewData *aData, MUIOperateInterface *aOperate)
	{
	CUIList* self = new (ELeave) CUIList;
	CleanupStack::PushL(self);
	self->ConstructL(aData, aOperate);
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIList::ConstructL(CUIViewData *aData, MUIOperateInterface *aOperate)
	{
	iData = aData;
	iOperate = aOperate;

	iList = CPlaylistMgr::NewL();
	}

TBool CUIList::Update()
	{
	return EFalse;
	}

void CUIList::UpdateDisplay(CWindowGc& gc)
	{
	iList->Draw(gc);
	}

void CUIList::UpdateDisplay(CFbsBitGc& aBitGc)
	{
	iList->Draw(aBitGc);
	}

TKeyResponse CUIList::KeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType,
		EAnimationEffectType& aEffect)
	{
	return iList->KeyEventL(aKeyEvent, aType, aEffect);
	}

TBool CUIList::IsOfferKey()
	{
	return EFalse;
	}

void CUIList::DynInitMenuBarL(TInt aResourceId, CEikMenuBar* aMenuBar)
	{
	if (aResourceId != R_LEMONPLAYER_LIST_MENUBAR)
		{
		aMenuBar->SetMenuTitleResourceId(R_LEMONPLAYER_LIST_MENUBAR);
		if (aMenuBar)
			{
			aMenuBar->StopDisplayingMenuBar();
			}
		if (aMenuBar)
			{
			aMenuBar->TryDisplayMenuBarL();
			}
		}
	}

void CUIList::HandleCommandL(TInt aCommand)
	{}