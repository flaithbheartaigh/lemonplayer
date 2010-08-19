/*
 ============================================================================
 Name        : GuiEngine.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CGuiEngine implementation
 ============================================================================
 */

#include <IMCVCODC.H>
#include <ImageConversion.h>
#include <e32math.h>
#include <math.h>

#include <bautils.h>
#include <eikenv.h>

#include "GuiEngine.h"
//#include "PeterMethod.h"
//#include "SetData.h"
//#include "FLogUtils.h"
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

CGuiEngine::CGuiEngine()
{
}

CGuiEngine::~CGuiEngine()
{
}

CGuiEngine* CGuiEngine::NewL()
{
    CGuiEngine* self = new (ELeave) CGuiEngine();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); // self;
    return self;
}

void CGuiEngine::ConstructL()
{
}

CFbsBitmapDevice* CGuiEngine::CreateBitmapDeviceLC(CFbsBitmap& aBitmap)
{
    CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(&aBitmap);
    CleanupStack::PushL(bitmapDevice);
    return bitmapDevice;
}
CFbsBitGc* CGuiEngine::CreateGraphicsContextLC(CFbsBitmapDevice& aBitmapDevice)
{
    CFbsBitGc* graphicsContext = NULL;
    User::LeaveIfError(aBitmapDevice.CreateContext(graphicsContext));
    CleanupStack::PushL(graphicsContext);
    return graphicsContext;
}

CFbsBitmap* CGuiEngine::GetBackGroundL(const TSize aSize,
        const TInt aShadowHeight, const TRgb aBackRgb, const TRgb aFrontRgb,
        const TInt aPos, TBool aShadow)
{
    //    CFbsBitmap* backgroundBmp1;
    //    return backgroundBmp1;
    TBool draw = ETrue;

    CFbsBitmap* backgroundBmp = new (ELeave) CFbsBitmap;
    if (aSize.iWidth == 0 || aSize.iHeight == 0)
        return backgroundBmp;
    User::LeaveIfError(backgroundBmp->Create(aSize, EColor16MU));

    CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(backgroundBmp);
    CleanupStack::PushL(bitmapDevice);

    CFbsBitGc* backgroundGc = NULL;
    User::LeaveIfError(bitmapDevice->CreateContext(backgroundGc));
    CleanupStack::PushL(backgroundGc);

    TInt midPos = aPos; //aSize.iHeight * aPos/320;

    TInt backRgbRed = aBackRgb.Red();
    TInt frontRgbRed = aFrontRgb.Red();
    TInt backRgbGreen = aBackRgb.Green();
    TInt frontRgbGreen = aFrontRgb.Green();
    TInt backRgbBlue = aBackRgb.Blue();
    TInt frontRgbBlue = aFrontRgb.Blue();

    TInt midLineSize = 1;
    TInt upHeight = 80 * aSize.iHeight / 320;
    TInt downHeight = min(aShadowHeight,40 * aSize.iHeight / 320);

    backgroundGc->SetPenColor(aBackRgb);
    backgroundGc->SetPenStyle(CGraphicsContext::ESolidPen);
    backgroundGc->SetBrushColor(aBackRgb);
    backgroundGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
    backgroundGc->DrawRect(aSize);

    backgroundGc->SetPenColor(aBackRgb); // is line color necessary?

    for (TInt i = 0; i < midLineSize; i++)
    {
        if (draw && aShadow)
            backgroundGc->DrawLine(TPoint(0, midPos + i), TPoint(aSize.iWidth,
                    midPos + i));
    }

    TInt k1 = 1000 * (frontRgbRed - backRgbRed) / upHeight;
    TInt k2 = 1000 * (frontRgbGreen - backRgbGreen) / upHeight;
    TInt k3 = 1000 * (frontRgbBlue - backRgbBlue) / upHeight;
    TInt start = midPos - 1 - upHeight;
    TInt end = start + upHeight;

    for (TInt i = start; i <= end; i++)
    {
        TInt tempRed = k1 * (i - start) / 1000 + backRgbRed;
        TInt tempGreen = k2 * (i - start) / 1000 + backRgbGreen;
        TInt tempBlue = k3 * (i - start) / 1000 + backRgbBlue;
        backgroundGc->SetPenColor(TRgb(tempRed, tempGreen, tempBlue));
        if (draw && aShadow)
            backgroundGc->DrawLine(TPoint(0, i), TPoint(aSize.iWidth, i));
    }

    k1 = 1000 * (-frontRgbRed + backRgbRed) / downHeight;
    k2 = 1000 * (-frontRgbGreen + backRgbGreen) / downHeight;
    k3 = 1000 * (-frontRgbBlue + backRgbBlue) / downHeight;
    start = midPos + midLineSize;
    end = start + downHeight;

    for (TInt i = start; i <= end; i++)
    {
        TInt tempRed = k1 * (i - start) / 1000 + frontRgbRed;
        TInt tempGreen = k2 * (i - start) / 1000 + frontRgbGreen;
        TInt tempBlue = k3 * (i - start) / 1000 + frontRgbBlue;
        backgroundGc->SetPenColor(TRgb(tempRed, tempGreen, tempBlue));
        if (draw && aShadow)
            backgroundGc->DrawLine(TPoint(0, i), TPoint(aSize.iWidth, i));
    }

    CleanupStack::PopAndDestroy(2);

    return backgroundBmp;
}

