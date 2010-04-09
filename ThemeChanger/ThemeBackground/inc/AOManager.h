/*
 ============================================================================
 Name		: AOManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAOManager declaration
 ============================================================================
 */

#ifndef AOMANAGER_H
#define AOMANAGER_H

#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib
#include <w32std.h>

class CThemeManager;

class CAOManager : public CActive
	{
public:
	// Cancel and destroy
	~CAOManager();

	// Two-phased constructor.
	static CAOManager* NewL();

	// Two-phased constructor.
	static CAOManager* NewLC();

public:
	// New functions
	// Function for making the initial request
	void StartL(TTimeIntervalMicroSeconds32 aDelay);

private:
	// C++ constructor
	CAOManager();

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
	TBool GetTime(TTime& aTime);

private:
	enum TAOManagerState
		{
		EUninitialized, // Uninitialized
		EInitialized, // Initalized
		EError
		// Error condition
		};

private:
	TInt iState; // State of the active object
	RTimer iTimer; // Provides async timing service

	CThemeManager* iThemeManager;
	
	};

#endif // AOMANAGER_H
