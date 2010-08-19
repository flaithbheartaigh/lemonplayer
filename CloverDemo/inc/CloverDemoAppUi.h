/*
 ============================================================================
 Name		: CloverDemoAppUi.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __CLOVERDEMOAPPUI_h__
#define __CLOVERDEMOAPPUI_h__

// INCLUDES
#include <aknappui.h>
#include <aknviewappui.h>

// FORWARD DECLARATIONS
class CCloverDemoAppView;

// CLASS DECLARATION
/**
 * CCloverDemoAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CCloverDemoAppUi : public CAknViewAppUi
	{
public:
	// Constructors and destructor
	void ConstructL();
	CCloverDemoAppUi();
	virtual ~CCloverDemoAppUi();

private:
	// Functions from base classes
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	// Data
	CCloverDemoAppView* iAppView;

	};

#endif // __CLOVERDEMOAPPUI_h__
// End of File
