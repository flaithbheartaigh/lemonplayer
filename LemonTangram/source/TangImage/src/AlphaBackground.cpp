/*
 ============================================================================
 Name		: AlphaBackground.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAlphaBackground implementation
 ============================================================================
 */

#include "AlphaBackground.h"
#include <AknUtils.h>
#include <eikenv.h>
#include <lemontangram.mbg>
#include "LMSvgUtil.h"

#include "MacroUtil.h"
#include "TangFileDefine.h"

#define KRgbJewelBlue	TRgb(0x5F69FF)

#define ALPHA_COLOR   128//256 2^8 最大值
#define ALPHA_SHAWDOW 128  //256 2^8 最大值
#define ALPHA_TEXTURE 128  //256 2^8 最大值

static const TInt BACKGROUND_SHADOW_OFFSET_X=5;
static const TInt BACKGROUND_SHADOW_OFFSET_Y=5;

CAlphaBackground::CAlphaBackground(const TSize& aSize)
:iScreenSize(aSize),iColorBack(KRgbDarkBlue)
	{
	// No implementation required
	}

CAlphaBackground::~CAlphaBackground()
	{
	SAFE_DELETE(iBackground);
	SAFE_DELETE(iTexture);
	}

CAlphaBackground* CAlphaBackground::NewLC(const TSize& aSize)
	{
	CAlphaBackground* self = new (ELeave)CAlphaBackground(aSize);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CAlphaBackground* CAlphaBackground::NewL(const TSize& aSize)
	{
	CAlphaBackground* self=CAlphaBackground::NewLC(aSize);
	CleanupStack::Pop(); // self;
	return self;
	}

void CAlphaBackground::ConstructL()
	{
#ifdef EKA2
	iBackground = LMSvgUtil::GetImageFromResourceL(EMbmLemontangramBackground);
	iTexture = LMSvgUtil::GetImageFromResourceL(EMbmLemontangramTexture);
#else
	TFileName path;
	CompleteWithAppPath(path);
	path.Append(KTangMbmFile);
	iBackground = CEikonEnv::Static()->CreateBitmapL(path,EMbmLemontangramBackground);
	iTexture = CEikonEnv::Static()->CreateBitmapL(path,EMbmLemontangramTexture);
#endif
	AlphaBackWithColor();
	BltGrayTexture();
	BltAlphaTexture();
	}

void CAlphaBackground::AlphaBackWithColor()
{
	TBitmapUtil dest_util(iBackground);
	dest_util.Begin(TPoint(0, 0));

	TInt mx,my;
	mx = Min(iBackground->SizeInPixels().iWidth, iScreenSize.iWidth);
	my = Min(iBackground->SizeInPixels().iHeight,iScreenSize.iHeight);

	for (TInt y=0; y<my; y++)
		for (TInt x=0; x<mx; x++)
			{
				dest_util.SetPos(TPoint(x, y));
				TRgb color = IntToColor(dest_util.GetPixel(),iBackground->DisplayMode());
				dest_util.SetPixel(AlphaColor(color,iColorBack,ALPHA_COLOR,iBackground->DisplayMode()));
			}
	dest_util.End();
}

//draw shadow
void CAlphaBackground::BltGrayTexture()
{
	TBitmapUtil back_util(iBackground);
	TBitmapUtil text_util(iTexture);
	back_util.Begin(TPoint(0, 0));
	text_util.Begin(TPoint(0, 0));
	
	TInt mx,my;
	mx = Min(iBackground->SizeInPixels().iWidth, iScreenSize.iWidth);
	my = Min(iBackground->SizeInPixels().iHeight,iScreenSize.iHeight);

	TInt sx,sy;
	sx = Max(0,mx - iTexture->SizeInPixels().iWidth);
	sy = Max(0,my - iTexture->SizeInPixels().iHeight);

	TInt ox,oy;
	ox = Min(0,mx - iTexture->SizeInPixels().iWidth);
	oy = Min(0,my - iTexture->SizeInPixels().iHeight);

	for (TInt y=my-1-BACKGROUND_SHADOW_OFFSET_Y; y>=sy; y--)
		for (TInt x=sx; x<mx-BACKGROUND_SHADOW_OFFSET_X; x++)
			{
				TInt tx,ty;
				tx = x - sx - ox;
				ty = y - sy - oy;
				TInt vx,vy;
				vx = tx + BACKGROUND_SHADOW_OFFSET_X;
				vy = ty + BACKGROUND_SHADOW_OFFSET_Y;

				if (vx < iTexture->SizeInPixels().iWidth && vy < iTexture->SizeInPixels().iHeight ) {
					text_util.SetPos(TPoint(vx,vy));
					if (text_util.GetPixel() == 1) {
						continue;
					}
				}
				back_util.SetPos(TPoint(x, y));
				text_util.SetPos(TPoint(tx,ty));

				TRgb color1 = IntToColor(back_util.GetPixel(),iBackground->DisplayMode());
				TUint32 c2;
				c2 = text_util.GetPixel();
				
				if (c2 == 1) {
					back_util.SetPos(TPoint(x+BACKGROUND_SHADOW_OFFSET_X, y+BACKGROUND_SHADOW_OFFSET_Y));
					back_util.SetPixel(AlphaColor(color1,KRgbBlack,ALPHA_SHAWDOW,iBackground->DisplayMode()));
				}
			}
	back_util.End();
	text_util.End();
}

void CAlphaBackground::BltAlphaTexture()
{
	TBitmapUtil back_util(iBackground);
	TBitmapUtil text_util(iTexture);
	back_util.Begin(TPoint(0, 0));
	text_util.Begin(TPoint(0, 0));
	
	TInt mx,my;
	mx = Min(iBackground->SizeInPixels().iWidth, iScreenSize.iWidth);
	my = Min(iBackground->SizeInPixels().iHeight,iScreenSize.iHeight);

	TInt sx,sy;
	sx = Max(0,mx - iTexture->SizeInPixels().iWidth);
	sy = Max(0,my - iTexture->SizeInPixels().iHeight);

	TInt ox,oy;
	ox = Min(0,mx - iTexture->SizeInPixels().iWidth);
	oy = Min(0,my - iTexture->SizeInPixels().iHeight);

	for (TInt y=sy; y<my; y++)
		for (TInt x=sx; x<mx; x++)
			{
				back_util.SetPos(TPoint(x, y));
				text_util.SetPos(TPoint(x-sx-ox,y-sy-oy));
				
				TRgb color1 = IntToColor(back_util.GetPixel(),iBackground->DisplayMode());
				TUint32 c2;
				c2 = text_util.GetPixel();
				
				if (c2 == 1) {
					back_util.SetPixel(AlphaColor(color1,KRgbWhite,ALPHA_TEXTURE,iBackground->DisplayMode()));
				}
			}
	back_util.End();
	text_util.End();
}

/**************************************
基本公式:alpha*R(B)+(1-alpha)*R(A)  
为了不产生小数,*256/256;
**************************************/
TRgb CAlphaBackground::AlphaColorToRgb(const TRgb& aColor1,const TRgb& aColor2,const TUint8& aAlpha)
	{
		TUint r,g,b;
		r=( aAlpha*aColor1.Red()   + (256-aAlpha)*aColor2.Red()  ) >>8;
		g=( aAlpha*aColor1.Green() + (256-aAlpha)*aColor2.Green()) >>8;
		b=( aAlpha*aColor1.Blue()  + (256-aAlpha)*aColor2.Blue() ) >>8;

		TRgb color;
		color.SetRed(r);
		color.SetGreen(g);
		color.SetBlue(b);

		return color;
	}
TUint32 CAlphaBackground::AlphaColor(const TRgb& aColor1,const TRgb& aColor2,const TUint8& aAlpha,TDisplayMode aMode)
{
	TRgb rgb = AlphaColorToRgb(aColor1,aColor2,aAlpha);
	return ColorToInt(rgb,aMode);
}
TUint32 CAlphaBackground::ColorToInt(const TRgb& aColor,TDisplayMode aMode)
	{
	TUint32 color;
	switch (aMode)
		{
		case EColor64K:
			color = aColor.Color64K();
			break;
		}
	return color;	
	}
TRgb CAlphaBackground::IntToColor(const TUint32& aColor,TDisplayMode aMode)
	{
	TRgb color;
	switch (aMode)
		{
		case EColor64K:
			color = TRgb::Color64K(aColor);
			break;
		}
	return color;		
	}

void CAlphaBackground::Draw(CBitmapContext& aGc)
{
	aGc.BitBlt(TPoint(0,0),iBackground);
	//aGc.BitBlt(TPoint(0,0),iTexture);
}
