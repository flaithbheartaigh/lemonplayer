/*
 ============================================================================
 Name		: RSAUtil.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRSAUtil implementation
 ============================================================================
 */

#include "RSAUtil.h"
#include "BigInt.h"

CRSAUtil::CRSAUtil()
	{
	// No implementation required
	}

CRSAUtil::~CRSAUtil()
	{
	}

CRSAUtil* CRSAUtil::NewLC()
	{
	CRSAUtil* self = new (ELeave) CRSAUtil();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CRSAUtil* CRSAUtil::NewL()
	{
	CRSAUtil* self = CRSAUtil::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CRSAUtil::ConstructL()
	{

	}

HBufC8* CRSAUtil::Encode(const TDesC8& aSource,const TDesC8& aE,const TDesC8& aN)
	{
	CBigInt e,n,s,d;
	TBuf8<BI_MAXLEN> dest;
	e.Get(aE);
	n.Get(aN);
	s.Get(aSource);
	
	d.Mov(s.RsaTrans(e,n));
	d.Put(dest);
	
	return dest.Alloc();
	}

HBufC8* CRSAUtil::Decode(const TDesC8& aSource,const TDesC8& aD,const TDesC8& aN)
	{
	CBigInt d,n,s,ds;
	TBuf8<BI_MAXLEN> dest;
	d.Get(aD);
	n.Get(aN);
	s.Get(aSource);
		
	ds.Mov(s.RsaTrans(d,n));
	ds.Put(dest);
	
	return dest.Alloc();	
	}
