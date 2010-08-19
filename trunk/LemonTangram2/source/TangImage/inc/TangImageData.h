/*
 ============================================================================
 Name		: TangImageData.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageData declaration
 ============================================================================
 */

#ifndef TANGIMAGEDATA_H
#define TANGIMAGEDATA_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION
class CImageElement;

/**
 *  CTangImageData
 * 
 */
class CTangImageData : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CTangImageData();

	/**
	 * Two-phased constructor.
	 */
	static CTangImageData* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CTangImageData* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CTangImageData();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	CImageElement** GetElements() {return iElements;};
	RArray<TInt> GetLayer() {return iLayer;};
	
	void SetSelected(const TInt& aIndex);
	TInt GetSelected() {return iSelectedIndex;};
	
private:
	void ChangeLayer();
	
private:
	CImageElement** iElements;
	RArray<TInt> iLayer;
	TInt iSelectedIndex;
	
	};

#endif // TANGIMAGEDATA_H
