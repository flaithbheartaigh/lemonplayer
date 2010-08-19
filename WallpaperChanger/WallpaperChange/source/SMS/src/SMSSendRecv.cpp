// SMSSendRecv.cpp
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#include "SMSSendRecv.h"

//To get SMS service centre address
#include <SMUTSET.H>  
#include <MSVAPI.H>

#include "OKCDebug.h"


#ifdef EKA2
	#include <csmsaccount.h>
#else
	//Observer class, required to get the service centre address before EKA2
	class CObserver : public MMsvSessionObserver
		{
	public:
		void HandleSessionEvent(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
		void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
		};
	void CObserver::HandleSessionEvent(TMsvSessionEvent /*aEvent*/, TAny* /*aArg1*/, TAny* /*aArg2*/, TAny* /*aArg3*/) {}
	void CObserver::HandleSessionEventL(TMsvSessionEvent /*aEvent*/, TAny* /*aArg1*/, TAny* /*aArg2*/, TAny* /*aArg3*/) {}
#endif


CSMSSender* CSMSSender::NewL()
/**
	Intended Usage: Static factory constructor. Uses two phase 
	construction and leaves nothing on the CleanupStack.

	@returns a new CSMSSender instance.
*/
	{
	CSMSSender* self = NewLC();
	CleanupStack::Pop();
	return self;
	}

CSMSSender* CSMSSender::NewLC()
/**
	Intended Usage: Static factory constructor. Uses two phase 
	construction and leaves a CSMSSender instance on the CleanupStack.

	@returns a new CSMSSender instance.
*/
	{
	CSMSSender* self = new(ELeave) CSMSSender;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

void CSMSSender::ConstructL()
/**
	Second phase of construction, opens connections to the Socket Server and File server,
	and opens an SMS socket.
*/
	{
	iSocketServer.Connect();
	iFs.Connect();
	User::LeaveIfError(iSocket.Open(iSocketServer, KSMSAddrFamily, KSockDatagram, KSMSDatagramProtocol));
	}

CSMSSender::~CSMSSender() 
/**
	Close the connections to the Socket Server, Socket and File Server
*/
	{
	iSocket.Close();
	iSocketServer.Close();
	iFs.Close();
	}


void CSMSSender::CreateSMSMessageL(const TDesC& aText, const TDesC& aAddress)
/**
	Prepare SMS specific objects ready to send via ESOCK
	@param aText buffer containing ascii contents of message to send
	@param aAddress buffer with telephone number of SMS receiver 
*/
	{
	TSmsAddr smsAddr;
    smsAddr.SetSmsAddrFamily(ESmsAddrSendOnly);
    smsAddr.SetPort(smsAddr.Port() + 1);//ycf
    __LOGSTR_TOFILE("sockent bind");
	iSocket.Bind(smsAddr);

	CSmsBuffer* smsBuffer = CSmsBuffer::NewL();
	//CleanupStack::PushL(smsBuffer) is NOT used because CSmsMessage takes ownership of our buffer :-)
	CSmsMessage* smsMsg = CSmsMessage::NewL(iFs, CSmsPDU::ESmsSubmit, smsBuffer);
	CleanupStack::PushL(smsMsg);
	
	TSmsUserDataSettings smsSettings;
    smsSettings.SetAlphabet(TSmsDataCodingScheme::ESmsAlphabetUCS2);
	smsSettings.SetTextCompressed(EFalse);
	smsMsg->SetUserDataSettingsL(smsSettings);
	
	TBuf<KMaxAddressSize> toAddress;
	toAddress.Copy(aAddress);
	smsMsg->SetToFromAddressL(toAddress);

	//Get service centre address.
	// The method used here assumes the SMS settings are provisioned, which is true in known cases.
	// There are alternative partner-only APIs, however this allow this source to be kept public
	#ifdef EKA2
		CSmsSettings* smsSCSettings = CSmsSettings::NewL();
		CleanupStack::PushL(smsSCSettings);
    	CSmsAccount* smsAccount=CSmsAccount::NewLC();
    	smsAccount->LoadSettingsL(*smsSCSettings);
 		// index of the default service centre address for this service
 		TInt defIndex;
		User::LeaveIfError(defIndex = smsSCSettings->DefaultServiceCenter());
 		// Get the service center address
		CSmsServiceCenter&  scAddr = smsSCSettings->GetServiceCenter(defIndex);
	
		TPtrC theAddress=scAddr.Address();
		HBufC* serviceCentreAddress=HBufC::NewLC(theAddress.Length());
		*serviceCentreAddress=theAddress;
		smsMsg->SmsPDU().SetServiceCenterAddressL(*serviceCentreAddress);
		CleanupStack::PopAndDestroy(serviceCentreAddress);//
		CleanupStack::PopAndDestroy(smsAccount);
		CleanupStack::PopAndDestroy(smsSCSettings);	
				
	#else
		TMsvId		serviceId;
		CObserver* pObserver = new (ELeave) CObserver();
		CleanupStack::PushL(pObserver);
		CMsvSession* pSession = CMsvSession::OpenSyncL(*pObserver);
		CleanupStack::PushL(pSession);
		TSmsUtilities::ServiceIdL(*pSession, serviceId, KUidMsgTypeSMS);
		CMsvEntry* service = pSession->GetEntryL(serviceId);
		CleanupStack::PushL(service);
		CMsvStore* msvstore = service->ReadStoreL();
		CleanupStack::PushL(msvstore);
		CSmsSettings* smsSCSettings = CSmsSettings::NewL();
		CleanupStack::PushL(smsSCSettings);
		smsSCSettings->RestoreL(*msvstore);
		TInt defIndex;
		User::LeaveIfError(defIndex = smsSCSettings->DefaultSC());
		defIndex = smsSCSettings->DefaultSC();
 		// Get the default service center address
		CSmsNumber&  scAddr = smsSCSettings->SCAddress(defIndex);
		TPtrC theAddress=scAddr.Address();
		HBufC* serviceCentreAddress=HBufC::NewLC(theAddress.Length());
		*serviceCentreAddress=theAddress;
		smsMsg->SmsPDU().SetServiceCenterAddressL(*serviceCentreAddress);
		CleanupStack::PopAndDestroy(serviceCentreAddress);//
		CleanupStack::PopAndDestroy(smsSCSettings); //smsSettings
		CleanupStack::PopAndDestroy(msvstore);
		CleanupStack::PopAndDestroy(service);
		CleanupStack::PopAndDestroy(pSession);
		CleanupStack::PopAndDestroy(pObserver);		
	#endif
	
	//convert to wide
	HBufC* payload = HBufC::NewL(aText.Length());
	CleanupStack::PushL(payload);
	TPtr pPayload=payload->Des();
	pPayload.Copy(aText); //copy from narrow to wide and convert
	smsBuffer->InsertL(0, pPayload); //copies payload
	RSmsSocketWriteStream writeStream(iSocket);
	CleanupClosePushL(writeStream);
	writeStream << *smsMsg; // remember << operator _CAN_ leave
	__LOGSTR_TOFILE("write stream commit");
	writeStream.CommitL();
	CleanupStack::PopAndDestroy(&writeStream);
	CleanupStack::PopAndDestroy(2);//smsMsg, payload	
	}


void CSMSSender::SendSMSL(const TDesC& aText, const TDesC& aAddress, TRequestStatus& aStatus)
/**
	Send an SMS message Asynchronously
	@param aText buffer containing ascii contents of message to send
	@param aAddress buffer with telephone number of SMS receiver 
	@param aStatus TRequestStatus which receives completion notification following a Send
	@capability NetworkServices
	@capability ReadUserData	
*/
	{
	__LOGSTR_TOFILE("create message");
	CreateSMSMessageL(aText, aAddress);
	__LOGSTR_TOFILE("socket ioctl");
	iSocket.Ioctl(KIoctlSendSmsMessage, aStatus, &iBuf, KSolSmsProv);
	__LOGSTR_TOFILE("send sms end");
	}


/*
	CSMSReceiver
*/

// Construction functions
CSMSReceiver::CSMSReceiver() : CActive(EPriorityStandard)
/**
	Standard priortiy active object.
*/
	{
	}

CSMSReceiver* CSMSReceiver::NewL()
/**
	Intended Usage: Static factory constructor. Uses two phase 
	construction and leaves nothing on the CleanupStack.

	@returns a new CSMSSender instance.
*/
	{
	CSMSReceiver* self = NewLC();
	CleanupStack::Pop();
	return self;
	}

CSMSReceiver* CSMSReceiver::NewLC()
/**
	Intended Usage: Static factory constructor. Uses two phase 
	construction and leaves an instance of CSMSReceiver on the CleanupStack.

	@returns a new CSMSSender instance.
*/
	{
	CSMSReceiver* self = new(ELeave) CSMSReceiver;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

void CSMSReceiver::ConstructL()
/**
	Second phase of construction, opens connections to the Socket Server and File server,
	and opens an SMS socket.
*/
	{
	iSocketServer.Connect();
	iFs.Connect();
	User::LeaveIfError(iSocket.Open(iSocketServer, KSMSAddrFamily, KSockDatagram, KSMSDatagramProtocol));
	iReceiveStatus = EIdle;
	CActiveScheduler::Add(this);
	}

CSMSReceiver::~CSMSReceiver() 
/**
	Cancels any outstanding Receive, before closing sessions with the Socket and File Servers.
*/
	{
	Cancel(); //Cancel any outstanding Receiver
	iSocket.Close();
	iSocketServer.Close();
	iFs.Close();
	if(iSmsMsg)
		{
		delete iSmsMsg;
		}
	}

void CSMSReceiver::RunL()
/**
	Handle asynchronous receive which is a two step process. 
	1. Accept and process an incoming SMS
	2. Inform network that you received the message and not to try a resend.

	Then we can complete the clients TRequestStatus we stored earlier
*/
	{
	switch (iReceiveStatus)
		{
		case EListening:	
			{
			// Got an SMS, lets extract it
			ExtractMessageL();
			// And now let the network know that we received the message so that we
			// do not receive another attempt
			iSocket.Ioctl(KIoctlReadMessageSucceeded, iStatus, &iBuf, KSolSmsProv);
			iReceiveStatus = EAcknowledging;
			SetActive();
			break;
			}
		case EAcknowledging:	
			// Finished Network acknowledgement. Client now needs to be informed 
			// of the outcome
			User::RequestComplete(iClientStatus, iStatus.Int());
			break;
		default:
			User::Panic(_L("Not Possible to be in RunL in Idle state"),KErrUnknown);
			break;
		}
	}

void CSMSReceiver::DoCancel()
/**
	Cancel any outstanding Ioctls.
*/
	{
	iSocket.CancelIoctl();
	User::RequestComplete(iClientStatus, KErrCancel);
	}


void CSMSReceiver::SetupSocketsL(const TDesC8& aPattern)
/**
	Bind to socket and specify pattern match so that only incoming messages matching
	the pattern are intercepted. Other messages will be caught by the messaging component.
	
	@param aPattern buffer pattern match at beginning of incoming SMS message. Only SMS 
	messages containing this Pattern match will be intercepted.
*/
	{
    TSmsAddr smsAddr;
	smsAddr.SetSmsAddrFamily(ESmsAddrMatchText);
	smsAddr.SetTextMatch(aPattern);
	
//	smsAddr.SetSmsAddrFamily(ESmsAddrApplication16BitPort);
//	smsAddr.SetPort(111); //kjava»½ÐÑ¶Ë¿Ú	
	
	User::LeaveIfError(iSocket.Bind(smsAddr));
	
	}


void CSMSReceiver::ExtractMessageL()
/**
	Following receive extract the contents of the message and store within CDatagram object.
*/
	{
	CSmsBuffer* buffer;
	buffer=CSmsBuffer::NewL();
	//CleanupStack::PushL(buffer) is NOT used because CSmsMessage takes ownership of our buffer :-)
	
	iSmsMsg = CSmsMessage::NewL(iFs, CSmsPDU::ESmsSubmit, buffer);
	RSmsSocketReadStream readStream(iSocket);
	CleanupClosePushL(readStream);
	readStream >> *iSmsMsg;
	CleanupStack::PopAndDestroy(&readStream);

	HBufC* dgram = HBufC::NewLC(KMaxSMSSize);
	TPtr ptr = dgram->Des();
	buffer->Extract(ptr, 0, buffer->Length());

	// Convert from unicode data 
	TBuf<KMaxSMSSize> buf; // it is ok to do this on the stack because SMS size is small
	buf.Copy(*dgram);
	iDatagram->SetDataL(buf);
	
	//ycf
	TPtrC addr = iSmsMsg->ToFromAddress();
	TBuf<KMaxSMSSize> bufAddr; // it is ok to do this on the stack because SMS size is small
	bufAddr.Copy( addr );
	iDatagram->SetAddressL( bufAddr );
	//ycf
	
	if (iSmsMsg)
		{
		delete iSmsMsg;
		iSmsMsg=NULL;
		}
	
//	RLog::Log(*dgram);
	
	CleanupStack::PopAndDestroy(); //dgram	
	
	}


void CSMSReceiver::ListenForSMSL(const TDesC8& aPattern, CDatagram* aDatagram, TRequestStatus& aStatus)
/**
	Receive an SMS message Asynchronously
	@param aPattern buffer pattern match at beginning of incoming SMS message. Only SMS 
	messages containing this Pattern match will be intercepted. Example: //MYPATTERN 

    @param aDatagram CDatagram to be populated during receive.
	@param aStatus will receive completion notification following receive
*/
	{
	aStatus = KRequestPending;
	iDatagram = aDatagram;
	iClientStatus = &aStatus;
	SetupSocketsL(aPattern);
    iBuf()=KSockSelectRead;
    iSocket.Ioctl(KIOctlSelect, iStatus, &iBuf,KSOLSocket);
	iReceiveStatus = EListening;
	SetActive();
	}



