/*
 ============================================================================
 Name		: AnimationStruct.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAnimationStruct implementation
 ============================================================================
 */

#include "AnimationStruct.h"

CAnimationStruct::~CAnimationStruct()
	{
	StopTimer();
	delete iPeriodicTimer;
	iPeriodicTimer = NULL;
	}

void CAnimationStruct::ConstructL()
	{
	iStartTick = 1000;
	iTick = 1000000;
	iPeriodicTimer = CPeriodic::NewL(CActive::EPriorityStandard);
	}

void CAnimationStruct::SetStartTick(TTimeIntervalMicroSeconds32  aTick)
	{
	iStartTick = aTick;
	}

void CAnimationStruct::SetTimerTick(TTimeIntervalMicroSeconds32 aTick)
	{
	iTick = aTick;
	}

void CAnimationStruct::DoPeriod()
	{
	if (Tick())
		{
		Update();
		}
	else
		{
		StopTimer();
		}
	}

TInt CAnimationStruct::Period(TAny * aPtr)
	{
	((CAnimationStruct*)aPtr)->DoPeriod();
	return TRUE;
	}

TBool CAnimationStruct::Tick()
	{
	return EFalse;
	}

void CAnimationStruct::Update()
	{
	}

void CAnimationStruct::StartTimer()
	{
	if (!iPeriodicTimer->IsActive())
		{
		iPeriodicTimer->Start(iStartTick, iTick, TCallBack(CAnimationStruct::Period,
				this));
		}
	}

void CAnimationStruct::StopTimer()
	{
	if (iPeriodicTimer)
		{
		if (iPeriodicTimer->IsActive())
			{
			iPeriodicTimer->Cancel();
			}
		}
	}
