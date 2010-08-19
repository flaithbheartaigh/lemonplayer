// SMSSendRecv.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

// CSMSSender - Send SMS Asynchronously via SMSProt.prt 
// CSMSReceiver - Recieve SMS Asynchronously via SMSProt.prt 

#ifndef __SMSSENDRECV_H_
#define __SMSSENDRECV_H_

#include <e32base.h>
#include <e32math.h>
#include <es_sock.h>
#include <gsmumsg.h>
#include <gsmubuf.h>
#include <gsmuset.h>
#include <smsuaddr.h> 
#include <smsustrm.h>
#include <f32file.h>
#include "SMSDatagramService.h"
#include "SMSDef.h"

// Forward Declarations
class CSMSSender;
class CSMSReceiver;




class CSMSSender : public CBase
/**
	@internalComponent

	Comments : Responsible for opening SMS socket and sending SMS datagrams.
*/
	{

public:
	static CSMSSender* NewL();
	static CSMSSender* NewLC();
	~CSMSSender();

	void SendSMSL(const TDesC& aText, const TDesC& aAddress, TRequestStatus& aStatus);

protected:
	CSMSSender(){};
	void CreateSMSMessageL(const TDesC& aText, const TDesC& aAddress);
	void ConstructL();
private:
	/** Connection to Socket Server*/
	RSocketServ iSocketServer;
	/** Socket over which SMS will be sent*/
	RSocket iSocket;
	/** Connection to File server required by CSMSMessage API*/
	RFs iFs;
	/** parameter to RSocket::Ioctl()*/
	TPckgBuf<TUint> iBuf;
	};


class CSMSReceiver : public CActive
/**
	@internalComponent

	Comments : Active object responsible for opening SMS socket and receiving SMS datagrams.
*/
	{
public:
	enum TReceiveStatus 
		{
		EIdle, EListening, EAcknowledging
		};

public:
	static CSMSReceiver* NewL();
	static CSMSReceiver* NewLC();
	~CSMSReceiver();

	TInt ListenForSMSL(const TDesC8& aPattern, CDatagram* aDatagram);
	void ListenForSMSL(const TDesC8& aPattern, CDatagram* aDatagram, TRequestStatus& aStatus);

	//Implemented functions from CActive
	void DoCancel();
	void RunL();	
	
protected:
	CSMSReceiver();
	void ConstructL();
	void SetupSocketsL(const TDesC8& aPattern);
	void ExtractMessageL();

private:
	/** Connection to Socket Server*/
	RSocketServ iSocketServer;
	/** Socket over which SMS will be sent*/
	RSocket iSocket;
	/** Connection to File server required by CSMSMessage API*/
	RFs iFs;
	/** parameter to RSocket::Ioctl()*/	
	CSmsMessage* iSmsMsg;
	TPckgBuf<TUint> iBuf;
	/** Current state transition*/
	TReceiveStatus iReceiveStatus;
	/** TRequestStatus to be completed upon Receive*/
	TRequestStatus* iClientStatus; //Not owned by this class
	/** Datagram to be populated*/
	CDatagram* iDatagram; //Not owned by this class
	};



#endif


