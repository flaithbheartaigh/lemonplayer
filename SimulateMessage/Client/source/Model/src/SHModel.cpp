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

CSHModel::CSHModel()
	{
	// No implementation required
	}

CSHModel::~CSHModel()
	{
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
