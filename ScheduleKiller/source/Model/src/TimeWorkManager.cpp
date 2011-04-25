/*
 ============================================================================
 Name		: TimeWorkManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTimeWorkManager implementation
 ============================================================================
 */

#include "TimeWorkManager.h"
#include "SHPlatform.h"

CTimeWorkManager::CTimeWorkManager() :
	CActive(EPriorityStandard) // Standard priority
	,iNotify(NULL)
	{
	}

CTimeWorkManager* CTimeWorkManager::NewLC()
	{
	CTimeWorkManager* self = new (ELeave) CTimeWorkManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTimeWorkManager* CTimeWorkManager::NewL()
	{
	CTimeWorkManager* self = CTimeWorkManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CTimeWorkManager::ConstructL()
	{
	User::LeaveIfError(iTimer.CreateLocal()); // Initialize timer
	CActiveScheduler::Add(this); // Add to scheduler
	}

CTimeWorkManager::~CTimeWorkManager()
	{
	Cancel(); // Cancel any request, if outstanding
	iTimer.Close(); // Destroy the RTimer object
	// Delete instance variables if any
	}

void CTimeWorkManager::DoCancel()
	{
	iTimer.Cancel();
	}

void CTimeWorkManager::StartL(TTimeIntervalMicroSeconds32 aDelay)
	{
	Cancel(); // Cancel any request, just to be sure
	iState = EUninitialized;
	iTimer.After(iStatus, aDelay); // Set for later
	SetActive(); // Tell scheduler a request is active
	}

void CTimeWorkManager::RunL()
	{
	if (iState == EUninitialized)
		{
		// Do something the first time RunL() is called
		iState = EInitialized;
		
		AtTime();
		}
	else if (iState != EError)
		{
		switch (iStatus.Int())
			{
			case KErrNone:
				{
				// Do something
				KillProcess();	
				}
				break;
			case KErrAbort:
				AtTime();
				break;
			default:
				break;
			}	
		}
	}

void CTimeWorkManager::AtTime()
	{
	TTime time = SHModel()->GetTaskInfoManager()->GetMinTime();
	TTime now;
	now.HomeTime();
	if (time > now)
		{
		iTimer.At(iStatus, time); // Set for 1 sec later
		SetActive(); // Tell scheduler a request is active
		}
	}

TInt CTimeWorkManager::RunError(TInt aError)
	{
	return aError;
	}

void CTimeWorkManager::KillProcess()
	{
	SHModel()->GetTaskInfoManager()->TimeOut();
	
	//Ë¢ÐÂ½çÃæ
	if (iNotify)
		iNotify->TimeOut();
	
	if (SHModel()->GetTaskInfoManager()->ExistTask())
		AtTime();
	else
		User::Exit(0);
	}
