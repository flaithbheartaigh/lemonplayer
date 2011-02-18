/*
 ============================================================================
 Name		: LoadAppEngine.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLoadAppEngine implementation
 ============================================================================
 */

#include "LoadAppEngine.h"

CLoadAppEngine::CLoadAppEngine(MLoadAppEngineNotify* aNotify) :
	CActive(EPriorityStandard), iNotify(aNotify) // Standard priority
	{
	}

CLoadAppEngine* CLoadAppEngine::NewLC(MLoadAppEngineNotify* aNotify)
	{
	CLoadAppEngine* self = new (ELeave) CLoadAppEngine(aNotify);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLoadAppEngine* CLoadAppEngine::NewL(MLoadAppEngineNotify* aNotify)
	{
	CLoadAppEngine* self = CLoadAppEngine::NewLC(aNotify);
	CleanupStack::Pop(); // self;
	return self;
	}

void CLoadAppEngine::ConstructL()
	{
	User::LeaveIfError(iTimer.CreateLocal()); // Initialize timer
	CActiveScheduler::Add(this); // Add to scheduler
	
	iALS = new (ELeave) RApaLsSession;
	}

CLoadAppEngine::~CLoadAppEngine()
	{
	if (iALS)
		{
		iALS->Close();
		delete iALS;
		}
	
	Cancel(); // Cancel any request, if outstanding
	iTimer.Close(); // Destroy the RTimer object
	// Delete instance variables if any
	}

void CLoadAppEngine::DoCancel()
	{
	iTimer.Cancel();
	}

void CLoadAppEngine::StartL(TTimeIntervalMicroSeconds32 aDelay)
	{
	Cancel(); // Cancel any request, just to be sure
	iState = EUninitialized;
	iTimer.After(iStatus, aDelay); // Set for later
	SetActive(); // Tell scheduler a request is active
	}

void CLoadAppEngine::RunL()
	{
	if (iState == EUninitialized)
		{
		// Do something the first time RunL() is called
		iState = EInitialized;
		SegmentInit();
		}
	else if (iState == EInitialized)
		{
		// Do something
		SegmentLoop();
		}
	else if (iState == EStop)
		{
		return;
		}
	iTimer.After(iStatus, 1000); // Set for 1 sec later
	SetActive(); // Tell scheduler a request is active
	}

TInt CLoadAppEngine::RunError(TInt aError)
	{
	return aError;
	}

void CLoadAppEngine::SegmentInit()
	{
	User::LeaveIfError(iALS->Connect());
	User::LeaveIfError(iALS->GetAllApps());
	iAppIndex = 0;
	}

TBool CLoadAppEngine::SegmentLoop()
	{
	//TInt errCode = KErrNone;
	TApaAppInfo appInfo;

	while (!(iALS->GetNextApp(appInfo)))
		{
		//errCode = iALS->GetNextApp(appInfo);

		if (appInfo.iFullName.Right(8).CompareF(_L(".fakeapp")) == 0) //不统计J2ME
			continue;

		CFbsBitmap* AppIcon(NULL);
		CFbsBitmap* AppIconMsk(NULL);
		MAknsSkinInstance* skin = AknsUtils::SkinInstance();
		CGulIcon* icon;
		TRAPD(err, AknsUtils::CreateAppIconLC(skin, appInfo.iUid, EAknsAppIconTypeList, AppIcon, AppIconMsk);CleanupStack::Pop(2));
		
		if (err == KErrNone)
			{
			AknIconUtils::SetSize(AppIcon, TSize(32, 32), EAspectRatioNotPreserved);
			icon = CGulIcon::NewL(AppIcon, AppIconMsk);
			}
		else
			{
			icon = AknsUtils::CreateGulIconL(skin, KAknsIIDQgnMenuUnknownLst, ETrue);
			}
		//icons->AppendL(icon);

		//__LOGDES_TOFILE(appInfo.iCaption)
		TBuf<KApaMaxAppCaption> record;
		record.AppendNum(iAppIndex++);
		record.Append('\t');
		record.Append(appInfo.iCaption);

		//items->AppendL(record);

		//iUids.Append(appInfo.iUid);

		if (iNotify)
			iNotify->GetAppInfo(icon, record, appInfo.iUid);

		return ETrue;
		}

	//结束
	iState = EStop;
	return EFalse;

	}
