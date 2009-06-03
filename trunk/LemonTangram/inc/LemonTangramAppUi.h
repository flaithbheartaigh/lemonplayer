/*
 ============================================================================
 Name		: LemonTangramAppUi.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __LEMONTANGRAMAPPUI_h__
#define __LEMONTANGRAMAPPUI_h__

// INCLUDES
#include <aknViewAppUi.h>//<aknappui.h>
#include "UIMgr.h"
#include "UIFactory.h"

// FORWARD DECLARATIONS
class CLemonTangramAppView;
class CYCSettingView;


// CLASS DECLARATION
/**
 * CLemonTangramAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CLemonTangramAppUi : public CAknViewAppUi
	{
public:
	// Constructors and destructor

	void ConstructL();
	CLemonTangramAppUi();
	virtual ~CLemonTangramAppUi();
	
	//สนำร STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->GetUIMgr()
	MUIMgr* GetUIMgr();
	void ChangeUIMgr(TInt aWidth,TInt aHeight);

public:
	// Functions from base classes
	void HandleCommandL(TInt aCommand);
	
private:
	void HandleStatusPaneSizeChange();
	CArrayFix<TCoeHelpContext>* HelpContextL() const;

private:
	// Data
	CLemonTangramAppView* iAppView;
	CYCSettingView *iSettingView;
	MUIMgr* iUIMgr;
	

	};

#endif // __LEMONTANGRAMAPPUI_h__
// End of File
