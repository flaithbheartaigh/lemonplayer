/*
 ============================================================================
 Name		: UI176x208.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUI176x208 implementation
 ============================================================================
 */

#include "UI176x208.h"


#include "YCSettingDefine.h"

const TInt KMenuWidth = 73;
const TInt KDLMenuWidth = 100;

//const TInt KSoftStateHeight = 44;

CUI176x208::CUI176x208()
	{
	// No implementation required
	iFont = CEikonEnv::Static()->NormalFont();
	iSysFont = LatinPlain12();
	iFontHeight = iFont->HeightInPixels();
	iSysFontHeight = iSysFont->HeightInPixels();
	iScreenWidth = 176;
	iScreenHeight = 208;
	}

CUI176x208::~CUI176x208()
	{
	}

TPoint CUI176x208::BottomBarPos()
	{
	//320-16-1 = 303
	return TPoint(0, 192-iStatusPaneHeight);
	}

TPoint CUI176x208::BottomLeftOption()
	{
	return TPoint(2,206-iStatusPaneHeight);
	}

TPoint CUI176x208::BottomRightOption()
	{
	return TPoint(150,206-iStatusPaneHeight);
	}

TPoint CUI176x208::MainMenuPos()
	{
	//208-44-20-
	TInt height = 146-MainMenuItemHeight()*KMainMenuItemNum;
	return TPoint(0,height); 
//	return TPoint(0,83);
	}

TSize CUI176x208::MainMenuSize() 
	{
	TInt height = (iSysFontHeight+5);
	height *= KMainMenuItemNum;
	return TSize(KMenuWidth,height);
	}

TInt CUI176x208::SubMenuWidth()
	{
	return 80;
	}

TInt CUI176x208::MainMenuItemHeight()
	{
	return 20;
	}

//工具条长度
TSize CUI176x208::TitleBarSize()
	{
	return TSize(176,16);
	}
TSize CUI176x208::BottomBarSize()
	{
	return TSize(176,16);
	}

TRect CUI176x208::TitleIconSize()
	{
	return TRect(TPoint(0,-7),TSize(25,32));
	}

TPoint CUI176x208::TitleTextPos()
	{
	return TPoint(40,14);
	}
TPoint CUI176x208::TitleTimePos()
	{
	return TPoint(147,14);
	}
TInt CUI176x208::TitleTextPixels()
	{
	return 100;
	}

TBool CUI176x208::ChangeFontSize(const TInt aSize)
	{
	if (aSize == iFontSize)
		return EFalse;
	
	iFontSize = aSize;
	switch(aSize)
		{
		case KFontSizeSmall:
			iFont = LatinPlain12();;
			break;
		case KFontSizeMiddle:
			iFont = CEikonEnv::Static()->NormalFont();
			break;
		case KFontSizeBig:
			iFont = CEikonEnv::Static()->TitleFont();
			break;
		}
	iFontHeight = iFont->HeightInPixels();
	return ETrue;
	}

TSize CUI176x208::DrawableSize()
	{
	TInt height = iScreenHeight - iStatusPaneHeight - 16;  //-状态栏 -菜单栏
	return TSize(iScreenWidth,height);
	}
