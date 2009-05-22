/*
 ============================================================================
 Name		: LemonTangram.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "LemonTangramApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CLemonTangramApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}

