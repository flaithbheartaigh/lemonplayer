/*
 ============================================================================
 Name		: ListBoxView.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxView declaration
 ============================================================================
 */

#ifndef MYLISTBOXVIEW_H
#define MYLISTBOXVIEW_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include "ViewNotify.h"

// CLASS DECLARATION
class CListBox;

/**
 *  CListBoxView
 * 
 */
class CMyListBoxView : public CAknView
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CMyListBoxView();

	/**
	 * Two-phased constructor.
	 */
	static CMyListBoxView* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CMyListBoxView* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CMyListBoxView();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	void DoActivateL( const TVwsViewId& aPrevViewId,
	                          TUid aCustomMessageId,
	                          const TDesC8& aCustomMessage );
	void DoDeactivate();
	
public:
	void SetData(CUIViewData *aData);
	void SetNotify(MListBoxViewNotify *aNotify);
	
private:
	CListBox* iBox;
	CUIViewData *iData;
	MListBoxViewNotify *iNotify;
	};

#endif // MYLISTBOXVIEW_H
