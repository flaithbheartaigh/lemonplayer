/*
 ============================================================================
 Name		: SkinImageScan.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSkinImageScan implementation
 ============================================================================
 */

#include "SkinImageScan.h"
#include <f32file.h>
#include <coemain.h>
#include <bautils.h>

CSkinImageScan::CSkinImageScan()
	{
	// No implementation required
	}

CSkinImageScan::~CSkinImageScan()
	{
	iSkins.ResetAndDestroy();
	}

CSkinImageScan* CSkinImageScan::NewLC()
	{
	CSkinImageScan* self = new (ELeave) CSkinImageScan();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSkinImageScan* CSkinImageScan::NewL()
	{
	CSkinImageScan* self = CSkinImageScan::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CSkinImageScan::ConstructL()
	{

	}

void CSkinImageScan::ScanFolder(const TDes& aFolder)
	{
	CDirScan* ds = CDirScan::NewLC(CCoeEnv::Static()->FsSession());
	TRAPD(err,ds->SetScanDataL(aFolder,KEntryAttDir,ESortByName|EAscending,CDirScan::EScanDownTree))

	if (err != KErrNone)
		{
		CleanupStack::PopAndDestroy(ds);
		return;
		}

	CDir* c = NULL;
	TFileName fullname;
	TRAPD(errNext,ds->NextL(c))
	if (errNext != KErrNone)
		{
		return;
		}

	iSkins.ResetAndDestroy();
	TInt index = 0;
	for (TInt i = 0; i < c->Count(); i++)
		{
		const TEntry e = (*c)[i];

		fullname.Copy(ds->FullPath());
		fullname.Append(e.iName);

		if (!e.IsDir())
			{
			pSkinImageStruct item = new SkinImageStruct;
			item->iFileName = fullname;
			item->iIndex = index++;
			iSkins.Append(item);
			}
		}
	delete c;
	c = NULL;

	CleanupStack::PopAndDestroy(ds);
	}

void CSkinImageScan::ScanFolder(const TDes& aFolder, const TDesC& aFilter)
	{
	iSkins.ResetAndDestroy();

	CDirScan* ds = CDirScan::NewLC(CCoeEnv::Static()->FsSession());
	TRAPD(err,ds->SetScanDataL(aFolder,KEntryAttDir,ESortByName|EAscending,CDirScan::EScanDownTree))

	if (err!=KErrNone)
		{
		CleanupStack::PopAndDestroy(ds);
		return;
		}

	CDir* c= NULL;
	TFileName fullname;
	TFileName shortname;

	if (!BaflUtils::PathExists(CCoeEnv::Static()->FsSession(),aFolder))
		return;
	
	TRAP(err,ds->NextL(c))
	if(err != KErrNone)
		{
		return;
		}
	
	TInt index = 0;
	for (TInt i=0; i<c->Count(); i++)
		{
		const TEntry e= (*c)[i];

		fullname.Copy(ds->FullPath());
		fullname.Append(e.iName);
	
		shortname.Copy(e.iName);
		shortname.LowerCase();
		
		if (!e.IsDir() && shortname.Find(aFilter)!= KErrNotFound)
			{
			pSkinImageStruct item = new SkinImageStruct;
			item->iFileName.Copy(fullname);
			item->iShortName.Copy(e.iName);
			item->iIndex = index++;
			iSkins.Append(item);
			}
		}
	delete c;
	c=NULL;

	CleanupStack::PopAndDestroy(ds);
	}
