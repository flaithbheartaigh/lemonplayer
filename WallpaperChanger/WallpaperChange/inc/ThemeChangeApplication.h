/*
 ============================================================================
 Name		: ThemeChangeApplication.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __THEMECHANGEAPPLICATION_H__
#define __THEMECHANGEAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "ThemeChange.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidThemeChangeApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CThemeChangeApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CThemeChangeApplication is the application part of the
 * AVKON application framework for the ThemeChange example application.
 */
class CThemeChangeApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidThemeChangeApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CThemeChangeDocument document object. The returned
	 * pointer in not owned by the CThemeChangeApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __THEMECHANGEAPPLICATION_H__
// End of File
