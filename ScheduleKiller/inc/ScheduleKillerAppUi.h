/*
 ============================================================================
 Name		: ScheduleKillerAppUi.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __SCHEDULEKILLERAPPUI_h__
#define __SCHEDULEKILLERAPPUI_h__

// INCLUDES
#include <aknappui.h>
#include <aknviewappui.h>

#include "SHModel.h"
#include "UIManager.h"
#include "SHError.h"
#include "OfferKeyManager.h"

// FORWARD DECLARATIONS
class CAppScreenView;
class CMainScreenView;
class CRuleScreenView;
class CSettingScreenView;
class CHelpView;
class CLogoView;

// CLASS DECLARATION
/**
 * CScheduleKillerAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CScheduleKillerAppUi : public CAknViewAppUi
	{
public:
	// Constructors and destructor
	void ConstructL();
	CScheduleKillerAppUi();
	virtual ~CScheduleKillerAppUi();

private:
	// Functions from base classes
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();
	TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	
public:
	CSHModel* GetModel() {return iDataModel;};
	CUIManager* GetUI() {return iUIMgr;};
	void SHError(const TSHErrInfo& aInfo,const TSHErrState& aState);
	
private:
	void About();
	void ExitApp();

private:
	// Data
	CAppScreenView* iAppView;
	CMainScreenView* iMainView;
	CRuleScreenView* iRuleView;
	CSettingScreenView* iSettingView;
	CHelpView* iHelpView;
	CLogoView* iLogoView;
	
	CSHModel* iDataModel;
	CUIManager* iUIMgr;

	COfferKeyManager* iKeyManager;
	};

#endif // __SCHEDULEKILLERAPPUI_h__
// End of File
