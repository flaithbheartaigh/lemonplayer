/*
 ============================================================================
 Name		: FileListView.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileListView declaration
 ============================================================================
 */

#ifndef FILELISTVIEW_H
#define FILELISTVIEW_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <aknview.h>

#include <LemonPlayer.hrh>

const TUid KFileListViewId = {EFileListView};

// CLASS DECLARATION
class CFileListContainer;
/**
 *  CFileListView
 * 
 */
class CFileListView : public CAknView
	{
public:
	~CFileListView();
	void ConstructL();

public:
	// Functions from base classes

	// From CAknView returns Uid of View
	TUid Id() const;

	// From MEikMenuObserver delegate commands from the menu
	void HandleCommandL(TInt aCommand);

	//From CAknView reaction if size change
	void HandleClientRectChange();

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
	
private:
	CFileListContainer *iContainer;
	};

#endif // FILELISTVIEW_H
