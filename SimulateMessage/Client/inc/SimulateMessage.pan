/*
 ============================================================================
 Name		: SimulateMessage.pan
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __SIMULATEMESSAGE_PAN__
#define __SIMULATEMESSAGE_PAN__

/** SimulateMessage application panic codes */
enum TSimulateMessagePanics
	{
	ESimulateMessageUi = 1
	// add further panics here
	};

inline void Panic(TSimulateMessagePanics aReason)
	{
	_LIT(applicationName, "SimulateMessage");
	User::Panic(applicationName, aReason);
	}

#endif // __SIMULATEMESSAGE_PAN__
