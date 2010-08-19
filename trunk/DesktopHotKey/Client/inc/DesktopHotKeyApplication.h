/*
 ============================================================================
 Name		: DesktopHotKeyApplication.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __DESKTOPHOTKEYAPPLICATION_H__
#define __DESKTOPHOTKEYAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "DesktopHotKey.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidDesktopHotKeyApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CDesktopHotKeyApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CDesktopHotKeyApplication is the application part of the
 * AVKON application framework for the DesktopHotKey example application.
 */
class CDesktopHotKeyApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidDesktopHotKeyApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CDesktopHotKeyDocument document object. The returned
	 * pointer in not owned by the CDesktopHotKeyApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __DESKTOPHOTKEYAPPLICATION_H__
// End of File
