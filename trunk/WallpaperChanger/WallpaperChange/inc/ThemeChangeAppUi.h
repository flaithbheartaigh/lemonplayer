/*
 ============================================================================
 Name		: ThemeChangeAppUi.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __THEMECHANGEAPPUI_h__
#define __THEMECHANGEAPPUI_h__

// INCLUDES
#include <aknappui.h>
#include <aknviewappui.h>
#include "OKCModel.h"
#include "UIManager.h"

// FORWARD DECLARATIONS
class CThemeChangeAppView;
class CHelpView ;
class CNormalSettingView;

// CLASS DECLARATION
/**
 * CThemeChangeAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CThemeChangeAppUi : public CAknViewAppUi
	{
public:
	// Constructors and destructor
	void ConstructL();
	CThemeChangeAppUi();
	virtual ~CThemeChangeAppUi();

private:
	// Functions from base classes
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();
	void HandleResourceChangeL(TInt aType);
	
	void About();
	
public:
	COKCModel* GetModel();
	CUIManager* GetUI();
	
private:
	// Data
	CThemeChangeAppView* appView;
	CHelpView* helpView ;
	CNormalSettingView* settingView;
	
	COKCModel* iDataModel;
	CUIManager* iUIMgr;

	};

inline void OKCChangeView(TInt aView)
	{
	STATIC_CAST(CThemeChangeAppUi*,CEikonEnv::Static()->AppUi())
	->ActivateLocalViewL(TUid::Uid(aView));
	}
;

inline void OKCChangeView(TInt aView,TInt aCustomMessageId,
        const TDesC8& aCustomMessage)
	{
	STATIC_CAST(CThemeChangeAppUi*,CEikonEnv::Static()->AppUi())
	->ActivateLocalViewL(TUid::Uid(aView),TUid::Uid(aCustomMessageId),aCustomMessage);
	}
;

inline COKCModel* OKCModel()
	{
	return STATIC_CAST(CThemeChangeAppUi*,CEikonEnv::Static()->AppUi())
	->GetModel();
	}
;

inline CUIManager* OKCUI()
	{
	return STATIC_CAST(CThemeChangeAppUi*,CEikonEnv::Static()->AppUi())
	->GetUI();
	}
;

#endif // __THEMECHANGEAPPUI_h__
// End of File
