/*
 ============================================================================
 Name		: ThemeBackground.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Exe source file
 ============================================================================
 */

//  Include Files  

#include "ThemeBackground.h"
#include <e32base.h>
#include <e32std.h>
#include <e32cons.h>			// Console
#include "AOManager.h"

//  Constants

LOCAL_C void MainL()
	{
	//
	// add your program code here, example code below
	//
	CAOManager *exampleViews = CAOManager::NewL();
	CleanupStack::PushL(exampleViews);
	exampleViews->StartL(100000);
	CActiveScheduler::Start();	
	CleanupStack::PopAndDestroy(exampleViews);
	}

LOCAL_C void DoStartL()
	{
	// Create active scheduler (to run active objects)
	CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);

	MainL();

	// Delete active scheduler
	CleanupStack::PopAndDestroy(scheduler);
	}

//  Global Functions

GLDEF_C TInt E32Main()
	{
	// Create cleanup stack
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();

	// Run application code inside TRAP harness, wait keypress when terminated
	TRAPD(mainError, DoStartL());

	delete cleanup;
	__UHEAP_MARKEND;
	return KErrNone;
	}

