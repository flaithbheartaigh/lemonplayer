/*
 ============================================================================
 Name		: UIKeyEvent.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIKeyEvent implementation
 ============================================================================
 */

#include "UIKeyEvent.h"
#include "UIData.h"

CUIKeyEvent::CUIKeyEvent(CUIViewData *aData):iData(aData)
	{
	// No implementation required
	}

CUIKeyEvent::~CUIKeyEvent()
	{
	}

CUIKeyEvent* CUIKeyEvent::NewLC(CUIViewData *aData)
	{
	CUIKeyEvent* self = new (ELeave)CUIKeyEvent(aData);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIKeyEvent* CUIKeyEvent::NewL(CUIViewData *aData)
	{
	CUIKeyEvent* self=CUIKeyEvent::NewLC(aData);
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIKeyEvent::ConstructL()
	{
	}

TInt CUIKeyEvent::OfferKeyEventL(
		const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	TInt result = KUIKeyEventNone;
	switch(aType)
		{
		case EEventKey:
			switch (aKeyEvent.iCode)
				{
					case EKeyDevice3://ok
						StateChange();
						result = KUIKeyEventState;
						break;
					case EKeyUpArrow:
						iData->AddVolumeOneBlock();
						result = KUIKeyEventVolume;
						break;
					case EKeyDownArrow:
						iData->DecVolumeOneBlock();
						result = KUIKeyEventVolume;
						break;
				}
		break;
		}
	return result;
	}

void CUIKeyEvent::StateChange()
	{
	if (iData->GetPlayerState() == KPlayerStateStop)
		{
		iData->SetPlayerState(KPlayerStatePlay);
		}
	else if (iData->GetPlayerState() == KPlayerStatePlay)
		{
		iData->SetPlayerState(KPlayerStatePause);
		}
	else if (iData->GetPlayerState() == KPlayerStatePause)
		{
		iData->SetPlayerState(KPlayerStatePlay);
		}
	}