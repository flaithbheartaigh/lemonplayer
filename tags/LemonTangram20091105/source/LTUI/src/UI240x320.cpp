/*
 ============================================================================
 Name		: UI240x320.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUI240x320 implementation
 ============================================================================
 */

#include "UI240x320.h"
#include "YCSettingDefine.h"

const TInt KMenuWidth = 86;
const TInt KDLMenuWidth = 138;

//const TInt KSoftStateHeight = 48;

CUI240x320::CUI240x320()
	{
	// No implementation required
	iFont = LatinBold16();
	iSysFont = LatinBold16();
	iFontHeight = iFont->HeightInPixels();
	iSysFontHeight = iSysFont->HeightInPixels();
	iScreenWidth = 240;
	iScreenHeight = 320;
	iBottomBarHeight = iSysFontHeight+4;
	iMenuItemHeight = iSysFontHeight+5;
	}

CUI240x320::~CUI240x320()
	{
	}

TPoint CUI240x320::BottomBarPos()
	{
	//320-字体-4-1 = 303
	return TPoint(0, iScreenHeight- iBottomBarHeight - iStatusPaneHeight);
//	return TPoint(0, 300);
	}

TPoint CUI240x320::BottomLeftOption()
	{
	return TPoint(2,318 - iStatusPaneHeight);
	}

TPoint CUI240x320::BottomRightOption()
	{
	//320-240 = 80   216
	return TPoint(iScreenWidth-iSysFont->WidthZeroInPixels()*4-6,318 - iStatusPaneHeight);
//	return TPoint(204,318);
	}

TPoint CUI240x320::MainMenuPos()
	{
	TInt height = iScreenHeight- iBottomBarHeight - iStatusPaneHeight-iMenuItemHeight*KMainMenuItemNum ;
	return TPoint(0,height); 
	}

TSize CUI240x320::MainMenuSize() 
	{
	//180 102 = 78
	TInt height = iMenuItemHeight*KMainMenuItemNum;
	return TSize(KMenuWidth,height);
	}

TInt CUI240x320::SubMenuWidth()
	{
	return 110;
	}

TInt CUI240x320::MainMenuItemHeight()
	{
	return iMenuItemHeight;
	}

//工具条长度
TSize CUI240x320::TitleBarSize()
	{
	return TSize(iScreenWidth,iSysFontHeight+4);
	}

TSize CUI240x320::BottomBarSize()
	{
	return TSize(iScreenWidth,iSysFontHeight+4);
	}

TRect CUI240x320::TitleIconSize()
	{
	return TRect(TPoint(0,-7),TSize(28,35));
	}

TPoint CUI240x320::TitleTextPos()
	{
	return TPoint(30,iSysFontHeight+2);
	}

TPoint CUI240x320::TitleTimePos()
	{
	//240-7*5
	TInt x = iScreenWidth - 36;
	return TPoint(x,iSysFontHeight+2);
	}
TInt CUI240x320::TitleTextPixels()
	{
	return iScreenWidth-80;
	}


TBool CUI240x320::ChangeFontSize(const TInt aSize)
	{
	if (aSize == iFontSize)
		return EFalse;
	
	iFontSize = aSize;
	switch(aSize)
		{
		case KFontSizeSmall:
			iFont = LatinPlain12();
			break;
		case KFontSizeMiddle:
			iFont = LatinBold16();
			break;
		case KFontSizeBig:
			iFont = CEikonEnv::Static()->NormalFont();
			break;
		}
	iFontHeight = iFont->HeightInPixels();
	return ETrue;
	}

TSize CUI240x320::DrawableSize()
	{
	TInt height = iScreenHeight - iStatusPaneHeight - iBottomBarHeight;  //-状态栏 -菜单栏
	return TSize(iScreenWidth,height);
	}
