/*
* ==============================================================================
*  Name        : smsdatagramreceiver.cpp
*  Part of     : 
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright (c) 2007 Symbian Ltd.  All rights reserved.
* ==============================================================================
*/

// INCLUDE FILES
#include "smsdatagramreceiver.h"
#include <e32std.h>
#include "Datagram.h"
#include "SMSDef.h"

const TUid KSMSDatagramServiceImplementationUID = {0x101FA9C3};
_LIT(KPanicSMSReceiver, "SMSRECEIVER");

CSmsDatagramReceiver* CSmsDatagramReceiver::NewL(MSmsDatagramReceiverObserver& aMsgOvserver)
	{
	CSmsDatagramReceiver* self = new (ELeave) CSmsDatagramReceiver(aMsgOvserver);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;	
	}
	

void CSmsDatagramReceiver::ConstructL()
	{
	// Create our buffer to store received data
	iSmsBuf = HBufC::NewMaxL(KMaxSMSSize);
		
	// Create the Datagram we wish to populate.
	iDatagram = CDatagram::NewL(*iSmsBuf);	
    CActiveScheduler::Add(this) ; // add to active scheduler
    
	}


CSmsDatagramReceiver::CSmsDatagramReceiver(MSmsDatagramReceiverObserver& aMsgOvserver)
		: CActive(EPriorityStandard), iMsgObserver(aMsgOvserver)
	{	
	}
	

CSmsDatagramReceiver::~CSmsDatagramReceiver()
	{
	Cancel();
	delete iSmsBuf;
	delete iDatagram;
	delete iReceiveService;
	delete iMatchPattern;	
	}


void CSmsDatagramReceiver::SetMatchPatternL(const TDesC8& aMatchPattern)
	{
	__ASSERT_ALWAYS(!IsActive(),User::Panic(KPanicSMSReceiver,KErrInUse));
	delete iMatchPattern;
	iMatchPattern=NULL;
	iMatchPattern = HBufC8::NewL(aMatchPattern.Length());
	*iMatchPattern=	aMatchPattern;
	}

	
void CSmsDatagramReceiver::StartReceiveL()
	{
	__ASSERT_ALWAYS(!IsActive(),User::Panic(KPanicSMSReceiver,KErrInUse));
	Cancel();
	//Check match pattern. Return if is active, otherwise restart
	delete iReceiveService;
	iReceiveService=NULL;
	iReceiveService = CSMSDatagramService::NewL();
	iReceiveService->ReceiveL(iDatagram, *iMatchPattern, iStatus);
	SetActive();
	}
		
void CSmsDatagramReceiver::DoCancel()
	{
	delete iReceiveService;
	iReceiveService=NULL;	//ensure no double deletion
	}
	
		
void CSmsDatagramReceiver::RunL()
	{
	User::LeaveIfError(iStatus.Int());
	TBuf<KMaxSMSSize> recvBuf;
	recvBuf.Copy(iDatagram->GetData());
	TBuf<KMaxAddressSize> recvNum;
	recvNum.Copy(iDatagram->GetAddress());
	iMsgObserver.MsgReceivedL(recvBuf,recvNum);
	StartReceiveL();	
	}




// End of File

