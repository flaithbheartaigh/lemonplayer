/*
 * ==============================================================================
 *  Name        : smsdatagramsender.cpp
 *  Part of     : 
 *  Interface   : 
 *  Description : 
 *  Version     : 
 *
 *  Copyright (c) 2007 Symbian Ltd.  All rights reserved.
 * ==============================================================================
 */

// INCLUDE FILES
#include "smsdatagramsender.h"
#include "OKCDebug.h"
#include "SMSDef.h"

const TUid KSMSDatagramServiceImplementationUID =
	{
	0x101FA9C3
	};
_LIT(KPanicSMSSender,"SMSSender");

CSmsDatagramSender* CSmsDatagramSender::NewL(
		MSmsDatagramSenderObserver& aMsgOvserver)
	{
	CSmsDatagramSender* self = new (ELeave) CSmsDatagramSender(aMsgOvserver);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

void CSmsDatagramSender::ConstructL()
	{
	CActiveScheduler::Add(this); // add to active scheduler
	}

CSmsDatagramSender::CSmsDatagramSender(MSmsDatagramSenderObserver& aMsgOvserver) :
	CActive(EPriorityStandard), iMsgObserver(aMsgOvserver)
	{
	}

CSmsDatagramSender::~CSmsDatagramSender()
	{
	Cancel();
	delete iDatagram;
	delete iSendService;
	}

void CSmsDatagramSender::SendAsyncL(const TDesC& aMessage,
		const TDesC& aPhoneNumber)
	{
	__ASSERT_ALWAYS(!IsActive(),User::Panic(KPanicSMSSender,KErrInUse));

	delete iDatagram;
	iDatagram = NULL;
	iDatagram = CDatagram::NewL(aMessage, aPhoneNumber);

	// and now send it asynchronously
	delete iSendService;
	iSendService = NULL;
	iSendService = CSMSDatagramService::NewL();
	iSendService->SendL(iDatagram, iStatus);
	SetActive();
	}

void CSmsDatagramSender::DoCancel()
	{
	delete iSendService;
	iSendService = NULL;
	}

void CSmsDatagramSender::RunL()
	{
	TInt status = iStatus.Int();
	if (status == KErrNone)
		{
		User::LeaveIfError(iStatus.Int());

		TBuf<KMaxSMSSize> sendBuf;
		sendBuf.Copy(iDatagram->GetData());
		iMsgObserver.MsgSentL(sendBuf);
		}
	else
		iMsgObserver.MsgSentErr(status);
	}

// End of File

