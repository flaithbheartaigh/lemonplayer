/*
 ============================================================================
 Name		: TaskManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTaskManager implementation
 ============================================================================
 */

#include "TaskManager.h"

#include "MacroUtil.h"
#include "TimerShutdownTask.h"

CTaskManager::CTaskManager():
iShutdown(NULL)
	{
	// No implementation required
	}

CTaskManager::~CTaskManager()
	{
	SAFE_DELETE(iShutdown);
	}

CTaskManager* CTaskManager::NewLC()
	{
	CTaskManager* self = new (ELeave)CTaskManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTaskManager* CTaskManager::NewL()
	{
	CTaskManager* self=CTaskManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CTaskManager::ConstructL()
	{
	}

void CTaskManager::StartShutDown(TTimeIntervalMicroSeconds32 anInterval)
	{
	if (iShutdown == NULL)
		{
		iShutdown = CTimerShutdownTask::NewL(EPriorityLow);
		}
	if (iShutdown)
		iShutdown->StartTask(anInterval);
	}

void CTaskManager::CancelShutDown()
	{
	if (iShutdown)
		iShutdown->CancelTask();
	}
