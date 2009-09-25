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
	//��ȡ��Դ
	void LoadL();
	//��ʼ������
	void InitData(TPoint aDisplayPoint, TSize aDisplaySize, TSize aOriginalSize);
	//����
	void Draw(CWindowGc& gc);
	//�ƶ�
	void Update(EScrollDirection aDirection,TInt aPixel);

private:
	//���·���ͼƬ
	CFbsBitmap* iBitmapDirection[2];
	//������ͼƬ
	CFbsBitmap* iBitmapScroller;

	TPoint iDisplayPoint;
	TSize iDisplaySize;

	TInt iScrollerPosY;
	TReal iOffset;
	
	TInt iBitmapWidth;
	TInt iBitmapHeight;
	};

#endif // CUSTOMCONTROLSCROLL_H
