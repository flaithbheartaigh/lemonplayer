#ifndef UIFACOTRY_H_
#define UIFACOTRY_H_

#include "UIMgr.h"

class UIFactory
	{
public:
	UIFactory();
	~UIFactory();
	
public:
	static MUIMgr* CreateUIMgr(TUIType aType);
	
	};
#endif /*UIFACOTRY_H_*/
