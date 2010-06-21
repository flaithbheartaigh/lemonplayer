/*
 ============================================================================
 Name		: SHModel.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSHModel implementation
 ============================================================================
 */

#include "SHModel.h"
#include "MacroUtil.h"

CSHModel::CSHModel()
:iEditMessage(NULL)
	{
	// No implementation required
	}

CSHModel::~CSHModel()
	{
	SAFE_DELETE(iEditMessage)
	}

CSHModel* CSHModel::NewLC()
	{
	CSHModel* self = new (ELeave) CSHModel();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSHModel* CSHModel::NewL()
	{
	CSHModel* self = CSHModel::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CSHModel::ConstructL()
	{
	
	}

void CSHModel::SetEditMessage(SimMsgData* aMsg)
	{
	SAFE_DELETE(iEditMessage)
	
	iEditMessage = new (ELeave) SimMsgData;
	if (aMsg->iName)
		iEditMessage->iName = aMsg->iName->AllocL();
	else
		iEditMessage->iName	= KNullDesC().AllocL();
	iEditMessage->iNumber 	= aMsg->iNumber->AllocL();
	iEditMessage->iTime 	= aMsg->iTime;
	iEditMessage->iContent 	= aMsg->iContent->AllocL();
	}
