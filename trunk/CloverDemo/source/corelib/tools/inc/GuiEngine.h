/*
 ============================================================================
 Name        : GuiEngine.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CGuiEngine declaration
 ============================================================================
 */

#ifndef GUIENGINE_H
#define GUIENGINE_H

// INCLUDES
#include <w32std.h>
#include <fbs.h>
#include <GDI.H>
#include <e32base.h>
#include <ImageConversion.h>
#include <GULICON.H>
#include <FBS.H>
#include <AknIconUtils.h>

// CLASS DECLARATION
class CPeterElement;
struct TScrollPara;
struct TTextStyle;


class CGuiEngine: public CBase
{
public:
    // Constructors and destructor
    CGuiEngine();

    ~CGuiEngine();
    static CGuiEngine* NewL();

    static CFbsBitmapDevice* CreateBitmapDeviceLC(CFbsBitmap& aBitmap);
    static CFbsBitGc* CreateGraphicsContextLC(CFbsBitmapDevice& aBitmapDevice);
    static CGulIcon* GetIconL(const TDesC& aFileName);

    static CFbsBitmap* GetBitmapL(const CWsBitmap* aSource);
    static CFbsBitmap* GetBitmapL(const CFbsBitmap* aSource);
    static CFbsBitmap* GetSvgBitmapL(const CFbsBitmap* aSource);
    static CFbsBitmap* GetBitmapL(const TDesC& aFileName);
    static CFbsBitmap* GetBitmapL(const TSize aSize, const TRgb aRgb);
    static CFbsBitmap* GetBitmapL(const TSize aSize, const TRgb aRgb,
            TRect aActiveRect, const TRgb aActiveRgb);
    static CFbsBitmap* GetBitmapFromMBML(TInt aFileNameRes, TInt aId);

    static CFbsBitmap* GetShadow(TRgb aRgb, CFbsBitmap* aImage);
    static CFbsBitmap* GetMaskShadow(TRgb aRgb, CFbsBitmap* aImage);
    static void DrawSideBitmap(CBitmapContext* aGc, CFbsBitmap* aSrcBitmap,
            TInt aAngle, TPoint aPos);
    static void DrawTextureWithAlpha(CFbsBitmap* aSourceBitmap,
            CFbsBitmap* aDestBitmap, TPoint& aDestPoint, TInt aAlphaValue,
            TBool aIsCenter);

    static TInt AngleToPerHeight(TInt aAngle, TInt aMaxPer);
    static TInt AngleToPerWidth(TInt aAngle);

    static CFbsBitmap* GetBackGroundL(const TSize aSize,
            const TInt aShadowHeight, const TRgb aBackRgb,
            const TRgb aFrontRgb, const TInt aPos, TBool aShadow);
    static CFbsBitmap* ChangePicSize(CFbsBitmap* aPic, TSize aSize);
    static CGulIcon* GetAlphaRectIconL(const TSize aSize, TInt aAlphaPer,
            const TRgb aLightColor, const TRgb aDarkColor, TInt aBorderWidth,
            const TRgb aBorderColor, TInt aRound, TInt aOneSideRound);
    static CGulIcon* GetAlphaRectIconL(const TSize aSize, TInt aAlphaPer,
            const TRgb aColor);

    static TInt CGuiEngine::DrawTriangleLR(CFbsBitGc& aGc, const TRect& aRect,
            const TRgb& aColor, TBool aLR);
    static void DrawTriangleTB(CFbsBitGc& aGc, const TRect& aRect,
            const TRgb& aColor, TBool aTB);
    static void DrawTrianglePair(CFbsBitGc& aGc, const TRgb& aColor,
            TInt aWidth, TInt aX, TInt aY);
    static void DrawTriangleRect(CFbsBitGc& aGc, const TRect& aRect,
            const TRgb& aColor);

    static void ResetSvgBitmapL(CFbsBitmap*& aSource);
    static CGulIcon* CreateSvgIconL(const TDesC& aFileName, TSize aSize,
            TInt aBitmapId, TInt aMaskId = -1, TScaleMode aMode =
                EAspectRatioPreservedAndUnusedSpaceRemoved);
    static CFbsBitmap* CreateSvgBitmapL(const TDesC& aFileName, TSize aSize,
            TInt aBitmapId);

private:
    void ConstructL();

};

#endif // GuiEngine_H
