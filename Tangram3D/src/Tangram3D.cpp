/*
 ============================================================================
 Name		: Tangram3D.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "Tangram3DApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CTangram3DApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

