/*
 ============================================================================
 Name		: LemonMicro.pan
 Author	  : 
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __LEMONMICRO_PAN__
#define __LEMONMICRO_PAN__

/** LemonMicro application panic codes */
enum TLemonMicroPanics
	{
	ELemonMicroUi = 1
	// add further panics here
	};

inline void Panic(TInt aReason)
	{
	_LIT(applicationName, "LemonMicro");
	User::Panic(applicationName, aReason);
	}

inline void PanicIfError(TInt aPanicCode)
	{
	if (aPanicCode != KErrNone)
		{
		Panic(aPanicCode);
		}
	}

#endif // __LEMONMICRO_PAN__