CGulIcon* CGuiEngine::GetIconL(const TDesC& aFileName)
{
    if (!BaflUtils::FileExists(CEikonEnv::Static()->FsSession(), aFileName))
        return CGulIcon::NewL();
    CGulIcon* icon = NULL;
    CFbsBitmap* image = NULL;
    CFbsBitmap* mask = NULL;
    CImageDecoder* converter = NULL;
    //initialise
    TRAPD(error,converter = CImageDecoder::FileNewL(CEikonEnv::Static()->FsSession(),aFileName,CImageDecoder::EOptionAlwaysThread));

    if (error == KErrNone)
    {
        image = new (ELeave) CFbsBitmap();
        image->Create(converter->FrameInfo().iOverallSizeInPixels, EColor64K);
        mask = new (ELeave) CFbsBitmap();
        mask->Create(converter->FrameInfo().iOverallSizeInPixels, EGray2);

        // wait for conversion to complete
        TRequestStatus convStatus;
        // Convert the image into a bitmap
        converter->Convert(&convStatus, *image, *mask);
        User::WaitForRequest(convStatus);
        // clean up
        converter->Cancel();
        icon = CGulIcon::NewL(image, mask);
    }
    delete converter;
    return icon;
}
CFbsBitmap* CGuiEngine::GetBitmapL(const CWsBitmap* aSource)
{
    CFbsBitmap* image = new (ELeave) CFbsBitmap();
    image->Create(aSource->SizeInPixels(), EColor16MU);

    CFbsBitmapDevice* device = CreateBitmapDeviceLC(*image);
    CFbsBitGc* gc = CreateGraphicsContextLC(*device);

    gc->BitBlt(TPoint(0, 0), aSource);
    CleanupStack::PopAndDestroy(2);

    return image;
}
CFbsBitmap* CGuiEngine::GetBitmapL(const TDesC& aFileName)
{
    if (!BaflUtils::FileExists(CEikonEnv::Static()->FsSession(), aFileName))
        return NULL;
    //FLogUtils::Write(_L("get bmp"));
    CFbsBitmap* image = NULL;
    CImageDecoder* converter = NULL;
    TRAPD(error,converter = CImageDecoder::FileNewL(CEikonEnv::Static()->FsSession(),aFileName,CImageDecoder::EOptionAlwaysThread));

    if (error == KErrNone)
    {
        //FLogUtils::Write(_L("no error"));
        image = new (ELeave) CFbsBitmap();
        image->Create(converter->FrameInfo().iOverallSizeInPixels, EColor16MU);

        // wait for conversion to complete
        TRequestStatus convStatus;
        // Convert the image into a bitmap
        converter->Convert(&convStatus, *image);
        User::WaitForRequest(convStatus);
        // clean up
        converter->Cancel();
        //FLogUtils::Write(_L("converter done"));
    }
    delete converter;
    converter = NULL;
    return image;
}

CFbsBitmap* CGuiEngine::GetBitmapL(const TSize aSize, const TRgb aRgb)
{
    CFbsBitmap* bitmap = new (ELeave) CFbsBitmap;
    User::LeaveIfError(bitmap->Create(aSize, EColor64K));
    CFbsBitmapDevice* device = CGuiEngine::CreateBitmapDeviceLC(*bitmap);
    CFbsBitGc* gc = CGuiEngine::CreateGraphicsContextLC(*device);

    gc->SetPenStyle(CGraphicsContext::ENullPen);
    gc->SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc->SetBrushColor(aRgb);
    gc->DrawRect(aSize);

    CleanupStack::PopAndDestroy(2);

    return bitmap;
}
CFbsBitmap* CGuiEngine::GetBitmapL(const TSize aSize, const TRgb aRgb,
        TRect aActiveRect, const TRgb aActiveRgb)
{
    CFbsBitmap* bitmap = new (ELeave) CFbsBitmap;
    User::LeaveIfError(bitmap->Create(aSize, EColor64K));
    CFbsBitmapDevice* device = CreateBitmapDeviceLC(*bitmap);
    CFbsBitGc* gc = CreateGraphicsContextLC(*device);

    gc->SetPenStyle(CGraphicsContext::ENullPen);
    gc->SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc->SetBrushColor(aRgb);
    gc->DrawRect(aSize);

    gc->SetBrushColor(aActiveRgb);
    aActiveRect.Move(-aActiveRect.iTl.iX, 0);
    gc->DrawRoundRect(aActiveRect, TSize(1, 1));

    CleanupStack::PopAndDestroy(2);

    return bitmap;
}

