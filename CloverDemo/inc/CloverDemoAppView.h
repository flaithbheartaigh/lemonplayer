/*
 ============================================================================
 Name		: CloverDemoAppView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __CLOVERDEMOAPPVIEW_h__
#define __CLOVERDEMOAPPVIEW_h__

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include <avkon.hrh>
#include <f32file.h>

#include "CloverDemoAppContainer.h"

// CLASS DECLARATION
class CCloverDemoAppView : public CAknView
	{
public:
	// Constructors and destructor
	~CCloverDemoAppView();
	static CCloverDemoAppView* NewL();
	static CCloverDemoAppView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	CCloverDemoAppView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CCloverDemoAppContainer * iContainer;
	};

#endif // __CLOVERDEMOAPPVIEW_h__
// End of File
