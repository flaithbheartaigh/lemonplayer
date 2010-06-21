/*
 ============================================================================
 Name		: MsgDataTimeControl.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMsgDataTimeControl declaration
 ============================================================================
 */

#ifndef MSGDATATIMECONTROL_H
#define MSGDATATIMECONTROL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <eikmfne.h> 
#include "MsgExpandableControl.h"
// CLASS DECLARATION

/**
 *  CMsgDataTimeControl
 * 
 */
class CMsgDataTimeControl : public CMsgExpandableControl
	{
public:
	// Constructors and destructor

	~CMsgDataTimeControl();
	
	CMsgDataTimeControl(MMsgBaseControlObserver& aBaseControlObserver);

public:
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	
	void ConstructFromResourceL( TInt aResourceId );
	TTime GetDateTime() ;
	void SetDateTime(const TTime& aTime);

protected:
	// from CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void SizeChanged();	
    void FocusChanged( TDrawNow aDrawNow );
    void SetContainerWindowL( const CCoeControl& aContainer );
    void Draw( const TRect& aRect ) const;
    
//    void SetAndGetSizeL( TSize& aSize );
    
    
    
private:
	CEikTimeAndDateEditor* iTimeAndDateEditor;
//	CEikTimeEditor* iTimeAndDateEditor;

	};

#endif // MSGDATATIMECONTROL_H
