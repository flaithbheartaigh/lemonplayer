/*
 ============================================================================
 Name		: FileUtils.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileUtils declaration
 ============================================================================
 */

#ifndef FILEUTILS_H
#define FILEUTILS_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <s32file.h>
// CLASS DECLARATION

/**
 *  CFileUtils
 * 
 */
class CFileUtils : public CBase
	{
public:
	// Constructors and destructor

	~CFileUtils();
	static CFileUtils* NewL();
	static CFileUtils* NewLC();

private:

	CFileUtils();
	void ConstructL();
	
public:
	static TInt WriteFile(const TDesC& aFileName,const TDesC& aDes);
	static TInt WriteFile(const TDesC& aFileName,const TDesC8& aDes);
	
	static TInt ReadLineL(RFileReadStream& aStream,TDes8& aDes);
	static TInt WriteLineL(RFileWriteStream& aStream,const TDesC8& aDes);

	};

#endif // FILEUTILS_H
