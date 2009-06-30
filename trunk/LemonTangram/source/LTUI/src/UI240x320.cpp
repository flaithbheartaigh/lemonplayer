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
	iFontHeightOffset = 0;
	iSysFontHeight = iSysFont->HeightInPixels();
	iScreenWidth = 240;
	iScreenHeight = 320;
	}

CUI240x320::~CUI240x320()
	{
	}

TPoint CUI240x320::BottomBarPos()
	{
	//320-字体-4-1 = 303
	return TPoint(0, iScreenHeight-iSysFontHeight-4 - iStatusPaneHeight);
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

TRect CUI240x320::BottomState() 
	{
	//(30,303
	TInt top = iScreenHeight-iSysFontHeight-4;
	TInt height = iSysFontHeight+4;
//	(240-118)/2
	TInt left = 50;
	TInt width = 140;
	return TRect(left,top,left+width,top+height);
	}

TPoint CUI240x320::BottomTextEnd() 
	{
	TInt width = 25;
	return TPoint(75,318);
	}

TPoint CUI240x320::BottomTextReceive() 
	{
	return TPoint(150,319);
	}

TPoint CUI240x320::BottomTextConnect() 
	{
	return TPoint(65,318);
	}

TPoint CUI240x320::MainMenuPos()
	{
	TInt height = 251-MainMenuItemHeight()*KMainMenuItemNum ;
	return TPoint(0,height); 
	}

TSize CUI240x320::MainMenuSize() 
	{
	//180 102 = 78
	TInt height = (iSysFontHeight+5);
	height *= KMainMenuItemNum;
	return TSize(KMenuWidth,height);
//	return TSize(63,147);
	}

TInt CUI240x320::SubMenuWidth()
	{
	return 110;
	}

TInt CUI240x320::MainMenuItemHeight()
	{
	return 20;
	}

TPoint CUI240x320::BMMenuPos()
	{
	TInt x = 0;
	TInt height = iScreenHeight-BMMenuSize().iHeight-BottomBarSize().iHeight;
	return TPoint(x,height); 
	}
TSize CUI240x320::BMMenuSize()
	{
	TInt height = (iSysFontHeight+5);
	height *= KBookmarkMenuItemNum;
	return TSize(KMenuWidth,height);
	}
	
TPoint CUI240x320::DLMenuPos()
	{
	TInt x = 0;
	TInt height = iScreenHeight-DLMenuSize().iHeight-BottomBarSize().iHeight;
	return TPoint(x,height); 
	}
TSize CUI240x320::DLMenuSize()
	{
	TInt height = (iSysFontHeight+5);
	height *= KDownloaderMenuItemNum;
	return TSize(KDLMenuWidth,height);
	}
TInt CUI240x320::DLSubMenuWidth()
	{
	return 140;
	}

//工具条长度
TSize CUI240x320::TitleBarSize()
	{
	return TSize(iScreenWidth,iSysFontHeight+4);
//	return TSize(240,20);
	}
TSize CUI240x320::BottomBarSize()
	{
	return TSize(iScreenWidth,iSysFontHeight+4);
//	return TSize(240,20);
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
			iFontHeightOffset = 0;
			break;
		case KFontSizeMiddle:
			iFont = LatinBold16();
			iFontHeightOffset = 0;
			break;
		case KFontSizeBig:
			iFont = CEikonEnv::Static()->NormalFont();
			iFontHeightOffset = 1;
			break;
		}
	iFontHeight = iFont->HeightInPixels();
	return ETrue;
	}

TSize CUI240x320::DownloadItemRest()
	{
	return TSize(iScreenWidth,14+iSysFontHeight);
	}
TSize CUI240x320::DownloadItemRun()
	{
	return TSize(iScreenWidth,27+iSysFontHeight);
	}

TRect CUI240x320::IMEIconPos()
	{
	TInt x = iScreenWidth - 52;
	return TRect(TPoint(x,4),TSize(48,12));
	//return TPoint(x,4);
	}

TSize CUI240x320::DrawableSize()
	{
	return TSize(240,293);
	}
