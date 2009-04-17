/*
 ============================================================================
 Name		: StreamRecordAdapter.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CStreamRecordAdapter implementation
 ============================================================================
 */

#include "StreamRecordAdapter.h"

CStreamRecordAdapter::CStreamRecordAdapter()
	{
	// No implementation required
	}

CStreamRecordAdapter::~CStreamRecordAdapter()
	{
	}

CStreamRecordAdapter* CStreamRecordAdapter::NewLC()
	{
	CStreamRecordAdapter* self = new (ELeave)CStreamRecordAdapter();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CStreamRecordAdapter* CStreamRecordAdapter::NewL()
	{
	CStreamRecordAdapter* self=CStreamRecordAdapter::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CStreamRecordAdapter::ConstructL()
	{

	}
