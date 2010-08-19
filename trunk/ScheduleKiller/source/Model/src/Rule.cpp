/*
 ============================================================================
 Name		: Rule.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRule implementation
 ============================================================================
 */

#include "Rule.h"

CRule::CRule()
:iName(NULL),iRuleName(NULL)
	{
	// No implementation required
	}

CRule::~CRule()
	{
	SAFE_DELETE(iName)
	SAFE_DELETE(iRuleName)
	}

CRule* CRule::NewLC()
	{
	CRule* self = new (ELeave) CRule();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CRule* CRule::NewL()
	{
	CRule* self = CRule::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CRule::ConstructL()
	{

	}
