#ifndef UIMGR_H_
#define UIMGR_H_

#include <e32std.h>
#include <e32base.h>
#include <gdi.h>
#include <AknUtils.h>
enum TUIType
	{
	EUIType176x208 = 0,
	EUIType208x208,
	EUIType240x320,
	EUIType320x240,
	EUIType320x240orig,
	EUIType416x352,
	EUIType352x416
	};

//菜单项目数
const TInt KMainMenuItemNum = 7;
const TInt KBookmarkMenuItemNum = 4;
const TInt KDownloaderMenuItemNum = 6;

class MUIMgr
	{
public:
	
	//bottom bar位置
	virtual TPoint BottomBarPos() = 0;
	
	//bottom bar 左右软件位置
	virtual TPoint BottomLeftOption() = 0;
	virtual TPoint BottomRightOption() = 0;
	
	//工具条长度
	virtual TSize TitleBarSize() = 0;
	virtual TSize BottomBarSize() = 0;
	virtual TRect TitleIconSize() = 0;
	
	//菜单
	virtual TPoint MainMenuPos() = 0;
	virtual TSize MainMenuSize() = 0;
	virtual TInt MainMenuItemHeight() = 0;

	virtual TInt SubMenuWidth() = 0;
	
	//字体
	const CFont* iFont;
	//系统显示字体
	const CFont* iSysFont;
	//修改字体 
	virtual TBool ChangeFontSize(const TInt aSize) = 0;
	TInt GetFontSize(){return iFontSize;};

	TInt GetSysFontHeight(){return iSysFontHeight;};
	
	//绘制区域 
	virtual TSize DrawableSize() = 0;

	//顶部状态栏高度

	void SetStatusPaneHeight(const TInt& aHeight) {iStatusPaneHeight = aHeight;};
protected:
	TInt iFontSize;
	TInt iFontHeight;	
	TInt iSysFontWidth;
	TInt iSysFontHeight;
	TInt iScreenWidth;
	TInt iScreenHeight;

	TInt iMenuItemHeight;
	TInt iBottomBarHeight;
	TInt iStatusPaneHeight;  //状态栏高度
	
	
	};
#endif /*UIMGR_H_*/
