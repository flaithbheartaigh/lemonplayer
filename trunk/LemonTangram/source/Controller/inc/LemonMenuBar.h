/*
 ============================================================================
 Name		: LemonMenuBar.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenuBar declaration
 ============================================================================
 */

#ifndef LEMONMENUBAR_H
#define LEMONMENUBAR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CLemonMenuBar
 * 
 */
class CLemonMenuBar : public CBase
	{
public:
	// Constructors and destructor
	~CLemonMenuBar();
	static CLemonMenuBar* NewL();
	static CLemonMenuBar* NewLC();

private:
	CLemonMenuBar();
	void ConstructL();

	};

#endif // LEMONMENUBAR_H
