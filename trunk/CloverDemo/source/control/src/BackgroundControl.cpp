/*
 ============================================================================
 Name		: BackgroundControl.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CBackgroundControl implementation
 ============================================================================
 */

#include "BackgroundControl.h"

CBackgroundControl::CBackgroundControl()
	{
	// No implementation required
	}

CBackgroundControl::~CBackgroundControl()
	{
	}

CBackgroundControl* CBackgroundControl::NewLC()
	{
	CBackgroundControl* self = new (ELeave) CBackgroundControl();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CBackgroundControl* CBackgroundControl::NewL()
	{
	CBackgroundControl* self = CBackgroundControl::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CBackgroundControl::ConstructL()
	{

	}
