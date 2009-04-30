/*
 ============================================================================
 Name		: MP3EncodeDLLDll.cpp 
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : MP3EncodeDLLDll.cpp - main DLL source
 ============================================================================
 */

//  Include Files  

#include <e32std.h>		 // GLDEF_C
#include "MP3EncodeDLL.pan"		// panic codes

//  Global Functions

GLDEF_C void Panic(TMP3EncodeDLLPanic aPanic)
// Panics the thread with given panic code
	{
	User::Panic(_L("MP3EncodeDLL"), aPanic);
	}

//  Exported Functions

#ifndef EKA2 // for EKA1 only
EXPORT_C TInt E32Dll(TDllReason /*aReason*/)
// Called when the DLL is loaded and unloaded. Note: have to define
// epoccalldllentrypoints in MMP file to get this called in THUMB.

	{
	return KErrNone;
	}
#endif

