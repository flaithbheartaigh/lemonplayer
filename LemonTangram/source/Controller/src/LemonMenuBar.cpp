/*
 ============================================================================
 Name		: LemonMenuBar.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenuBar implementation
 ============================================================================
 */

#include "LemonMenuBar.h"
#include <LemonTangram.rsg>
#include <StringLoader.h> 
#include "LemonTangramAppUi.h"
#include "MacroUtil.h"
#include <LemonTangram.mbg>
#include "LMSvgUtil.h"

//_LIT(KFileMbm,"z:\\resource\\apps\\LemonTangram.mbm");

CLemonMenuBar::CLemonMenuBar()
:iTextColor(KRgbBlack)
	{
	// No implementation required
	}

CLemonMenuBar::~CLemonMenuBar()
	{
	SAFE_DELETE(iFrame);
	}

CLemonMenuBar* CLemonMenuBar::NewLC()
	{
	CLemonMenuBar* self = new (ELeave)CLemonMenuBar();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLemonMenuBar* CLemonMenuBar::NewL()
	{
	CLemonMenuBar* self=CLemonMenuBar::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CLemonMenuBar::ConstructL()
	{
	HBufC* text1 = StringLoader::LoadLC(R_TEXT_OPTION_LEFT_HIDE);
	iOptionText[EOptionLeftHide].Append(text1->Des());
	CleanupStack::PopAndDestroy(text1);
	
	HBufC* text2 = StringLoader::LoadLC(R_TEXT_OPTION_RIGHT_HIDE);
	iOptionText[EOptionRightHide].Append(text2->Des());
	CleanupStack::PopAndDestroy(text2);
	
	HBufC* text3 = StringLoader::LoadLC(R_TEXT_OPTION_LEFT_ACTIVE);
	iOptionText[EOptionLeftActive].Append(text3->Des());
	CleanupStack::PopAndDestroy(text3);
	
	HBufC* text4 = StringLoader::LoadLC(R_TEXT_OPTION_RIGHT_ACTIVE);
	iOptionText[EOptionRightActive].Append(text4->Des());
	CleanupStack::PopAndDestroy(text4);
	
	iFrame = LMSvgUtil::GetImageFromResourceL(EMbmLemontangramBottom);
	MUIMgr* uiMgr = STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->GetUIMgr();
	LMSvgUtil::SetIconSize(iFrame, uiMgr->BottomBarSize());
	//iFrame = CEikonEnv::Static()->CreateBitmapL(KFileMbm,EMbmLemontangramBottomsvg);
	}

void CLemonMenuBar::Draw(CFbsBitGc& gc,TBool aActive)
	{
	MUIMgr* uiMgr = STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->GetUIMgr();
		
	if (iFrame)
		gc.BitBlt(uiMgr->BottomBarPos(),iFrame);
	
	gc.SetPenStyle( CGraphicsContext::ESolidPen );
	gc.SetPenColor(iTextColor);
	gc.UseFont(uiMgr->iSysFont);
	
	if (aActive)
		{
		gc.DrawText(iOptionText[EOptionLeftActive],uiMgr->BottomLeftOption());
		gc.DrawText(iOptionText[EOptionRightActive],uiMgr->BottomRightOption());
		}	
	else
		{
		gc.DrawText(iOptionText[EOptionLeftHide],uiMgr->BottomLeftOption());
		gc.DrawText(iOptionText[EOptionRightHide],uiMgr->BottomRightOption());
		}
	gc.DiscardFont();
	}
