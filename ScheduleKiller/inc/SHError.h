/*
 * LAError.h
 *
 *  Created on: 2009-9-1
 *      Author: yicha
 */

#ifndef SHERROR_H_
#define SHERROR_H_

#include <e32std.h>
#include <e32base.h>

enum TSHErrState
{
	ESHErrNormal = 0,	//��ͨ
	ESHErrWarning,		//��ʾ
	ESHErrSerious 		//�����˳�
};

enum TSHErrInfo
{
	ESHErrNone = 0,
	ELAWarnChooseAppNull,			//δѡ�����	,
	ELAWarnTimeLowerThanNow,		//ʱ�����ڹ�ȥ
	ELAWarnDuplicateTask			//�ظ�����
};

#endif /* LAERROR_H_ */
