/*
 ============================================================================
 Name		: ThemeChange.pan
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __THEMECHANGE_PAN__
#define __THEMECHANGE_PAN__

/** ThemeChange application panic codes */
enum TThemeChangePanics
	{
	EThemeChangeUi = 1
	// add further panics here
	};

inline void Panic(TThemeChangePanics aReason)
	{
	_LIT(applicationName, "ThemeChange");
	User::Panic(applicationName, aReason);
	}

#endif // __THEMECHANGE_PAN__
