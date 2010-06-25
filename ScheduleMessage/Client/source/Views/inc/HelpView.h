/*
 ============================================================================
 Name		: HelpView.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CHelpView declaration
 ============================================================================
 */

#ifndef HELPVIEW_H
#define HELPVIEW_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include <avkon.hrh>
#include <f32file.h>

#include "HelpContainer.h"

// CLASS DECLARATION

/**
 *  CHelp
 * 
 */
class CHelpView : public CAknView
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CHelpView();

	/**
	 * Two-phased constructor.
	 */
	static CHelpView* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CHelpView* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CHelpView();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CHelpContainer * iContainer;
	};

#endif // HELPVIEW_H
