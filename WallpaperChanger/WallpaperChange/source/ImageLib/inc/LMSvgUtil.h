#ifndef YICHAUTILE_H_
#define YICHAUTILE_H_

#ifdef EKA2
#include <akniconutils.h>
#endif
#include <e32std.h>
#include <e32base.h>
#include <FBS.H>


class LMSvgUtil
{
public:
	~LMSvgUtil();
	LMSvgUtil();
	static TInt SetIconSize(CFbsBitmap* aBitmap, const TSize& aSize);
	static CFont* GetFontFromId(TInt aId);
	static CFbsBitmap* GetImageFromResourceL(TInt aId);
	static void GetImageAndMaskFormResourceL(CFbsBitmap*& aBitmap,
			CFbsBitmap*& aBitmapMask,TInt aBitmapId, TInt aMaskId);
};

#endif /*YICHAUTILE_H_*/
