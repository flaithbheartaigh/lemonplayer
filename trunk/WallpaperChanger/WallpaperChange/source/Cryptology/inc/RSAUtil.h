/*
 ============================================================================
 Name		: RSAUtil.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRSAUtil declaration
 ============================================================================
 */

#ifndef RSAUTIL_H
#define RSAUTIL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CRSAUtil
 * 
 */
class CRSAUtil : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CRSAUtil();

	/**
	 * Two-phased constructor.
	 */
	static CRSAUtil* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CRSAUtil* NewLC();
	
	static HBufC8* Encode(const TDesC8& aSource,const TDesC8& aE,const TDesC8& aN);
	static HBufC8* Decode(const TDesC8& aSource,const TDesC8& aD,const TDesC8& aN);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CRSAUtil();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

	};

#endif // RSAUTIL_H
