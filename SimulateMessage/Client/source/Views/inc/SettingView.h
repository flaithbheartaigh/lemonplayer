/*
 ============================================================================
 Name		: SettingView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef SETTINGVIEW_H
#define SETTINGVIEW_H

// INCLUDES
#include <aknview.h>

#include "SettingList.h"
// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CSettingView view class.
 * 
 */
class CSettingView : public CAknView
	{
public:
	// Constructors and destructor
	~CSettingView();
	static CSettingView* NewL();
	static CSettingView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	CSettingView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CSettingList * iContainer;
	};

#endif

