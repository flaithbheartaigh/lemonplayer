/*
 ============================================================================
 Name		: SimulateMessageAppView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __SIMULATEMESSAGEAPPVIEW_h__
#define __SIMULATEMESSAGEAPPVIEW_h__

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include <avkon.hrh>
#include <f32file.h>

#include "SimulateMessageAppContainer.h"

// CLASS DECLARATION
class CSimulateMessageAppView : public CAknView
	{
public:
	// Constructors and destructor
	~CSimulateMessageAppView();
	static CSimulateMessageAppView* NewL();
	static CSimulateMessageAppView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	CSimulateMessageAppView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CSimulateMessageAppContainer * iContainer;
	};

#endif // __SIMULATEMESSAGEAPPVIEW_h__
// End of File
