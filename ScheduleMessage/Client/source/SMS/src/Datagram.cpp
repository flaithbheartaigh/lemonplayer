// Datagram.cpp
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//
// CDatagram (implementation)


#include "Datagram.h"


CDatagram* CDatagram::NewL(TDesC& aBuf)
/**
	Intended Usage: Static factory constructor. Uses two phase 
	construction and leaves nothing on the CleanupStack.

	@param aBuf buffer to fill with incoming data
	@returns a new CDatagram instance.
*/
	{
	CDatagram* self = new(ELeave) CDatagram();
	CleanupStack::PushL(self);
	self->ConstructL(aBuf);
	CleanupStack::Pop();
	return self;
	}



CDatagram* CDatagram::NewL(const TDesC& aBuf, const TDesC& aAddress)
/**
	Intended Usage: Static factory constructor. Uses two phase 
	construction and leaves nothing on the CleanupStack.

	@param aBuf buffer containing data to send via service
	@param aAddress buffer containing datagram service specific outgoing address
	@returns a new CDatagram instance.
*/
	{
	CDatagram* self = new(ELeave) CDatagram();
	CleanupStack::PushL(self);
	self->ConstructL(aBuf);
	self->SetAddressL(aAddress);
	CleanupStack::Pop();
	return self;
	}



CDatagram::~CDatagram()
/**
	Deletes internal HBufC8 buffers.
*/
	{
	delete iAddress;
	delete iData;
	}



void CDatagram::ConstructL(const TDesC& aBuf)
/**
	Second phase of construction.
	@param aBuf external buffer. 
*/
    {
	iData = aBuf.AllocL();
    }



EXPORT_C const TDesC& CDatagram::GetAddress()
/**
	Accessor for the outgoing address information,

	@returns reference to outgoing address.
*/
	{
	return *iAddress;
	}



EXPORT_C void CDatagram::SetAddressL(const TDesC& aAddress)
/**
	Sets the current outgoing address.

	@param aAddress buffer containing datagram service specific outgoing address
*/
	{
	delete iAddress;
	iAddress = NULL;
	iAddress = aAddress.AllocL();
	}



EXPORT_C const TDesC& CDatagram::GetData()
/**
	Accessor for incoming message data received from datagram service.

	@returns Reference to internal buffer containing service specific incoming data.
*/
	{
	return *iData;
	}
	

	
EXPORT_C void CDatagram::SetDataL(const TDesC& aData)
/**
	Sets the outgoing data to be send via the datagram service.

	@param aData buffer containing data to send via service
*/
	{
	delete iData;
	iData = NULL;
	iData = aData.AllocL();
	}

