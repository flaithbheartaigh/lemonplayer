/*
 ============================================================================
 Name		: TimerShutdownTask.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTimerShutdownTask implementation
 ============================================================================
 */

#include "TimerShutdownTask.h"

#include "MacroUtil.h"
#include "TimeOutTimer.h"

CTimerShutdownTask::CTimerShutdownTask()
	{
	// No implementation required
	}

CTimerShutdownTask::~CTimerShutdownTask()
	{
	SAFE_DELETE_ACTIVE(iTimer);	
	}

CTimerShutdownTask* CTimerShutdownTask::NewLC(const TInt aPriority)
	{
	CTimerShutdownTask* self = new (ELeave)CTimerShutdownTask();
	CleanupStack::PushL(self);
	self->ConstructL(aPriority);
	return self;
	}

CTimerShutdownTask* CTimerShutdownTask::NewL(const TInt aPriority)
	{
	CTimerShutdownTask* self=CTimerShutdownTask::NewLC(aPriority);
	CleanupStack::Pop(); // self;
	return self;
	}

void CTimerShutdownTask::ConstructL(const TInt aPriority)
	{
	iTimer = CTimeOutTimer::NewL(aPriority, *this);
	}

void CTimerShutdownTask::TimerExpired()
	{
	User::Exit(0);
	}

//��ʼ��ʱ�ػ�
void CTimerShutdownTask::StartTask(TTimeIntervalMicroSeconds32 anInterval)
	{
	if (iTimer)
		{
		iTimer->After(anInterval);
		}
	}

//ȡ����ʱ�ػ�
void CTimerShutdownTask::CancelTask()
	{
	if (iTimer)
		{
		if (iTimer->IsActive())
			iTimer->Cancel();
		}
	}
