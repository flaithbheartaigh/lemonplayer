/*
 ============================================================================
 Name		: MainScreenView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef MAINSCREENVIEW_H
#define MAINSCREENVIEW_H

// INCLUDES
#include <aknview.h>

#include "MainScreenContainer.h"
// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CMainScreenView view class.
 * 
 */
class CMainScreenView : public CAknView
	{
public:
	// Constructors and destructor
	~CMainScreenView();
	static CMainScreenView* NewL();
	static CMainScreenView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();
	void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );
private:
	CMainScreenView();
	void ConstructL();
	
	void UpdateCBA();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CMainScreenContainer * iContainer;
	};

#endif

