/*
 ============================================================================
 Name		: LemonMenuItem.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenuItem implementation
 ============================================================================
 */

#include "LemonMenuItem.h"
#include "LemonMenuList.h"
#include "MacroUtil.h"
#include "LemonMenuDef.h"


CLemonMenuItem::CLemonMenuItem(const CFont* aFont):
iChildList(NULL),iText(NULL),
iTextColor(KRgbBlack),iSelectedColor(KRgbMenuSelected),iUnSelectedColor(KRgbWhite),
iFont(aFont),iSelected(EFalse)
	{
	// No implementation required
	}

CLemonMenuItem::~CLemonMenuItem()
	{
	Clear();
	}

CLemonMenuItem* CLemonMenuItem::NewLC(const CFont* aFont)
	{
	CLemonMenuItem* self = new (ELeave)CLemonMenuItem(aFont);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLemonMenuItem* CLemonMenuItem::NewL(const CFont* aFont)
	{
	CLemonMenuItem* self=CLemonMenuItem::NewLC(aFont);
	CleanupStack::Pop(); // self;
	return self;
	}

void CLemonMenuItem::ConstructL()
	{

	}

CLemonMenuItem* CLemonMenuItem::FindItemById(const TInt& aId)
	{
	if (iId == aId)
		return this;
	if (iChildList)
		return iChildList->FindItemById(aId);
	return NULL;
	}

CLemonMenuList*& CLemonMenuItem::GetChildListAdd()
	{
	return iChildList;
	}

CLemonMenuList* CLemonMenuItem::GetChildList()
	{
	return iChildList;
	}

void CLemonMenuItem::Clear()
	{
	if (iChildList)
		{
		iChildList->Clear();
		SAFE_DELETE(iChildList);
		}
	SAFE_DELETE(iText);
	}

void CLemonMenuItem::Draw(CBitmapContext& gc)
	{
	TRect rect;

	rect.iTl.iX = iItemPosition.iX;
	rect.iTl.iY = iItemPosition.iY;
	rect.iBr.iX = iItemPosition.iX + iItemWidth;
	rect.iBr.iY = iItemPosition.iY + iItemHeight;

	if (iSelected)
		{
		gc.SetBrushColor(iSelectedColor);
		gc.Clear(rect);
		}
	else
		{
		gc.SetBrushColor(iUnSelectedColor);
		gc.Clear(rect);		
		}
	gc.SetPenColor(iTextColor);
	gc.UseFont(iFont);	
	gc.DrawText(iText->Des(),rect,rect.Height()/2 + iFont->AscentInPixels()/2);
	gc.DiscardFont();
	}
