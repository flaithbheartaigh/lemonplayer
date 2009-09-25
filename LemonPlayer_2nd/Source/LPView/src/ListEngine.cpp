/*
 ============================================================================
 Name		: ListEngine.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListEngine implementation
 ============================================================================
 */
#include <f32file.h>
#include <coemain.h>

#include "ListEngine.h"

CListEngine::CListEngine()
	{
	// No implementation required
	}

CListEngine::~CListEngine()
	{
	}

CListEngine* CListEngine::NewLC()
	{
	CListEngine* self = new (ELeave)CListEngine();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CListEngine* CListEngine::NewL()
	{
	CListEngine* self=CListEngine::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CListEngine::ConstructL()
	{

	}

void CListEngine::GetJarPath()
	{
	_LIT(iSkinFileDir,"C:\\Data\\");

	CDirScan* ds = CDirScan::NewLC(CCoeEnv::Static()->FsSession());
	TRAPD(err,ds->SetScanDataL(iSkinFileDir,KEntryAttDir,ESortByName|EAscending,CDirScan::EScanDownTree))
	;
	if (err!=KErrNone)
		{
		CleanupStack::PopAndDestroy(ds);
		return;
		}

	CDir* c= NULL;
	TFileName fullname;
	//		while (1)
	//			{

	ds->NextL(c);
	//			if (!c)
	//				break;

//	RLog::Log(c->Count());
//	RLog::Log(ds->FullPath());
	for (TInt i=0; i<c->Count(); i++)
		{
		const TEntry e= (*c)[i];

		fullname.Copy(ds->FullPath());
		fullname.Append(e.iName);
//		RLog::Log(ds->FullPath());
//		//				RLog::Log(e.iName);
//		RLog::Log(fullname);

		//				TParsePtrC p(fullname);
		//				RLog::Log(p.NameAndExt());

		}
	delete c;
	c=NULL;
	//			}

	CleanupStack::PopAndDestroy(ds);
	}

//RArray<TFileName> CListEngine::ScanDir(const TDesC &aPath)
//	{
//	RArray<TFileName> iArray;
//
//	CDirScan* ds = CDirScan::NewLC(CCoeEnv::Static()->FsSession());
//	TRAPD(err,ds->SetScanDataL(aPath,KEntryAttDir,ESortByName|EAscending,CDirScan::EScanDownTree))
//	;
//	if (err!=KErrNone)
//		{
//		CleanupStack::PopAndDestroy(ds);
//		return;
//		}
//
//	CDir* c= NULL;
//	TFileName fullname;
//
//	ds->NextL(c);
//	
//	for (TInt i=0; i<c->Count(); i++)
//		{
//		const TEntry e= (*c)[i];
//
//		fullname.Copy(ds->FullPath());
//		fullname.Append(e.iName);
//		
//		RLog::Log(fullname);
//		iArray.Append(fullname);
//
//		}
//	delete c;
//	c=NULL;
//
//	CleanupStack::PopAndDestroy(ds);
//	
//	return iArray;
//	}

RPointerArray<TListItem>* CListEngine::ScanDir(const TDesC &aPath)
	{
	RPointerArray<TListItem> *iArray = new RPointerArray<TListItem>;

	CDirScan* ds = CDirScan::NewLC(CCoeEnv::Static()->FsSession());
	TRAPD(err,ds->SetScanDataL(aPath,KEntryAttDir,ESortByName|EAscending,CDirScan::EScanDownTree))
	;
	if (err!=KErrNone)
		{
		CleanupStack::PopAndDestroy(ds);
		return NULL;
		}

	CDir* c= NULL;
	TFileName fullname;

	TRAPD(errNext,ds->NextL(c))
	if(errNext != KErrNone)
		{
		return NULL;
		}
	
	for (TInt i=0; i<c->Count(); i++)
		{
		const TEntry e= (*c)[i];

		fullname.Copy(ds->FullPath());
		fullname.Append(e.iName);
		
		TListItem* item = new TListItem;
		item->iFullpath = fullname;
		item->iName = e.iName;
		if (e.IsDir())
			item->iPref = EItemTypeDir;
		else
			item->iPref = EItemTypeFile;
		iArray->Append(item);

		}
	delete c;
	c=NULL;

	CleanupStack::PopAndDestroy(ds);
	
	return iArray;
	}
