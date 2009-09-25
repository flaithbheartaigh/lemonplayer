/*
 ============================================================================
 Name		: FileListView.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileListView declaration
 ============================================================================
 */

#ifndef MAINVIEW_H
#define MAINVIEW_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <aknview.h>

#include <LemonPlayer.hrh>


const TUid KMainViewId = {EMainView};

// CLASS DECLARATION
class CMainContainer;
class CUIViewData;
/**
 *  CFileListView
 * 
 */
class CMainView : public CAknView
	{
public:
	~CMainView();
	void ConstructL(CUIViewData *aData);

public:
	// Functions from base classes

	// From CAknView returns Uid of View
	TUid Id() const;

	// From MEikMenuObserver delegate commands from the menu
	void HandleCommandL(TInt aCommand);

	//From CAknView reaction if size change
	void HandleClientRectChange();
	
public:
	void SetData(CUIViewData *aData);

private:
	/**
	 * From CAknView activate the view
	 * @param aPrevViewId 
	 * @param aCustomMessageId 
	 * @param aCustomMessage 
	 * @return void
	 */
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);

	//From CAknView deactivate the view (free resources)
	void DoDeactivate();
	
public:
	void PlayFile();
		
private:
	CMainContainer *iContainer;
	CUIViewData *iData;
	
	
	};

#endif // MAINVIEW_H
