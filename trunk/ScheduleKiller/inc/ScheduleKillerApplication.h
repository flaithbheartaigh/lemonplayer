/*
 ============================================================================
 Name		: ScheduleKillerApplication.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __SCHEDULEKILLERAPPLICATION_H__
#define __SCHEDULEKILLERAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "ScheduleKiller.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidScheduleKillerApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CScheduleKillerApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CScheduleKillerApplication is the application part of the
 * AVKON application framework for the ScheduleKiller example application.
 */
class CScheduleKillerApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidScheduleKillerApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CScheduleKillerDocument document object. The returned
	 * pointer in not owned by the CScheduleKillerApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __SCHEDULEKILLERAPPLICATION_H__
// End of File
