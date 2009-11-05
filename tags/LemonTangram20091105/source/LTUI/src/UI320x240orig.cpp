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
	return TPoint(0, iScreenHeight-iSysFontHeight-4-iStatusPaneHeight);
	}

TPoint CUI320x240orig::BottomLeftOption()
	{
	return TPoint(0,238-iStatusPaneHeight);
	}

TPoint CUI320x240orig::BottomRightOption()
	{
//	return TPoint(296,238);
	return TPoint(iScreenWidth-iSysFont->WidthZeroInPixels()*4-7,238-iStatusPaneHeight);
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

TSize CUI320x240orig::DrawableSize()
	{
	return TSize(320,219);
	}
