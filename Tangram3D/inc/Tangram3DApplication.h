/*
 ============================================================================
 Name		: Tangram3DApplication.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __TANGRAM3DAPPLICATION_H__
#define __TANGRAM3DAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "Tangram3D.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidTangram3DApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CTangram3DApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CTangram3DApplication is the application part of the
 * AVKON application framework for the Tangram3D example application.
 */
class CTangram3DApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidTangram3DApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CTangram3DDocument document object. The returned
	 * pointer in not owned by the CTangram3DApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __TANGRAM3DAPPLICATION_H__
// End of File
