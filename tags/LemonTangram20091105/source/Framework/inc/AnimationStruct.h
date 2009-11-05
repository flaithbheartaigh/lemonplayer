/*
 ============================================================================
 Name		: AnimationStruct.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAnimationStruct declaration
 ============================================================================
 */

#ifndef ANIMATIONSTRUCT_H
#define ANIMATIONSTRUCT_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION
/**
 *  CAnimationStruct
 * 
 */
class CAnimationStruct 
	{
public:	
	virtual ~CAnimationStruct();	
	
	void ConstructL();
	
	virtual TBool Tick();
	virtual void Update();
	static TInt Period(TAny* aPtr);
	void DoPeriod();

	void StartTimer();
	void StopTimer();

	void SetStartTick(TTimeIntervalMicroSeconds32  aTick);
	void SetTimerTick(TTimeIntervalMicroSeconds32  aTick);

private:
	CPeriodic* iPeriodicTimer;
	TTimeIntervalMicroSeconds32  iStartTick;
	TTimeIntervalMicroSeconds32  iTick;
	};

#endif // ANIMATIONSTRUCT_H
