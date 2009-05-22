/*
 ============================================================================
 Name		: LemonTangramApplication.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __LEMONTANGRAMAPPLICATION_H__
#define __LEMONTANGRAMAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "LemonTangram.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidLemonTangramApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CLemonTangramApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CLemonTangramApplication is the application part of the
 * AVKON application framework for the LemonTangram example application.
 */
class CLemonTangramApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidLemonTangramApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CLemonTangramDocument document object. The returned
	 * pointer in not owned by the CLemonTangramApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __LEMONTANGRAMAPPLICATION_H__
// End of File
