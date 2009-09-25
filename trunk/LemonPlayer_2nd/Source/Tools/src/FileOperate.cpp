/*
 ============================================================================
 Name		: FileOperate.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileOperate implementation
 ============================================================================
 */

#include "FileOperate.h"
#include <coemain.h>

CFileOperate::CFileOperate(MFileOperateNotify* aNotifier) :
	iNotifier(aNotifier)
	{
	// No implementation required
	}

CFileOperate::~CFileOperate()
	{
	}

CFileOperate* CFileOperate::NewLC(MFileOperateNotify* aNotifier)
	{
	CFileOperate* self = new (ELeave)CFileOperate(aNotifier);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CFileOperate* CFileOperate::NewL(MFileOperateNotify* aNotifier)
	{
	CFileOperate* self=CFileOperate::NewLC(aNotifier);
	CleanupStack::Pop(); // self;
	return self;
	}

void CFileOperate::ConstructL()
	{

	}

TInt CFileOperate::WriteFileL(const TDesC& aFileName)
	{
	int pos = aFileName.LocateReverse( '\\');
	if (pos!=KErrNotFound)
		{
		TPtrC dirName = aFileName.Left(pos+1);
		CCoeEnv::Static()->FsSession().MkDirAll(dirName);
		}

	RFile file;

	TInt err = file.Replace(CCoeEnv::Static()->FsSession(), aFileName, EFileWrite);
	CleanupClosePushL(file);
	if (KErrNone != err)
		{
		CleanupStack::PopAndDestroy(1); // file
		return err;
		}

	RFileWriteStream outputFileStream(file);
	CleanupClosePushL(outputFileStream);

	iNotifier->FileWriteData(outputFileStream);

	CleanupStack::PopAndDestroy(2); // outputFileStream, file
	return KErrNone;
	}

TInt CFileOperate::ReadFileL(const TDesC& aFileName)
	{
	RFile file;
	TInt err = file.Open(CCoeEnv::Static()->FsSession(), aFileName, EFileRead);
	CleanupClosePushL(file);
	if (KErrNone != err)
		{
		CleanupStack::PopAndDestroy(1); // file
		return err;
		}

	//²Ù×÷
	RFileReadStream stream(file);
	CleanupClosePushL(stream);

	iNotifier->FileReadData(stream);

	CleanupStack::PopAndDestroy(2);
	return KErrNone;
	}
