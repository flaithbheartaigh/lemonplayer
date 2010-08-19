/*
 ============================================================================
 Name		: BackgroundControl.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CBackgroundControl declaration
 ============================================================================
 */

#ifndef BACKGROUNDCONTROL_H
#define BACKGROUNDCONTROL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "BaseControl.h"
// CLASS DECLARATION

/**
 *  CBackgroundControl
 * 
 */
class CBackgroundControl : public CBaseControl
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CBackgroundControl();

	/**
	 * Two-phased constructor.
	 */
	static CBackgroundControl* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CBackgroundControl* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CBackgroundControl();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

	};

#endif // BACKGROUNDCONTROL_H
