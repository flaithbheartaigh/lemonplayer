/*
 ============================================================================
 Name		: ViewMotify.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CViewMotify implementation
 ============================================================================
 */

#include "ViewNotify.h"

CViewMotify::CViewMotify()
	{
	// No implementation required
	}

CViewMotify::~CViewMotify()
	{
	}

CViewMotify* CViewMotify::NewLC()
	{
	CViewMotify* self = new (ELeave)CViewMotify();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CViewMotify* CViewMotify::NewL()
	{
	CViewMotify* self=CViewMotify::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CViewMotify::ConstructL()
	{

	}
