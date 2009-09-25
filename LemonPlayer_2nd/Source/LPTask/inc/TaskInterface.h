#ifndef TASKINTERFACE_H
#define TASKINTERFACE_H

#include "TimeOutNotifier.h"
#include "TimeOutTimer.h"

class MTaskInterface : public MTimeOutNotifier
	{
public:
	//开始定时关机
	virtual void StartTask(TTimeIntervalMicroSeconds32 anInterval) = 0;
	//取消定时关机
	virtual void CancelTask() = 0;

protected:
	CTimeOutTimer* iTimer;
	};
#endif /*TASKINTERFACE_H*/
