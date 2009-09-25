/*
 ============================================================================
 Name		: UIInterface.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIInterface declaration
 ============================================================================
 */

#ifndef UIINTERFACE_H
#define UIINTERFACE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <coedef.h>
#include <ECom.h>
// CLASS DECLARATION
class CUIViewData;
class CEikMenuBar;
#include "UIOperateInterface.h"
#include "AnimationEffectDefine.h"
/**
 *  CUIInterface
 * 
 */
class CUIInterface : public CBase
	{
public:
	static CUIInterface* NewL();
	static CUIInterface* NewL(const TDesC8& aMatch,CUIViewData *aData=NULL,
			MUIOperateInterface *aOperate=NULL);
	virtual ~CUIInterface();
	
public:
	virtual TBool Update() = 0;
	virtual void UpdateDisplay(CWindowGc& gc) = 0;
	virtual void UpdateDisplay(CFbsBitGc& aBitGc) = 0;
	virtual TKeyResponse KeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType,
			EAnimationEffectType& aEffect) = 0;
	virtual TBool IsOfferKey() = 0;
	virtual void DynInitMenuBarL(TInt aResourceId, CEikMenuBar* aMenuBar) = 0;
	virtual void HandleCommandL(TInt aCommand) = 0;
	
private:
	TUid iDestructorIDKey;
protected:
	CUIViewData 		*iData;
	MUIOperateInterface *iOperate;
	};

#include "UIInterface.inl"

#endif // UIINTERFACE_H
