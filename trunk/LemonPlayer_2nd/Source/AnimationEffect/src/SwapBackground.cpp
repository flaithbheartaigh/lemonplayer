/*
 ============================================================================
 Name		: SwapBackground.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSwapBackground implementation
 ============================================================================
 */

#include "SwapBackground.h"
#include <eikenv.h>
#include <gdi.h>

#include "MacroUtil.h"

CSwapBackground::CSwapBackground(MEffectSwapNotify* aSwapNotify) :
	iSwapNotify(aSwapNotify)
	{
	// No implementation required
	}

CSwapBackground::~CSwapBackground()
	{
	//	delete iBackground;
	SAFE_DELETE(iSwapBitmap[0]);
	SAFE_DELETE(iSwapBitmap[1]);
	//	delete iSwapBitmap[0];
	//	delete iSwapBitmap[1];
	}

CSwapBackground* CSwapBackground::NewLC(MEffectSwapNotify* aSwapNotify)
	{
	CSwapBackground* self = new (ELeave)CSwapBackground(aSwapNotify);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSwapBackground* CSwapBackground::NewL(MEffectSwapNotify* aSwapNotify)
	{
	CSwapBackground* self=CSwapBackground::NewLC(aSwapNotify);
	CleanupStack::Pop(); // self;
	return self;
	}

void CSwapBackground::ConstructL()
	{
	iSwapBitmap[0] = new (ELeave) CFbsBitmap();
	iSwapBitmap[0]->Create(CEikonEnv::Static()->ScreenDevice()->SizeInPixels(), CEikonEnv::Static()->DefaultDisplayMode());

	iSwapBitmap[1] = new (ELeave) CFbsBitmap();
	iSwapBitmap[1]->Create(CEikonEnv::Static()->ScreenDevice()->SizeInPixels(), CEikonEnv::Static()->DefaultDisplayMode());
	}

void CSwapBackground::InitBitmap()
	{
	//	iBackground = new (ELeave) CFbsBitmap();
	//	iBackground->Create(CEikonEnv::Static()->ScreenDevice()->SizeInPixels(), CEikonEnv::Static()->DefaultDisplayMode());
	//
	//	CFbsBitmapDevice *bitDev = CFbsBitmapDevice::NewL(iBackground);
	//	CleanupStack::PushL(bitDev);
	//	CFbsBitGc *bitGc;
	//	User::LeaveIfError(bitDev->CreateContext(bitGc));
	//	bitGc->SetPenStyle(CGraphicsContext::ENullPen);
	//	bitGc->SetBrushColor( KRgbBlack);
	//	bitGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	//	bitGc->DrawRect(TRect(TSize(CEikonEnv::Static()->ScreenDevice()->SizeInPixels())) );
	//	CleanupStack::PopAndDestroy();//bitGc
	//	delete bitGc;

	CFbsBitmapDevice *bitDev0 = CFbsBitmapDevice::NewL(iSwapBitmap[0]);
	CleanupStack::PushL(bitDev0);
	CFbsBitGc *bitGc0;
	User::LeaveIfError(bitDev0->CreateContext(bitGc0));
	//	bitGc0->BitBlt(TPoint(0,0),iBackground);
	bitGc0->SetPenStyle(CGraphicsContext::ESolidPen);
	bitGc0->SetPenColor(KRgbRed);
	bitGc0->UseFont(CEikonEnv::Static()->LegendFont());
	bitGc0->DrawText(_L("Hello,world."),TPoint(10,10));
	bitGc0->DiscardFont();
	CleanupStack::PopAndDestroy();//bitDev0
	delete bitGc0;

	CFbsBitmapDevice *bitDev1 = CFbsBitmapDevice::NewL(iSwapBitmap[1]);
	CleanupStack::PushL(bitDev1);
	CFbsBitGc *bitGc1;
	User::LeaveIfError(bitDev1->CreateContext(bitGc1));
//	bitGc1->BitBlt(TPoint(0, 0), iBackground);
	bitGc1->SetPenStyle(CGraphicsContext::ESolidPen);
	bitGc1->SetPenColor(KRgbYellow);
	bitGc1->UseFont(CEikonEnv::Static()->LegendFont());
	bitGc1->DrawText(_L("Hell,world."),TPoint(10,10));
	bitGc1->DiscardFont();
	CleanupStack::PopAndDestroy();//bitDev1
	delete bitGc1;

	}

void CSwapBackground::InitSwap(TInt aWidth, TInt aStep, ESwapMode aMode)
	{
	InitMove(aWidth, aStep);
	InitMode(aMode);
	InitDisplay();
	}

void CSwapBackground::InitMove(TInt aWidth, TInt aStep)
	{
	iWidth = aWidth;
	iStep = aStep;
	iOffset = iWidth/iStep;
	}

void CSwapBackground::InitMode(ESwapMode aMode)
	{
	iMode = aMode;

	switch (iMode)
		{
		case KSwapLeftToRight:
			iCurrentPos = 0;
			break;
		case KSwapRightToLeft:
			iCurrentPos = iWidth;
			iOffset = -iOffset;
			break;
		default:
			break;
		}
	}

TBool CSwapBackground::Update()
	{
	iCurrentPos += iOffset;
	if (iMode == KSwapLeftToRight)
		{
		if (iCurrentPos < iWidth)
			{
			return ETrue;
			}
		else
			{
			iCurrentPos = iWidth;
			return EFalse;
			}
		}
	else
		if (iMode == KSwapRightToLeft)
			{
			if (iCurrentPos > 0)
				{
				return ETrue;
				}
			else
				{
				iCurrentPos = 0;
				return EFalse;
				}
			}
		else
			return EFalse;
	}

void CSwapBackground::UpdateDisplay(CFbsBitGc& gc)
	{
	if (iMode == KSwapLeftToRight)
		{
		gc.BitBlt(TPoint(iCurrentPos, 0), iSwapBitmap[0]);
		gc.BitBlt(TPoint(iCurrentPos-iWidth, 0), iSwapBitmap[1]);
		}
	else
		if (iMode == KSwapRightToLeft)
			{
			gc.BitBlt(TPoint(iCurrentPos-iWidth, 0), iSwapBitmap[0]);
			gc.BitBlt(TPoint(iCurrentPos, 0), iSwapBitmap[1]);
			}
	}


void CSwapBackground::InitDisplay()
	{
	iSwapNotify->InitOrigBitmap(iSwapBitmap[0]);

	
	CFbsBitmapDevice *bitDev0 = CFbsBitmapDevice::NewL(iSwapBitmap[1]);
	CleanupStack::PushL(bitDev0);
	CFbsBitGc *bitGc0;
	User::LeaveIfError(bitDev0->CreateContext(bitGc0));

	CleanScreen(*bitGc0);
	iSwapNotify->InitDestBitmap(*bitGc0);

	CleanupStack::PopAndDestroy();//bitDev0
	delete bitGc0;

	}

void CSwapBackground::CleanScreen(CFbsBitGc& aBitGc)
	{
	aBitGc.SetPenStyle(CGraphicsContext::ENullPen);
	aBitGc.SetBrushColor(KRgbWhite);
	aBitGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	TRect rect(TPoint(0, 0), CEikonEnv::Static()->ScreenDevice()->SizeInPixels());
	aBitGc.DrawRect(rect);
	}