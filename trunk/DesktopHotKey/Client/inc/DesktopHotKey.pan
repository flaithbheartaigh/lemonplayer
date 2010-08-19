/*
 ============================================================================
 Name		: DesktopHotKey.pan
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __DESKTOPHOTKEY_PAN__
#define __DESKTOPHOTKEY_PAN__

/** DesktopHotKey application panic codes */
enum TDesktopHotKeyPanics
	{
	EDesktopHotKeyUi = 1
	// add further panics here
	};

inline void Panic(TDesktopHotKeyPanics aReason)
	{
	_LIT(applicationName, "DesktopHotKey");
	User::Panic(applicationName, aReason);
	}

#endif // __DESKTOPHOTKEY_PAN__
