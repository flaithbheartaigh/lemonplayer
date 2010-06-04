/*
 ============================================================================
 Name		: KCContactEntry.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : sohu
 Description : CKCContactEntry implementation
 ============================================================================
 */

#include "KCContactEntry.h"
#include "MacroUtil.h"

CKCContactEntry::CKCContactEntry()
	{
	// No implementation required
	iName = NULL;
	iNumber = NULL;
	}

CKCContactEntry::~CKCContactEntry()
	{
	SAFE_DELETE(iName);
	SAFE_DELETE(iNumber);
	}

CKCContactEntry* CKCContactEntry::NewLC()
	{
	CKCContactEntry* self = new (ELeave) CKCContactEntry();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CKCContactEntry* CKCContactEntry::NewL()
	{
	CKCContactEntry* self = CKCContactEntry::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CKCContactEntry::ConstructL()
	{

	}

void CKCContactEntry::SetNameL(const TDesC& aName)
	{
	iName = HBufC::NewL(aName.Length());
	iName->Des().Copy(aName);
	iName->Des().TrimAll();
	}


void CKCContactEntry::SetNumberL(const TDesC& aNumber)
	{
	iNumber = HBufC::NewL(aNumber.Length());
	iNumber->Des().Copy(aNumber);
	iNumber->Des().TrimAll();
	}
