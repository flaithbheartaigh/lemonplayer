/*
 ============================================================================
 Name		: TimeWorkManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTimeWorkManager declaration
 ============================================================================
 */

#ifndef TIMEWORKMANAGER_H
#define TIMEWORKMANAGER_H

#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib
class CTimeWorkManager : public CActive
	{
public:
	// Cancel and destroy
	~CTimeWorkManager();

	// Two-phased constructor.
	static CTimeWorkManager* NewL();

	// Two-phased constructor.
	static CTimeWorkManager* NewLC();

public:
	// New functions
	// Function for making the initial request
	void StartL(TTimeIntervalMicroSeconds32 aDelay);

private:
	// C++ constructor
	CTimeWorkManager();

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
	
	void AtTime();

private:
	enum TTimeWorkManagerState
		{
		EUninitialized, // Uninitialized
		EInitialized, // Initalized
		EError
		// Error condition
		};
	
public:
	//new func
	void KillProcess();

private:
	TInt iState; // State of the active object
	RTimer iTimer; // Provides async timing service

	};

#endif // TIMEWORKMANAGER_H
