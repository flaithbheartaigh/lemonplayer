/*
 ============================================================================
 Name		: DetailListItemDrawer.cpp
 Author	  : JohnLZeng
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDetailListItemDrawer implementation
 ============================================================================
 */

#include "DetailListItemDrawer.h"
#include <EIKENV.H>
#include <eiktxlbm.h> 
#include <aknsskininstance.h> 
#include <aknsutils.h> 
#include "SHPlatform.h"
#include "MacroUtil.h"
#include "UI_Layout.h"
#include "LMSvgUtil.h"
//#include <ScheduleKiller.mbg>

CDetailListItemDrawer::CDetailListItemDrawer(const CEikTextListBox& aListBox) :
	CListItemDrawer(), iListBox(aListBox)
	{
	// 设置图形上下文
	iGc = &CCoeEnv::Static()->SystemGc();
	SetGc(iGc);
	
	InitIcons();
	}

CDetailListItemDrawer::~CDetailListItemDrawer()
	{
	SAFE_DELETE(iDeleteIcon)
	SAFE_DELETE_RPONTERARRAY(iClock)
	}

void CDetailListItemDrawer::DrawActualItem(TInt aItemIndex,
		const TRect& aActualItemRect, TBool aItemIsCurrent,
		TBool aViewIsEmphasized, TBool /*aViewIsDimmed*/, TBool /*aItemIsSelected*/) const
	{
	DrawClock(aItemIndex,aActualItemRect);
	DrawApp(aItemIndex,aActualItemRect);
	if (aItemIsCurrent && aViewIsEmphasized )
		DrawDelButton(aActualItemRect);		
	}

void CDetailListItemDrawer::InitIcons()
	{
	iClock = new RPointerArray<CGulIcon> (4);

	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewZero, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewOne, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewTwo, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewThree, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewFour, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewFive, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewSix, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewSeven, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewEight, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewNine, ETrue));
	iClock->Append(AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),
			KAknsIIDQsnCpClockDigitalNewColon, ETrue));
	
//	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
//	iDeleteIcon = AknsUtils::CreateGulIconL(skin, KAknsIIDQgnMenuUnknownLst, ETrue);
	iDeleteIcon = CGulIcon::NewL();
	CFbsBitmap* bitmap;
	CFbsBitmap* mask;
	LMSvgUtil::GetImageAndMaskFormResourceL(bitmap,mask,
			EMbmSchedulekillerRemove,EMbmSchedulekillerRemove_mask);
	iDeleteIcon->SetBitmap(bitmap);
	iDeleteIcon->SetMask(mask);
	}

void CDetailListItemDrawer::DrawClock(TInt aItemIndex,const TRect& aRect) const
	{
	RPointerArray<TaskInfo>& tasks = SHModel()->GetTaskInfoManager()->GetTaskList();	
	if (aItemIndex >= tasks.Count())
		return;
	
	pTaskInfo info = tasks[aItemIndex];
	RArray<TInt>& array = info->iNumArray;
	
	TInt x, y ,colon;
	TInt count = array.Count();
	
	//冒号对齐
	for (TInt i = 0; i < count; i++)
		{
		TInt index = array[i];		
		if (index >= 10)
			{
			colon = i;
			break;
			}
		}
	
	x = (3-colon) * LIST_DIGITAL_SIZE.iWidth + LIST_DELETE_AREA_SIZE.iWidth + aRect.iTl.iX;
	y = (LIST_APP_TIME_AREA_SIZE.iHeight - LIST_DIGITAL_SIZE.iHeight)/2 + aRect.iTl.iY 
			+ LIST_APP_ICON_AREA_SIZE.iHeight;
	for (TInt i = 0; i < count; i++)
		{
		TInt index = array[i];
		DrawClockDigital(index, TPoint(x, y));
		if (index < 10)
			x += LIST_DIGITAL_SIZE.iWidth;
		else
			x += LIST_COLON_SIZE.iWidth;
		}
	}