CFbsBitmap* CGuiEngine::GetBitmapFromMBML(TInt aFileNameRes, TInt aId)
{
    TFileName fileName;
    CEikonEnv::Static()->ReadResource(fileName, aFileNameRes);
    return CEikonEnv::Static()->CreateBitmapL(fileName, aId);
}

CFbsBitmap* CGuiEngine::GetShadow(TRgb aRgb, CFbsBitmap* aImage)
{
    if (!aImage)
        return NULL;
    TInt red = aRgb.Blue();
    TInt blue = aRgb.Red();
    aRgb.SetRed(red);
    aRgb.SetBlue(blue);

    TSize inSize = aImage->SizeInPixels();
    TInt shadowWidth = inSize.iWidth;
    TInt shadowHeight = inSize.iHeight / 2;

    CFbsBitmap* shadowCover = new (ELeave) CFbsBitmap();
    shadowCover->Create(inSize + TPoint(0, shadowHeight), EColor16MU);

    aImage->LockHeap();
    shadowCover->LockHeap();

    TUint32* srcPos = (TUint32*) aImage->DataAddress();
    TUint32* desPos = (TUint32*) shadowCover->DataAddress();
    TSize desSize = shadowCover->SizeInPixels();

    for (TInt i = 0; i < shadowCover->SizeInPixels().iHeight; i++)
    {
        for (TInt j = 0; j < shadowCover->SizeInPixels().iWidth; j++)
        {
            // Algorithm here:
            // shadow percentage is a subsection function of j;
            //		P = 1/2		if j< width/2
            //		P = k*(j-w) = (1/2-0)*(w/2-w) * (1-w) = 1 - j/w		if j>width/2
            if (i < inSize.iHeight)
            {
                *(desPos + j + i * desSize.iWidth) = *(srcPos + j + i
                        * inSize.iWidth);
            }
            else
            {
                TUint32 src32 = *(srcPos + j + (inSize.iHeight - 1 - (i
                        - inSize.iHeight)) * inSize.iWidth);
                TUint32 bg32 = aRgb.Value();
                TUint32 des32;
                TUint8 r, g, b;

                if (i - inSize.iHeight < shadowHeight / 2)
                {
                    r = (src32 & 0xFF) / 2 + (bg32 & 0xFF) / 2;
                    g = ((src32 & 0xFF00) / 2 + (bg32 & 0xFF00) / 2) >> 8;
                    b = ((src32 & 0xFF0000) / 2 + (bg32 & 0xFF0000) / 2) >> 16;
                    des32 = r | g << 8 | b << 16;
                }
                else
                {
                    TInt per = (shadowHeight - 1 - (i - inSize.iHeight)) * 1000
                            / shadowHeight;
                    r = (per * static_cast<TUint32> (src32 & 0xFF) + (1000
                            - per) * static_cast<TUint32> (bg32 & 0xFF)) / 1000;
                    g = (per * static_cast<TUint32> ((src32 & 0xFF00) >> 8)
                            + (1000 - per) * static_cast<TUint32> ((bg32
                                    & 0xFF00) >> 8)) / 1000;
                    b = (per * static_cast<TUint32> ((src32 & 0xFF0000) >> 16)
                            + ((1000 - per) * static_cast<TUint32> ((bg32
                                    & 0xFF0000) >> 16))) / 1000;
                    des32 = r | g << 8 | b << 16;
                }
                *(desPos + j + i * desSize.iWidth) = des32;
            }
        }
    }
    aImage->UnlockHeap();
    shadowCover->UnlockHeap();

    return shadowCover;
}

