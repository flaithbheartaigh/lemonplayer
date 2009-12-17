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

//�˵���Ŀ��
const TInt KMainMenuItemNum = 7;
const TInt KBookmarkMenuItemNum = 4;
const TInt KDownloaderMenuItemNum = 6;

class MUIMgr
	{
public:
	
	//bottom barλ��
	virtual TPoint BottomBarPos() = 0;
	
	//bottom bar �������λ��
	virtual TPoint BottomLeftOption() = 0;
	virtual TPoint BottomRightOption() = 0;
	
	//����������
	virtual TSize TitleBarSize() = 0;
	virtual TSize BottomBarSize() = 0;
	virtual TRect TitleIconSize() = 0;
	
	//�˵�
	virtual TPoint MainMenuPos() = 0;
	virtual TSize MainMenuSize() = 0;
	virtual TInt MainMenuItemHeight() = 0;

	virtual TInt SubMenuWidth() = 0;
	
	//����
	const CFont* iFont;
	//ϵͳ��ʾ����
	const CFont* iSysFont;
	//�޸����� 
	virtual TBool ChangeFontSize(const TInt aSize) = 0;
	TInt GetFontSize(){return iFontSize;};

	TInt GetSysFontHeight(){return iSysFontHeight;};
	
	//�������� 
	virtual TSize DrawableSize() = 0;

	//����״̬���߶�

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
	TInt iStatusPaneHeight;  //״̬���߶�
	
	
	};
#endif /*UIMGR_H_*/