void CDetailListItemDrawer::DrawApp(TInt aItemIndex,const TRect& aRect) const
	{
	RPointerArray<TaskInfo>& tasks = SHModel()->GetTaskInfoManager()->GetTaskList();
	if (aItemIndex >= tasks.Count())
		return;
	
	TPtrC name = tasks[aItemIndex]->iName;	
	const CFont* font = SHUI()->GetFont();

	TInt x = (LIST_APP_ICON_AREA_SIZE.iWidth - LIST_APP_ICON_SIZE.iWidth)/2 + aRect.iTl.iX 
		+ LIST_DELETE_AREA_SIZE.iWidth;
	TInt y = (LIST_APP_ICON_AREA_SIZE.iHeight - LIST_APP_ICON_SIZE.iHeight)/2 + aRect.iTl.iY;
	TSize size = LIST_APP_ICON_SIZE;
	CGulIcon* icon = tasks[aItemIndex]->iIcon;
	CFbsBitmap* b1 = icon->Bitmap();
	CFbsBitmap* b2 = icon->Mask();
	AknIconUtils::SetSize(b1, size, EAspectRatioNotPreserved);
	AknIconUtils::SetSize(b2, size, EAspectRatioNotPreserved);
	TPoint point = TPoint(x, y);
	iGc->BitBltMasked(point, b1, size, b2, EFalse);

	TInt fontWidth = font->MeasureText(name);
	TInt fontHeight = font->HeightInPixels();
	x += LIST_APP_ICON_AREA_SIZE.iWidth;
	y = (LIST_APP_NAME_AREA_SIZE.iHeight - fontHeight ) / 2 + aRect.iTl.iY;
	size.iWidth = fontWidth;
	size.iHeight = fontHeight;
	TRect rect = TRect(TPoint(x, y), size);

	TRgb color;
	AknsUtils::GetCachedColor(AknsUtils::SkinInstance(), color,
			KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG1/*EAknsCIQsnLineColorsCG1 */);
	iGc->SetPenStyle(CGraphicsContext::ESolidPen);
	iGc->SetPenColor(color);
	iGc->UseFont(font);
	iGc->DrawText(name, rect, rect.Height() / 2 + font->AscentInPixels() / 2,
			CGraphicsContext::ELeft, 0);
	iGc->DiscardFont();
	}

void CDetailListItemDrawer::DrawClockDigital(TInt& aNumber, const TPoint& aPoint) const
	{
	if (aNumber >= 0)
		{
		TInt index = aNumber;
		if (aNumber > 9)
			index = 10;
		CGulIcon* icon = (*iClock)[index];

		TSize size;
		if (aNumber < 10)
			size = LIST_DIGITAL_SIZE;
		else
			size = LIST_COLON_SIZE;
		CFbsBitmap* b1 = icon->Bitmap();
		CFbsBitmap* b2 = icon->Mask();

		AknIconUtils::SetSize(b1, size, EAspectRatioNotPreserved);
		AknIconUtils::SetSize(b2, size, EAspectRatioNotPreserved);

		iGc->BitBltMasked(aPoint, b1, size, b2, EFalse);
		}
	}

void CDetailListItemDrawer::DrawDelButton(const TRect& aRect) const
	{
	TInt x = (LIST_DELETE_AREA_SIZE.iWidth - LIST_DELETE_ICON_SIZE.iWidth)/2 + aRect.iTl.iX ;
	TInt y = (LIST_DELETE_AREA_SIZE.iHeight - LIST_DELETE_ICON_SIZE.iHeight)/2 + aRect.iTl.iY;
	TPoint point = TPoint(x, y);
	TSize size = LIST_DELETE_ICON_SIZE;
	if (iDeleteIcon)
		{
		CFbsBitmap* b1 = iDeleteIcon->Bitmap();
		CFbsBitmap* b2 = iDeleteIcon->Mask();
		AknIconUtils::SetSize(b1, size, EAspectRatioNotPreserved);
		AknIconUtils::SetSize(b2, size, EAspectRatioNotPreserved);
	
		iGc->BitBltMasked(point, b1, size, b2, EFalse);
		}
	}

