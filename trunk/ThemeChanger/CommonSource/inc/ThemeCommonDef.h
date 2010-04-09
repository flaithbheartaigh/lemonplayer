/*
 * ThemeCommonDef.h
 *
 *  Created on: 2010-4-2
 *      Author: johnzeng
 */

#ifndef THEMECOMMONDEF_H_
#define THEMECOMMONDEF_H_

#include <e32def.h>

//ÅäÖÃÎÄ¼þ
_LIT(KConfigFile,"C:\\data\\ThemeChanger\\config.ini");

_LIT(KCfgAttAutoStart,"autostart");
_LIT(KCfgAttFrequency,"frequency");

//ÆµÂÊ
enum TFrequencyTime
	{
	EFrequencyOneHour = 0,
	EFrequencyEightHours,
	EFrequencyOneDay,
	EFrequencyThreeDays,
	EFrequencyOneWeek,
	EFrequencyTotal
	};

const TUid KUidServer = TUid::Uid(0xEBCE407F);
_LIT(KServerFileName,"\\sys\\bin\\ThemeBackground.exe");
_LIT(KProcessToSearch, "ThemeBackground");
#endif /* THEMECOMMONDEF_H_ */
