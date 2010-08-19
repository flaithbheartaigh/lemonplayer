/*
 ============================================================================
 Name		: CloverDemo.pan
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __CLOVERDEMO_PAN__
#define __CLOVERDEMO_PAN__

/** CloverDemo application panic codes */
enum TCloverDemoPanics
	{
	ECloverDemoUi = 1
	// add further panics here
	};

inline void Panic(TCloverDemoPanics aReason)
	{
	_LIT(applicationName, "CloverDemo");
	User::Panic(applicationName, aReason);
	}

#endif // __CLOVERDEMO_PAN__
