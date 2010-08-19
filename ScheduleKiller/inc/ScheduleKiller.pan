/*
 ============================================================================
 Name		: ScheduleKiller.pan
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __SCHEDULEKILLER_PAN__
#define __SCHEDULEKILLER_PAN__

/** ScheduleKiller application panic codes */
enum TScheduleKillerPanics
	{
	EScheduleKillerUi = 1
	// add further panics here
	};

inline void Panic(TScheduleKillerPanics aReason)
	{
	_LIT(applicationName, "ScheduleKiller");
	User::Panic(applicationName, aReason);
	}

#endif // __SCHEDULEKILLER_PAN__
