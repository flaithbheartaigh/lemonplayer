/*
 ============================================================================
 Name		: ListEngine.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListEngine declaration
 ============================================================================
 */

#ifndef LISTENGINE_H
#define LISTENGINE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "ListStructure.h"

// CLASS DECLARATION

/**
 *  CListEngine
 * 
 */
class CListEngine : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CListEngine();

	/**
	 * Two-phased constructor.
	 */
	static CListEngine* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CListEngine* NewLC();
	
	void GetJarPath();
//	RArray<TFileName> ScanDir(const TDesC &aPath);
	RPointerArray<TListItem>* ScanDir(const TDesC &aPath);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CListEngine();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

	};

#endif // LISTENGINE_H
