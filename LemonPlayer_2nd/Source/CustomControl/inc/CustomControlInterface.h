/*
 ============================================================================
 Name		: CustomControlInterface.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCustomControlInterface declaration
 ============================================================================
 */

#ifndef CUSTOMCONTROLINTERFACE_H
#define CUSTOMCONTROLINTERFACE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CCustomControlInterface
 * 
 */
class CCustomControlInterface : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CCustomControlInterface();

	/**
	 * Two-phased constructor.
	 */
	static CCustomControlInterface* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CCustomControlInterface* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CCustomControlInterface();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

	};

#endif // CUSTOMCONTROLINTERFACE_H
