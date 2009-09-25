/*
 ============================================================================
 Name		: UIKeyEvent.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIKeyEvent declaration
 ============================================================================
 */

#ifndef UIKEYEVENT_H
#define UIKEYEVENT_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <w32std.h>
#include <coedef.h>
// CLASS DECLARATION
class CUIViewData;
/**
 *  CUIKeyEvent
 * 
 */
enum TUIKeyEventType
	{
	KUIKeyEventNone = 0,
	KUIKeyEventState,
	KUIKeyEventVolume
	};

class CUIKeyEvent : public CBase
	{
public:
	// Constructors and destructor

	~CUIKeyEvent();

	static CUIKeyEvent* NewL(CUIViewData *aData);
	static CUIKeyEvent* NewLC(CUIViewData *aData);
	
public:
	TInt OfferKeyEventL(const TKeyEvent& aKeyEvent,
			TEventCode aType);

private:
	CUIKeyEvent(CUIViewData *aData);
	void ConstructL();
	
private:
	void StateChange();

private:
	CUIViewData *iData;

	};

#endif // UIKEYEVENT_H
