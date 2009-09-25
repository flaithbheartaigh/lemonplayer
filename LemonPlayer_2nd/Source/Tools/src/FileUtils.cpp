/*
 ============================================================================
 Name		: FileUtils.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileUtils implementation
 ============================================================================
 */

#include "FileUtils.h"
#include <coemain.h>
#include <f32file.h>
#include <s32file.h>

_LIT8(KLineBrak,"\r\n");

CFileUtils::CFileUtils()
	{
	// No implementation required
	}

CFileUtils::~CFileUtils()
	{
	}

CFileUtils* CFileUtils::NewLC()
	{
	CFileUtils* self = new (ELeave)CFileUtils();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CFileUtils* CFileUtils::NewL()
	{
	CFileUtils* self=CFileUtils::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CFileUtils::ConstructL()
	{

	}

TInt CFileUtils::WriteFile(const TDesC& aFileName, const TDesC& aDes)
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
	outputFileStream.WriteL(aDes);

	CleanupStack::PopAndDestroy(2); // outputFileStream, file
	return KErrNone;
	}

TInt CFileUtils::WriteFile(const TDesC& aFileName, const TDesC8& aDes)
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
	outputFileStream.WriteL(aDes);

	CleanupStack::PopAndDestroy(2); // outputFileStream, file
	return KErrNone;
	}

TInt CFileUtils::ReadLineL(RFileReadStream& aStream, TDes8& aDes)
	{
	TBuf8<1> ch;
	TBuf8<1> next;
	TInt pos = 0;
	TInt len = aDes.MaxLength();
	TInt err;
	aDes.Copy(KNullDesC8);
	while (pos < len)
		{
		TRAP(err,aStream.ReadL(ch));
		if (err != KErrNone)
			return err;
		if (ch.Compare(_L8("\r")) != 0)
			{
			pos++;
			aDes.Append(ch);
			}
		else
			{
			TRAP(err,aStream.ReadL(next));
			if (err != KErrNone)
				{
				aDes.Append(ch);
				return err;
				}
			if (next.Compare(_L8("\n")) != 0)
				{
				pos += 2;
				aDes.Append(ch);
				aDes.Append(next);
				}
			else
				{
				return KErrNone;
				}
			}
		}
	return KErrNone;
	}

TInt CFileUtils::WriteLineL(RFileWriteStream& aStream,const TDesC8& aDes)
	{
	TRAPD(err,
	aStream.WriteL(aDes);
	aStream.WriteL(KLineBrak);
	);
	return err;
	}