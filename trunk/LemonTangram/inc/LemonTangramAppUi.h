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

// FORWARD DECLARATIONS
class CLemonTangramAppView;


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

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CLemonTangramAppUi.
	 * C++ default constructor. This needs to be public due to
	 * the way the framework constructs the AppUi
	 */
	CLemonTangramAppUi();

	/**
	 * ~CLemonTangramAppUi.
	 * Virtual Destructor.
	 */
	virtual ~CLemonTangramAppUi();

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
	 * Owned by CLemonTangramAppUi
	 */
	CLemonTangramAppView* iAppView;
	

	};

#endif // __LEMONTANGRAMAPPUI_h__
// End of File