CFbsBitmap* CGuiEngine::GetMaskShadow(TRgb aRgb, CFbsBitmap* aImage)
{
    TInt red = aRgb.Blue();
    TInt blue = aRgb.Red();
    aRgb.SetRed(red);
    aRgb.SetBlue(blue);

    TSize inSize = aImage->SizeInPixels();
    TInt shadowWidth = inSize.iWidth;
    TInt shadowHeight = inSize.iHeight / 2;

    CFbsBitmap* shadowCover = new (ELeave) CFbsBitmap();
    shadowCover->Create(inSize + TPoint(0, shadowHeight), EColor16MU);

    aImage->LockHeap();
    shadowCover->LockHeap();

    TUint32* srcPos = (TUint32*) aImage->DataAddress();
    TUint32* desPos = (TUint32*) shadowCover->DataAddress();
    TSize desSize = shadowCover->SizeInPixels();

    for (TInt i = 0; i < shadowCover->SizeInPixels().iHeight; i++)
    {
        for (TInt j = 0; j < shadowCover->SizeInPixels().iWidth; j++)
        {
            // Algorithm here:
            // shadow percentage is a subsection function of j;
            //		P = 1/2		if j< width/2
            //		P = k*(j-w) = (1/2-0)*(w/2-w) * (1-w) = 1 - j/w		if j>width/2
            if (i < inSize.iHeight)
            {
                *(desPos + j + i * desSize.iWidth) = *(srcPos + j + i
                        * inSize.iWidth);
            }
            else
            {
                *(desPos + j + i * desSize.iWidth) = *(srcPos + j
                        + (inSize.iHeight - (i - inSize.iHeight))
                                * inSize.iWidth);
            }
        }
    }
    aImage->UnlockHeap();
    shadowCover->UnlockHeap();

    return shadowCover;
}

void CGuiEngine::DrawSideBitmap(CBitmapContext* aGc, CFbsBitmap* aSrcBitmap,
        TInt aAngle, TPoint aPos)
{
    TInt type = -1;
    if (aAngle > 90)
    {
        aAngle = 180 - aAngle;
        type = 1;
    }

    TInt W = aSrcBitmap->SizeInPixels().iWidth;
    TInt H = aSrcBitmap->SizeInPixels().iHeight;

    TInt pHeight = AngleToPerHeight(aAngle, 80);
    TInt pWidth = AngleToPerWidth(aAngle);
    TInt minHeight = H * pHeight / 100;
    TInt maxHeight = H * 100 / pHeight;
    TInt width = W * pWidth / 100;
    if (width == 0)
        width = 1;

    TSize sideSize(width, maxHeight);

    CFbsBitmap* sidePic = new (ELeave) CFbsBitmap();
    sidePic->Create(sideSize, EColor16MU);
    CFbsBitmap* sideMask = new (ELeave) CFbsBitmap();
    sideMask->Create(sideSize, EColor16MU);

    TPoint origin = aPos + TPoint(W / 2, H / 2);
    TPoint side = origin - TPoint(width / 2, maxHeight / 2);

    aSrcBitmap->LockHeap();
    sidePic->LockHeap();
    sideMask->LockHeap();

    TUint32* srcPos = (TUint32*) aSrcBitmap->DataAddress();
    TSize srcSize = aSrcBitmap->SizeInPixels();
    TUint32* sidePos = (TUint32*) sidePic->DataAddress();
    TUint32* maskPos = (TUint32*) sideMask->DataAddress();
    TSize maskSize = sideMask->SizeInPixels();

    TUint32* srcCenter = srcPos + W / 2 + (H / 2) * W;
    TUint32* sideCenter = sidePos + width / 2 + (maxHeight / 2) * width;
    TUint32* maskCenter = sideCenter;

    // mask initialization
    TUint32* tempPos = maskPos;
    for (TInt y = 0; y < maxHeight; y++)
    {
        for (TInt x = 0; x < width; x++)
        {
            *(tempPos + x) = KRgbWhite.Value();
            //*(tempPos+x) = 0xFFFF;
        }
        tempPos += width;
    }

    // draw sidePic & maskPic
    //_LIT(Knum,"%d, %d");
    for (TInt x = -width / 2; x < width / 2; x++)
    {
        TInt height = type * (maxHeight - minHeight) * x / width + H; // 2H = minH + maxH;
        TInt startY = -height / 2; // 1 if from left to right, -1 else
        TInt endY = height / 2;

        for (TInt y = startY; y < endY; y++)
        {
            TInt x1 = x * W / width; // x1-0 = W/(w/2)*(x-0)
            TInt y1 = y * H / height;

            *(sidePos + width / 2 + x + (maxHeight / 2 + y) * width) = *(srcPos
                    + W / 2 + x1 + (H / 2 + y1) * W);
            *(maskPos + width / 2 + x + (maxHeight / 2 + y) * width)
                    = KRgbBlack.Value();
        }
    }
    aSrcBitmap->UnlockHeap();
    sidePic->UnlockHeap();
    sideMask->UnlockHeap();

    aGc->BitBltMasked(side, sidePic, sidePic->SizeInPixels(), sideMask, ETrue);

    delete sidePic;
    sidePic = NULL;
    delete sideMask;
    sideMask = NULL;
}

