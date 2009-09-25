/*
 ============================================================================
 Name		: ListBoxView.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxView implementation
 ============================================================================
 */
#include <aknViewAppUi.h> 

#include "LemonPlayer.hrh"

#include "ListBox.h"
#include "ListBoxView.h"

_LIT(iSkinFileDir,"C:\\");

CMyListBoxView::CMyListBoxView()
	{
	// No implementation required
	}

CMyListBoxView::~CMyListBoxView()
	{
	if (iBox)
		{
		AppUi()->RemoveFromViewStack( *this, iBox);
		delete iBox;
		iBox = NULL;
		}
	}

CMyListBoxView* CMyListBoxView::NewLC()
	{
	CMyListBoxView* self = new (ELeave)CMyListBoxView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyListBoxView* CMyListBoxView::NewL()
	{
	CMyListBoxView* self=CMyListBoxView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}



void CMyListBoxView::ConstructL()
	{
	BaseConstructL();
	
//	iBox = CListBox::NewL(ClientRect());
//	iBox->SetMopParent( this);
	}

TUid CMyListBoxView::Id() const
	{
	return TUid::Uid(EListboxSettingView);
	}

void CMyListBoxView::HandleCommandL(TInt aCommand)
	{
	AppUi()->HandleCommandL(aCommand);
	}

void CMyListBoxView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{

	if (!iBox)
		{
		iBox = CListBox::NewL(ClientRect());
		iBox->SetData(iData);
		iBox->SetNotify(iNotify);
		iBox->SetMopParent( this);
		iBox->OpenItem(iSkinFileDir);
		
		AppUi()->AddToStackL( *this, iBox);		
		}
	}

void CMyListBoxView::DoDeactivate()
	{
	if (iBox)
		{
		AppUi()->RemoveFromViewStack( *this, iBox);	
		}
	delete iBox;
	iBox = NULL;
	}

void CMyListBoxView::SetData(CUIViewData *aData)
	{
	iData = aData;
//	iBox->SetData(iData);
	}

void CMyListBoxView::SetNotify(MListBoxViewNotify *aNotify)
	{
	iNotify = aNotify;
//	
	}