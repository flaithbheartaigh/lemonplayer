/*
 ============================================================================
 Name		: FileListView.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileListView implementation
 ============================================================================
 */
#include <aknViewAppUi.h> 

#include "FileListView.h"
#include "FileListContainer.h"

CFileListView::~CFileListView()
	{
	if (iContainer)
		{
		AppUi()->RemoveFromViewStack( *this, iContainer);
		}

	delete iContainer;
	}

void CFileListView::ConstructL()
	{
	BaseConstructL();
	}

// ---------------------------------------------------------
// TUid CSymbian1View::Id()
//
// ---------------------------------------------------------
//
TUid CFileListView::Id() const
	{
	return KFileListViewId;
	}

// ---------------------------------------------------------
// CSymbian1View::HandleCommandL(TInt aCommand)
// takes care of view command handling
// ---------------------------------------------------------
//
void CFileListView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
//		case EAknSoftkeyOk:
//			{
//			iEikonEnv->InfoMsg( _L("view1 ok") );
//			break;
//			}
//		case EAknSoftkeyBack:
//			{
//			AppUi()->HandleCommandL(EEikCmdExit);
//			break;
//			}
		default:
			{
			AppUi()->HandleCommandL(aCommand);
			break;
			}
		}
	}

// ---------------------------------------------------------
// CSymbian1View::HandleClientRectChange()
// ---------------------------------------------------------
//
void CFileListView::HandleClientRectChange()
	{
	if (iContainer)
		{
		iContainer->SetRect(ClientRect() );
		}
	}

// ---------------------------------------------------------
// CSymbian1View::DoActivateL(...)
// 
// ---------------------------------------------------------
//
void CFileListView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (!iContainer)
		{
		iContainer = new (ELeave) CFileListContainer;
		iContainer->SetMopParent(this);
		iContainer->ConstructL(ClientRect() );
		AppUi()->AddToStackL( *this, iContainer);
		}
	}

// ---------------------------------------------------------
// CSymbian1View::DoDeactivate()
// 
// ---------------------------------------------------------
//
void CFileListView::DoDeactivate()
	{
	if (iContainer)
		{
		AppUi()->RemoveFromViewStack( *this, iContainer);
		}

	delete iContainer;
	iContainer = NULL;
	}

