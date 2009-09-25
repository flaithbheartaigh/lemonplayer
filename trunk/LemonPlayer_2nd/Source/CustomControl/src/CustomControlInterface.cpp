/*
 ============================================================================
 Name		: CustomControlInterface.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCustomControlInterface implementation
 ============================================================================
 */

#include "CustomControlInterface.h"

CCustomControlInterface::CCustomControlInterface()
	{
	// No implementation required
	}

CCustomControlInterface::~CCustomControlInterface()
	{
	}

CCustomControlInterface* CCustomControlInterface::NewLC()
	{
	CCustomControlInterface* self = new (ELeave)CCustomControlInterface();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CCustomControlInterface* CCustomControlInterface::NewL()
	{
	CCustomControlInterface* self=CCustomControlInterface::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CCustomControlInterface::ConstructL()
	{

	}
