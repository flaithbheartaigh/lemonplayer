/*
 ============================================================================
 Name		: UIView.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIView implementation
 ============================================================================
 */

#include "UIView.h"
#include "UIData.h"

#include <eikenv.h>

CUIView::CUIView()
	{
	// No implementation required
	}

CUIView::~CUIView()
	{
	}

CUIView* CUIView::NewLC()
	{
	CUIView* self = new (ELeave)CUIView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIView* CUIView::NewL()
	{
	CUIView* self=CUIView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIView::ConstructL()
	{

	}

//////////////////////////////////////////////

CUIDisplay::CUIDisplay(CUIViewData *aData) :
	iData(aData)
	{
	// No implementation required
	}

CUIDisplay::~CUIDisplay()
	{
	}

CUIDisplay* CUIDisplay::NewLC(CUIViewData *aData)
	{
	CUIDisplay* self = new (ELeave)CUIDisplay(aData);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIDisplay* CUIDisplay::NewL(CUIViewData *aData)
	{
	CUIDisplay* self=CUIDisplay::NewLC(aData);
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIDisplay::ConstructL()
	{

	}

void CUIDisplay::Draw(CWindowGc& gc)
	{
	for (TInt i=KCtrlIndexStop; i<KCtrlIndexTotal; i++)
		{
		DrawControlViewData(gc, i);
		}

	if (iData->GetPlayerState() == KPlayerStateStop || iData->GetPlayerState()
			== KPlayerStatePause)
		{
		DrawControlViewData(gc, KCtrlIndexPlay);
		}
	else
		if (iData->GetPlayerState() == KPlayerStatePlay)
			{
			DrawControlViewData(gc, KCtrlIndexPause);
			}
	DrawControlViewData(gc, KCtrlIndexStop);

	//	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	//	gc.SetPenColor(KRgbRed);
	//	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	//	gc.SetBrushColor( KRgbGray);
	//	gc.UseFont(CEikonEnv::Static()->LegendFont());
	//	TBuf<10> volume;
	//	volume.AppendNum(iData->GetDrawVolume());
	//	gc.DrawText(volume, TPoint(100, 100));
	//	gc.DiscardFont();
	}

void CUIDisplay::Draw(CFbsBitGc& aBitGc)
	{
	for (TInt i=KCtrlIndexStop; i<KCtrlIndexTotal; i++)
		{
		DrawControlViewData(aBitGc, i);
		}

	if (iData->GetPlayerState() == KPlayerStateStop || iData->GetPlayerState()
			== KPlayerStatePause)
		{
		DrawControlViewData(aBitGc, KCtrlIndexPlay);
		}
	else
		if (iData->GetPlayerState() == KPlayerStatePlay)
			{
			DrawControlViewData(aBitGc, KCtrlIndexPause);
			}
	DrawControlViewData(aBitGc, KCtrlIndexStop);
	}

void CUIDisplay::DrawControlViewData(CBitmapContext& aGc, TInt index)
	{
	pControlViewData data = iData->GetData(index);
	TInt dx;
	if (data && data->bitmap && data->isShow)
		{
		switch (data->index)
			{
			case KCtrlIndexPlay:
				if (iData->GetPlayerState() == KPlayerStateStop
						|| iData->GetPlayerState() == KPlayerStatePause)
					{
					aGc.BitBlt(TPoint(data->x, data->y), data->bitmap);
					}
				break;
			case KCtrlIndexPause:
				if (iData->GetPlayerState() == KPlayerStatePlay)
					{
					aGc.BitBlt(TPoint(data->x, data->y), data->bitmap);
					}
				break;
			case KCtrlIndexVolumeSlip:
				dx = (iData->GetDrawVolume())*(data->iSlip);
				aGc.BitBlt(TPoint(data->x+dx, data->y), data->bitmap);
				break;
			case KErrNotFound:
				break;
			default:
				aGc.BitBlt(TPoint(data->x, data->y), data->bitmap);
				break;
			}
		}
	}