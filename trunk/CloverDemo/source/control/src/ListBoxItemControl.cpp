/*
 ============================================================================
 Name		: ListBoxItemControl.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxItemControl implementation
 ============================================================================
 */

#include "ListBoxItemControl.h"
#include "MacroUtil.h"

CListBoxItemControl::CListBoxItemControl() :
	iPainter(NULL),iText(NULL),iItemScrollAnimationIndex(KErrNotFound),
			iCallFunc(NULL)
	{
	// No implementation required
	}

CListBoxItemControl::~CListBoxItemControl()
	{
		SAFE_DELETE(iText)
	}

CListBoxItemControl* CListBoxItemControl::NewLC()
	{
	CListBoxItemControl* self = new (ELeave) CListBoxItemControl();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CListBoxItemControl* CListBoxItemControl::NewL()
	{
	CListBoxItemControl* self = CListBoxItemControl::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CListBoxItemControl::ConstructL()
	{

	}

void CListBoxItemControl::Draw(CBitmapContext& gc) const
	{
	if (iPainter && iText)
		{
		const CFont* font = iPainter->GetFont();
		gc.SetPenStyle(CGraphicsContext::ESolidPen);
		if (iPainter)
			gc.SetPenColor(iPainter->GetTextColor());
		gc.SetBrushStyle(CGraphicsContext::ENullBrush);
		//		gc.SetBrushColor( KRgbWhite );

		gc.UseFont(font);

		TPoint point = iPosition;
		point.iX += iMarqueeOffset;
		TSize size = iSize;
		size.iWidth += (-iMarqueeOffset);
		TRect rect = TRect(point, size);
		gc.DrawText(iText->Des(), rect, rect.Height() / 2
				+ font->AscentInPixels() / 2, CGraphicsContext::ELeft, 0);

		gc.DiscardFont();
		}
	}
void CListBoxItemControl::SetText(const TDesC& aText)
	{
		SAFE_DELETE(iText)
	iText = aText.AllocL();
	}

void CListBoxItemControl::StartAnimationMarquee()
	{
	iItemScrollFrame = 0;

	if (iPainter && iText)
		{
		const CFont* font = iPainter->GetFont();
		if (font->MeasureText(iText->Des()) > iSize.iWidth)
			{
			if (iAnimation)
				{
				iCallFunc = new TCallBack(
						CListBoxItemControl::CallbackAnimationMarquee, this);
				iItemScrollAnimationIndex = iAnimation->AppendAnimation(
						iCallFunc);
				}
			}
		}
	}

void CListBoxItemControl::StopAnimationMarquee()
	{
	iMarqueeOffset = 0;
	if (iCallFunc)
		iAnimation->RemoveAnimation(iCallFunc);
	iItemScrollAnimationIndex = KErrNotFound;
	}

TInt CListBoxItemControl::AnimationMarquee()
	{
	if (iPainter)
		{
		if (iItemScrollFrame < iPainter->GetAnimationMarqueeStartFrame())
			{
			iItemScrollFrame++;
			}
		else
			{
			if (iPainter && iText)
				{
				const CFont* font = iPainter->GetFont();
				TInt width = font->MeasureText(iText->Des());

				if (iPosition.iX + iMarqueeOffset + width > iSize.iWidth)
					iMarqueeOffset--;
				else
					iMarqueeOffset = 0;
				}
			}
		}

	return KErrNone;
	}

TInt CListBoxItemControl::CallbackAnimationMarquee(TAny* aThis)
	{
	return static_cast<CListBoxItemControl*> (aThis)->AnimationMarquee();
	}
