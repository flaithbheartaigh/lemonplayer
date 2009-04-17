/*
 ============================================================================
 Name		: StreamRecordAdapter.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CStreamRecordAdapter declaration
 ============================================================================
 */

#ifndef STREAMRECORDADAPTER_H
#define STREAMRECORDADAPTER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CStreamRecordAdapter
 * 
 */
class CStreamRecordAdapter : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CStreamRecordAdapter();

	/**
	 * Two-phased constructor.
	 */
	static CStreamRecordAdapter* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CStreamRecordAdapter* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CStreamRecordAdapter();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

	};

#endif // STREAMRECORDADAPTER_H