TInt CGuiEngine::AngleToPerHeight(TInt aAngle, TInt aMaxPer)
{
    return (aMaxPer - 100) * aAngle / 90 + 100;
}
TInt CGuiEngine::AngleToPerWidth(TInt aAngle)
{
    TReal src = ((TReal) aAngle) * 3.1416 / 2 / 90;
    TReal des;
    Math::Cos(des, src);
    return (TInt) (des * 100);
}
void CGuiEngine::DrawTextureWithAlpha(CFbsBitmap* aSourceBitmap,
        CFbsBitmap* aDestBitmap, TPoint& aDestPoint, TInt aAlphaValue,
        TBool aIsCenter)
{
    //
    TBitmapUtil tDestbitmapUtil(aDestBitmap);
    tDestbitmapUtil.Begin(aDestPoint);

    //ȡַ
    TUint16* pSource = (TUint16*) aSourceBitmap->DataAddress();
    TUint16* pDest = (TUint16*) aDestBitmap->DataAddress();
    TSize tSourceSize = aSourceBitmap->SizeInPixels();
    TSize tDestSize = aDestBitmap->SizeInPixels();

    TInt iOdd = 0;
    if (tSourceSize.iWidth % 2)
    {
        iOdd = 1;
    }

    if (aIsCenter)
    {
        aDestPoint.iX = aDestPoint.iX - tSourceSize.iWidth / 2;
        aDestPoint.iY = aDestPoint.iY - tSourceSize.iHeight / 2;
    }

    //λ
    TInt iY = aDestPoint.iY;
    TInt iX = aDestPoint.iX;
    if (aDestPoint.iY <= 0)
    {
        iY = 1;
    }
    if (aDestPoint.iX < 0)
    {
        iX = 0;
    }

    pDest = pDest + iX + (iY - 1) * tDestSize.iWidth;

    TInt iHeight, iWidth, iBeginX = 0, iBeginY = 0;

    if (aDestPoint.iX < 0)
    {
        iBeginX = -aDestPoint.iX;
    }

    if (aDestPoint.iY < 0)
    {
        iBeginY = -aDestPoint.iY;
    }

    pSource = pSource + iBeginX + iBeginY * tSourceSize.iWidth;

    if (tDestSize.iHeight > tSourceSize.iHeight + aDestPoint.iY)
    {
        iHeight = tSourceSize.iHeight;
    }
    else
    {
        iHeight = tDestSize.iHeight - aDestPoint.iY;
    }

    if (tDestSize.iWidth > tSourceSize.iWidth + aDestPoint.iX)
    {
        iWidth = tSourceSize.iWidth;
    }
    else
    {
        iWidth = tDestSize.iWidth - aDestPoint.iX;
    }

    for (TInt y = 0; y < iHeight - iBeginY; y++)
    {
        for (TInt x = 0; x < iWidth - iBeginX; x++)
        {
            //жҪMASK
            TInt16 bDest = (static_cast<TInt16> (*(pDest + x) & 0x1F)) * (256
                    - aAlphaValue);
            TInt16 gDest = (static_cast<TInt16> ((*(pDest + x) & 0x07E0) >> 5))
                    * (256 - aAlphaValue);
            TInt16 rDest =
                    (static_cast<TInt16> ((*(pDest + x) & 0xF800) >> 11))
                            * (256 - aAlphaValue);

            TInt16 bSource = (static_cast<TInt16> (*(pSource + x) & 0x1F))
                    * aAlphaValue;
            TInt16 gSource = (static_cast<TInt16> ((*(pSource + x) & 0x07E0)
                    >> 5)) * aAlphaValue;
            TInt16 rSource = (static_cast<TInt16> ((*(pSource + x) & 0xF800)
                    >> 11)) * aAlphaValue;

            *(pDest + x) = (bSource + bDest) >> 8;
            *(pDest + x) |= (((gSource + gDest) >> 8) << 5);
            *(pDest + x) |= (((rSource + rDest) >> 8) << 11);
        }
        pDest = pDest + tDestSize.iWidth;
        pSource = pSource + tSourceSize.iWidth + iOdd;
    }
    // 0000rrrrggggbbbb -> rrrr0000gggg0000bbbb0000 ( 4K to 16M color )
    //*tp = ( ( c & 0xf00 ) << 12 ) + ( ( c & 0x0f0 ) << 8 ) + ( ( c & 0x00f ) << 4 );
    //ͷŶ
    tDestbitmapUtil.End();
}

