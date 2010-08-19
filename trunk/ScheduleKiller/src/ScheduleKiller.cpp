/*
 ============================================================================
 Name		: ScheduleKiller.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "ScheduleKillerApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CScheduleKillerApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

