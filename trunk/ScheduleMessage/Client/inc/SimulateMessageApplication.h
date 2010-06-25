/*
 ============================================================================
 Name		: SimulateMessageApplication.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __SIMULATEMESSAGEAPPLICATION_H__
#define __SIMULATEMESSAGEAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "SimulateMessage.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidSimulateMessageApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CSimulateMessageApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CSimulateMessageApplication is the application part of the
 * AVKON application framework for the SimulateMessage example application.
 */
class CSimulateMessageApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidSimulateMessageApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CSimulateMessageDocument document object. The returned
	 * pointer in not owned by the CSimulateMessageApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __SIMULATEMESSAGEAPPLICATION_H__
// End of File
