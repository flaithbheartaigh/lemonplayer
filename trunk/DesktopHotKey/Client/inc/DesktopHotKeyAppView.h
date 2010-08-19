/*
 ============================================================================
 Name		: DesktopHotKeyAppView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __DESKTOPHOTKEYAPPVIEW_h__
#define __DESKTOPHOTKEYAPPVIEW_h__

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include <avkon.hrh>
#include <f32file.h>

#include "DesktopHotKeyAppContainer.h"

// CLASS DECLARATION
class CDesktopHotKeyAppView : public CAknView
	{
public:
	// Constructors and destructor
	~CDesktopHotKeyAppView();
	static CDesktopHotKeyAppView* NewL();
	static CDesktopHotKeyAppView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();

private:
	CDesktopHotKeyAppView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CDesktopHotKeyAppContainer * iContainer;
	};

#endif // __DESKTOPHOTKEYAPPVIEW_h__
// End of File
