/*
 ============================================================================
 Name		: AppScreenView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef APPSCREENVIEW_H
#define APPSCREENVIEW_H

// INCLUDES
#include <aknview.h>

#include "AppScreenContainer.h"
// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CAppScreenView view class.
 * 
 */
class CAppScreenView : public CAknView
	{
public:
	// Constructors and destructor
	~CAppScreenView();
	static CAppScreenView* NewL();
	static CAppScreenView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	CAppScreenView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CAppScreenContainer * iContainer;
	};

#endif

