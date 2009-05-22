/*
 ============================================================================
 Name		: ImageBitmapReader.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CImageBitmapReader declaration
 ============================================================================
 */

#ifndef IMAGEBITMAPREADER_H
#define IMAGEBITMAPREADER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <fbs.h>

// CLASS DECLARATION

/**
 *  CImageBitmapReader
 * 
 */
class CImageBitmapReader : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CImageBitmapReader();

	/**
	 * Two-phased constructor.
	 */
	static CImageBitmapReader* NewL(const TDesC& aFileName);

	/**
	 * Two-phased constructor.
	 */
	static CImageBitmapReader* NewLC(const TDesC& aFileName);
	
	CFbsBitmap* GetFbsBitmap();
	void DoMyBitmapEffect(CFbsBitmap* aBitmap);
	void DoMyBitmapEffect();
	
	void HeaderInfo();
	void DataInfo();
	

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CImageBitmapReader();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL(const TDesC& aFileName);
	
	void CreateImage(const TDesC& aFileName);
	TInt32 NameToId(const TDesC& aFileName);
	
private:
	CFbsBitmap* iBitmap;

	};

#endif // IMAGEBITMAPREADER_H
