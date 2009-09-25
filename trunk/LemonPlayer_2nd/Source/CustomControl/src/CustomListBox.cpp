// --------------------------------------------------------------------------
// CustomListBox.cpp
//
// Copyright 2005, Antony Pranata
// http://www.antonypranata.com
//
// An example of subclassing a list box in Symbian (UIQ).
// --------------------------------------------------------------------------

// INCLUDE FILES
#include <coemain.h>
#include <eikenv.h>
#include <gulicon.h>
#include <eiktxlbm.h>   // CTextListBoxModel
//#include <e32keys.h > // keys for jog dial

#include "CustomListBox.h"


// MEMBER FUNCTIONS

// --------------------------------------------------------------------------
// CCustomListItemDrawer
// --------------------------------------------------------------------------

CCustomListItemDrawer::CCustomListItemDrawer(const CEikTextListBox& aListBox)
:CListItemDrawer(),
 iListBox(aListBox)
	{
	// Store a GC for later use
	iGc = &CCoeEnv::Static()->SystemGc();
	SetGc(iGc);
	}

CCustomListItemDrawer::~CCustomListItemDrawer()
	{
	DeleteIconArray();
	}

//
// Draws the item, which might contain an icon and a text.
// The format of the item text shall look like one of the following formats:
//		- "\ttext"				(text only)
//		- "icon\ttext"			(icon and text)
//		- "\theading\ttext"		(heading and text)
//		- "icon\theading\ttext"	(icon, heading and text)
//		
void CCustomListItemDrawer::DrawActualItem(TInt aItemIndex,
		const TRect& aActualItemRect, TBool aItemIsCurrent,
		TBool /*aViewIsEmphasized*/, TBool /*aViewIsDimmed*/,
		TBool aItemIsSelected) const
	{
	const MDesCArray* itemArray = iListBox.Model()->ItemTextArray();
	if ((!itemArray) || (itemArray->MdcaCount() <= aItemIndex))
		return;
    
	// Gets the item text if the conditions above are met.
	TPtrC itemText = itemArray->MdcaPoint(aItemIndex);

	// We have to find the position of tabs to decide the components
	// available in the item text (icon, heading and text).
	TInt tabPosition1 = itemText.Locate('\t');
	TInt tabPosition2 = itemText.Mid(tabPosition1 + 1).Locate('\t');
	if (tabPosition2 >= 0)
		{
		// We need to add tabPosition1 because the return value of
		// Locate() is relative to tabPosition1.
		tabPosition2 += tabPosition1 + 1;
		}

	// Sets the attributes to draw the icon.
	iGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	if ((aItemIsCurrent) || (aItemIsSelected))
		{
		iGc->SetBrushColor(iHighlightedBackColor);
		}
	else
		{
		iGc->SetBrushColor(iBackColor);
		}

	// Gets the icon index, i.e. the number in the text item before
	// the first tab.
	TInt iconIndex = 0;
	if (tabPosition1 > 0)
		{
		TLex(itemText.Mid(0, tabPosition1)).Val(iconIndex);
		}
	if ((iIconArray) && (iIconArray->Count() > iconIndex)
		&& (tabPosition1 > 0))
		{
		// Draws the icon.
		CFbsBitmap* bitmap = (*iIconArray)[iconIndex]->Bitmap();
		iGc->BitBltMasked(
			aActualItemRect.iTl,
			bitmap,
			TRect(TPoint(0, 0), bitmap->Header().iSizeInPixels),
			(*iIconArray)[iconIndex]->Mask(),
			ETrue);

		// Draws the rectangle, just in case there are some icons that are
		// smaller than the height of item width and/or height.
		iGc->SetPenStyle(CGraphicsContext::ENullPen);
		if (bitmap->Header().iSizeInPixels.iHeight < aActualItemRect.Height())
			{
			TRect rect(
				aActualItemRect.iTl.iX,
				aActualItemRect.iTl.iY + bitmap->Header().iSizeInPixels.iHeight,
				aActualItemRect.iTl.iX + iMaxIconSize.iWidth,
				aActualItemRect.iBr.iY);
			iGc->DrawRect(rect);
			}

		if (bitmap->Header().iSizeInPixels.iWidth < iMaxIconSize.iWidth)
			{
			TRect rect = TRect(
				aActualItemRect.iTl.iX + bitmap->Header().iSizeInPixels.iWidth,
				aActualItemRect.iTl.iY,
				aActualItemRect.iTl.iX + iMaxIconSize.iWidth,
				aActualItemRect.iBr.iY);
			iGc->DrawRect(rect);
			}
		}
	else
		{
		iGc->SetPenStyle(CGraphicsContext::ENullPen);
		TRect rect(
			aActualItemRect.iTl.iX,
			aActualItemRect.iTl.iY,
			aActualItemRect.iTl.iX + iMaxIconSize.iWidth,
			aActualItemRect.iBr.iY);
		iGc->DrawRect(rect);
		}

	// Sets the attributes to draw text, except the font.
	const CFont* font = Font(aItemIndex);
	iGc->SetPenStyle(CGraphicsContext::ESolidPen);
	iGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	if ((aItemIsCurrent) || (aItemIsSelected))
		{
		iGc->SetPenColor(iHighlightedTextColor);
		iGc->SetBrushColor(iHighlightedBackColor);
		}
	else
		{
		iGc->SetPenColor(iTextColor);
		iGc->SetBrushColor(iBackColor);
		}

	// If there is only one tab, it means we have to display single line item
	if (tabPosition2 < 0)
		{		
		if (!font)
			{
			font = CEikonEnv::Static()->TitleFont();
			}
		iGc->UseFont(font);
		TRect textRect(
			TPoint(aActualItemRect.iTl.iX + iMaxIconSize.iWidth,
					aActualItemRect.iTl.iY),
			aActualItemRect.iBr);
		TInt baseline =
			(textRect.iBr.iY - textRect.iTl.iY - font->HeightInPixels()) / 2
				+ font->AscentInPixels();

		if (tabPosition1 < 0)
			{
			iGc->DrawText(itemText, textRect, baseline,
				CGraphicsContext::ELeft, 1);
			}
		else
			{
			iGc->DrawText(itemText.Mid(tabPosition1 + 1), textRect, baseline,
				CGraphicsContext::ELeft, 1);
			}
		}
	else
		{
		// If there are more than one tab, then we have to display double line
		// item text
		TRect textRect(
			TPoint(aActualItemRect.iTl.iX + iMaxIconSize.iWidth,
				aActualItemRect.iTl.iY),
			aActualItemRect.iBr);
		textRect.iBr.iY -= aActualItemRect.Height() / 2;

		// Draws the first line.
		if (!font)
			{
			font = CEikonEnv::Static()->LegendFont();
			}
		iGc->UseFont(font);
		TInt baseline =
			(textRect.iBr.iY - textRect.iTl.iY - font->HeightInPixels()) / 2
				+ font->AscentInPixels();
		iGc->DrawText(
			itemText.Mid(tabPosition1 + 1, tabPosition2 - tabPosition1 - 1),
			textRect, baseline, CGraphicsContext::ELeft, 1);

		// Draws the second line. For the second line, we use normal font.
		font = CCoeEnv::Static()->NormalFont();
		iGc->UseFont(font);
		textRect.Move(0, aActualItemRect.Height() / 2);
		baseline =
			(textRect.iBr.iY - textRect.iTl.iY - font->HeightInPixels()) / 2
				+ font->AscentInPixels();
		iGc->DrawText(itemText.Mid(tabPosition2 + 1), textRect, baseline,
			CGraphicsContext::ELeft, 1);
		}
	}

