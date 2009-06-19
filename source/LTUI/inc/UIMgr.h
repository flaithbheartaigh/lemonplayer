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
	
	//bottom ״̬��λ��
	virtual TRect BottomState() = 0;
	//bottom ����
	virtual TPoint BottomTextEnd() = 0;
	virtual TPoint BottomTextReceive() = 0;
	virtual TPoint BottomTextConnect() = 0;
	
	//����������
	virtual TSize TitleBarSize() = 0;
	virtual TSize BottomBarSize() = 0;
	virtual TRect TitleIconSize() = 0;
	//����������
	virtual TPoint TitleTextPos() = 0;
	virtual TPoint TitleTimePos() = 0;
	virtual TInt   TitleTextPixels() = 0;
	
	//�˵���ʼλ��
	virtual TPoint MainMenuPos() = 0;
	virtual TSize MainMenuSize() = 0;
	
	virtual TInt SubMenuWidth() = 0;
	virtual TInt MainMenuItemHeight() = 0;
	
	//��ǩ�������˵�
	virtual TPoint BMMenuPos() = 0;
	virtual TSize BMMenuSize() = 0;
	
	//���ع������˵�
	virtual TPoint DLMenuPos() = 0;
	virtual TSize DLMenuSize() = 0;
	virtual TInt DLSubMenuWidth() = 0;
	
	//����
	const CFont* iFont;
	//ϵͳ��ʾ����
	const CFont* iSysFont;
	//�޸����� 
	virtual TBool ChangeFontSize(const TInt aSize) = 0;
	TInt GetFontSize(){return iFontSize;};
	TInt GetFontHeightOffset(){return iFontHeightOffset;};
	TInt GetSysFontHeight(){return iSysFontHeight;};
	
	//���ع�����
	virtual TSize DownloadItemRest() = 0;
	virtual TSize DownloadItemRun() = 0;
	
	//���뷨λ��
	virtual TRect IMEIconPos() = 0;
	
	//�������� �������ع��������ػ�.
	virtual TSize DrawableSize() = 0;
protected:
	TInt iFontSize;
	TInt iFontHeight;	
	TInt iFontHeightOffset; //������ʱ��,�м����Ҫ�Ӵ�
	TInt iSysFontWidth;
	TInt iSysFontHeight;
	TInt iScreenWidth;
	TInt iScreenHeight;
	
	
	};
#endif /*UIMGR_H_*/
