/*
 ============================================================================
 Name		: ScrollControl.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CScrollControl implementation
 ============================================================================
 */

#include "ScrollControl.h"
#include "ListBoxPainter.h"
#include "GuiEngine.h"
#include "MacroUtil.h"
#include <COEMAIN.H>
CScrollControl::CScrollControl() :
	iPainter(NULL),iAlpha(0)
	{
	// No implementation required
	}

CScrollControl::~CScrollControl()
	{
	}

CScrollControl* CScrollControl::NewLC()
	{
	CScrollControl* self = new (ELeave) CScrollControl();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CScrollControl* CScrollControl::NewL()
	{
	CScrollControl* self = CScrollControl::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CScrollControl::ConstructL()
	{
	}

TBool CScrollControl::CheckScroll() const
	{
	TInt height = iSize.iHeight;
	if (iTotal <= height)
		return EFalse;

	if (iStart >= iEnd)
		return EFalse;

	return ETrue;
	}
void CScrollControl::Draw(CBitmapContext& gc) const
	{
	TInt height = iSize.iHeight;

	if (!CheckScroll())
		return;
	
	if (!iAlpha)
		return;

	TInt start = iStart * height / iTotal;
	TInt end = iEnd * height / iTotal;

	TPoint 	point = iPosition;
	point.iY += start;
	
	TSize size;
	size.iWidth = iSize.iWidth;
	size.iHeight = end - start;
	
	gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.SetPenColor(KRgbGray);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	TRgb custom = KRgbGray;
	custom.SetAlpha(iAlpha);//设置透明度的
	gc.SetBrushColor(custom );
	gc.DrawRoundRect(TRect(point, size), TSize(size.iWidth / 2,
			size.iWidth / 2));

	}

void CScrollControl::StartAnimationScroll()
	{
	if (!CheckScroll())
		return;

	iItemScrollFrame = 0;
	iAlpha = 255;
	if (iAnimation)
		{
		if (iCallFunc)
			iAnimation->RemoveAnimation(iCallFunc);
		iCallFunc = new TCallBack(CScrollControl::CallbackAnimationScroll, this);
		iAnimation->AppendAnimation(iCallFunc);
		}
	}

TInt CScrollControl::AnimationScroll()
	{
	if (iPainter)
		{
		TInt frame = iPainter->GetAnimationScrollFrame();
		TInt item  = iPainter->GetAnimationScrollStartFadeFrame();
		if (iItemScrollFrame++ < frame)
			{
			if (iItemScrollFrame > item && frame > item)
				{
				iAlpha -= 256/(frame - item);
				if (iAlpha < 0)
					iAlpha = 0;
				}
			}
		else
			{
			iAlpha = 0;
			iAnimation->RemoveAnimation(iCallFunc);
			}

		}
	else
		{
		iAlpha = 0;
		iAnimation->RemoveAnimation(iCallFunc);
		}

	return KErrNone;
	}

TInt CScrollControl::CallbackAnimationScroll(TAny* aThis)
	{
	return static_cast<CScrollControl*> (aThis)->AnimationScroll();
	}
