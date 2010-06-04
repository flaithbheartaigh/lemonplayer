// SMSDatagramService.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __SMSDATAGRAMSERVICE_H__
#define __SMSDATAGRAMSERVICE_H__

#include "Datagram.h"

// Forward Declarations
class CSMSSender;
class CSMSReceiver;

class CSMSDatagramService : public CBase
/**
@publishedAll

	An SMS Specific Datagram Service API. 

	CSMSDatagramSerive provides a simple way of sending SMS in 7Bit format most
	universally recognised. Sending binary data is not possible without first encoding
	the data in a method which will survive being 7Bit encoded.
*/
	{	
public:
	~CSMSDatagramService();
	static CSMSDatagramService* NewL();
	
	// from CDatagramService
	void SendL(CDatagram* aDatagram, TRequestStatus& aStatus);	
	void ReceiveL(CDatagram* aDatagram, const TDesC8& aRecvParams, TRequestStatus& aStatus);	

private:
	CSMSDatagramService();
	void ConstructL();
		
private:	
	
	/** Encapsulating Socket based send*/
	CSMSSender* iSender;
	/** Active object encapsulating Socket based receive*/
	CSMSReceiver* iReceiver;
	};

#endif
