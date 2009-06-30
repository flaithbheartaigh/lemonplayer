/*
 ============================================================================
 Name		: UI320x240.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUI320x240 implementation
 ============================================================================
 */

#include "UI320x240.h"
#include "YCSettingDefine.h"

const TInt KMenuWidth = 86;
const TInt KDLMenuWidth = 127;
const TInt KLeftBottomX = 5;

CUI320x240::CUI320x240()
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

CUI320x240::~CUI320x240()
	{
	}

TPoint CUI320x240::BottomBarPos()
	{
	//320-16-1 = 303
	//320-240 = 80
//	return TPoint(0, 223);
	return TPoint(0, iScreenHeight-iSysFontHeight-4-iStatusPaneHeight);
	}

TPoint CUI320x240::BottomLeftOption()
	{
	return TPoint(iScreenWidth-iSysFont->WidthZeroInPixels()*4-7,238-iStatusPaneHeight);
	}

TPoint CUI320x240::BottomRightOption()
	{
//	return TPoint(296,238);
	return TPoint(iScreenWidth-iSysFont->WidthZeroInPixels()*4-7,iSysFontHeight+1-iStatusPaneHeight);
	}

TRect CUI320x240::BottomState() 
	{
	TInt top = iScreenHeight-iSysFontHeight-4;
	TInt height = iSysFontHeight+4;
	//	(320-140)/2
	TInt left = 90;
	TInt width = 140;
	return TRect(left,top,left+width,top+height);
//	return TRect(30,223,148,239);
	}

TPoint CUI320x240::BottomTextEnd() 
	{
	return TPoint(115,238);
	}

TPoint CUI320x240::BottomTextReceive() 
	{
	return TPoint(190,239);
	}

TPoint CUI320x240::BottomTextConnect() 
	{
	return TPoint(105,238);
	}

TPoint CUI320x240::MainMenuPos()
	{
	//iScreenHeight-40
	TInt x = iScreenWidth-KMenuWidth-1;
	TInt height = iScreenHeight-40-(iSysFontHeight<<3)+iSysFontHeight+5;
	return TPoint(x,height); 
//	return TPoint(0,121); 
	}

TSize CUI320x240::MainMenuSize() 
	{
	TInt height = (iSysFontHeight+5);
	height *= KMainMenuItemNum;
	return TSize(KMenuWidth,height);
	}

TInt CUI320x240::SubMenuWidth()
	{
	return 110;
	}

TInt CUI320x240::MainMenuItemHeight()
	{
	return 20;
	}

TPoint CUI320x240::BMMenuPos()
	{
	TInt x = iScreenWidth-KDLMenuWidth-1;
	TInt height = iScreenHeight-BMMenuSize().iHeight-BottomBarSize().iHeight;
	return TPoint(x,height); 
	}
TSize CUI320x240::BMMenuSize()
	{
	TInt height = (iSysFontHeight+5);
	height *= KBookmarkMenuItemNum;
	return TSize(KDLMenuWidth,height);
	}
	
TPoint CUI320x240::DLMenuPos()
	{
	TInt x = iScreenWidth-KDLMenuWidth-1;
	TInt height = iScreenHeight-DLMenuSize().iHeight-BottomBarSize().iHeight;
	return TPoint(x,height); 
	}
TSize CUI320x240::DLMenuSize()
	{
	TInt height = (iSysFontHeight+5);
	height *= KDownloaderMenuItemNum;
	return TSize(KDLMenuWidth,height);
	}
TInt CUI320x240::DLSubMenuWidth()
	{
	return 140;
	}

//工具条长度
TSize CUI320x240::TitleBarSize()
	{
	return TSize(iScreenWidth,iSysFontHeight+4);
//	return TSize(320,20);
	}
TSize CUI320x240::BottomBarSize()
	{
	return TSize(iScreenWidth,iSysFontHeight+4);
//	return TSize(320,20);
	}

TRect CUI320x240::TitleIconSize()
	{
	return TRect(TPoint(0,-7),TSize(28,35));
	}

TPoint CUI320x240::TitleTextPos()
	{
	return TPoint(30,iSysFontHeight+2);
//	return TPoint(35,14);
	}
TPoint CUI320x240::TitleTimePos()
	{
	TInt x = KLeftBottomX;
	TInt y = iScreenHeight - 1 ;
	return TPoint(x,y);
	}
TInt CUI320x240::TitleTextPixels()
	{
	return iScreenWidth-80;
	}

TBool CUI320x240::ChangeFontSize(const TInt aSize)
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

TSize CUI320x240::DownloadItemRest()
	{
	return TSize(iScreenWidth,14+iSysFontHeight);
//	return TSize(iScreenWidth,26);
	}
TSize CUI320x240::DownloadItemRun()
	{
	return TSize(iScreenWidth,27+iSysFontHeight);
//	return TSize(iScreenWidth,39);
	}

TRect CUI320x240::IMEIconPos()
	{
	TInt x = KLeftBottomX;
	TInt y = iScreenHeight - 16 ;
	return TRect(TPoint(x,y),TSize(48,12));
	//return TPoint(x,y);
	}

TSize CUI320x240::DrawableSize()
	{
	return TSize(320,219);
	}
