/*
 ============================================================================
 Name		: OKCModel.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : COKCModel implementation
 ============================================================================
 */

#include "OKCModel.h"
#include "MacroUtil.h"

COKCModel::COKCModel() 
	{
	// No implementation required
	}

COKCModel::~COKCModel()
	{
	}

COKCModel* COKCModel::NewLC()
	{
	COKCModel* self = new (ELeave) COKCModel();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

COKCModel* COKCModel::NewL()
	{
	COKCModel* self = COKCModel::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void COKCModel::ConstructL()
	{
	}

