/*
 * ============================================================================
 *  Name     : CLemonPlayerAppUi from LemonPlayerAppui.cpp
 *  Part of  : LemonPlayer
 *  Created  : 17.09.2008 by zengcity
 *  Implementation notes:
 *     Initial content was generated by Series 60 Application Wizard.
 *  Version  :
 *  Copyright: 
 * ============================================================================
 */

// INCLUDE FILES
#include "LemonPlayerAppui.h"
#include "LemonPlayerContainer.h" 
#include <LemonPlayer.rsg>
#include "LemonPlayer.hrh"

#include <avkon.hrh>

#include "MacroUtil.h"
//#include "MainView.h"
//#include "FileListView.h"
//#include "ListBoxView.h"
#include "UIData.h"

//#include "MusicListMgr.h"
//#include "MusicDBMgr.h"
#include "TaskManager.h"
// ================= MEMBER FUNCTIONS =======================
//
// ----------------------------------------------------------
// CLemonPlayerAppUi::ConstructL()
// 
// ----------------------------------------------------------
//
void CLemonPlayerAppUi::ConstructL()
	{
	BaseConstructL();

//	iAppContainer = new (ELeave) CLemonPlayerContainer;
//	iAppContainer->SetMopParent( this);
//	iAppContainer->ConstructL(ClientRect() );
//	iAppContainer->ConstructL(ApplicationRect() );
	
	iTaskMgr = CTaskManager::NewL();

//	AddToStackL(iAppContainer);
	}

// ----------------------------------------------------
// CLemonPlayerAppUi::~CLemonPlayerAppUi()
// Destructor
// Frees reserved resources
// ----------------------------------------------------
//
CLemonPlayerAppUi::~CLemonPlayerAppUi()
	{
	
	SAFE_DELETE(iTaskMgr);
//	SAFE_DELETE(iMainView);
	
//	SAFE_DELETE(iListBoxView);
	SAFE_DELETE(iData);
	
//	if (iAppContainer)
//		{
//		RemoveFromStack(iAppContainer);
//		delete iAppContainer;
//		}
	}

// ------------------------------------------------------------------------------
// CLemonPlayerAppUi::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
// ------------------------------------------------------------------------------
//
//void CLemonPlayerAppUi::DynInitMenuBarL(TInt aResourceId, CEikMenuBar* aMenuBar)
//	{
//	iAppContainer->DynInitMenuBarL(aResourceId,aMenuBar);
//	}

// ----------------------------------------------------
// CLemonPlayerAppUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// takes care of key event handling
// ----------------------------------------------------
//
TKeyResponse CLemonPlayerAppUi::HandleKeyEventL(const TKeyEvent& /*aKeyEvent*/,
		TEventCode /*aType*/)
	{
	return EKeyWasNotConsumed;
	}

// ----------------------------------------------------
// CLemonPlayerAppUi::HandleCommandL(TInt aCommand)
// takes care of command handling
// ----------------------------------------------------
//
void CLemonPlayerAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EAknSoftkeyBack:
		case EEikCmdExit:
			{
			Exit();
			break;
			}
		case ELemonPlayerCmdAppTest:
			{
			iAppContainer->StartEffect(KAnimationEffectNormal);
//			iTaskMgr->StartShutDown(10000000);
//			ActivateLocalViewL(iListBoxView->Id());
			//            ActivateLocalViewL(iFileListView->Id());
			break;
			}
			// TODO: Add Your command handling code here
		default:
			iAppContainer->HandleCommandL(aCommand);
			//        	Panic(ELemonPlayerUi);
			break;
		}
	}

void CLemonPlayerAppUi::OnListBoxViewNotify()
	{
	ActivateLocalViewL(iMainView->Id());
	}
// End of File  