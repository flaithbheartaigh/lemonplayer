/*
 ============================================================================
 Name		: LemonTangramAppView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __LEMONTANGRAMAPPVIEW_h__
#define __LEMONTANGRAMAPPVIEW_h__

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include <aknviewappui.h>
// CLASS DECLARATION
class CTangImageManager;
class CLemonTangramContainer;

class CLemonTangramAppView : public CAknView
	{
public:
	// New methods
	static CLemonTangramAppView* NewL(const TRect& aRect);
	static CLemonTangramAppView* NewLC(const TRect& aRect);
	virtual ~CLemonTangramAppView();

public:
	// Functions from base classes
	void  HandleCommandL (TInt aCommand) ;
	TUid  Id () const ;
	
//	void Draw(const TRect& aRect) const;
//	virtual void SizeChanged();

private:
	// Constructors
	void ConstructL(const TRect& aRect);
	CLemonTangramAppView();
	
	void DoActivateL (const TVwsViewId &aPrevViewId, TUid aCustomMessageId, const TDesC8 &aCustomMessage) ;
	void DoDeactivate () ;
	
private:
//	CTangImageManager* iManager;
	CLemonTangramContainer* iBWContainer ;
	};

#endif // __LEMONTANGRAMAPPVIEW_h__
// End of File
