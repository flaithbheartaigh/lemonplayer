/*
 * ThemeCommonDef.h
 *
 *  Created on: 2010-4-2
 *      Author: johnzeng
 */

#ifndef THEMECOMMONDEF_H_
#define THEMECOMMONDEF_H_

#include <e32def.h>

//�����ļ�
_LIT(KConfigFile,"C:\\data\\WallpaperChanger\\config.ini");

_LIT(KCfgAttAutoStart,"autostart");
_LIT(KCfgAttFrequency,"frequency");

//Ƶ��
enum TFrequencyTime
	{
	EFrequencyOneHour = 0,
	EFrequencyEightHours,
	EFrequencyOneDay,
	EFrequencyThreeDays,
	EFrequencyOneWeek,
	EFrequencyTotal
	};

const TUid KUidServer = TUid::Uid(0xEAC842A1);
_LIT(KServerFileName,"\\sys\\bin\\WallpaperBackground.exe");
_LIT(KProcessToSearch, "WallpaperBackground");
#endif /* THEMECOMMONDEF_H_ */
