/*
 ============================================================================
 Name		: UIMain.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIMain implementation
 ============================================================================
 */

#include "UIMain.h"
#include "UIView.h"
#include "UIXmlParser.h"
#include "MacroUtil.h"
#include "TangramAnimation.h"
#include <eikmenub.h>
#include <LemonPlayer.rsg>
#include "LemonPlayer.hrh"
#include "MainCommand.h"

_LIT(KFile,"c:\\lemonplayer\\defaultui.xml");

CUIMain::CUIMain() :
	iDisplay(NULL), iParser(NULL), iTangram(NULL)
	{
	// No implementation required
	}

CUIMain* CUIMain::NewL(CUIViewData *aData, MUIOperateInterface *aOperate)
	{
	CUIMain* self = new (ELeave) CUIMain;
	CleanupStack::PushL(self);
	self->ConstructL(aData, aOperate);
	CleanupStack::Pop(); // self;
	return self;
	}

CUIMain::~CUIMain()
	{
	SAFE_DELETE(iCommand);
	SAFE_DELETE(iTangram);
	SAFE_DELETE(iDisplay);
	SAFE_DELETE(iParser);
	}

void CUIMain::ConstructL(CUIViewData *aData, MUIOperateInterface *aOperate)
	{
	iData = aData;
	iOperate = aOperate;

	if (iData)
		{
		iDisplay = CUIDisplay::NewL(iData);
		iParser = CUIXmlParser::NewL(iData);
		iParser->LoadFile(KFile);
		}

	iTangram = CTangramAnimation::NewL();
	if (iTangram)
		iTangram->Init();
	iCommand = CMainCommand::NewL();
	}

TBool CUIMain::Update()
	{
	if (iTangram)
		return iTangram->Update();
	return EFalse;
	}

void CUIMain::UpdateDisplay(CWindowGc& gc)
	{
	if (iDisplay)
		{
		iDisplay->Draw(gc);
		}
	}

void CUIMain::UpdateDisplay(CFbsBitGc& aBitGc)
	{
	if (iDisplay)
		{
		iDisplay->Draw(aBitGc);
		if (iTangram)
			iTangram->UpdateDisplay(aBitGc);
		}
	}
TKeyResponse CUIMain::KeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType,
		EAnimationEffectType& aEffect)
	{
	if (aType== EEventKey)
		{
		switch (aKeyEvent.iScanCode)
			{
			case EStdKeyDevice3:
				if (iOperate)
					{
					iOperate->PlayFile();
					}
				return EKeyWasConsumed;
			case EStdKeyUpArrow:
				if (iOperate)
					{
					iOperate->AddVolumeOneBlock();
					}
				return EKeyWasConsumed;
			case EStdKeyDownArrow:
				if (iOperate)
					{
					iOperate->DecVolumeOneBlock();
					}
				return EKeyWasConsumed;
			}
		}
	return EKeyWasNotConsumed;
	}

TBool CUIMain::IsOfferKey()
	{
	return EFalse;
	}

void CUIMain::DynInitMenuBarL(TInt aResourceId, CEikMenuBar* aMenuBar)
	{
	if (aResourceId != R_LEMONPLAYER_PLAY_MENUBAR)
		{
		aMenuBar->SetMenuTitleResourceId(R_LEMONPLAYER_PLAY_MENUBAR);
		if (aMenuBar)
			{
			aMenuBar->StopDisplayingMenuBar();
			}
		if (aMenuBar)
			{
			aMenuBar->TryDisplayMenuBarL();
			}
		}
	}

void CUIMain::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ELemonPlayerCmdAppOpenAll:
			iCommand->OpenAll();
			break;
		case ELemonPlayerCmdAppOpenSingle:
			iCommand->OpenOne();
			break;
		case ELemonPlayerCmdAppOpenAdd:
			iCommand->AddOne();
			break;
		default:
			break;
		}
	}