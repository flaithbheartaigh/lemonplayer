/*
 ============================================================================
 Name		: UI320x240.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUI320x240orig implementation
 ============================================================================
 */

#include "UI320x240orig.h"
#include <YCBrowser_bg.mbg>
#include "YCSettingDefine.h"

const TInt KMenuWidth = 83;
const TInt KDLMenuWidth = 127;
const TInt KLeftBottomX = 5;

CUI320x240orig::CUI320x240orig()
	{
	// No implementation required
//	iFont = LatinPlain12();
	iFont = LatinBold16();
	iSysFont = LatinBold16();
	iFontHeight = iFont->HeightInPixels();
	iFontHeightOffset = 0;
	iSysFontHeight = iSysFont->HeightInPixels();
	iScreenWidth = 320;
	iScreenHeight = 240;
	}

CUI320x240orig::~CUI320x240orig()
	{
	}

TPoint CUI320x240orig::BottomBarPos()
	{
	//320-16-1 = 303
	//320-240 = 80
//	return TPoint(0, 223);
	return TPoint(0, iScreenHeight-iSysFontHeight-4);
	}

TPoint CUI320x240orig::BottomLeftOption()
	{
	return TPoint(0,238);
	}

TPoint CUI320x240orig::BottomRightOption()
	{
//	return TPoint(296,238);
	return TPoint(iScreenWidth-iSysFont->WidthZeroInPixels()*4-7,238);
	}

TRect CUI320x240orig::BottomState() 
	{
	TInt top = iScreenHeight-iSysFontHeight-4;
	TInt height = iSysFontHeight+4;
	//	(320-140)/2
	TInt left = 90;
	TInt width = 140;
	return TRect(left,top,left+width,top+height);
//	return TRect(30,223,148,239);
	}

TPoint CUI320x240orig::BottomTextEnd() 
	{
	return TPoint(115,238);
	}

TPoint CUI320x240orig::BottomTextReceive() 
	{
	return TPoint(190,239);
	}

TPoint CUI320x240orig::BottomTextConnect() 
	{
	return TPoint(105,238);
	}

TPoint CUI320x240orig::MainMenuPos()
	{
	//iScreenHeight-40
	TInt height = iScreenHeight-40-(iSysFontHeight<<3)+iSysFontHeight+5;
	return TPoint(0,height); 
//	return TPoint(0,121); 
	}

TSize CUI320x240orig::MainMenuSize() 
	{
	TInt height = (iSysFontHeight+5);
	height *= KMainMenuItemNum;
	return TSize(KMenuWidth,height);
	}

TInt CUI320x240orig::SubMenuWidth()
	{
	return 110;
	}

TInt CUI320x240orig::MainMenuItemHeight()
	{
	return 20;
	}

TPoint CUI320x240orig::BMMenuPos()
	{
	TInt height = iScreenHeight-BMMenuSize().iHeight-BottomBarSize().iHeight;
	return TPoint(0,height); 
	}
TSize CUI320x240orig::BMMenuSize()
	{
	TInt height = (iSysFontHeight+5);
	height *= KBookmarkMenuItemNum;
	return TSize(KMenuWidth,height);
	}
	
TPoint CUI320x240orig::DLMenuPos()
	{
	TInt height = iScreenHeight-DLMenuSize().iHeight-BottomBarSize().iHeight;
	return TPoint(0,height); 
	}
TSize CUI320x240orig::DLMenuSize()
	{
	TInt height = (iSysFontHeight+5);
	height *= KDownloaderMenuItemNum;
	return TSize(KDLMenuWidth,height);
	}
TInt CUI320x240orig::DLSubMenuWidth()
	{
	return 140;
	}

//工具条长度
TSize CUI320x240orig::TitleBarSize()
	{
	return TSize(iScreenWidth,iSysFontHeight+4);
//	return TSize(320,20);
	}
TSize CUI320x240orig::BottomBarSize()
	{
	return TSize(iScreenWidth,iSysFontHeight+4);
//	return TSize(320,20);
	}

TRect CUI320x240orig::TitleIconSize()
	{
	return TRect(TPoint(0,-7),TSize(28,35));
	}

TPoint CUI320x240orig::TitleTextPos()
	{
	return TPoint(33,iSysFontHeight+2);
//	return TPoint(35,14);
	}
TPoint CUI320x240orig::TitleTimePos()
	{
	TInt x = iScreenWidth - 36;
	return TPoint(x,iSysFontHeight+2);
	}
TInt CUI320x240orig::TitleTextPixels()
	{
	return iScreenWidth-80;
	}

TBool CUI320x240orig::ChangeFontSize(const TInt aSize)
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

TSize CUI320x240orig::DownloadItemRest()
	{
	return TSize(iScreenWidth,14+iSysFontHeight);
//	return TSize(iScreenWidth,26);
	}
TSize CUI320x240orig::DownloadItemRun()
	{
	return TSize(iScreenWidth,27+iSysFontHeight);
//	return TSize(iScreenWidth,39);
	}

TRect CUI320x240orig::IMEIconPos()
	{
	TInt x = iScreenWidth - 52;
	return TRect(TPoint(x,4),TSize(48,12));
	//return TPoint(x,y);
	}

TSize CUI320x240orig::DrawableSize()
	{
	return TSize(320,219);
	}
