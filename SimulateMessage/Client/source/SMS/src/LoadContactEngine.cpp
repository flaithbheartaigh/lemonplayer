/*
 ============================================================================
 Name		: LoadContactEngine.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLoadContactEngine implementation
 ============================================================================
 */

#include "LoadContactEngine.h"

#include <f32file.h>
#include <coemain.h>
#include <s32file.h>

#define COMPARE_NUMBER_LENGTH 11

MLoadContactEngine::MLoadContactEngine() :
	iRemoveObserver(NULL)
	{
	// No implementation required
	}

MLoadContactEngine::~MLoadContactEngine()
	{
	}

void MLoadContactEngine::AddToContactArrayL(const TDesC& aName,
		const TDesC& aNumber, pCKCContactEntryArray aContactArray)
	{

	//会有一些名字号码都为空的情况
	if (aName.Compare(KNullDesC) == 0 && aNumber.Compare(KNullDesC) == 0)
		return;

	CKCContactEntry* entry = CKCContactEntry::NewL();
	entry->SetNameL(aName);
	entry->SetNumberL(aNumber);
	aContactArray->AppendL(entry);
	
	}


void MLoadContactEngine::AddToContactArrayL(const TDesC& aName,
		const TDesC& aNumber, pCKCContactEntryArray aContactArray,
		RStrMap& aHash)
	{

	//会有一些名字号码都为空的情况
	if (aName.Compare(KNullDesC) == 0 && aNumber.Compare(KNullDesC) == 0)
		return;

	//排重
	TPtrC key;
	key.Set(aNumber);
	HBufC* const * str = aHash.Find(key);
	if (str)
		{
		return;
		}

	//长度比较
	TStrMapIter mimeIter(aHash);
	for (HBufC* const * pMime = mimeIter.NextValue(); pMime; pMime
			= mimeIter.NextValue())
		{
		TPtrC number;
		number.Set((*pMime)->Des());
		
		if (IsSameNumber(number,aNumber))
			{
			HBufC* value = aNumber.AllocL();
			CleanupStack::PushL(value);
			aHash.InsertL(value->Des(), value);
			CleanupStack::Pop();
			return;
			}
		}

	HBufC* value = aNumber.AllocL();
	CleanupStack::PushL(value);
	aHash.InsertL(value->Des(), value);
	CleanupStack::Pop();

	CKCContactEntry* entry = CKCContactEntry::NewL();
	entry->SetNameL(aName);
	entry->SetNumberL(aNumber);
	aContactArray->AppendL(entry);
	
	}

void MLoadContactEngine::InitHashTable()
	{
	iHashTable = new RStrMap(&TPtrCHash, &TPtrCIdent);
	}
void MLoadContactEngine::ReleaseHashTable()
	{
	//	DestroyHashContents(iHashTable);
	if (iHashTable)
		{
		DestroyHashContents(iHashTable);
		iHashTable->Close();
		delete iHashTable;
		iHashTable = NULL;
		}
	}

TBool MLoadContactEngine::InsertHashTable(const TDesC& aValue, RStrMap& aHash)
	{
	HBufC* value = aValue.AllocL();
	CleanupStack::PushL(value);
	aHash.InsertL(value->Des(), value);
	CleanupStack::Pop();
	return ETrue;
	}

TBool MLoadContactEngine::IsSameNumber(const TDesC& aNumber1,const TDesC& aNumber2)
	{
	if (aNumber1.Length() > aNumber2.Length())
		return IsSameNumberShortFirst(aNumber2,aNumber1);
	else if (aNumber1.Length() < aNumber2.Length())
		return IsSameNumberShortFirst(aNumber1,aNumber2);
	else
		return (aNumber1.Compare(aNumber2) == 0);
	}


TBool MLoadContactEngine::IsSameNumberShortFirst(const TDesC& aNumberShort,const TDesC& aNumberLong)
	{
	TInt pos;
	pos = aNumberLong.Find(aNumberShort);
	if (pos != KErrNotFound && pos+aNumberShort.Length() == aNumberLong.Length())
		return ETrue;
	else if (aNumberShort.Length() >=COMPARE_NUMBER_LENGTH && aNumberLong.Length() >=COMPARE_NUMBER_LENGTH && 
			aNumberShort.Right(COMPARE_NUMBER_LENGTH).Compare(aNumberLong.Right(COMPARE_NUMBER_LENGTH)) == 0)
		return ETrue;
	else
		return EFalse;
	}

TBool MLoadContactEngine::IsInHashTable(const TDesC& aNumber,RStrMap& aHash)
	{
	//排重
	TPtrC key;
	key.Set(aNumber);
	HBufC* const * str = aHash.Find(key);
	if (str)
		{
		return ETrue;
		}

	//长度比较
	TStrMapIter mimeIter(aHash);
	for (HBufC* const * pMime = mimeIter.NextValue(); pMime; pMime
			= mimeIter.NextValue())
		{
		TPtrC number;
		number.Set((*pMime)->Des());
		
		if (IsSameNumber(number,aNumber))
			{
			InsertHashTable(aNumber,aHash);
			return ETrue;
			}
		}

	return EFalse;
	}


void MLoadContactEngine::SetRemoveObserver(
		MRemoveContentEngineObserver* aObserver)
	{
	iRemoveObserver = aObserver;
	}


