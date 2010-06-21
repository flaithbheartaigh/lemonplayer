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

_LIT(KDataFile,"data.txt");
_LIT(KRemovedDataFile,"rdata.txt");
_LIT(KDateFormat,"%Y%M%D%1%/1%2%/1%3 %H:%T");
_LIT8(KSplitItemFormat,"\n");
_LIT8(KSplitElementNumberFormat,"#");
_LIT8(KSplitElementLengthFormat,"@");

const TInt KSplitElementDateLength = 15; //ʱ��̶�����15λ

//���ݽṹ
typedef struct _SimMsgData
	{
	TTime iTime;
	HBufC* iNumber;
	HBufC* iName;
	HBufC* iContent;	
	
	_SimMsgData()
		{
		iNumber = NULL;
		iName = NULL;
		iContent = NULL;
		}
	
	~_SimMsgData()
		{
		SAFE_DELETE(iNumber)
		SAFE_DELETE(iName)
		SAFE_DELETE(iContent)
		}
	
	}SimMsgData,*pSimMsgData;
	
typedef RPointerArray<SimMsgData> RSimMsgDataArray;
#endif /* SIMMSGSTRUCT_H_ */
