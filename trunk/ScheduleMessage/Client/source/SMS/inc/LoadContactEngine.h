/*
 ============================================================================
 Name		: LoadContactEngine.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLoadContactEngine declaration
 ============================================================================
 */

#ifndef LOADCONTACTENGINE_H
#define LOADCONTACTENGINE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <badesca.h>
#include <e32hashtab.h>
#include <e32cmn.h>

// CLASS DECLARATION
#include "EventsObserver.h"
#include "KCContactEntry.h"

//哈希表
typedef RHashMap<TPtrC, HBufC*> RStrMap;
typedef THashMapIter<TPtrC, HBufC*> TStrMapIter;

typedef RPointerArray<CKCContactEntry> CKCContactEntryArray,*pCKCContactEntryArray;

/**
 *  CLoadContactEngine
 * 
 */
// RHashMap does not support TPtrC8 as a native key type
// so we must provide the hash function.
inline TUint32 TPtrCHash(const TPtrC& aPtr)
	{
	return DefaultHash::Des16(aPtr);
	}

inline void DestroyHashContents(TAny* aHash)
	{
	RStrMap& hash = *static_cast<RStrMap*>(aHash);
	TStrMapIter mimeIter(hash);
	for (HBufC* const* pMime = mimeIter.NextValue(); pMime; pMime = mimeIter.NextValue())
		{
		delete *pMime;
		}
	}

// RHashMap does not support TPtrC8 as a native key type
// so we must provide the identity function.
inline TBool TPtrCIdent(const TPtrC& aL, const TPtrC& aR)
	{
	return DefaultIdentity::Des16(aL, aR);
	}

class MLoadContactEngine 
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	virtual ~MLoadContactEngine();
	MLoadContactEngine();

public:
	//根据不同情况读取电话,联系人姓名	
	void SetRemoveObserver(MRemoveContentEngineObserver* aObserver);
	
protected:
	void AddToContactArrayL(const TDesC& aName,const TDesC& aNumber,pCKCContactEntryArray aContactArray);
	void AddToContactArrayL(const TDesC& aName,const TDesC& aNumber,pCKCContactEntryArray aContactArray,RStrMap& aHash);
	
	void InitHashTable();
	void ReleaseHashTable();
	TBool InsertHashTable(const TDesC& aValue,RStrMap& aHash);
	
	TBool IsSameNumber(const TDesC& aNumber1,const TDesC& aNumber2);
	TBool IsSameNumberShortFirst(const TDesC& aNumberShort,const TDesC& aNumberLong);
	
	TBool IsInHashTable(const TDesC& aNumber,RStrMap& aHash);
	
	
public:
	//测试方法

protected:
	MRemoveContentEngineObserver* iRemoveObserver;
	
	pCKCContactEntryArray iContactArray;		//不保存数据 异步用	
	
	RStrMap* iHashTable;
	
	};

#endif // LOADCONTACTENGINE_H