void CCustomListItemDrawer::SetIconArray(CArrayPtr<CGulIcon>* aIconArray)
	{
	DeleteIconArray();
	iIconArray = aIconArray;
	CalculateMaxIconSize();
	}

TSize CCustomListItemDrawer::MaxIconSize() const
{
	return iMaxIconSize;
	}

void CCustomListItemDrawer::DeleteIconArray()
	{
	if (iIconArray)
		{
		iIconArray->ResetAndDestroy();
		delete iIconArray;
		iIconArray = 0;
		}
	}

void CCustomListItemDrawer::CalculateMaxIconSize()
	{
	iMaxIconSize = TSize(0, 0);

	// Finds the maximum width and height of the icon.
	if (iIconArray)
		{
		for (TInt i = 0; i < iIconArray->Count(); i++)
			{
			TInt width = (*iIconArray)[i]->Bitmap()->Header().iSizeInPixels.iWidth;
			if (iMaxIconSize.iWidth < width)
				{
				iMaxIconSize.iWidth = width;
				}

			TInt height = (*iIconArray)[i]->Bitmap()->Header().iSizeInPixels.iHeight;
			if (iMaxIconSize.iHeight < height)
				{
				iMaxIconSize.iHeight = height;
				}
			} // for
		} // iIconArray
	}


// --------------------------------------------------------------------------
// CCustomListBox
// --------------------------------------------------------------------------

CCustomListBox::CCustomListBox()
:CEikTextListBox()
	{
	}

void CCustomListBox::ConstructL(const CCoeControl* aParent, TInt aFlags)
	{
	CEikTextListBox::ConstructL(aParent, aFlags);
	}

void CCustomListBox::CreateItemDrawerL()
	{
	iItemDrawer = new (ELeave) CCustomListItemDrawer(*this);
	}

TKeyResponse CCustomListBox::OfferKeyEventL(const TKeyEvent& aKeyEvent,
											TEventCode aType)
	{
	if (EEventKeyDown == aType)
		{
		switch (aKeyEvent.iScanCode)
			{
			// Down arrow in UIQ
			case EStdKeyDownArrow:
				{
				if (CurrentItemIndex() < Model()->NumberOfItems() - 1)
					{
					SetCurrentItemIndex(CurrentItemIndex() + 1);
					DrawNow();
					}
				return EKeyWasConsumed;
				}

			// Up arrow in UIQ
			case EStdKeyUpArrow:
				{
				if (CurrentItemIndex() > 0)
					{
					SetCurrentItemIndex(CurrentItemIndex() - 1);
					DrawNow();
					}
				return EKeyWasConsumed;
				}
				
			default:
				return CEikTextListBox::OfferKeyEventL(aKeyEvent, aType);
			}
		}
	return EKeyWasNotConsumed;
	}

// End of File  
 