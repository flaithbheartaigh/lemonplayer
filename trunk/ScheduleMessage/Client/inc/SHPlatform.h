/*
 * SHPlatform.h
 *
 *  Created on: 2010-5-21
 *      Author: johnzeng
 */

#ifndef SHPLATFORM_H_
#define SHPLATFORM_H_

#include "SimulateMessage.hrh"
#include <ScheduleMessage_0xE70CE84A.rsg>

#include "SimulateMessageAppUi.h"

#include "SimMsgServerSession.h"

_LIT8(KViewChangeFromLoadDraft,"draft");
_LIT8(KViewChangeFromModify,"modify");
_LIT8(KViewChangeParamReboot,"reboot");

inline void SHChangeView(TInt aView)
	{
	STATIC_CAST(CSimulateMessageAppUi*,CEikonEnv::Static()->AppUi())
	->ActivateLocalViewL(TUid::Uid(aView));
	}
;

inline void SHChangeViewParam(TInt aView,const TDesC8& aCustomMessage)
	{
	STATIC_CAST(CSimulateMessageAppUi*,CEikonEnv::Static()->AppUi())
	->ActivateLocalViewL(TUid::Uid(aView),TUid::Uid(aView),aCustomMessage);
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

inline CSimMsgServerSession& SHSession()
	{
	return STATIC_CAST(CSimulateMessageAppUi*,CEikonEnv::Static()->AppUi())
	->GetSession();
	}
;
#endif /* SHPLATFORM_H_ */
