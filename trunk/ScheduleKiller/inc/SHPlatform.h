/*
 * SHPlatform.h
 *
 *  Created on: 2010-5-21
 *      Author: johnzeng
 */
#ifndef SHPLATFORM_H_
#define SHPLATFORM_H_
#include <ScheduleKiller_0xE35F8580.rsg>
#include <ScheduleKiller.mbg>
#include "ScheduleKiller.hrh"
#include "ScheduleKillerAppUi.h"
#include "SHError.h"

_LIT8(KViewChangeFromMain, 	"main");
_LIT8(KViewChangeFromApp, 	"app");
_LIT8(KViewChangeParamReboot,"reboot");

inline void SHChangeView(TInt aView)
	{
	STATIC_CAST(CScheduleKillerAppUi*,CEikonEnv::Static()->AppUi()) ->ActivateLocalViewL(TUid::Uid(aView));
	}
;

inline void SHChangeViewParam(TInt aView, const TDesC8& aCustomMessage)
	{
	STATIC_CAST(CScheduleKillerAppUi*,CEikonEnv::Static()->AppUi()) ->ActivateLocalViewL(TUid::Uid(aView), TUid::Uid(aView),
			aCustomMessage);
	}
;

inline CSHModel* SHModel()
	{
	return STATIC_CAST(CScheduleKillerAppUi*,CEikonEnv::Static()->AppUi()) ->GetModel();
	}
;

inline CUIManager* SHUI()
	{
	return STATIC_CAST(CScheduleKillerAppUi*,CEikonEnv::Static()->AppUi()) ->GetUI();
	}
;

inline void SHErrFun(const TSHErrInfo& aInfo,const TSHErrState& aState)
	{
	STATIC_CAST(CScheduleKillerAppUi*,CEikonEnv::Static()->AppUi())->SHError(aInfo, aState);
	}
;

inline void SHErr(const TInt& aErr, const TSHErrInfo& aInfo,const TSHErrState& aState)
	{
	if (aErr != KErrNone)
		STATIC_CAST(CScheduleKillerAppUi*,CEikonEnv::Static()->AppUi())->SHError(aInfo, aState);
	}
;
#endif /* SHPLATFORM_H_ */
