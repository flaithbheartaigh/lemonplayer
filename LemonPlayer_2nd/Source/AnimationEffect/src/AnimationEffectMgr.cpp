/*
 ============================================================================
 Name		: AnimationEffectMgr.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAnimationEffectMgr implementation
 ============================================================================
 */

#include "AnimationEffectMgr.h"

#include <eikenv.h>
#include "MacroUtil.h"
#include "SwapBackground.h"
//#include "TangramAnimation.h"

CAnimationEffectMgr::CAnimationEffectMgr(
		MAnimationEffectNotify* aAnimationNotify) :
	iAnimationNotify(aAnimationNotify),iEffectType(KAnimationEffectNone)
	{
	// No implementation required
	}

CAnimationEffectMgr::~CAnimationEffectMgr()
	{
//	SAFE_DELETE(iTangram);
	
	SAFE_DELETE(iSwap);
	SAFE_DELETE(iBitmap);	
	}

CAnimationEffectMgr* CAnimationEffectMgr::NewLC(
		MAnimationEffectNotify* aAnimationNotify)
	{
	CAnimationEffectMgr* self = new (ELeave)CAnimationEffectMgr(aAnimationNotify);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CAnimationEffectMgr* CAnimationEffectMgr::NewL(
		MAnimationEffectNotify* aAnimationNotify)
	{
	CAnimationEffectMgr* self=CAnimationEffectMgr::NewLC(aAnimationNotify);
	CleanupStack::Pop(); // self;
	return self;
	}

void CAnimationEffectMgr::ConstructL()
	{
	iBitmap = new (ELeave) CFbsBitmap();
	iBitmap->Create(CEikonEnv::Static()->ScreenDevice()->SizeInPixels(), 
			CEikonEnv::Static()->DefaultDisplayMode());
	
	iSwap = CSwapBackground::NewL(this);
	
//	iTangram = CTangramAnimation::NewL();
	}

TBool CAnimationEffectMgr::Update()
	{
	TBool ret = EFalse;
	switch (iEffectType)
		{
		case KAnimationEffectSwap:
			ret = iSwap->Update();
			break;
		case KAnimationEffectNormal:
			ret = iAnimationNotify->UpdateAction();
//			ret = iTangram->Update();
			break;
		default:
			break;
		}
	UpdateDisplay();
	return ret;
	}

void CAnimationEffectMgr::Draw(CWindowGc& gc)
	{
	DrawScreen(gc);
	}

void CAnimationEffectMgr::UpdateDisplay()
	{
	CFbsBitmapDevice *bitDev1 = CFbsBitmapDevice::NewL(iBitmap);
	CleanupStack::PushL(bitDev1);
	CFbsBitGc *bitGc1;
	User::LeaveIfError(bitDev1->CreateContext(bitGc1));

	switch (iEffectType)
		{
		case KAnimationEffectSwap:
			iSwap->UpdateDisplay(*bitGc1);
			break;
		case KAnimationEffectNormal:
			iAnimationNotify->UpdateDisplay(*bitGc1);
//			iTangram->UpdateDisplay(*bitGc1);
			break;
		default:
			iAnimationNotify->UpdateDisplay(*bitGc1);
			break;
		}

	CleanupStack::PopAndDestroy();//bitGc
	delete bitGc1;
	}

void CAnimationEffectMgr::StartEffect(EAnimationEffectType aType)
	{
	iEffectType = aType;
	}

void CAnimationEffectMgr::InitSwap(TInt aWidth, TInt aStep, ESwapMode aMode)
	{
	iSwap->InitSwap(aWidth, aStep, aMode);
	}

void CAnimationEffectMgr::InitNormal()
	{
//	iTangram->Init();
	}

void CAnimationEffectMgr::DrawScreen(CWindowGc& gc)
	{
	if (iBitmap!=NULL)
		gc.BitBlt(TPoint(0, 0), iBitmap);
	}

void CAnimationEffectMgr::CleanScreen(CFbsBitGc& aBitGc)
	{
	aBitGc.SetPenStyle(CGraphicsContext::ENullPen);
	aBitGc.SetBrushColor(KRgbWhite);
	aBitGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	TRect rect(TPoint(0, 0), CEikonEnv::Static()->ScreenDevice()->SizeInPixels());
	aBitGc.DrawRect(rect);
	}

void CAnimationEffectMgr::InitOrigBitmap(CFbsBitmap*& aBitmap)
	{
	CopyScreenToBitmap(aBitmap);
	}

void CAnimationEffectMgr::InitDestBitmap(CFbsBitGc& aBitGc)
	{
	if (iAnimationNotify)
		{
		iAnimationNotify->UpdateDisplay(aBitGc);
		}
	}

void CAnimationEffectMgr::CopyScreenToBitmap(CFbsBitmap*& aBitmap)
	{
	TRect rect(TPoint(0, 0), CEikonEnv::Static()->ScreenDevice()->SizeInPixels());
	CEikonEnv::Static()->ScreenDevice()->CopyScreenToBitmap(aBitmap, rect);
	}