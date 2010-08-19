/*
 ============================================================================
 Name		: CloverDemoApplication.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __CLOVERDEMOAPPLICATION_H__
#define __CLOVERDEMOAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "CloverDemo.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidCloverDemoApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CCloverDemoApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CCloverDemoApplication is the application part of the
 * AVKON application framework for the CloverDemo example application.
 */
class CCloverDemoApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidCloverDemoApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CCloverDemoDocument document object. The returned
	 * pointer in not owned by the CCloverDemoApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __CLOVERDEMOAPPLICATION_H__
// End of File
