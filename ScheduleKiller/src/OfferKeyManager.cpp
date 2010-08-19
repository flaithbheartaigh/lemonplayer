/*
 ============================================================================
 Name		: OfferKeyManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : COfferKeyManager implementation
 ============================================================================
 */

#include "OfferKeyManager.h"
#include "MacroUtil.h"
#include "SHPlatform.h"

COfferKeyManager::COfferKeyManager()
:iActive(EFalse)
	{
	// No implementation required
	}

COfferKeyManager::~COfferKeyManager()
	{
	SAFE_DELETE_ACTIVE(iTimer);
	}

COfferKeyManager* COfferKeyManager::NewLC()
	{
	COfferKeyManager* self = new (ELeave) COfferKeyManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

COfferKeyManager* COfferKeyManager::NewL()
	{
	COfferKeyManager* self = COfferKeyManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void COfferKeyManager::TimerExpired()
	{
	iActive = EFalse;
	}

void COfferKeyManager::ConstructL()
	{
	iTimer = CTimeOutTimer::NewL(CActive::EPriorityStandard,*this);
	}

void COfferKeyManager::StartTimer()
	{
	iTimer->Cancel();
	iTimer->After(1000000);
	}

TKeyResponse COfferKeyManager::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	if (aType != EEventKey)
		return EKeyWasNotConsumed;
	
	TInt code = aKeyEvent.iCode;

	if (code == '#')
		{
		iActive = ETrue;
		StartTimer();
		return EKeyWasConsumed;
		}
	else if (code >= '1' && code <= '9')
		{
		if (iActive)
			{
			TInt index = code - '1';
			if (SHModel()->GetRuleManager()->Select(index))
				return EKeyWasConsumed;
			}
		}
	return EKeyWasNotConsumed;
	}
