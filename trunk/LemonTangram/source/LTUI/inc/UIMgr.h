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
	
	//bottom 状态条位置
	virtual TRect BottomState() = 0;
	//bottom 文字
	virtual TPoint BottomTextEnd() = 0;
	virtual TPoint BottomTextReceive() = 0;
	virtual TPoint BottomTextConnect() = 0;
	
	//工具条长度
	virtual TSize TitleBarSize() = 0;
	virtual TSize BottomBarSize() = 0;
	virtual TRect TitleIconSize() = 0;
	//工具条文字
	virtual TPoint TitleTextPos() = 0;
	virtual TPoint TitleTimePos() = 0;
	virtual TInt   TitleTextPixels() = 0;
	
	//菜单起始位置
	virtual TPoint MainMenuPos() = 0;
	virtual TSize MainMenuSize() = 0;
	
	virtual TInt SubMenuWidth() = 0;
	virtual TInt MainMenuItemHeight() = 0;
	
	//书签管理器菜单
	virtual TPoint BMMenuPos() = 0;
	virtual TSize BMMenuSize() = 0;
	
	//下载管理器菜单
	virtual TPoint DLMenuPos() = 0;
	virtual TSize DLMenuSize() = 0;
	virtual TInt DLSubMenuWidth() = 0;
	
	//字体
	const CFont* iFont;
	//系统显示字体
	const CFont* iSysFont;
	//修改字体 
	virtual TBool ChangeFontSize(const TInt aSize) = 0;
	TInt GetFontSize(){return iFontSize;};
	TInt GetFontHeightOffset(){return iFontHeightOffset;};
	TInt GetSysFontHeight(){return iSysFontHeight;};
	
	//下载管理器
	virtual TSize DownloadItemRest() = 0;
	virtual TSize DownloadItemRun() = 0;
	
	//输入法位置
	virtual TRect IMEIconPos() = 0;
	
	//绘制区域 用于下载管理器的重绘.
	virtual TSize DrawableSize() = 0;
protected:
	TInt iFontSize;
	TInt iFontHeight;	
	TInt iFontHeightOffset; //大字体时候,行间距需要加大
	TInt iSysFontWidth;
	TInt iSysFontHeight;
	TInt iScreenWidth;
	TInt iScreenHeight;
	
	
	};
#endif /*UIMGR_H_*/
