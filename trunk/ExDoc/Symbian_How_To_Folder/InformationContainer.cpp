/*
 ============================================================================
 Name		: InformationContainer.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CInformationContainer implementation
 ============================================================================
 */

#include "InformationContainer.h"

void CInformationContainer::ConstructL(const TRect& aRect)
	{
	iInfoArray = NULL;
	iWordWrap = EFalse;

	iTopLine = 0;
	iLeftMargin = 3;
	iRightMargin = 3;
	iTopMargin = 2;
	iLineSpace = 1;
	iBorderWidth = aRect.Width();
	iBorderHeight = aRect.Height();

	iFont = CEikonEnv::Static()->TitleFont();
	iDispLines = iBorderHeight / (iFont->HeightInPixels() + iLineSpace);

	CreateWindowL();

	SetRect(aRect);

	iScrollBar = new (ELeave) CEikScrollBarFrame(this, this);
	iScrollBar->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,
			CEikScrollBarFrame::EOn);

	ActivateL();
	}

CInformationContainer::~CInformationContainer()
	{
	delete iScrollBar;
	iScrollBar = NULL;
	delete iInfoArray;
	}

void CInformationContainer::SizeChanged()
	{
	// TODO: Add here control resize code etc.
	}

// 设置内容
void CInformationContainer::setInformationL(const TDesC& info)
	{
	iTopLine = 0;
	iInfoArray = new (ELeave) CDesC16ArrayFlat(10);

	TInt loc, eloc, sloc, offset(0);
	TBool loop(ETrue);
	while (loop)
		{
		loc = calcLineChar(info.Mid(offset), eloc, sloc);
		if (loc <= 0)
			{
			iInfoArray->AppendL(info.Mid(offset));
			break;
			}
		else
			{
			iInfoArray->AppendL(info.Mid(offset, eloc));
			offset += sloc;
			}
		}

	if (iInfoArray->Count() - iDispLines > 0)
		{
		// Initialize the scroll bar
		TEikScrollBarModel vSbarModel;

		vSbarModel.iThumbSpan = 1;
		vSbarModel.iThumbPosition = 0; // iVThumbPosition

		// Adjust the scrollbar span for each tab page
		vSbarModel.iScrollSpan = iInfoArray->Count() - iDispLines + 1;
		iScrollBar->Tile(&vSbarModel);
		}
	}

// 计算换行的位置
TInt CInformationContainer::calcLineChar(const TDesC& info, TInt& thisEnd,
		TInt& nextStart)
	{
	TInt len = -1;
	TUint wd = 0;
	for (TInt i = 0; i < info.Length(); i++)
		{
		if (info[i] == 0x0A)
			{
			thisEnd = len + 1;
			nextStart = len + 2;
			return len + 2;
			}
		else
			if (info[i] == 0x0D)
				{
				if (i + 1 < info.Length())
					{
					if (info[i + 1] == 0x0A)
						{
						thisEnd = len + 1;
						nextStart = len + 3;
						return len + 3;
						}
					else
						{
						thisEnd = len + 1;
						nextStart = len + 2;
						return len + 2;
						}
					}
				else
					{
					thisEnd = 0;
					nextStart = 0;
					return 0;
					}
				}

		wd = iFont->TextWidthInPixels(info.Left(i));
		if (wd > iBorderWidth - iLeftMargin - iRightMargin)
			{
			if (iWordWrap)
				{
				for (TInt j = len; j >= 0; j--)
					{
					if (info[j] < 0x30 || info[j] >= 128)
						{
						len = j + 1;
						break;
						}
					}
				}

			thisEnd = len;
			nextStart = len;
			return len;
			}

		len = i;
		}

	if (wd < iBorderWidth - iLeftMargin - iRightMargin)
		{
		thisEnd = len + 1;
		nextStart = len + 2;
		return -1;
		}
	else
		{
		thisEnd = 0;
		nextStart = 0;
		return 0;
		}

	}

TInt CInformationContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

CCoeControl* CInformationContainer::ComponentControl(TInt /*aIndex*/) const
	{
	return NULL;
	}

void CInformationContainer::Draw(const TRect& aRect) const
	{
	CWindowGc& gc = SystemGc();

	gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.SetBrushColor(TRgb(0xaaddff));
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(aRect);

	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.UseFont(iFont);

	if (iInfoArray)
		{
		TUint y = iFont->AscentInPixels() + iTopMargin;
		TInt count = iInfoArray->Count();
		if (count > iDispLines)
			count = iDispLines;

		for (TInt i = 0; i < count; i++, y += iFont->HeightInPixels()
				+ iLineSpace)
			{
			gc.DrawText((*iInfoArray)[i + iTopLine], TPoint(iLeftMargin, y));
			}
		}

	}

TKeyResponse CInformationContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	if (aType == EEventKey)
		{
		if (aKeyEvent.iCode == EKeyUpArrow) // 上键
			{
			if (iTopLine != 0)
				{
				iTopLine --;
				iScrollBar->MoveVertThumbTo(iTopLine);
				DrawNow();
				}
			}
		else
			if (aKeyEvent.iCode == EKeyDownArrow) // 下键
				{
				TInt val = iInfoArray->Count() - iDispLines;
				if (val > 0 && (TInt)iTopLine < val)
					{
					iTopLine ++;
					iScrollBar->MoveVertThumbTo(iTopLine);
					DrawNow();
					}
				}
		}

	return EKeyWasNotConsumed;
	}

void CInformationContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	}

void CInformationContainer::HandleScrollEventL(CEikScrollBar* /*aScrollBar*/,
		TEikScrollEvent /*aEventType*/)
	{
	}
