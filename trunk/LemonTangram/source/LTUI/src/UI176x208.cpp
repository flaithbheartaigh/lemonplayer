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

const TInt KSoftStateHeight = 44;

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
	return TPoint(0, 192-KSoftStateHeight);
	}

TPoint CUI176x208::BottomLeftOption()
	{
	return TPoint(2,206-KSoftStateHeight);
	}

TPoint CUI176x208::BottomRightOption()
	{
	return TPoint(150,206-KSoftStateHeight);
	}

TRect CUI176x208::BottomState() 
	{
	return TRect(30,191,148,207);
	}

TPoint CUI176x208::BottomTextEnd() 
	{
	return TPoint(55,205);
	}

TPoint CUI176x208::BottomTextReceive() 
	{
	return TPoint(110,207);
	}

TPoint CUI176x208::BottomTextConnect() 
	{
	return TPoint(45,205);
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

TPoint CUI176x208::BMMenuPos()
	{
	TInt x = 0;
	TInt height = iScreenHeight-BMMenuSize().iHeight-BottomBarSize().iHeight;
	return TPoint(x,height); 
	}
TSize CUI176x208::BMMenuSize()
	{
	TInt height = (iSysFontHeight+5);
	height *= KBookmarkMenuItemNum;
	return TSize(KMenuWidth,height);
	}
	
TPoint CUI176x208::DLMenuPos()
	{
	TInt x = 0;
	TInt height = iScreenHeight-DLMenuSize().iHeight-BottomBarSize().iHeight;
	return TPoint(x,height); 
	}
TSize CUI176x208::DLMenuSize()
	{
	TInt height = (iSysFontHeight+5);
	height *= KDownloaderMenuItemNum;
	return TSize(KDLMenuWidth,height);
	}

TInt CUI176x208::DLSubMenuWidth()
	{
	return 104;
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

TSize CUI176x208::DownloadItemRest()
	{
	return TSize(iScreenWidth,26);
	}
TSize CUI176x208::DownloadItemRun()
	{
	return TSize(iScreenWidth,35);
	}

TRect CUI176x208::IMEIconPos()
	{
	TInt x = iScreenWidth - 52;
	return TRect(TPoint(x,2),TSize(48,12));
	//return TPoint(130,0);
	}

TSize CUI176x208::DrawableSize()
	{
	return TSize(176,208);
	}
