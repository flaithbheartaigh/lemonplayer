/*
 * SHPlatform.h
 *
 *  Created on: 2010-5-21
 *      Author: johnzeng
 */

#ifndef SHPLATFORM_H_
#define SHPLATFORM_H_

#include "SimulateMessage.hrh"
#include <SimulateMessage_0xE70CE849.rsg>

#include "SimulateMessageAppUi.h"

inline void SHChangeView(TInt aView)
	{
	STATIC_CAST(CSimulateMessageAppUi*,CEikonEnv::Static()->AppUi())
	->ActivateLocalViewL(TUid::Uid(aView));
	}
;

inline CSHModel* SHModel()
	{
	return STATIC_CAST(CSimulateMessageAppUi*,CEikonEnv::Static()->AppUi())
	->GetModel();
	}
;

inline CUIManager* SHUI()
	{
	return STATIC_CAST(CSimulateMessageAppUi*,CEikonEnv::Static()->AppUi())
	->GetUI();
	}
;

#endif /* SHPLATFORM_H_ */
