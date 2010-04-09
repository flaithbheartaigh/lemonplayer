/*
 ============================================================================
 Name		: ThemeChangeAppView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __THEMECHANGEAPPVIEW_h__
#define __THEMECHANGEAPPVIEW_h__

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include <avkon.hrh>
#include <f32file.h>

#include "ThemeChangeAppContainer.h"

// CLASS DECLARATION
class CThemeChangeAppView : public CAknView
	{
public:
	// Constructors and destructor
	~CThemeChangeAppView();
	static CThemeChangeAppView* NewL();
	static CThemeChangeAppView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();
	void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );
	
private:
	CThemeChangeAppView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CThemeChangeAppContainer * iContainer;
	};

#endif // __THEMECHANGEAPPVIEW_h__
// End of File
