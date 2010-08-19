/*
 ============================================================================
 Name		: ThemeChange.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "ThemeChangeApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CThemeChangeApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

