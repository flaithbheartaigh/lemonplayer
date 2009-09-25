#ifndef ANIMATIONEFFECTABSTRACT_
#define ANIMATIONEFFECTABSTRACT_

#include <bitstd.h>

class MAnimationEffectNotify
	{
public:
	virtual TBool UpdateAction() = 0;
	virtual void UpdateDisplay(CFbsBitGc& aBitGc) = 0;
	};

class MEffectSwapNotify
	{
public:
	virtual void InitOrigBitmap(CFbsBitmap*& aBitmap) = 0;
	virtual void InitDestBitmap(CFbsBitGc& aBitGc) = 0;
	};

#endif /*ANIMATIONEFFECTABSTRACT_*/
