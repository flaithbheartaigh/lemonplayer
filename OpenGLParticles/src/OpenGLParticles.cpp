/*
 ============================================================================
 Name		: OpenGLParticles.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "OpenGLParticlesApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new COpenGLParticlesApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

