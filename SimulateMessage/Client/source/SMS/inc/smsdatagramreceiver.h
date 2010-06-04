/*
* ==============================================================================
*  Name        : smsdatagramreceiver.h
*  Copyright (c) 2007 Symbian Ltd.  All rights reserved.
* ==============================================================================
*/

#ifndef __SMSDATAGRAMRECEIVER_H__
#define __SMSDATAGRAMRECEIVER_H__

// INCLUDES
#include "Datagram.h"
#include "SMSDatagramService.h"
// FORWARD DECLARATIONS
//

// CLASS DECLARATION
/**
* MSmsDatagramReceiverObserver observer interface
* Implementations of this interface can register for notifications when datagram received.
*/




class MSmsDatagramReceiverObserver
	{
public:	
	virtual void MsgReceivedL(const TDesC& aMsg,const TDesC& aNumber) = 0;
	};


// CLASS DECLARATION
/**
* CSmsDatagramReceiver class is active object for receiving SMS datagrams and
* notifying the specified MSmsDatagramReceiverObserver.
*/	
class CSmsDatagramReceiver: public CActive
	{
public:
	static CSmsDatagramReceiver* NewL(MSmsDatagramReceiverObserver& aMsgOvserver);
	~CSmsDatagramReceiver();
public:
	void SetMatchPatternL(const TDesC8& aMatchPattern);
	void StartReceiveL();
	virtual void DoCancel();
	virtual void RunL();
private:
	CSmsDatagramReceiver(MSmsDatagramReceiverObserver& aMsgOvserver);
	void ConstructL();	
private:
	CSMSDatagramService* iReceiveService;	
	CDatagram* iDatagram;
	MSmsDatagramReceiverObserver& iMsgObserver;	//not owned by this class
	HBufC8* iMatchPattern;
	HBufC* iSmsBuf;	
	};	


#endif // __SMSDATAGRAMRECEIVER_H__

// End of File

