/*
 ============================================================================
 Name		: CustomControlScroll.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCustomControlScroll implementation
 ============================================================================
 */

#include "CustomControlScroll.h"
#include <aknutils.h>
#include <CCScroll.mbg>

CCustomControlScroll::CCustomControlScroll()
	{
	// No implementation required
	}

CCustomControlScroll::~CCustomControlScroll()
	{
	delete iBitmapDirection[0];
	delete iBitmapDirection[1];
	delete iBitmapScroller;
	}

CCustomControlScroll* CCustomControlScroll::NewLC()
	{
	CCustomControlScroll* self = new (ELeave)CCustomControlScroll();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CCustomControlScroll* CCustomControlScroll::NewL()
	{
	CCustomControlScroll* self=CCustomControlScroll::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CCustomControlScroll::ConstructL()
	{
	LoadL();
	}

void CCustomControlScroll::LoadL()
	{
	TFileName file(KMultiBitmapFilename);
	User::LeaveIfError(CompleteWithAppPath(file));
		
	iBitmapDirection[0] = new (ELeave)CFbsBitmap;
	iBitmapDirection[0]->Load(file, EMbmCcscrollScrollup);
	iBitmapDirection[1] = new (ELeave)CFbsBitmap;
	iBitmapDirection[1]->Load(file, EMbmCcscrollScrolldown);
	iBitmapScroller = new (ELeave)CFbsBitmap;
	iBitmapScroller->Load(file, EMbmCcscrollScroller);

	iBitmapWidth = iBitmapScroller->SizeInPixels().iWidth;
	iBitmapHeight = iBitmapScroller->SizeInPixels().iHeight;
	}

//初始化数据
void CCustomControlScroll::InitData(TPoint aDisplayPoint, TSize aDisplaySize,
		TSize aOriginalSize)
	{
	iDisplayPoint = aDisplayPoint;
	iDisplaySize = aDisplaySize;

	iOffset = ((TReal)iDisplaySize.iHeight)/ ((TReal)aOriginalSize.iHeight);
	iScrollerPosY = iBitmapHeight;
	}

void CCustomControlScroll::Draw(CWindowGc& gc)
	{
	TInt x, y;
	//上图标
	x = iDisplayPoint.iX;
	y = iDisplayPoint.iY;
	if (iBitmapDirection[0])
		gc.BitBlt(TPoint(x, y), iBitmapDirection[0]);
	//下图标
	y += iDisplaySize.iHeight-iBitmapHeight;
	if (iBitmapDirection[1])
		gc.BitBlt(TPoint(x, y), iBitmapDirection[1]);
	//滚动条
	y = iDisplayPoint.iY+iScrollerPosY;
	if (iBitmapScroller)
		gc.BitBlt(TPoint(x, y), iBitmapScroller);
	}

void CCustomControlScroll::Update(EScrollDirection aDirection, TInt aPixel)
	{
	if (aDirection == KScrollUp)
		{
		iScrollerPosY -= iOffset*aPixel;
		if (iScrollerPosY < iBitmapHeight)
			{
			iScrollerPosY = iBitmapHeight;
			}
		}
	else
		if (aDirection == KScrollDown)
			{
			iScrollerPosY += iOffset*aPixel;
			if (iScrollerPosY > iDisplaySize.iHeight-iBitmapHeight*2)
				{
				iScrollerPosY = iDisplaySize.iHeight-iBitmapHeight*2;
				}
			}
	}
