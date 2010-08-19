/*
 ============================================================================
 Name		: DesktopHotKeyAppUi.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __DESKTOPHOTKEYAPPUI_h__
#define __DESKTOPHOTKEYAPPUI_h__

// INCLUDES
#include <aknappui.h>
#include <aknviewappui.h>

#include "SHModel.h"
#include "UIManager.h"
#include "SHError.h"

// FORWARD DECLARATIONS
class CDesktopHotKeyAppView;

class CHelpView;
class CLogoView;
// CLASS DECLARATION
/**
 * CDesktopHotKeyAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CDesktopHotKeyAppUi : public CAknViewAppUi
	{
public:
	// Constructors and destructor
	void ConstructL();
	CDesktopHotKeyAppUi();
	virtual ~CDesktopHotKeyAppUi();

private:
	// Functions from base classes
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

public:
	CSHModel* GetModel() {return iDataModel;};
	CUIManager* GetUI() {return iUIMgr;};
	void SHError(const TSHErrInfo& aInfo,const TSHErrState& aState);
	
private:
	void About();
	
private:
	// Data
	CHelpView* iHelpView;
	CLogoView* iLogoView;
		
	CSHModel* iDataModel;
	CUIManager* iUIMgr;
		
	CDesktopHotKeyAppView* iAppView;

	};

#endif // __DESKTOPHOTKEYAPPUI_h__
// End of File
