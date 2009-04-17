/*
 ============================================================================
 Name		: LemonMicroApplication.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __LEMONMICROAPPLICATION_H__
#define __LEMONMICROAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "LemonMicro.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidLemonMicroApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CLemonMicroApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CLemonMicroApplication is the application part of the
 * AVKON application framework for the LemonMicro example application.
 */
class CLemonMicroApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidLemonMicroApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CLemonMicroDocument document object. The returned
	 * pointer in not owned by the CLemonMicroApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __LEMONMICROAPPLICATION_H__
// End of File
