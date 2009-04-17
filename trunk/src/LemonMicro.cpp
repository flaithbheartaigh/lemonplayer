/*
 ============================================================================
 Name		: LemonMicro.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "LemonMicroApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CLemonMicroApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}

