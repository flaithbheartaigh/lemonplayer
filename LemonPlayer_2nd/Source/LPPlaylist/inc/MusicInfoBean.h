/*
 ============================================================================
 Name		: MusicInfoBean.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMusicInfoBean declaration
 ============================================================================
 */

#ifndef MUSICINFOBEAN_H
#define MUSICINFOBEAN_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CMusicInfoBean
 * 
 */
class CMusicInfoBean : public CBase
	{
public:
	enum EInfoState
		{
		KInfoInit = 0,
		KInfoParsed 
		};
public:
	~CMusicInfoBean();
	static CMusicInfoBean* NewL();
	static CMusicInfoBean* NewLC();

private:
	void ConstructL();
	CMusicInfoBean();
	
public:
	void setId(const TInt aId){id = aId;};
	TInt getId() const {return id;};
	
	void setTitleL(const TDesC8& aTitle);
	const TDesC8& getTitle () const {return *title;};
	
	void setArtistL(const TDesC8& aArtist);
	const TDesC8& getArtist() const {return *artist;};
	
	void setAblumL(const TDesC8& aAblum);
	const TDesC8& getAblum() const {return *ablum;};
	
	void setGenre(const TInt aGenre){genre = aGenre;};
	TInt getGenre() const {return genre;};
	
	void setFileNameL(const TDesC8& aFileName);
	const TDesC8& getFileName() const {return *filename;};
	
	void setFileFolderL(const TDesC8& aFileFolder);
	const TDesC8& getFileFolder() const {return *filefolder;};
	
	HBufC* GetFile();
	
	void setFullNameL(const TDesC8& aFileName);
	
	void setInfoState(const EInfoState aState);
	const EInfoState getInfoState() const {return iState;};

private:
	TInt id;
	HBufC8* title;
	HBufC8* artist;
	HBufC8* ablum;
	TInt genre;
	HBufC8* filename;
	HBufC8* filefolder;
	EInfoState iState;
	//	HBufC* file;
	//	TInt duration;
	//	TInt filesize;
	//	TInt bitrate;
	//	TInt samrate;
	//	TInt channel;
	};

#endif // MUSICINFOBEAN_H
