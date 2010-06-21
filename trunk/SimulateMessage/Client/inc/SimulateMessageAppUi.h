/*
 ============================================================================
 Name		: SimulateMessageAppUi.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __SIMULATEMESSAGEAPPUI_h__
#define __SIMULATEMESSAGEAPPUI_h__

// INCLUDES
#include <aknappui.h>
#include <aknviewappui.h>

#include "SHModel.h"
#include "UIManager.h"
#include "SimMsgServerSession.h"

// FORWARD DECLARATIONS
class CSimulateMessageAppView;
class CLogoView;
class CHelpView;
class CLoadDraftView;
class CMainScreenView;
class CSettingView;
class CEditorAppView;
class CRemovedScreenView;

// CLASS DECLARATION
/**
 * CSimulateMessageAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CSimulateMessageAppUi : public CAknViewAppUi
	{
public:
	// Constructors and destructor
	void ConstructL();
	CSimulateMessageAppUi();
	virtual ~CSimulateMessageAppUi();

private:
	// Functions from base classes
	void HandleCommandL(TInt aCommand);
//	void HandleStatusPaneSizeChange();
	void About();
	
public:
	CSHModel* GetModel() {return iDataModel;};
	CUIManager* GetUI() {return iUIMgr;};
	CSimMsgServerSession& GetSession() {return iSession;}; 

private:
	// Data
	CSimulateMessageAppView* iAppView;
	CLogoView* 		iLogoView;
	CHelpView* 		iHelpView;
	CLoadDraftView* iDraftView;
	CMainScreenView* iMainView;
	CRemovedScreenView* iRemovedView;
	CSettingView*	iSettingView;
	CEditorAppView*	iEditView;
	
	CSHModel* iDataModel;
	CUIManager* iUIMgr;
	CSimMsgServerSession iSession;
	};

#endif // __SIMULATEMESSAGEAPPUI_h__
// End of File
