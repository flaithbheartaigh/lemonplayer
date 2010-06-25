/*
 ============================================================================
 Name		: LoadDraftView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef LOADDRAFTVIEW_H
#define LOADDRAFTVIEW_H

// INCLUDES
#include <aknview.h>

#include "LoadDraftContainer.h"
// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CLoadDraftView view class.
 * 
 */
class CLoadDraftView : public CAknView
	{
public:
	// Constructors and destructor
	~CLoadDraftView();
	static CLoadDraftView* NewL();
	static CLoadDraftView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	CLoadDraftView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CLoadDraftContainer * iContainer;
	};

#endif

