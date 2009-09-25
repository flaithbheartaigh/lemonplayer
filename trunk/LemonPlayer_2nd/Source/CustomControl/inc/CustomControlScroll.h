/*
 ============================================================================
 Name		: CustomControlScroll.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCustomControlScroll declaration
 ============================================================================
 */

#ifndef CUSTOMCONTROLSCROLL_H
#define CUSTOMCONTROLSCROLL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <w32std.h>

// CLASS DECLARATION

/**
 *  CCustomControlScroll
 * 
 */
_LIT ( KMultiBitmapFilename,"\\system\\apps\\customcontrol\\customcontrol.mbm" );
class CCustomControlScroll : public CBase
	{
public:
	enum EScrollDirection
		{
		KScrollUp,
		KScrollDown
		};
	// Constructors and destructor

	~CCustomControlScroll();
	static CCustomControlScroll* NewL();
	static CCustomControlScroll* NewLC();

private:
	CCustomControlScroll();
	void ConstructL();

public:
	//读取资源
	void LoadL();
	//初始化数据
	void InitData(TPoint aDisplayPoint, TSize aDisplaySize, TSize aOriginalSize);
	//绘制
	void Draw(CWindowGc& gc);
	//移动
	void Update(EScrollDirection aDirection,TInt aPixel);

private:
	//上下方向图片
	CFbsBitmap* iBitmapDirection[2];
	//滚动条图片
	CFbsBitmap* iBitmapScroller;

	TPoint iDisplayPoint;
	TSize iDisplaySize;

	TInt iScrollerPosY;
	TReal iOffset;
	
	TInt iBitmapWidth;
	TInt iBitmapHeight;
	};

#endif // CUSTOMCONTROLSCROLL_H
