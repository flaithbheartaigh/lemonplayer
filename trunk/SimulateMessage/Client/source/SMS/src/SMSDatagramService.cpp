// SMSDatagramService.cpp
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#include "SMSDatagramService.h"
#include "SMSSendRecv.h"

CSMSDatagramService::CSMSDatagramService()
	{
	
	}

CSMSDatagramService::~CSMSDatagramService()
/**
	ECOM will destroy the current instance. We also clean up our internal 
	send and receiver helper classes.
*/
	{
	delete iSender;
	delete iReceiver;
	}


CSMSDatagramService* CSMSDatagramService::NewL()
/**
	Intended Usage: Static factory constructor. Uses two phase 
	construction and leaves nothing on the CleanupStack.

	Will be called explicitly by the ECOM framework.

	@returns a new CSMSDatagramService instance.
*/	
	{
	CSMSDatagramService* self = new (ELeave) CSMSDatagramService();
	CleanupStack::PushL(self);
	self->ConstructL();	
	CleanupStack::Pop();
	return self;
	}


void CSMSDatagramService::ConstructL()
/**
	Intended Usage: Static factory constructor. Uses two phase 
	construction and leaves an instance of CSMSDatagramService on the CleanupStack.

	@returns a new CSMSDatagramService instance.
*/	
	{	
	iSender = CSMSSender::NewL();
	iReceiver = CSMSReceiver::NewL();
	}


void CSMSDatagramService::SendL(CDatagram* aDatagram, TRequestStatus& aStatus)
/**
	Send an SMS Asynchronously
	@param aDatagram CDatagram to be sent
	@param aStatus Clients TRequestStatus which will be notified of completion of send
	@capability NetworkServices
	@capability ReadUserData
*/
	{
	iSender->SendSMSL(aDatagram->GetData(), aDatagram->GetAddress(), aStatus);
	}


void CSMSDatagramService::ReceiveL(CDatagram* aDatagram,  const TDesC8& aRecvParams, TRequestStatus& aStatus)
/**
	Receive an SMS message Asynchronously
	@param aDatagram CDatagram to be populated during receive.
	@param aRecvParams buffer pattern match at beginning of incoming SMS message. Only SMS 
	messages containing this Pattern match will be intercepted. Example: //MYPATTERN 
	@param aStatus Clients TRequestStatus which will be notified of completion of Receive
	@capability NetworkServices
	@capability ReadUserData
*/
	{
	iReceiver->ListenForSMSL(aRecvParams, aDatagram, aStatus);
	}

