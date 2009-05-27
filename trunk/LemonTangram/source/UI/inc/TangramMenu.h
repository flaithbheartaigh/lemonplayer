/*
 ============================================================================
 Name		: TangramMenu.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangramMenu declaration
 ============================================================================
 */

#ifndef TANGRAMMENU_H
#define TANGRAMMENU_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CTangramMenu
 * 
 */
class CTangramMenu : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CTangramMenu();

	/**
	 * Two-phased constructor.
	 */
	static CTangramMenu* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CTangramMenu* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CTangramMenu();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

	};

#endif // TANGRAMMENU_H
