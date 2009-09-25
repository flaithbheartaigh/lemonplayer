/*
 ============================================================================
 Name		: FileOperate.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileOperate declaration
 ============================================================================
 */

#ifndef FILEOPERATE_H
#define FILEOPERATE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <s32file.h>

// CLASS DECLARATION

/**
 *  CFileOperate
 * 
 */
class MFileOperateNotify
	{
public:
	virtual void FileWriteData(RFileWriteStream& aStream) = 0;
	virtual void FileReadData(RFileReadStream& aStream) = 0;
	};

class CFileOperate : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFileOperate();

	/**
	 * Two-phased constructor.
	 */
	static CFileOperate* NewL(MFileOperateNotify* aNotifier);

	/**
	 * Two-phased constructor.
	 */
	static CFileOperate* NewLC(MFileOperateNotify* aNotifier);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFileOperate(MFileOperateNotify* aNotifier);

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	TInt WriteFileL(const TDesC& aFileName);
	TInt ReadFileL(const TDesC& aFileName);
	
private:
	MFileOperateNotify* iNotifier;

	};

#endif // FILEOPERATE_H
