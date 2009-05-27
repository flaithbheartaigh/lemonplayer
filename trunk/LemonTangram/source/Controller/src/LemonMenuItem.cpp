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

CLemonMenuItem::CLemonMenuItem():
iChildList(NULL),iText(NULL)
	{
	// No implementation required
	}

CLemonMenuItem::~CLemonMenuItem()
	{
	Clear();
	}

CLemonMenuItem* CLemonMenuItem::NewLC()
	{
	CLemonMenuItem* self = new (ELeave)CLemonMenuItem();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLemonMenuItem* CLemonMenuItem::NewL()
	{
	CLemonMenuItem* self=CLemonMenuItem::NewLC();
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

void CLemonMenuItem::Draw(CFbsBitGc& gc)
	{}
