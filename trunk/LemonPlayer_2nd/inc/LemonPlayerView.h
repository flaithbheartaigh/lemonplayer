/*
 ============================================================================
 Name		: LemonPlayerView.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonPlayerView declaration
 ============================================================================
 */

#ifndef LEMONPLAYERVIEW_H
#define LEMONPLAYERVIEW_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
// CLASS DECLARATION
class CLemonPlayerContainer;
/**
 *  CLemonPlayerView
 * 
 */
class CLemonPlayerView : public CAknView
	{
public:
	// Constructors and destructor

	~CLemonPlayerView();
	static CLemonPlayerView* NewL();
	static CLemonPlayerView* NewLC();

private:
	CLemonPlayerView();
	void ConstructL();
	
public:
	//From CAknView.
	virtual TUid Id() const;
	virtual void DoActivateL( const TVwsViewId& aPrevViewId,
	                          TUid aCustomMessageId,
	                          const TDesC8& aCustomMessage );
	virtual void DoDeactivate();
	void HandleCommandL( TInt aCommand );
	
	//From MEikMenuObserver
	void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

private:
	CLemonPlayerContainer* iAppContainer;
	};

#endif // LEMONPLAYERVIEW_H
