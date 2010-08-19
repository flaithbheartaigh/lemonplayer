/*
 ============================================================================
 Name		: ThemeAutoStart.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Exe source file
 ============================================================================
 */

//  Include Files  

#include "ThemeAutoStart.h"
#include <e32base.h>
#include <e32std.h>
#include <e32cons.h>			// Console
#include <apgtask.h>
#include <eikenv.h>
#include <apgcli.h>

#include "Configuration.h"
#include "ThemeCommonDef.h"
//  Local Functions

LOCAL_C TBool IsAutoStart()
	{
	CConfiguration* config;
	TBool result = EFalse;
	TBuf<8> value;
	value.FillZ();
	config = CConfiguration::NewL(KConfigFile);
	if (config->Get(KCfgAttAutoStart, value))
		{
		if (value.Compare(_L("1")) == 0)		
			result = ETrue;
		else
			result = EFalse;
		}
	else
		{
		result = EFalse;
		}
	delete config;
	return result;
	}

LOCAL_C void StartServer()
	{
	TApaTaskList taskList(CEikonEnv::Static()->WsSession());
	TApaTask task = taskList.FindApp(KUidServer);
	if (!task.Exists())
		{
		RApaLsSession ras;
		User::LeaveIfError(ras.Connect());
		CleanupClosePushL(ras);
		TApaAppInfo appInfo;
		ras.GetAppInfo(appInfo, KUidServer);
		CApaCommandLine *cmd = CApaCommandLine::NewLC();
		//cmd->SetExecutableNameL(appInfo.iFullName);
		cmd->SetExecutableNameL(KServerFileName);
		cmd->SetCommandL(EApaCommandRun);
		ras.StartApp(*cmd);
		CleanupStack::PopAndDestroy(cmd);
		CleanupStack::Pop();
		ras.Close();
		}	
	}
LOCAL_C void MainL()
	{
	//检查文件,存在自动启动,则启动
	if (IsAutoStart())
		StartServer();
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

