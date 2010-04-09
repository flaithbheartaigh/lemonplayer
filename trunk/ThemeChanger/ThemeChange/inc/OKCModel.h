/*
 ============================================================================
 Name		: OKCModel.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : COKCModel declaration
 ============================================================================
 */

#ifndef OKCMODEL_H
#define OKCMODEL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <badesca.h>

// CLASS DECLARATION

/**
 *  COKCModel
 * 
 */
class COKCModel : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~COKCModel();

	/**
	 * Two-phased constructor.
	 */
	static COKCModel* NewL();

	/**
	 * Two-phased constructor.
	 */
	static COKCModel* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	COKCModel();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
	};

#endif // OKCMODEL_H
