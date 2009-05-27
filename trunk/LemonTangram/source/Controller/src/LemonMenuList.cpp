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

CLemonMenuList::CLemonMenuList()
:iItemHeight(MENU_ITEM_HEIGHT)
	{
	// No implementation required
	}

CLemonMenuList::~CLemonMenuList()
	{
	Clear();
	}

CLemonMenuList* CLemonMenuList::NewLC()
	{
	CLemonMenuList* self = new (ELeave)CLemonMenuList();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLemonMenuList* CLemonMenuList::NewL()
	{
	CLemonMenuList* self=CLemonMenuList::NewLC();
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
			break;
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

void CLemonMenuList::Draw(CFbsBitGc& gc)
	{
	TInt x = iPosition.iX;
	TInt y = iPosition.iY;
	CLemonMenuItem* item = NULL;
	CLemonMenuList* child = NULL;
	
//	gc.SetPenStyle( CGraphicsContext::ESolidPen );
//	gc.SetPenColor(KRgbRed);	
//	gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
//	gc.SetBrushColor( KRgbGray );
//	gc.UseFont(CEikonEnv::Static()->LegendFont());	
	
	for(TInt i=0; i<iItems.Count(); i++)
		{
		item = iItems[i];
		child = item->GetChildList();
		gc.DrawText(item->GetText(),TPoint(x,y));
		if (child)
			child->Draw(gc);
		y += iItemHeight;
		}
//	gc.DiscardFont();
	}