CFbsBitmap* CGuiEngine::ChangePicSize(CFbsBitmap* aPic, TSize aSize)
{
    TSize size(aSize);
    TSize origSize(aPic->SizeInPixels());

    if (origSize != size)
    {
        CFbsBitmap* newImage = new (ELeave) CFbsBitmap();
        newImage->Create(size, EColor16MU);

        aPic->LockHeap();
        newImage->LockHeap();

        TUint32* srcPos = (TUint32*) aPic->DataAddress();
        TUint32* desPos = (TUint32*) newImage->DataAddress();

        for (TInt i = 0; i < size.iWidth; i++)
        {
            for (TInt j = 0; j < size.iHeight; j++)
            {
                *(desPos + j * size.iWidth + i) = *(srcPos + (j
                        * origSize.iHeight / size.iHeight) * origSize.iWidth
                        + (i * origSize.iWidth / size.iWidth));
            }
        }

        aPic->UnlockHeap();
        newImage->UnlockHeap();

        delete aPic;
        aPic = NULL;

        return newImage;
    }
    return aPic;
}

CFbsBitmap* CGuiEngine::GetSvgBitmapL(const CFbsBitmap* aSource)
{
    if (aSource == NULL)
        return NULL;
    TSize size(aSource->SizeInPixels());
    CFbsBitmap* newImage = new (ELeave) CFbsBitmap();
    newImage->Create(size, EColor64K);

//    FLogUtils::Write(_L8("display mode = "), aSource->DisplayMode());

    aSource->LockHeap();
    newImage->LockHeap();

    TUint16* srcPos = (TUint16*) aSource->DataAddress();
    TUint16* desPos = (TUint16*) newImage->DataAddress();
    //    TUint16* srcPos = static_cast<TUint16*> (*aSource->DataAddress() & 0xffff);
    //    TUint16* desPos = static_cast<TUint16*> (*newImage->DataAddress() & 0xffff);

    for (TInt i = 0; i < size.iWidth; i++)
        for (TInt j = 0; j < size.iHeight; j++)
        {

            *(desPos + j * size.iWidth + i) = *(srcPos + j * size.iWidth + i);
            TUint16 t1 = *(srcPos + j * size.iWidth + i);
            TUint16 t2 = *(desPos + j * size.iWidth + i);
            //            FLogUtils::Write(_L8("src"),t1);
            //            FLogUtils::Write(_L8("src"),t2);
        }

    aSource->UnlockHeap();
    newImage->UnlockHeap();

    return newImage;
}

CFbsBitmap* CGuiEngine::GetBitmapL(const CFbsBitmap* aSource)
{
    if (aSource == NULL)
        return NULL;
    TSize size(aSource->SizeInPixels());
    CFbsBitmap* newImage = new (ELeave) CFbsBitmap();
    newImage->Create(size, EColor16MU);

    aSource->LockHeap();
    newImage->LockHeap();

    TUint32* srcPos = (TUint32*) aSource->DataAddress();
    TUint32* desPos = (TUint32*) newImage->DataAddress();

    for (TInt i = 0; i < size.iWidth; i++)
        for (TInt j = 0; j < size.iHeight; j++)
            *(desPos + j * size.iWidth + i) = *(srcPos + j * size.iWidth + i);

    aSource->UnlockHeap();
    newImage->UnlockHeap();

    return newImage;
}
CGulIcon* CGuiEngine::GetAlphaRectIconL(const TSize aSize, TInt aAlphaPer,
        const TRgb aLightColor, const TRgb aDarkColor, TInt aBorderWidth,
        const TRgb aBorderColor, TInt aRound, TInt aOneSideRound)
{
    TRect rect(aSize);
    if (aOneSideRound == 1)
        rect.iBr.iY += rect.Height();
    else if (aOneSideRound == -1)
        rect.iTl.iY -= rect.Height();

    CFbsBitmap* bitmap = new (ELeave) CFbsBitmap;
    User::LeaveIfError(bitmap->Create(aSize, EColor64K));
    {
        CFbsBitmapDevice* device = CreateBitmapDeviceLC(*bitmap);
        CFbsBitGc* gc = CreateGraphicsContextLC(*device);

        gc->SetPenStyle(CGraphicsContext::ENullPen);
        gc->SetBrushStyle(CGraphicsContext::ESolidBrush);

        gc->SetBrushColor(aLightColor);
        if (aLightColor != aDarkColor)
        {
            TRect highRect(aSize);
            highRect.iBr.iY -= aSize.iHeight / 2;
            gc->DrawRect(highRect);

            TRect lowRect(aSize);
            lowRect.iTl.iY += aSize.iHeight / 2;
            gc->SetBrushColor(aDarkColor);
            gc->DrawRect(lowRect);
        }
        else
        {
            gc->DrawRect(rect);
        }

        if (aBorderWidth > 0)
        {
            TRect bolderRect = rect;
            bolderRect.Shrink(1, 1);
            gc->SetBrushStyle(CGraphicsContext::ENullBrush);
            gc->SetPenStyle(CGraphicsContext::ESolidPen);
            gc->SetPenColor(aBorderColor);
            gc->SetPenSize(TSize(aBorderWidth, aBorderWidth));
            if (aRound > 0)
            {
                gc->DrawRoundRect(bolderRect, TSize(aRound, aRound));
            }
            else
            {
                gc->DrawRect(bolderRect);
            }
            gc->SetPenSize(TSize(1, 1));
        }
        CleanupStack::PopAndDestroy(2);
    }
    CFbsBitmap* mask = new (ELeave) CFbsBitmap;
    User::LeaveIfError(mask->Create(aSize, EGray256));
    {
        CFbsBitmapDevice* device = CreateBitmapDeviceLC(*mask);
        CFbsBitGc* gc = CreateGraphicsContextLC(*device);
        gc->SetPenStyle(CGraphicsContext::ENullPen);
        gc->SetBrushStyle(CGraphicsContext::ESolidBrush);
        gc->SetBrushColor(KRgbBlack);
        gc->DrawRect(rect);
        TInt color = 255 * aAlphaPer / 100;
        gc->SetBrushColor(TRgb(color, color, color));
        if (aRound > 0)
        {
            gc->DrawRoundRect(rect, TSize(aRound, aRound));
        }
        else
        {
            gc->DrawRect(rect);
        }

        CleanupStack::PopAndDestroy(2);
    }
    return CGulIcon::NewL(bitmap, mask);
}
CGulIcon* CGuiEngine::GetAlphaRectIconL(const TSize aSize, TInt aAlphaPer,
        const TRgb aColor)
{
    return CGuiEngine::GetAlphaRectIconL(aSize, aAlphaPer, aColor, aColor, 0,
            aColor, 0, 0);
}

