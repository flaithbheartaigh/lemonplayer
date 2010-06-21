/*
 * SMSDef.h
 *
 *  Created on: 2010-4-15
 *      Author: johnzeng
 */

#ifndef SMSDEF_H_
#define SMSDEF_H_

#include <msvstd.h>
#include <BADESCA.H>
#include "MacroUtil.h"

const TInt KMaxSMSSize = 300; // Max SMS size
const TInt KMaxAddressSize = 20; //Max Telephone Number size

typedef struct _CSMSInfoList
	{
	HBufC* iNumber;
	HBufC* iContent;
	TMsvId iMsgId;

	_CSMSInfoList()
		{
		iNumber = NULL;
		iContent = NULL;
		}

	~_CSMSInfoList()
		{
			SAFE_DELETE(iNumber)
			SAFE_DELETE(iContent)
		}
	} CSMSInfoList;

typedef RPointerArray<CSMSInfoList> CSMSInfoListArray;
	
typedef struct _CSMSDraftInfo
	{
	CDesCArray* iNumbers;
	CDesCArray* iNames;	
	HBufC* iContent;

	_CSMSDraftInfo()
		{
		iNumbers = NULL;
		iNames = NULL;
		iContent = NULL;
		}

	~_CSMSDraftInfo()
		{
		iNumbers->Reset();
		delete iNumbers;
		
		iNames->Reset();
		delete iNames;
		
		SAFE_DELETE(iContent)
		}
	
	} CSMSDraftInfo;


#endif /* SMSDEF_H_ */
