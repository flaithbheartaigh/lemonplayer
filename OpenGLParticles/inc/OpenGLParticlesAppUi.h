/*
 ============================================================================
 Name		: OpenGLParticlesAppUi.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __OPENGLPARTICLESAPPUI_h__
#define __OPENGLPARTICLESAPPUI_h__

// INCLUDES
#include <aknappui.h>
#include <aknviewappui.h>

// FORWARD DECLARATIONS
class COpenGLParticlesAppView;

// CLASS DECLARATION
/**
 * COpenGLParticlesAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class COpenGLParticlesAppUi : public CAknViewAppUi
	{
public:
	// Constructors and destructor
	void ConstructL();
	COpenGLParticlesAppUi();
	virtual ~COpenGLParticlesAppUi();

private:
	// Functions from base classes
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	// Data
	COpenGLParticlesAppView* iAppView;

	};

#endif // __OPENGLPARTICLESAPPUI_h__
// End of File
