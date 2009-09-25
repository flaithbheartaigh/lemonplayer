#ifndef TASKINTERFACE_H
#define TASKINTERFACE_H

#include "TimeOutNotifier.h"
#include "TimeOutTimer.h"

class MTaskInterface : public MTimeOutNotifier
	{
public:
	//��ʼ��ʱ�ػ�
	virtual void StartTask(TTimeIntervalMicroSeconds32 anInterval) = 0;
	//ȡ����ʱ�ػ�
	virtual void CancelTask() = 0;

protected:
	CTimeOutTimer* iTimer;
	};
#endif /*TASKINTERFACE_H*/
