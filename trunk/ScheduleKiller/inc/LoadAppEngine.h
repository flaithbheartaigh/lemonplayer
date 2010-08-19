/*
 ============================================================================
 Name		: LoadAppEngine.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLoadAppEngine declaration
 ============================================================================
 */

#ifndef LOADAPPENGINE_H
#define LOADAPPENGINE_H

#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib

#include <coemain.h>
#include <apgcli.h>
#include <apgwgnam.h>
#include <apgtask.h>
#include <eikenv.h>
#include <apgcli.h>
#include <aknlists.h> 
#include <AknIconArray.h> 
#include <eikclbd.h>
#include <w32std.h>
#include <GULICON.H>

class MLoadAppEngineNotify
	{
public:
	virtual void GetAppInfo(CGulIcon* aIcon,const TDesC& aInfo,const TUid aUid) = 0;
	};

class CLoadAppEngine : public CActive
	{
public:
	// Cancel and destroy
	~CLoadAppEngine();

	// Two-phased constructor.
	static CLoadAppEngine* NewL(MLoadAppEngineNotify* aNotify);

	// Two-phased constructor.
	static CLoadAppEngine* NewLC(MLoadAppEngineNotify* aNotify);

public:
	// New functions
	// Function for making the initial request
	void StartL(TTimeIntervalMicroSeconds32 aDelay);

private:
	// C++ constructor
	CLoadAppEngine(MLoadAppEngineNotify* aNotify);

	// Second-phase constructor
	void ConstructL();

private:
	// From CActive
	// Handle completion
	void RunL();

	// How to cancel me
	void DoCancel();

	// Override to handle leaves from RunL(). Default implementation causes
	// the active scheduler to panic.
	TInt RunError(TInt aError);
	
	void SegmentInit();
	TBool SegmentLoop();

private:
	enum TLoadAppEngineState
		{
		EUninitialized, // Uninitialized
		EInitialized, // Initalized
		EStop,
		EError
		// Error condition
		};

private:
	TInt iState; // State of the active object
	RTimer iTimer; // Provides async timing service

	MLoadAppEngineNotify* iNotify;
	
	RApaLsSession *iALS;  
	TInt iAppIndex;
	};

#endif // LOADAPPENGINE_H
