/*
 ============================================================================
 Name		: MusicInfoBean.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMusicInfoBean implementation
 ============================================================================
 */

#include "MusicInfoBean.h"
#include "MacroUtil.h"

CMusicInfoBean::CMusicInfoBean() :
	title(NULL), artist(NULL), ablum(NULL), filename(NULL), filefolder(NULL),
	id(-1), genre(-1)
	{
	// No implementation required
	}

CMusicInfoBean::~CMusicInfoBean()
	{
	SAFE_DELETE(title);
	SAFE_DELETE(artist);
	SAFE_DELETE(ablum);
	SAFE_DELETE(filename);
	SAFE_DELETE(filefolder);
	}

CMusicInfoBean* CMusicInfoBean::NewLC()
	{
	CMusicInfoBean* self = new (ELeave)CMusicInfoBean();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMusicInfoBean* CMusicInfoBean::NewL()
	{
	CMusicInfoBean* self=CMusicInfoBean::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CMusicInfoBean::ConstructL()
	{
	title 		= KNullDesC8().AllocL();
	artist 		= KNullDesC8().AllocL();
	ablum 		= KNullDesC8().AllocL();
	filename 	= KNullDesC8().AllocL();
	filefolder 	= KNullDesC8().AllocL();
	}

void CMusicInfoBean::setTitleL(const TDesC8& aTitle)
	{
	SAFE_DELETE(title);
	title = aTitle.AllocL();
	}

void CMusicInfoBean::setArtistL(const TDesC8& aArtist)
	{
	SAFE_DELETE(artist);
	artist = aArtist.AllocL();
	}

void CMusicInfoBean::setAblumL(const TDesC8& aAblum)
	{
	SAFE_DELETE(ablum);
	ablum = aAblum.AllocL();
	}

void CMusicInfoBean::setFileNameL(const TDesC8& aFileName)
	{
	SAFE_DELETE(filename);
	filename = aFileName.AllocL();
	}

void CMusicInfoBean::setFileFolderL(const TDesC8& aFileFolder)
	{
	SAFE_DELETE(filefolder);
	filefolder = aFileFolder.AllocL();
	}

HBufC* CMusicInfoBean::GetFile()
	{
	
	}

void CMusicInfoBean::setFullNameL(const TDesC8& aFileName)
	{
	TInt i=aFileName.LocateReverse('\\');
	if (i != KErrNotFound)
		{
		setFileFolderL(aFileName.Left(i+1));
		setFileNameL(aFileName.Mid(i+1));
		}
	}

void CMusicInfoBean::setInfoState(const EInfoState aState)
	{
	iState = aState;
	}