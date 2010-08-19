/*
 ============================================================================
 Name		: CloverDemo.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "CloverDemoApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CCloverDemoApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

