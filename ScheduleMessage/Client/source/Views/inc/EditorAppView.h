/*
 ============================================================================
 Name		: TestEditorAppView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __TESTEDITORAPPVIEW_h__
#define __TESTEDITORAPPVIEW_h__

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include <avkon.hrh>
#include <f32file.h>
#include <msvstd.h>

#include "MsgEditorView.h"
#include "MsgEditorObserver.h"             	// for MMsgEditorObserver
#include "UniEditorHeader.h"				//CUniEditorHeader

// CLASS DECLARATION
class CEditorAppView : public CAknView ,public MMsgEditorObserver
	{
public:
    
	// Constructors and destructor
	~CEditorAppView();
	static CEditorAppView* NewL();
	static CEditorAppView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

    CMsgBaseControl* CreateCustomControlL(TInt aControlType);
    void EditorObserver(TMsgEditorObserverFunc aFunc, TAny* aArg1, TAny* aArg2, TAny* aArg3);
    
private:
	CEditorAppView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();
	
private:
	void SaveTask();
	void LoadMessage(TMsvId aMsg);
	void LoadMessage();
	
	void Back();

private:
//	CTestEditorAppContainer * iContainer;
	CMsgEditorView* iContainer;
	
	CUniEditorHeader*          iHeader;
	};

#endif // __TESTEDITORAPPVIEW_h__
// End of File
