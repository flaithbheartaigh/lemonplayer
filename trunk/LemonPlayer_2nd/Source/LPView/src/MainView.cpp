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

#include "MainView.h"

#include "MainContainer.h"

CMainView::~CMainView()
	{
	if (iContainer)
		{
//		AppUi()->RemoveFromViewStack( *this, iContainer);
		delete iContainer;
		}
	
	}

void CMainView::ConstructL(CUIViewData *aData)
	{
	BaseConstructL();
	
	iData = aData;
	
	iContainer = new (ELeave) CMainContainer;
	iContainer->SetData(iData);
	iContainer->SetMopParent(this);
	iContainer->ConstructL(ClientRect());
	
	
	}

// ---------------------------------------------------------
// TUid CSymbian1View::Id()
//
// ---------------------------------------------------------
//
TUid CMainView::Id() const
	{
//	return KMainViewId;
	return TUid::Uid(EMainView);
	}

// ---------------------------------------------------------
// CSymbian1View::HandleCommandL(TInt aCommand)
// takes care of view command handling
// ---------------------------------------------------------
//
void CMainView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ELemonPlayerCmdAppSaveData:
			iContainer->SaveData();
			break;
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
void CMainView::HandleClientRectChange()
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
void CMainView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (iContainer)
		{				
//		iContainer = new (ELeave) CMainContainer;
//		iContainer->SetData(iData);
		iContainer->SetMopParent(this);
//		iContainer->ConstructL(ClientRect());
			
		AppUi()->AddToStackL( *this, iContainer);
		
		PlayFile();
		}
	}

// ---------------------------------------------------------
// CSymbian1View::DoDeactivate()
// 
// ---------------------------------------------------------
//
void CMainView::DoDeactivate()
	{
	if (iContainer)
		{
		AppUi()->RemoveFromViewStack( *this, iContainer);
//		delete iContainer;
//		iContainer = NULL;
		}	
	}

void CMainView::SetData(CUIViewData *aData)
	{
	iData = aData;
	iContainer->SetData(iData);
	}


void CMainView::PlayFile()
	{
	iContainer->PlayFile();
	}