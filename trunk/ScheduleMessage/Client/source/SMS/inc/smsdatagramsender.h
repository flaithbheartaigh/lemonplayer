/*
* ==============================================================================
*  Name        : smsdatagramsender.h
*  Copyright (c) 2007 Symbian Ltd.  All rights reserved.
* ==============================================================================
*/

#ifndef __SMSDATAGRAMSENDER_H__
#define __SMSDATAGRAMSENDER_H__

// INCLUDES
#include "Datagram.h"
#include "SMSDatagramService.h"
// FORWARD DECLARATIONS
//

// CLASS DECLARATION
/**
* MSmsDatagramSenderObserver sender observer interface
* Observer for sent messages
*/


class MSmsDatagramSenderObserver
	{
public:	
	virtual void MsgSentL(TDesC& aMsg)=0;
	virtual void MsgSentErr(const TInt& aError) = 0;
	};


	
class CSmsDatagramSender: public CActive
	{
public:
	static CSmsDatagramSender* NewL(MSmsDatagramSenderObserver& aMsgOvserver);
	~CSmsDatagramSender();
public:
	void SendAsyncL(const TDesC& aMessage, const TDesC& aPhoneNumber);
	virtual void DoCancel();
	virtual void RunL();
private:
	CSmsDatagramSender(MSmsDatagramSenderObserver& aMsgOvserver);
	void ConstructL();	
private:
	CSMSDatagramService* iSendService;	
	CDatagram* iDatagram;
	MSmsDatagramSenderObserver& iMsgObserver;	//not owned by this class	
	};	


#endif // __SMSDATAGRAMSENDER_H__

// End of File

