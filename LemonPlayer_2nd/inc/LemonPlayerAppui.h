/*
 * ============================================================================
 *  Name     : CLemonPlayerAppUi from LemonPlayerAppui.h
 *  Part of  : LemonPlayer
 *  Created  : 17.09.2008 by zengcity
 *  Description:
 *     Declares UI class for application.
 *  Version  :
 *  Copyright: 
 * ============================================================================
 */

#ifndef LEMONPLAYERAPPUI_H
#define LEMONPLAYERAPPUI_H

// INCLUDES
#include <aknViewAppUi.h> 
#include "ViewNotify.h"
// FORWARD DECLARATIONS
//class CLemonPlayerContainer;
//class CMainView;
//class CFileListView;
//class CMyListBoxView;
class CUIViewData;

//class CMusicListMgr;
class CTaskManager;
// CLASS DECLARATION

/**
 * Application UI class.
 * Provides support for the following features:
 * - EIKON control architecture
 * 
 */
class CLemonPlayerAppUi : 	public CAknViewAppUi,
							public MListBoxViewNotify
	{
public:
	// // Constructors and destructor

	/**
	 * EPOC default constructor.
	 */
	void ConstructL();

	/**
	 * Destructor.
	 */
	~CLemonPlayerAppUi();

public:
	// New functions

public:
	// Functions from base classes

private:
	// From MEikMenuObserver
//	void DynInitMenuBarL(TInt aResourceId, CEikMenuBar* aMenuBar);

private:
	/**
	 * From CEikAppUi, takes care of command handling.
	 * @param aCommand command to be handled
	 */
	void HandleCommandL(TInt aCommand);

	/**
	 * From CEikAppUi, handles key events.
	 * @param aKeyEvent Event to handled.
	 * @param aType Type of the key event. 
	 * @return Response code (EKeyWasConsumed, EKeyWasNotConsumed). 
	 */
	virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,
			TEventCode aType);
	
public:
	virtual void OnListBoxViewNotify();

private:
	//Data
//	CLemonPlayerContainer* iAppContainer;
//	CFileListView* iFileListView;
//	CMainView* iMainView;
//	CMyListBoxView* iListBoxView;
	
	CUIViewData *iData;
	
	CTaskManager* iTaskMgr;
	
	
	};

#endif

// End of File