TInt CGuiEngine::DrawTriangleLR(CFbsBitGc& aGc, const TRect& aRect,
        const TRgb& aColor, TBool aLR)
{
    aGc.SetPenStyle(CGraphicsContext::ESolidPen);
    aGc.SetPenColor(aColor);
    TInt x = aLR ? aRect.iBr.iX - aRect.Width() / 3 : aRect.iTl.iX
            + aRect.Width() / 3;
    TInt y1 = aRect.iTl.iY;
    TInt height = aRect.Height() % 2 == 0 ? aRect.Height() - 1 : aRect.Height();
    TInt y2 = y1 + height;
    TInt i = 0;
    for (i = 0; i < aRect.Width(); i++)
    {
        aGc.DrawLine(TPoint(x, y1), TPoint(x, y2));
        y1 += 1;
        y2 -= 1;
        x = aLR ? x - 1 : x + 1;
        if (y1 >= y2)
        {
            break;
        }
    }
    return aLR ? x + i + 1 - aRect.iTl.iX : x - aRect.iTl.iX;
}

void CGuiEngine::DrawTriangleTB(CFbsBitGc& aGc, const TRect& aRect,
        const TRgb& aColor, TBool aTB)
{
    aGc.SetPenStyle(CGraphicsContext::ESolidPen);
    aGc.SetPenColor(aColor);
    TInt y = aTB ? aRect.iBr.iY - aRect.Height() / 3 : aRect.iTl.iY
            + aRect.Height() / 3;
    TInt x1 = aRect.iTl.iX;
    TInt width = aRect.Width();
    TInt x2 = x1 + width;
    for (TInt i = 0; i < aRect.Height(); i++)
    {
        aGc.DrawLine(TPoint(x1, y), TPoint(x2, y));
        x1 += 1;
        x2 -= 1;
        y = aTB ? y - 1 : y + 1;
        if (x1 >= x2)
        {
            break;
        }
    }
}

void CGuiEngine::DrawTrianglePair(CFbsBitGc& aGc, const TRgb& aColor,
        TInt aWidth, TInt aX, TInt aY)
{
    aGc.SetPenStyle(CGraphicsContext::ESolidPen);
    aGc.SetPenColor(aColor);

    TInt S = aWidth / 2;
    TInt l = aX - aWidth / 2 - S;
    TInt r = aX + aWidth / 2 + S;
    TInt h = aY;
    for (TInt j = 0; j < 5; j++)
    {
        aGc.DrawLine(TPoint(l - 5 + j, h - j), TPoint(l, h - j));
        aGc.DrawLine(TPoint(l - 5 + j, h + j), TPoint(l, h + j));
        aGc.DrawLine(TPoint(r, h - j), TPoint(r + 5 - j, h - j));
        aGc.DrawLine(TPoint(r, h + j), TPoint(r + 5 - j, h + j));
    }

}

