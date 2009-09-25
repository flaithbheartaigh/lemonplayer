/*
 ============================================================================
 Name		: TimerShutdownTask.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTimerShutdownTask declaration
 ============================================================================
 */

#ifndef TIMERSHUTDOWNTASK_H
#define TIMERSHUTDOWNTASK_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>


#include "TaskInterface.h"
// CLASS DECLARATION

/**
 *  CTimerShutdownTask
 * 
 */
class CTimerShutdownTask : 	public CBase,
							public MTaskInterface
	{
public:
	// Constructors and destructor
	~CTimerShutdownTask();
	static CTimerShutdownTask* NewL(const TInt aPriority);
	static CTimerShutdownTask* NewLC(const TInt aPriority);

private:
	CTimerShutdownTask();
	void ConstructL(const TInt aPriority);
	
public:
	//MTaskInterface
	virtual void TimerExpired();
	//��ʼ��ʱ�ػ�
	void StartTask(TTimeIntervalMicroSeconds32 anInterval);
	//ȡ����ʱ�ػ�
	void CancelTask();
	
	};

#endif // TIMERSHUTDOWNTASK_H
