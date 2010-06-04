/*
 ============================================================================
 Name		: SimulateMessage.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "SimulateMessageApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CSimulateMessageApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