void CGuiEngine::DrawTriangleRect(CFbsBitGc& aGc, const TRect& aRect,
        const TRgb& aColor)
{
    aGc.SetPenStyle(CGraphicsContext::ESolidPen);
    aGc.SetPenColor(aColor);

    const TInt midX = (aRect.iTl.iX + aRect.iBr.iX) / 2;
    const TInt midY = (aRect.iTl.iY + aRect.iBr.iY) / 2;
    const TInt height = aRect.Height();
    const TInt width = height / 2;
    const TInt leftEnd = aRect.iTl.iX + width;
    const TInt rightEnd = aRect.iBr.iX - width;
    for (TInt j = 0; j < width; j++)
    {
        aGc.DrawLine(TPoint(leftEnd - width + j, midY - j), TPoint(leftEnd,
                midY - j));
        aGc.DrawLine(TPoint(leftEnd - width + j, midY + j), TPoint(leftEnd,
                midY + j));
        aGc.DrawLine(TPoint(rightEnd, midY - j), TPoint(rightEnd + width - j,
                midY - j));
        aGc.DrawLine(TPoint(rightEnd, midY + j), TPoint(rightEnd + width - j,
                midY + j));
    }
}

void CGuiEngine::ResetSvgBitmapL(CFbsBitmap*& aSource)
{
    CFbsBitmap* shd = new (ELeave) CFbsBitmap;
    shd->Create(aSource->SizeInPixels(), EColor16MU);
    CFbsBitmapDevice* shddev = CFbsBitmapDevice::NewL(shd);
    CFbsBitGc* shdgc = NULL;
    shddev->CreateContext(shdgc);
    shdgc->BitBlt(TPoint(), aSource);
    delete shdgc;
    delete shddev;
    delete aSource;
    aSource = shd;
    shd = NULL;
}

CGulIcon* CGuiEngine::CreateSvgIconL(const TDesC& aFileName, TSize aSize,
        TInt aBitmapId, TInt aMaskId, TScaleMode aMode)
{
    CFbsBitmap* bmp = AknIconUtils::CreateIconL(aFileName, aBitmapId);
    AknIconUtils::SetSize(bmp, aSize, aMode);
    CGuiEngine::ResetSvgBitmapL(bmp);

    CFbsBitmap* mask = NULL;
    if (aMaskId != -1)
    {
        mask = AknIconUtils::CreateIconL(aFileName, aMaskId);
        AknIconUtils::SetSize(mask, aSize, aMode);
        CGuiEngine::ResetSvgBitmapL(mask);
    }

    CGulIcon* icon = CGulIcon::NewL(bmp, mask);

    return icon;
}

CFbsBitmap* CGuiEngine::CreateSvgBitmapL(const TDesC& aFileName, TSize aSize,
        TInt aBitmapId)
{
    CFbsBitmap* bmp = AknIconUtils::CreateIconL(aFileName, aBitmapId);
    AknIconUtils::SetSize(bmp, aSize,
            EAspectRatioPreservedAndUnusedSpaceRemoved);
    CGuiEngine::ResetSvgBitmapL(bmp);

    return bmp;
}

//void CGuiEngine::DrawTriangle(CFbsBitGc& aGc, const TRect& aRect,
//		const TRgb& aColor, TBool aTB)
//{
//	aGc.SetPenStyle(CGraphicsContext::ESolidPen);
//	aGc.SetPenColor(aColor);
//	TInt y = aTB ? aRect.iBr.iY - aRect.Height() / 3 : aRect.iTl.iY
//			+ aRect.Height() / 3;
//	TInt x1 = aRect.iTl.iX;
//	TInt width = aRect.Width();
//	TInt x2 = x1 + width;
//	for (TInt i = 0; i < aRect.Height(); i++)
//	{
//		aGc.DrawLine(TPoint(x1, y), TPoint(x2, y));
//		x1 += 1;
//		x2 -= 1;
//		y = aTB ? y - 1 : y + 1;
//		if (x1 >= x2)
//		{
//			break;
//		}
//	}
//
//	TInt l = X - H - width - S;
//	TInt r = X - H + S;
//	TInt h = H + (H + S) * i + H / 2 + H / 4;
//	for (TInt j = 0; j < 5; j++)
//	{
//		aGc ->DrawLine(TPoint(l - 5 + j, h - j), TPoint(l, h - j));
//		aGc ->DrawLine(TPoint(l - 5 + j, h + j), TPoint(l, h + j));
//		aGc ->DrawLine(TPoint(r, h - j), TPoint(r + 5 - j, h - j));
//		aGc ->DrawLine(TPoint(r, h + j), TPoint(r + 5 - j, h + j));
//	}
//}

