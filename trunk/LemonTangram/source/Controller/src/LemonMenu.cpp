/*
 ============================================================================
 Name		: LemonMenu.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenu implementation
 ============================================================================
 */

#include "LemonMenu.h"
#include "LemonMenuBar.h"
#include "LemonMenuList.h"
#include "LemonMenuDef.h"
#include "DefaultDeclHandler.h"
#include <coemain.h>
#include "CommonUtils.h"
#include "LemonMenuItem.h"
#include "MacroUtil.h"
#include <eikenv.h>
#include "LemonTangramAppUi.h"

CLemonMenu::CLemonMenu(MLemonMenuNotify* aNotify)
:iNotify(aNotify),iMenuList(NULL),iPtrList(NULL),iMenuActive(EFalse)
	{
	// No implementation required
	}

CLemonMenu::~CLemonMenu()
	{
	SAFE_DELETE(iMenuList);
	SAFE_DELETE(iMenuBar);
	}

CLemonMenu* CLemonMenu::NewLC(MLemonMenuNotify* aNotify)
	{
	CLemonMenu* self = new (ELeave)CLemonMenu(aNotify);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLemonMenu* CLemonMenu::NewL(MLemonMenuNotify* aNotify)
	{
	CLemonMenu* self=CLemonMenu::NewLC(aNotify);
	CleanupStack::Pop(); // self;
	return self;
	}

void CLemonMenu::ConstructL()
	{
	iUIMgr = STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->GetUIMgr();
	iMenuBar = CLemonMenuBar::NewL();
	}

void CLemonMenu::LoadMenu(const TDesC& aFileName)
	{
	CDefaultDeclHandler *decl = new (ELeave)CDefaultDeclHandler;
	CleanupStack::PushL(decl);

	CSyParser *syParser = CSyParser::NewLC(TPtrC());
	syParser->SetHandler(this);
	syParser->SetHandler(decl);

	RFile file;
	TInt err = file.Open(CCoeEnv::Static()->FsSession(), aFileName, EFileRead);

	if (KErrNone == err)
		{
		CleanupClosePushL(file);
		//²Ù×÷
		TBuf8<512> strBuffer;

		file.Read(strBuffer);
		while (strBuffer.Length() != 0)
			{
			syParser->Parse(strBuffer, EFalse);
			file.Read(strBuffer);
			}
		syParser->Parse(strBuffer, ETrue);
		CleanupStack::PopAndDestroy(1);
		}
	CleanupStack::PopAndDestroy(2);	
	}
void CLemonMenu::Draw(CFbsBitGc& gc)
	{
	iMenuBar->Draw(gc,iMenuActive);
	
	if (iMenuActive)
		{
		iMenuList->Draw(gc);
		}
	}
TKeyResponse CLemonMenu::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	if (iMenuActive)
		{
		switch(aType)
			{
			case EEventKeyUp:
				switch (aKeyEvent.iScanCode)
					{
						case EStdKeyDevice0:
						case EStdKeyDevice3://ok
							iNotify->HandMenuCommand(iMenuList->GetSelectedCommand());
							iMenuActive = EFalse;
							return EKeyWasConsumed;					
						case EStdKeyDevice1:
							iMenuActive = EFalse;
							return EKeyWasConsumed;
						case EStdKeyUpArrow:
							iMenuList->DecreaseSelected();
							return EKeyWasConsumed;
						case EStdKeyDownArrow:
							iMenuList->IncreaseSelected();
							return EKeyWasConsumed;				
					}
			break;
			}
		return EKeyWasConsumed;
		}
	else
		{
		switch(aType)
			{
			case EEventKeyUp:
				switch (aKeyEvent.iScanCode)
					{
						case EStdKeyDevice0://ok
							iMenuActive = ETrue;
							return EKeyWasConsumed;
					}
			break;
			}
		}
	return EKeyWasNotConsumed;
	}

//CDefaultDocHandler
void CLemonMenu::StartElement(const TQualified& aName,
		const RArray<TAttribute>& aAttributes)
	{
	TInt num = ConvertNameToNumber(aName.iLocalName);
	switch (num)
		{
		case EMenuTagMenu:
			ParseMenu(aAttributes);
			break;
		case EMenuTagItem:
			ParseItem(aAttributes);
			break;
		default:
			break;
		}
	}

void CLemonMenu::EndElement(const TQualified& aName)
	{
	TInt num = ConvertNameToNumber(aName.iLocalName);
	switch (num)
		{
		case EMenuTagMenu:
			EndParseMenu();
			break;
		default:
			break;
		}	
	}

TInt CLemonMenu::ConvertNameToNumber(const TDesC& aName)
	{
	HBufC* name = aName.AllocLC();
	name->Des().LowerCase();
	TInt num = EMenuTagNone;

	if (name->Compare(KMenuDomTagMenu) == 0)
		{
		num = EMenuTagMenu;
		}
	else
		if (name->Compare(KMenuDomTagItem) == 0)
			{
			num = EMenuTagItem;
			}
	CleanupStack::PopAndDestroy();
	return num;
	}

void CLemonMenu::ParseMenu(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KMenuAttrParent) == 0)
			{
			TInt num = CCommonUtils::StrToInt(attrValue->Des());
			FindListById(num);
//			iPtrList = CLemonMenuList::NewL();
			}
		CleanupStack::PopAndDestroy(2);
		}
	}
void CLemonMenu::ParseItem(const RArray<TAttribute>& aAttributes)
	{
	CLemonMenuItem* item = CLemonMenuItem::NewL(iUIMgr->iSysFont);
	TInt width;
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KMenuAttrId) == 0)
			{
			TInt id = CCommonUtils::StrToInt(attrValue->Des());
			item->SetId(id);
			}
		if (attrName->Compare(KMenuAttrText) == 0)
			{
			item->SetText(attrValue->Des());
			}
		if (attrName->Compare(KMenuAttrCommand) == 0)
			{			
			TInt command = CCommonUtils::StrToInt(attrValue->Des());
			item->SetCommand(command);
			}		
		CleanupStack::PopAndDestroy(2);
		}
	width = iUIMgr->SubMenuWidth();
	iPtrList->RecordItemWidth(width);
	iPtrList->AddItem(item);
	}

void CLemonMenu::EndParseMenu()
	{
	iPtrList->SetSelectedIndex(0);
	iPtrList->SetItemHeight(iUIMgr->MainMenuItemHeight());
	iPtrList->OffsetItem();	
	}

void CLemonMenu::FindListById(const TInt& aId)
	{
	if (aId < 0 )
		{
		iMenuList = CLemonMenuList::NewL(iUIMgr->iSysFont);
		iPtrList = iMenuList;
		iPtrList->SetPositon(iUIMgr->MainMenuPos());
		return;
		}
	else
		{
		CLemonMenuList*& list = iMenuList->FindListById(aId);
		list = CLemonMenuList::NewL(iUIMgr->iSysFont);
		iPtrList = list;
		
		CLemonMenuItem* item = iMenuList->FindItemById(aId);
		TInt x = item->GetItemPosition().iX;
		TInt y = item->GetItemPosition().iY;
		x += item->GetItemWidth();
		iPtrList->SetPositon(TPoint(x,y));
		}
	}
