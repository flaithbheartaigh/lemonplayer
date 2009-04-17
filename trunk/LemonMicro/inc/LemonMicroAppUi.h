/*
 ============================================================================
 Name		: LemonMicroAppUi.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __LEMONMICROAPPUI_h__
#define __LEMONMICROAPPUI_h__

// INCLUDES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CLemonMicroAppView;
class CFileRecordAdapter;
// CLASS DECLARATION
/**
 * CLemonMicroAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CLemonMicroAppUi : public CAknAppUi
	{
public:
	// Constructors and destructor

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CLemonMicroAppUi.
	 * C++ default constructor. This needs to be public due to
	 * the way the framework constructs the AppUi
	 */
	CLemonMicroAppUi();

	/**
	 * ~CLemonMicroAppUi.
	 * Virtual Destructor.
	 */
	virtual ~CLemonMicroAppUi();

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
	 * Owned by CLemonMicroAppUi
	 */
	CLemonMicroAppView* iAppView;

	CFileRecordAdapter* iFileRecorder;
	};

#endif // __LEMONMICROAPPUI_h__
// End of File
