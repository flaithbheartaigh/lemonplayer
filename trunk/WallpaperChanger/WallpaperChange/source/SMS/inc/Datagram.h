// DatagramService.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __DATAGRAM_H__
#define __DATAGRAM_H__

#include <e32base.h>
#include <e32std.h>

/** DatagramService ECOM UID */
const TUid KDatagramServiceInterfaceUID = {0x101FA9C1};
	

/*	class CDatagram
	Send and Receive data storage
*/

class CDatagram : public CBase
/**
	@publishedAll

	Comments : The API for a single datagram to be sent via a Datagram Service, or as a receptical
	for an incoming datagram. 			.
*/

	{
public:

	static CDatagram* NewL(TDesC& aBuf);
	static CDatagram* NewL(const TDesC& aBuf, const TDesC& aAddress);	
	virtual ~CDatagram();

	// Accessors/mutators
	virtual const TDesC& GetAddress();
	virtual void  SetAddressL(const TDesC& aAddress);
	virtual const TDesC& GetData();
	virtual void  SetDataL(const TDesC& aData);

private: 
	void ConstructL(const TDesC& aBuf);

private:

	/** Buffer for the incoming outgoing message */
	HBufC* iData;

	/** Buffer for the outgoing address */
	HBufC* iAddress;

	};	


#endif
