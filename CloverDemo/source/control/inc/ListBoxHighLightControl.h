/*
 ============================================================================
 Name		: ListBoxHighLightControl.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxHighLightControl declaration
 ============================================================================
 */

#ifndef LISTBOXHIGHLIGHTCONTROL_H
#define LISTBOXHIGHLIGHTCONTROL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "BaseControl.h"
#include "ListBoxPainter.h"
// CLASS DECLARATION

/**
 *  CListBoxHighLightControl
 * 
 */
class CListBoxHighLightControl : public CBaseControl
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CListBoxHighLightControl();

	/**
	 * Two-phased constructor.
	 */
	static CListBoxHighLightControl* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CListBoxHighLightControl* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CListBoxHighLightControl();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

public:
	//from base
	virtual void Draw(CBitmapContext& gc) const;
		
	//new func
	void SetPainter(CListBoxPainter* aPainter) {iPainter = aPainter;};
	
private:
	CListBoxPainter* iPainter;		//not own
	};

#endif // LISTBOXHIGHLIGHTCONTROL_H
