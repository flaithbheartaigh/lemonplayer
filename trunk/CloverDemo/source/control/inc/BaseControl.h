#ifndef BASECONTROL_H_
#define BASECONTROL_H_

#include <e32base.h>
#include <coecntrl.h>
#include <GDI.H>

#include "AnimationFrame.h"

class CBaseControl : public CBase
{
public:
	CBaseControl()
		{
		iVisible = ETrue;
		iAnimation = NULL;
		}
	virtual ~CBaseControl()
		{
		}
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/)
		{
		return EKeyWasNotConsumed;
		}
	
	virtual void Draw(CBitmapContext& /*gc*/) const
		{	
		}
	
	virtual TInt GetHeight()
		{
		return 0;
		}
	virtual TInt GetHeight(TInt /*aWidth*/)
		{
		return 0;
		}
	virtual TInt GetWidth()
		{
		return 0;
		}

	virtual void SetFocus(TBool isFocus)
		{
		iFocus = isFocus;
		}
	TBool IsFocused() const
		{
		return iFocus;
		}

	void SetVisible(TBool aVisible)
		{
		iVisible = aVisible;
		}
	TBool IsVisible() const
		{
		return iVisible;
		}

	virtual void SetRect(const TRect &aRect)
		{
		iPosition = aRect.iTl;
		iSize = aRect.Size();
		}
	
	virtual void ReSize(const TRect &aRect)
		{
		iPosition = aRect.iTl;
		iSize = aRect.Size();
		}

	TRect Rect() const
		{
		return TRect(iPosition, iSize);
		}
	
	virtual void SetAnimation(CAnimationFrame* aAnimation) 
		{
		iAnimation = aAnimation;
		}

protected:
        TBool  iFocus;
        TPoint iPosition;
        TSize  iSize;       
        TBool  iVisible;
        
        CAnimationFrame* iAnimation;		//not own
};

#endif /*BASECONTROL_H_*/
