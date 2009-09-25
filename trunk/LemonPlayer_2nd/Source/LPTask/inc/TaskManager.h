/*
 ============================================================================
 Name		: TaskManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTaskManager declaration
 ============================================================================
 */

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION
class CTimerShutdownTask;
/**
 *  CTaskManager
 * 
 */
class CTaskManager : public CBase
	{
public:
	// Constructors and destructor
	~CTaskManager();
	static CTaskManager* NewL();
	static CTaskManager* NewLC();

private:
	CTaskManager();
	void ConstructL();
	
public:
	void StartShutDown(TTimeIntervalMicroSeconds32 anInterval);
	void CancelShutDown();
	
private:
	CTimerShutdownTask* iShutdown;

	};

#endif // TASKMANAGER_H
