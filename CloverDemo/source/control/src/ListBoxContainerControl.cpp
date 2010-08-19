/*
 ============================================================================
 Name		: ListBoxContainerControl.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxContainerControl implementation
 ============================================================================
 */

#include "ListBoxContainerControl.h"

#include "ListBoxItemControl.h"
#include "ListBoxHighLightControl.h"
#include "ListBoxPainter.h"
#include "ScrollControl.h"

#include "MacroUtil.h"

CListBoxContainerControl::CListBoxContainerControl() :
	iItems(NULL),iHighLight(NULL),iPainter(NULL),iSelectedIndex(0),
			iEnableRing(EFalse), iScroll(NULL),iCallFunc(NULL),iResizeOffset(0)
	{
	// No implementation required
	}

CListBoxContainerControl::~CListBoxContainerControl()
	{
		SAFE_DELETE(iScroll)
		SAFE_DELETE(iPainter)
		SAFE_DELETE(iHighLight)
		SAFE_DELETE_RPONTERARRAY(iItems)
	}

CListBoxContainerControl* CListBoxContainerControl::NewLC()
	{
	CListBoxContainerControl* self = new (ELeave) CListBoxContainerControl();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CListBoxContainerControl* CListBoxContainerControl::NewL()
	{
	CListBoxContainerControl* self = CListBoxContainerControl::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CListBoxContainerControl::ConstructL()
	{
	iItems = new (ELeave) RPointerArray<CListBoxItemControl> ;
	iHighLight = CListBoxHighLightControl::NewL();

	iPainter = CListBoxPainter::NewL();
	iHighLight->SetPainter(iPainter);

	iScroll = CScrollControl::NewL();
	iScroll->SetPainter(iPainter);
	}

void CListBoxContainerControl::Draw(CBitmapContext& gc) const
	{
	if (iHighLight)
		iHighLight->Draw(gc);

	TPoint point = iActualPoint;
	TSize size;
	if (iPainter)
		{
		if (iResizeOffset)
			size.iWidth = iOldSize.iWidth + iResizeOffset;
		else
			size.iWidth = iSize.iWidth;
		size.iHeight = iPainter->GetItemHeight();
		}
	if (iItems)
		{
		for (TInt i = 0; i < iItems->Count(); i++)
			{
			CListBoxItemControl* item = (*iItems)[i];
			
			if (point.iY + size.iHeight > iPosition.iY)
				{
				item->SetRect(TRect(point, size));
				item->Draw(gc);
				}

			point.iY += iPainter->GetItemHeight();

			if (point.iY > iPosition.iY + iSize.iHeight)
				break;
			}
		}

	if (iScroll)
		{
		iScroll->SetPosition(iActualSize.iHeight, -iActualPoint.iY,
				-iActualPoint.iY + Rect().Height());
		iScroll->Draw(gc);
		}
	}

TKeyResponse CListBoxContainerControl::OfferKeyEventL(
		const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	TInt old = iSelectedIndex;
	if (aType == EEventKey)
		{
		switch (aKeyEvent.iCode)
			{
			case EKeyDownArrow:
				if (!iCallFunc)
					{
					if (iItems && iItems->Count())
						{
						if (iEnableRing)
							{
							if (++iSelectedIndex >= iItems->Count())
								{
								iSelectedIndex = 0;
								}
							}
						else
							{
							if (iSelectedIndex < iItems->Count() - 1)
								{
								iSelectedIndex++;
								}
							}
						if (old != iSelectedIndex)
							{
							CListBoxItemControl* item = (*iItems)[old];
							item->StopAnimationMarquee();
							CListBoxItemControl* item2 =
									(*iItems)[iSelectedIndex];
							item2->StartAnimationMarquee();
							StartAnimationScrollDown();
							}
						return EKeyWasConsumed;
						}
					}
				break;
			case EKeyUpArrow:
				if (!iCallFunc)
					{
					if (iItems && iItems->Count())
						{
						if (iEnableRing)
							{
							if (--iSelectedIndex < 0)
								iSelectedIndex = iItems->Count() - 1;
							}
						else
							{
							if (iSelectedIndex > 0)
								{
								iSelectedIndex--;
								}
							}
						if (old != iSelectedIndex)
							{
							CListBoxItemControl* item = (*iItems)[old];
							item->StopAnimationMarquee();
							CListBoxItemControl* item2 =
									(*iItems)[iSelectedIndex];
							item2->StartAnimationMarquee();
							StartAnimationScrollUp();
							}
						return EKeyWasConsumed;
						}
					}
				break;
			default:
				break;
			}
		}
	return EKeyWasNotConsumed;
	}

void CListBoxContainerControl::SetRect(const TRect &aRect)
	{
	CBaseControl::SetRect(aRect);

	iActualPoint = aRect.iTl;
	iActualSize = TSize(aRect.Width(), 0);

	if (iPainter)
		iPainter->SetWidth(aRect.Width());

	iHighLight->SetRect(TRect(aRect.iTl, TSize(aRect.Width(),
			iPainter->GetItemHeight())));

	if (iScroll)
		iScroll->SetRect(TRect(TPoint(aRect.iBr.iX - iPainter->GetScrollWidth()
				- 2, aRect.iTl.iY), TSize(iPainter->GetScrollWidth(),
				aRect.Height())));
	}

void CListBoxContainerControl::ReSize(const TRect &aRect)
	{
	iOldSize.iWidth = iSize.iWidth;

	SetRect(aRect);

	StartAnimationResize();
	}

void CListBoxContainerControl::SetAnimation(CAnimationFrame* aAnimation)
	{
	CBaseControl::SetAnimation(aAnimation);

	if (iScroll)
		iScroll->SetAnimation(aAnimation);
	}

void CListBoxContainerControl::AddItem(CListBoxItemControl* aItem)
	{
	if (iItems)
		{
		if (iPainter)
			{
			aItem->SetPainter(iPainter);
			iActualSize.iHeight += iPainter->GetItemHeight();
			}
		if (iAnimation)
			aItem->SetAnimation(iAnimation);

		iItems->Append(aItem);
		}
	}

void CListBoxContainerControl::StartAnimationScrollDown()
	{
	iItemScrollFrame = 0;
	if (iAnimation)
		{
		//		if (iCallFunc)
		//			iAnimation->RemoveAnimation(iCallFunc);
		iCallFunc = new TCallBack(
				CListBoxContainerControl::CallbackAnimationScrollDown, this);
		iAnimation->AppendAnimation(iCallFunc);
		}

	iScroll->SetPosition(iActualSize.iHeight, -iActualPoint.iY,
			-iActualPoint.iY + Rect().Height());
	iScroll->StartAnimationScroll();
	}

TInt CListBoxContainerControl::AnimationScrollDown()
	{
	if (iPainter)
		{
		TInt frame = iPainter->GetAnimationItemScrollFrame();
		if (iItemScrollFrame++ < iPainter->GetAnimationItemScrollFrame())
			{
			TRect rect = iHighLight->Rect();
			TInt f = iPainter->GetItemHeight() / frame;

			if (rect.iBr.iY + f <= Rect().iBr.iY)
				{
				//高亮条动
				rect.Move(0, f);
				iHighLight->SetRect(rect);
				}
			else if (rect.iBr.iY == Rect().iBr.iY)
				{
				//文字移动
				iActualPoint.iY -= f;

				//iScroll->SetPosition(iActualSize.iHeight,-iActualPoint.iY,-iActualPoint.iY + Rect().Height());
				}
			else
				{
				//高亮条移动部分 文字移动部分
				TInt offset = Rect().iBr.iY - rect.iBr.iY;
				rect.Move(0, offset);
				iHighLight->SetRect(rect);

				offset = f - offset;
				iActualPoint.iY -= offset;

				//iScroll->SetPosition(iActualSize.iHeight,-iActualPoint.iY,-iActualPoint.iY + Rect().Height());
				}
			}
		else
			//iAnimation->RemoveAnimation(iCallFunc);
			StopAnimation();

		}
	else
		//iAnimation->RemoveAnimation(iCallFunc);
		StopAnimation();

	return KErrNone;
	}

TInt CListBoxContainerControl::CallbackAnimationScrollDown(TAny* aThis)
	{
	return static_cast<CListBoxContainerControl*> (aThis)->AnimationScrollDown();
	}

void CListBoxContainerControl::StartAnimationScrollUp()
	{
	iItemScrollFrame = 0;
	if (iAnimation)
		{
		//		if (iCallFunc)
		//			iAnimation->RemoveAnimation(iCallFunc);
		iCallFunc = new TCallBack(
				CListBoxContainerControl::CallbackAnimationScrollUp, this);
		iAnimation->AppendAnimation(iCallFunc);
		}

	iScroll->SetPosition(iActualSize.iHeight, -iActualPoint.iY,
			-iActualPoint.iY + Rect().Height());
	iScroll->StartAnimationScroll();
	}

TInt CListBoxContainerControl::AnimationScrollUp()
	{
	if (iPainter)
		{
		TInt frame = iPainter->GetAnimationItemScrollFrame();
		if (iItemScrollFrame++ < iPainter->GetAnimationItemScrollFrame())
			{
			TRect rect = iHighLight->Rect();
			TInt f = iPainter->GetItemHeight() / frame;

			if (rect.iTl.iY - f >= 0)
				{
				//高亮条动
				rect.Move(0, -f);
				iHighLight->SetRect(rect);
				}
			else if (rect.iTl.iY == 0)
				{
				//文字移动
				iActualPoint.iY += f;

				//iScroll->SetPosition(iActualSize.iHeight,-iActualPoint.iY,-iActualPoint.iY + Rect().Height());
				}
			else
				{
				//高亮条移动部分 文字移动部分
				TInt offset = rect.iTl.iY - Rect().iTl.iY;
				rect.Move(0, -offset);
				iHighLight->SetRect(rect);

				offset = f - offset;
				iActualPoint.iY += offset;

				//iScroll->SetPosition(iActualSize.iHeight,-iActualPoint.iY,-iActualPoint.iY + Rect().Height());
				}
			}
		else
			//iAnimation->RemoveAnimation(iCallFunc);
			StopAnimation();

		}
	else
		//iAnimation->RemoveAnimation(iCallFunc);
		StopAnimation();

	return KErrNone;
	}

TInt CListBoxContainerControl::CallbackAnimationScrollUp(TAny* aThis)
	{
	return static_cast<CListBoxContainerControl*> (aThis)->AnimationScrollUp();
	}

void CListBoxContainerControl::StartAnimationResize()
	{
	iResizeOffset = 0;
	if (iAnimation)
		{
		if (iCallFunc)
			iAnimation->RemoveAnimation(iCallFunc);
		iCallFunc = new TCallBack(
				CListBoxContainerControl::CallbackAnimationResize, this);
		iAnimation->AppendAnimation(iCallFunc);
		}
	}

TInt CListBoxContainerControl::AnimationResize()
	{
	if (iPainter)
		{
		if (iOldSize.iWidth + (++iResizeOffset) < iSize.iWidth)
			{

			}
		else
			{
			iResizeOffset = 0;
			iAnimation->RemoveAnimation(iCallFunc);
			}
		}
	else
		{
		iResizeOffset = 0;
		iAnimation->RemoveAnimation(iCallFunc);
		}

	return KErrNone;
	}

TInt CListBoxContainerControl::CallbackAnimationResize(TAny* aThis)
	{
	return static_cast<CListBoxContainerControl*> (aThis)->AnimationResize();
	}

void CListBoxContainerControl::StopAnimation()
	{
	if (iCallFunc)
		{
		iAnimation->RemoveAnimation(iCallFunc);
		iCallFunc = NULL;
		}
	}

void CListBoxContainerControl::CheckMarquee()
	{
	if (iItems && iItems->Count() )
		{
		if (iSelectedIndex >= 0 && iSelectedIndex < iItems->Count())
			{
			CListBoxItemControl* item = (*iItems)[iSelectedIndex];
			item->StartAnimationMarquee();
			}
		}
	}
