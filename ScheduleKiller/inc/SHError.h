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
	ESHErrNormal = 0,	//普通
	ESHErrWarning,		//提示
	ESHErrSerious 		//严重退出
};

enum TSHErrInfo
{
	ESHErrNone = 0,
	ELAWarnChooseAppNull,			//未选择程序	,
	ELAWarnTimeLowerThanNow,		//时间是在过去
	ELAWarnDuplicateTask			//重复任务
};

#endif /* LAERROR_H_ */
