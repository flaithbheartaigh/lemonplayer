/*
 ============================================================================
 Name		: LogoView.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLogoView implementation
 ============================================================================
 */
#include <aknviewappui.h>
#include "LogoView.h"

#include "TimeOutTimer.h"
#include "MacroUtil.h"
#include "SHPlatform.h"

#define LOGOD_DELAY_TIME 1000000

CLogoView::CLogoView()
	{
	// No implementation required
	iContainer = NULL;
	}

CLogoView::~CLogoView()
	{
	DoDeactivate();
		SAFE_DELETE_ACTIVE(iTimer);
	}

CLogoView* CLogoView::NewLC()
	{
	CLogoView* self = new (ELeave) CLogoView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLogoView* CLogoView::NewL()
	{
	CLogoView* self = CLogoView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CLogoView::ConstructL()
	{
	BaseConstructL();
	}

TUid CLogoView::Id() const
	{
	return TUid::Uid(ESHLogoViewId);
	}

void CLogoView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}

//void CLogoView::HandleStatusPaneSizeChange()
//	{
//	if (iContainer != NULL)
//		iContainer->SetRect(AppUi()->ApplicationRect());
//	}

/**
 * 
 * */
void CLogoView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (iContainer == NULL)
		{
		iTimer = CTimeOutTimer::NewL(CActive::EPriorityStandard, *this);
		iTimer->After(LOGOD_DELAY_TIME);

		iContainer = CLogoContainer::NewL(AppUi()->ApplicationRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...
		}
	}
void CLogoView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}

void CLogoView::TimerExpired()
	{
	AppUi()->ActivateLocalViewL(TUid::Uid(EScheduleKillerMainScreenViewId));
	}
