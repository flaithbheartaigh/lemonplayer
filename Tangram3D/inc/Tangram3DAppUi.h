/*
 ============================================================================
 Name		: Tangram3DAppUi.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __TANGRAM3DAPPUI_h__
#define __TANGRAM3DAPPUI_h__

// INCLUDES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CTangram3DAppView;

// CLASS DECLARATION
/**
 * CTangram3DAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CTangram3DAppUi : public CAknAppUi
	{
public:
	// Constructors and destructor

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CTangram3DAppUi.
	 * C++ default constructor. This needs to be public due to
	 * the way the framework constructs the AppUi
	 */
	CTangram3DAppUi();

	/**
	 * ~CTangram3DAppUi.
	 * Virtual Destructor.
	 */
	virtual ~CTangram3DAppUi();

private:
	// Functions from base classes

	/**
	 * From CEikAppUi, HandleCommandL.
	 * Takes care of command handling.
	 * @param aCommand Command to be handled.
	 */
	void HandleCommandL(TInt aCommand);

	/**
	 *  HandleStatusPaneSizeChange.
	 *  Called by the framework when the application status pane
	 *  size is changed.
	 */
	void HandleStatusPaneSizeChange();

	/**
	 *  From CCoeAppUi, HelpContextL.
	 *  Provides help context for the application.
	 *  size is changed.
	 */
	CArrayFix<TCoeHelpContext>* HelpContextL() const;

private:
	// Data

	/**
	 * The application view
	 * Owned by CTangram3DAppUi
	 */
	CTangram3DAppView* iAppView;

	};

#endif // __TANGRAM3DAPPUI_h__
// End of File
