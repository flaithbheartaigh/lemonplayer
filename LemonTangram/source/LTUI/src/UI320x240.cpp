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

TSize CUI320x240::DrawableSize()
	{
	return TSize(320,219);
	}
