/*
 ============================================================================
 Name		: SettingScreenView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef SETTINGSCREENVIEW_H
#define SETTINGSCREENVIEW_H

// INCLUDES
#include <aknview.h>

#include "SettingScreenContainer.h"
// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CSettingScreenView view class.
 * 
 */
class CSettingScreenView : public CAknView
	{
public:
	// Constructors and destructor
	~CSettingScreenView();
	static CSettingScreenView* NewL();
	static CSettingScreenView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	CSettingScreenView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CSettingScreenContainer * iContainer;
	};

#endif

