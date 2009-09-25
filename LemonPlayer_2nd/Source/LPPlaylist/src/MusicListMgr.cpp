/*
 ============================================================================
 Name		: MusicListMgr.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMusicListMgr implementation
 ============================================================================
 */

#include "MusicListMgr.h"
#include "MusicInfoBean.h"
#include "FileUtils.h"

_LIT8(KEXTM3U,"#EXTM3U");
_LIT8(KEXTINF,"#EXTINF:");
_LIT8(KTEXTSEP," - ");

CMusicListMgr::CMusicListMgr()
	{
	// No implementation required
	}

CMusicListMgr::~CMusicListMgr()
	{
	}

CMusicListMgr* CMusicListMgr::NewLC()
	{
	CMusicListMgr* self = new (ELeave)CMusicListMgr();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMusicListMgr* CMusicListMgr::NewL()
	{
	CMusicListMgr* self=CMusicListMgr::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CMusicListMgr::ConstructL()
	{
//	iList = new (ELeave) RPointerArray<CMusicInfoBean>;
	}

TInt CMusicListMgr::ReadFile(const TDesC& aFileName)
	{
	RFile file;
	TInt err = file.Open(CCoeEnv::Static()->FsSession(), aFileName, EFileRead);
	CleanupClosePushL(file);
	if (KErrNone != err)
		{
		CleanupStack::PopAndDestroy(1); // file
		ObserverError(err);
		return err;
		}

	//操作
	TBuf8<KMaxFileName> text;
	RFileReadStream stream(file);
	CleanupClosePushL(stream);

	//文件头是否正确
	CFileUtils::ReadLineL(stream, text);
	if (text.Compare(KEXTM3U) != 0)
		{
		ObserverError(KErrNotSupported);
		CleanupStack::PopAndDestroy(2);
		return KErrNotSupported;
		}

	while (CFileUtils::ReadLineL(stream, text) == KErrNone)
		{
		CMusicInfoBean* bean = CMusicInfoBean::NewL();
		ReadInfoToBean(bean, text);
		//保存文件名
		CFileUtils::ReadLineL(stream, text);
		ReadFileToBean(bean, text);

		iList->Append(bean);
		}

	CleanupStack::PopAndDestroy(2);
	return KErrNone;
	}

TInt CMusicListMgr::WriteFile(const TDesC& aFileName)
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
		ObserverError(err);
		return err;
		}

	RFileWriteStream stream(file);
	CleanupClosePushL(stream);

	//操作
	CFileUtils::WriteLineL(stream, KEXTM3U);
	TBuf8<KMaxFileName> text;
	for (TInt i=0; i<iList->Count(); i++)
		{
		CMusicInfoBean* bean = (*iList)[i];
		WriteInfoToBean(bean, text);
		CFileUtils::WriteLineL(stream, text);
		WriteFileToBean(bean, text);
		CFileUtils::WriteLineL(stream, text);
		}

	CleanupStack::PopAndDestroy(2); // outputFileStream, file
	return KErrNone;
	}

void CMusicListMgr::ReadInfoToBean(CMusicInfoBean* aBean, const TDesC8& aText)
	{
	TInt pos = KErrNotFound;
	TBuf8<KMaxFileName> text(aText);
	text.Delete(0, 8); //#EXTINF:	

	pos = text.Locate(',');
	text.Left(pos); //时间
	text.Delete(0, pos+1);

	pos = text.Find(KTEXTSEP);
	if (pos != KErrNotFound)
		{
		aBean->setArtistL(text.Left(pos)); //歌手
		text.Delete(0, pos+3);
		}
	else
		{
		aBean->setArtistL(text);
		return;
		}

	pos = text.Find(KTEXTSEP);
	if (pos != KErrNotFound)
		{
		aBean->setTitleL(text.Left(pos)); //歌名
		text.Delete(0, pos+3);
		}
	else
		{
		aBean->setTitleL(text);
		return;
		}

	pos = text.Find(KTEXTSEP);
	if (pos != KErrNotFound)
		{
		aBean->setAblumL(text.Left(pos)); //专辑
		text.Delete(0, pos+3);
		}
	else
		{
		aBean->setAblumL(text);
		return;
		}

	pos = text.Find(KTEXTSEP);
	if (pos != KErrNotFound)
		{
		//		aBean->setArtistL(text.Left(pos)); //类型
		text.Delete(0, pos+3);
		}
	else
		{
		//		aBean->setTitleL(text);
		return;
		}

	}

void CMusicListMgr::ReadFileToBean(CMusicInfoBean* aBean, const TDesC8& aText)
	{
	TInt pos = aText.LocateReverse('\\');
	if (pos != KErrNotFound)
		{
		aBean->setFileFolderL(aText.Left(pos));
		aBean->setFileNameL(aText.Mid(pos+1));
		}
	}

void CMusicListMgr::WriteInfoToBean(CMusicInfoBean* aBean, TDes8& aText)
	{
	aText.Copy(KNullDesC8);
	aText.Append(KEXTINF);
	aText.AppendNum(0);
	aText.Append(',');
	if (aBean->getArtist().Compare(KNullDesC8))
		{
		aText.Append(aBean->getArtist());
		}
	if (aBean->getTitle().Compare(KNullDesC8))
		{
		aText.Append(KTEXTSEP);
		aText.Append(aBean->getTitle());
		}
	else
		return;

	if (aBean->getAblum().Compare(KNullDesC8))
		{
		aText.Append(KTEXTSEP);
		aText.Append(aBean->getAblum());
		}
	else
		return;

	if (aBean->getGenre()!=-1)
		{
		aText.Append(KTEXTSEP);
		aText.AppendNum(aBean->getGenre());
		}
	else
		return;
	}
void CMusicListMgr::WriteFileToBean(CMusicInfoBean* aBean, TDes8& aText)
	{
	aText.Copy(KNullDesC8);
	aText.Append(aBean->getFileFolder());
	aText.Append('\\');
	aText.Append(aBean->getFileName());
	}