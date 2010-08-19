/*
 ============================================================================
 Name		: SHModel.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSHModel declaration
 ============================================================================
 */

#ifndef SHMODEL_H
#define SHMODEL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CSHModel
 * 
 */
class CSHModel : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CSHModel();

	/**
	 * Two-phased constructor.
	 */
	static CSHModel* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CSHModel* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CSHModel();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
	};

#endif // SHMODEL_H
