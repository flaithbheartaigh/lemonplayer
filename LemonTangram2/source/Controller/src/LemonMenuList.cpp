/*
 ============================================================================
 Name		: LemonMenuList.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenuList implementation
 ============================================================================
 */

#include "LemonMenuList.h"
#include "LemonMenuItem.h"
#include "LemonMenuDef.h"
#include <eikenv.h>

CLemonMenuList::CLemonMenuList(const CFont* aFont)
:iItemHeight(0),iItemWidth(0),
iFrameColor(KRgbGray),iBackgroundColor(KRgbWhite),
iFont(aFont),iSelectedIndex(0)
	{
	// No implementation required
	}

CLemonMenuList::~CLemonMenuList()
	{
	Clear();
	}

CLemonMenuList* CLemonMenuList::NewLC(const CFont* aFont)
	{
	CLemonMenuList* self = new (ELeave)CLemonMenuList(aFont);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLemonMenuList* CLemonMenuList::NewL(const CFont* aFont)
	{
	CLemonMenuList* self=CLemonMenuList::NewLC(aFont);
	CleanupStack::Pop(); // self;
	return self;
	}

void CLemonMenuList::ConstructL()
	{

	}

CLemonMenuItem* CLemonMenuList::FindItemById(const TInt& aId)
	{
	CLemonMenuItem* item = NULL;
	for(TInt i=0; i<iItems.Count(); i++)
		{
		item = iItems[i]->FindItemById(aId);
		if(item)
			break;
		}
	return item;
	}

CLemonMenuList*& CLemonMenuList::FindListById(const TInt& aId)
	{
	CLemonMenuItem* item = NULL;
	for(TInt i=0; i<iItems.Count(); i++)
		{
		item = iItems[i]->FindItemById(aId);
		if(item)
			{
			return item->GetChildListAdd();
			}
		}
	}

void CLemonMenuList::AddItem(CLemonMenuItem* aItem)
	{
	iItems.Append(aItem);
	}

void CLemonMenuList::Clear()
	{
	iItems.ResetAndDestroy();
//	CLemonMenuItem* item = NULL;
//	for(TInt i=0; i<iItems.Count(); i++)
//		{
//		item = iItems[i]->Clear();
//		}	
	}

void CLemonMenuList::Draw(CBitmapContext& gc)
	{
	DrawFrame(gc);
	
	TInt x = iPosition.iX;
	TInt y = iPosition.iY;
	CLemonMenuItem* item = NULL;
	CLemonMenuList* child = NULL;
	
	for(TInt i=0; i<iItems.Count(); i++)
		{
		item = iItems[i];
		item->Draw(gc);
		child = item->GetChildList();
//		gc.DrawText(item->GetText(),TPoint(x,y));
		if (child)
			child->Draw(gc);
		y += iItemHeight;
		}
	}

void CLemonMenuList::DrawFrame(CBitmapContext& gc)
	{
	gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
	gc.SetBrushColor( iFrameColor );
//	gc.SetPenSize(TSize(2,2));
	TRect rect;
	rect.iTl.iX = iPosition.iX - 1;
	rect.iTl.iY = iPosition.iY - 1;
	rect.iBr.iX = rect.iTl.iX + iSize.iWidth + 2;
	rect.iBr.iY = rect.iTl.iY + iSize.iHeight + 2;
//	gc.DrawRect(rect);
	gc.Clear(rect);
	
	gc.SetBrushColor( iBackgroundColor );
	rect.iTl.iX = iPosition.iX ;
	rect.iTl.iY = iPosition.iY ;
	rect.iBr.iX = rect.iTl.iX + iSize.iWidth ;
	rect.iBr.iY = rect.iTl.iY + iSize.iHeight ;	
//	gc.DrawRect(rect);
	gc.Clear(rect);
	}

void CLemonMenuList::RecordItemWidth(TInt aWidth)
	{
	if (aWidth > iItemWidth)
		iItemWidth = aWidth;
	}
void CLemonMenuList::OffsetItem()
	{
	TInt x = iPosition.iX;
	TInt y = iPosition.iY;
	for(TInt i=0; i<iItems.Count(); i++)
		{
		CLemonMenuItem* item = iItems[i];
		item->SetItemHeight(iItemHeight);
		item->SetItemWidth(iItemWidth);
		item->SetItemPosition(TPoint(x,y));
		y += iItemHeight;
		}
	
	iSize.iWidth = iItemWidth;
	iSize.iHeight = y - iPosition.iY;
	}

void CLemonMenuList::ResetSelectedIndex()
	{
	CLemonMenuItem* item = iItems[iSelectedIndex];
	item->SetSelected(EFalse);
	
	iSelectedIndex = 0;
	
	item = iItems[iSelectedIndex];
	item->SetSelected(ETrue);		
	}
void CLemonMenuList::SetSelectedIndex(const TInt& aIndex)
	{
	CLemonMenuItem* item = iItems[aIndex];
	item->SetSelected(ETrue);
	iSelectedIndex = aIndex;
	}
void CLemonMenuList::IncreaseSelected()
	{
	CLemonMenuItem* item = iItems[iSelectedIndex];
	item->SetSelected(EFalse);
	
	if (++iSelectedIndex >= iItems.Count())
		iSelectedIndex = 0;
	
	item = iItems[iSelectedIndex];
	item->SetSelected(ETrue);	
	}

void CLemonMenuList::DecreaseSelected()
	{
	CLemonMenuItem* item = iItems[iSelectedIndex];
	item->SetSelected(EFalse);
	
	if (--iSelectedIndex < 0)
		iSelectedIndex = iItems.Count()-1;
	
	item = iItems[iSelectedIndex];
	item->SetSelected(ETrue);	
	}

TInt CLemonMenuList::GetSelectedCommand()
	{
	TInt command;
	CLemonMenuItem* item = iItems[iSelectedIndex];
	command = item->GetCommand();
	return command;
	}
