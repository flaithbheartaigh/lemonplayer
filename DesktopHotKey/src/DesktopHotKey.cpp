/*
 ============================================================================
 Name		: DesktopHotKey.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "DesktopHotKeyApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CDesktopHotKeyApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

