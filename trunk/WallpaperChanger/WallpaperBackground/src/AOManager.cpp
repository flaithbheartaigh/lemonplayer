/*
 ============================================================================
 Name		: AOManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAOManager implementation
 ============================================================================
 */

#include "AOManager.h"
#include "ThemeManager.h"

#include <apgwgnam.h>
#include "Configuration.h"
#include "ThemeCommonDef.h"

CAOManager::CAOManager() :
	CActive(EPriorityStandard), iThemeManager(NULL)
	{
	}

CAOManager* CAOManager::NewLC()
	{
	CAOManager* self = new (ELeave) CAOManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CAOManager* CAOManager::NewL()
	{
	CAOManager* self = CAOManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CAOManager::ConstructL()
	{
	User::LeaveIfError(iTimer.CreateLocal()); // Initialize timer
	CActiveScheduler::Add(this); // Add to scheduler

	iThemeManager = CThemeManager::NewL();

	//	User::LeaveIfError(iWsSession.Connect());
	//
	//	iWindowGroup = new (ELeave) RWindowGroup(iWsSession);
	//	User::LeaveIfError(iWindowGroup->Construct(
	//			reinterpret_cast<TUint32> (iWindowGroup), EFalse));
	//	User::LeaveIfError(iWindowGroup->SetName(KTextConsoleTitle));
	//
	//	//好像只用把Name前面写为 200 打头, 就可以变为任务列表隐藏    
	////    TBuf<300> name;
	////    iWindowGroup->Name(name);
	//    
	//    CApaWindowGroupName* wgName = CApaWindowGroupName::NewLC(iWsSession, iWindowGroup->Identifier());
	//    wgName->SetHidden(ETrue);
	//    wgName->SetWindowGroupName(*iWindowGroup);
	//    CleanupStack::PopAndDestroy(wgName);

	//    name.Zero();
	//    iWindowGroup->Name(name);

	}

CAOManager::~CAOManager()
	{
	delete iThemeManager;

	Cancel(); // Cancel any request, if outstanding
	iTimer.Close(); // Destroy the RTimer object
	// Delete instance variables if any
	}

void CAOManager::DoCancel()
	{
	iTimer.Cancel();
	}

void CAOManager::StartL(TTimeIntervalMicroSeconds32 aDelay)
	{
	Cancel(); // Cancel any request, just to be sure
	iState = EUninitialized;
	iTimer.After(iStatus, aDelay); // Set for later
	SetActive(); // Tell scheduler a request is active
	}

void CAOManager::RunL()
	{
	if (iState == EUninitialized)
		{
		// Do something the first time RunL() is called
		iState = EInitialized;
		}
	else if (iState != EError)
		{
		// Do something
		TRAPD(err,iThemeManager->ChangeTheme());
		}

	AtTime();
	//	iTimer.After(iStatus, 5000000); // Set for 5 sec later
	//	SetActive(); // Tell scheduler a request is active
	}

void CAOManager::AtTime()
	{
	TTime timer;
	//读取配置文件
	if (GetTime(timer))
		{
		iTimer.At(iStatus, timer);
		SetActive(); // Tell scheduler a request is active
		}
	}

TBool CAOManager::GetTime(TTime& aTime)
	{
	CConfiguration* config;
	TBool result = EFalse;
	TBuf<8> value;
	value.FillZ();
	config = CConfiguration::NewL(KConfigFile);
	if (config->Get(KCfgAttFrequency, value))
		{
		TLex a(value);
		TUint num;
		if (a.Val(num,EDecimal) == KErrNone)
			{			
			aTime.HomeTime();
			TInt64 timer = aTime.Int64();

			TInt64 offset[EFrequencyTotal] = {
					20000000ll,//3600000000,			//1 hour 60*60
					28800000000ll,		//8 hours,
					86400000000ll,		//1 day
					259200000000ll,		//3 days
					604800000000ll,		//1 week
			};
			if (num >= 0 && num < EFrequencyTotal)
				{
				timer += offset[num];
				aTime = TTime(timer);
				result = ETrue;
				}
			else
				result = EFalse;
			}
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

TInt CAOManager::RunError(TInt aError)
	{
	return aError;
	}
