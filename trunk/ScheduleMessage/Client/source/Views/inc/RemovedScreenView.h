/*
 ============================================================================
 Name		: RemovedScreenView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef REMOVEDSCREENVIEW_H
#define REMOVEDSCREENVIEW_H

// INCLUDES
#include <aknview.h>

#include "RemovedScreenContainer.h"
// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CRemovedScreenView view class.
 * 
 */
class CRemovedScreenView : public CAknView
	{
public:
	// Constructors and destructor
	~CRemovedScreenView();
	static CRemovedScreenView* NewL();
	static CRemovedScreenView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	CRemovedScreenView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CRemovedScreenContainer * iContainer;
	};

#endif

