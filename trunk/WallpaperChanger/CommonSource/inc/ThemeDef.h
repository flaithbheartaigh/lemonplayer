/*
 * ThemeDef.h
 *
 *  Created on: 2010-3-29
 *      Author: johnzeng
 */

#ifndef THEMEDEF_H_
#define THEMEDEF_H_

#include <aknspkgid.h>		//TAknsPkgID

enum TSknLocation
	{
	ESknLoactionPhone = 0,
	ESknLoactionMMC,
	ESknLoactionNone,
	};

struct TThemeInfo
	{
	TAknsPkgID 	iPID;
	TFileName	iName;
//	TInt 		iLoacation;
	TBool		iDeletable;
	};

#endif /* THEMEDEF_H_ */
