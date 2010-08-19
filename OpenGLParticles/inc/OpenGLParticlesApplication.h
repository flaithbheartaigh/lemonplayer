/*
 ============================================================================
 Name		: OpenGLParticlesApplication.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __OPENGLPARTICLESAPPLICATION_H__
#define __OPENGLPARTICLESAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "OpenGLParticles.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidOpenGLParticlesApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * COpenGLParticlesApplication application class.
 * Provides factory to create concrete document object.
 * An instance of COpenGLParticlesApplication is the application part of the
 * AVKON application framework for the OpenGLParticles example application.
 */
class COpenGLParticlesApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidOpenGLParticlesApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates COpenGLParticlesDocument document object. The returned
	 * pointer in not owned by the COpenGLParticlesApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __OPENGLPARTICLESAPPLICATION_H__
// End of File
