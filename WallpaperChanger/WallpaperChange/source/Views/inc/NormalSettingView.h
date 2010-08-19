/*
 ============================================================================
 Name		: NormalSettingView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef NORMALSETTINGVIEW_H
#define NORMALSETTINGVIEW_H

// INCLUDES
#include <aknview.h>

#include "NormalSettingContainer.h"
// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CNormalSettingView view class.
 * 
 */
class CNormalSettingView : public CAknView
	{
public:
	// Constructors and destructor
	~CNormalSettingView();
	static CNormalSettingView* NewL();
	static CNormalSettingView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	CNormalSettingView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CNormalSettingContainer * iContainer;
	};

#endif

