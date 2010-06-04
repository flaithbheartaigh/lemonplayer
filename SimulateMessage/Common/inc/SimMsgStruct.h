/*
 * SimMsgStruct.h
 *
 *  Created on: 2010-5-25
 *      Author: johnzeng
 */

#ifndef SIMMSGSTRUCT_H_
#define SIMMSGSTRUCT_H_

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <e32cmn.h>

#include "MacroUtil.h"

//数据结构
typedef struct _SimMsgData
	{
	TTime iTime;
	HBufC* iNumber;
	HBufC* iContent;	
	
	_SimMsgData()
		{
		iNumber = NULL;
		iContent = NULL;
		}
	
	~_SimMsgData()
		{
		SAFE_DELETE(iNumber)
		SAFE_DELETE(iContent)
		}
	
	}SimMsgData,*pSimMsgData;
	
typedef RPointerArray<SimMsgData> RSimMsgDataArray;
#endif /* SIMMSGSTRUCT_H_ */
