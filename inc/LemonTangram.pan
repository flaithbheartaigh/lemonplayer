/*
 ============================================================================
 Name		: LemonTangram.pan
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __LEMONTANGRAM_PAN__
#define __LEMONTANGRAM_PAN__

/** LemonTangram application panic codes */
enum TLemonTangramPanics
	{
	ELemonTangramUi = 1
	// add further panics here
	};

inline void Panic(TLemonTangramPanics aReason)
	{
	_LIT(applicationName, "LemonTangram");
	User::Panic(applicationName, aReason);
	}

#endif // __LEMONTANGRAM_PAN__
