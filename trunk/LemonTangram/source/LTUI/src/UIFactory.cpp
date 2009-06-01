#include "UIFactory.h"
#include "UI240x320.h"
#include "UI320x240.h"
#include "UI320x240orig.h"

#include "MacroUtil.h"
UIFactory::UIFactory()
//:iInstance(NULL)
	{
//	iInstance = NULL;
	}

UIFactory::~UIFactory()
	{
	}

MUIMgr* UIFactory::CreateUIMgr(TUIType aType)
	{
	MUIMgr* ui= NULL;
	switch (aType)
		{
		case EUIType240x320:
			ui = new (ELeave) CUI240x320;
			break;
		case EUIType320x240:
			ui = new (ELeave) CUI320x240;
			break;
		case EUIType320x240orig:
			ui = new (ELeave) CUI320x240orig;
			break;
		default:
			ui = new (ELeave) CUI240x320;
			break;
		}
	return ui;
	}

//MUIMgr* UIFactory::GetInstance()
//	{
//	if (iInstance == NULL)
//		CreateUIMgr();
//	return iInstance;
//	}
//
//void UIFactory::SetType(TUIType aType)
//	{
//	iType = aType;
//	}
//
//void UIFactory::ChangeType(TUIType aType)
//	{
//	SetType(aType);
//	if (iInstance)
//		{
//		delete iInstance;
//		iInstance = NULL;
//		}
//	CreateUIMgr();
//	}
//
//void UIFactory::CreateUIMgr()
//	{
//	switch (iType)
//		{
//		case EUIType240x320:
//			iInstance = new (ELeave) CUI240x320;
//			break;
//		case EUIType320x240:
//			iInstance = new (ELeave) CUI320x240;
//			break;
//		default:
//			break;
//		}
//	}