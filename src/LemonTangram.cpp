/*
 ============================================================================
 Name		: LemonTangram.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "LemonTangramApplication.h"

#ifdef __SERIES60_3X__
#include <eikstart.h>

LOCAL_C CApaApplication* NewApplication()
    {
    return new CLemonTangramApplication;
    }
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
	}
	
#else
EXPORT_C CApaApplication* NewApplication()
    {
    return (static_cast<CApaApplication*>(new CLemonTangramApplication));
    }
#ifndef EKA2
GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }
#endif
#endif

