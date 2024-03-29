/*
 * ============================================================================
 *  Name     : CLemonPlayerContainer from LemonPlayerContainer.h
 *  Part of  : LemonPlayer
 *  Created  : 17.09.2008 by zengcity
 *  Implementation notes:
 *     Initial content was generated by Series 60 Application Wizard.
 *  Version  :
 *  Copyright: 
 * ============================================================================
 */

// INCLUDE FILES
#include "LemonTangramContainer.h"

#include <coemain.h>
#include "MacroUtil.h"
#include "TangImageManager.h"
#include <LemonTangram.mbg>
#include <eikenv.h>
#include "LemonMenu.h"
#include "LemonTangramAppUi.h"
#include "LemonTangram.hrh"
#include "LMSvgUtil.h"
#include <StringLoader.h> 
#include <LemonTangram.rsg>
#include "Utils.h"
#include "TangFileDefine.h"
#include "Configuration.h"
#include "ConfigDefine.h"
#include "bautils.h"
#include "TangErrDefine.h"
// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CLemonPlayerContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//

void CLemonTangramContainer::ConstructL(const TRect& aRect)
	{
	iWidth = aRect.Width();
	iHeight = aRect.Height();
	CAnimationStruct::ConstructL();
	
	iDoubleBufferGc = NULL;
	iDoubleBufferDevice = NULL;
	iDoubleBufferBmp = NULL;
	CreateDoubleBufferBitmapL();
	
	iGameState = EGameStateLogo;
	StateLogoInit();

	SetTimerTick(1000000);
	StartTimer();
	
	CreateWindowL();
	}

// Destructor
CLemonTangramContainer::~CLemonTangramContainer()
	{
	SAFE_DELETE(iLogo);
	
	SAFE_DELETE(iMenu);	
	SAFE_DELETE(iManager);
	
	SAFE_DELETE(iDoubleBufferGc);
	SAFE_DELETE(iDoubleBufferDevice);
	SAFE_DELETE(iDoubleBufferBmp);
	}

// ---------------------------------------------------------
// CLemonPlayerContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CLemonTangramContainer::SizeChanged()
	{
	// TODO: Add here control resize code etc.
	}

// ---------------------------------------------------------
// CLemonPlayerContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CLemonTangramContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CLemonPlayerContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CLemonTangramContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CLemonPlayerContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CLemonTangramContainer::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	// TODO: Add your drawing code here
	// example code...
//	gc.SetPenStyle(CGraphicsContext::ENullPen);
//	gc.SetBrushColor(KRgbGray);
//	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
//	gc.DrawRect(aRect);

	gc.SetBrushColor(KRgbWhite);
	gc.Clear();
		
	if (iDoubleBufferBmp)
		{	//title
			gc.BitBlt(TPoint(0,0),	iDoubleBufferBmp);
		}
	}

// ---------------------------------------------------------
// CLemonPlayerContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CLemonTangramContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

TKeyResponse CLemonTangramContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{	
	return StateKey(aKeyEvent,aType);
	}

void CLemonTangramContainer::CreateDoubleBufferBitmapL()
{
	SAFE_DELETE(iDoubleBufferGc);
	SAFE_DELETE(iDoubleBufferDevice);
	SAFE_DELETE(iDoubleBufferBmp);
	
	TDisplayMode displayMode = CEikonEnv::Static()->ScreenDevice()->DisplayMode();
	
	iDoubleBufferBmp = new(ELeave) CFbsBitmap();
	CleanupStack::PushL(iDoubleBufferBmp);
	TInt nErr =	iDoubleBufferBmp->Create(TSize(iWidth,iHeight),displayMode);
	if (nErr != KErrNone)
	{
		CleanupStack::PopAndDestroy(iDoubleBufferBmp);
		iDoubleBufferBmp =NULL;
		return;
	}
	// 创建离屏位图设备。
	iDoubleBufferDevice = CFbsBitmapDevice::NewL(iDoubleBufferBmp);	
	CleanupStack::PushL(iDoubleBufferDevice);
	nErr = iDoubleBufferDevice->CreateContext(iDoubleBufferGc);
	if (nErr != KErrNone)
	{
		CleanupStack::PopAndDestroy(2);
		iDoubleBufferDevice =NULL;
		iDoubleBufferBmp =NULL;
		return;
	}	
	iDoubleBufferGc->SetBrushColor(KRgbWhite);
	iDoubleBufferGc->SetBrushStyle(CGraphicsContext::ENullBrush);
	iDoubleBufferGc->Clear();
	CleanupStack::Pop(2);
}
TBool CLemonTangramContainer::Tick()
	{
	StateLoop();
	return ETrue;
	}

void CLemonTangramContainer::Update()
	{	
	if (iDoubleBufferGc) 
		{
			StateDisplay(*iDoubleBufferGc);
			DrawNow();
		}
	}

void CLemonTangramContainer::HandleCommandL(TInt /*aCommand*/)
	{
	}

void CLemonTangramContainer::StateLoop()
	{
	switch (iGameState)
		{
		case EGameStateLogo:
			StateLogoLoop();
			break;
		case EGameStateInit:
			StateInitLoop();
			break;
		case EGameStateMain:
			StateMainLoop();
			break;
		default:
			break;
		}
	}
void CLemonTangramContainer::StateDisplay(CFbsBitGc& gc)
	{
	gc.SetBrushColor(KRgbWhite);
	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
	gc.Clear();
	switch (iGameState)
		{
		case EGameStateLogo:
			StateLogoDisplay(gc);
			break;
		case EGameStateInit:
			StateInitDisplay(gc);
			break;
		case EGameStateMain:
			StateMainDisplay(gc);
			break;
		default:
			break;
		}	
	}

void CLemonTangramContainer::StateChange(TGameState aState)
{
	switch (iGameState)
		{
		case EGameStateLogo:
			StateLogoRelease();
			break;
		case EGameStateInit:
			StateInitRelease();
			break;
		case EGameStateMain:
			StateMainRelease();
			break;
		default:
			break;
		}

	iGameState = aState;

	switch (iGameState)
		{
		case EGameStateLogo:
			StateLogoInit();
			break;
		case EGameStateInit:
			StateInitInit();
			break;
		case EGameStateMain:
			StateMainInit();
			break;
		default:
			break;
		}
}

TKeyResponse CLemonTangramContainer::StateKey(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	switch (iGameState)
		{
		case EGameStateLogo:
			break;
		case EGameStateInit:
			break;
		case EGameStateMain:
			return StateMainKey(aKeyEvent,aType);
			break;
		default:
			break;
		}	
	return EKeyWasNotConsumed;
	}

void CLemonTangramContainer::StateLogoInit()
	{
	iLogoState = 0;
#ifdef EKA2
	iLogo = LMSvgUtil::GetImageFromResourceL(EMbmLemontangramLog);
#else
	TFileName path;
	CompleteWithAppPath(path);
	path.Append(KTangMbmFile);
	iLogo = CEikonEnv::Static()->CreateBitmapL(path,EMbmLemontangramLog);
#endif
	}

void CLemonTangramContainer::StateLogoRelease()
{
}

void CLemonTangramContainer::StateLogoLoop()
	{
	if (iLogoState++ > 0)
		{
		StateChange(EGameStateInit);
		StopTimer();
		SetTimerTick(100000);
		StartTimer();
		}
	}

void CLemonTangramContainer::StateLogoDisplay(CFbsBitGc& gc)
	{
	if (iLogo)
		{
		int x = (iWidth-iLogo->SizeInPixels().iWidth) >> 1;
		int y = (iHeight-iLogo->SizeInPixels().iHeight)>> 1;
		gc.BitBlt(TPoint(x,y),iLogo);
		}
	}

void CLemonTangramContainer::StateInitInit()
	{
	InitManager();
	InitMenu();
	}

void CLemonTangramContainer::StateInitRelease()
{
	SAFE_DELETE(iLogo);
}

void CLemonTangramContainer::StateInitLoop()
	{
	iLoadState = iManager->GetConvertedNum();
	
	if (iManager->GetConvertDown())
		{
		TFileName path;
		GetAppPath(path);
		path.Append(KFileTangram);

		TRAPD(err,iManager->LoadImageDataFileL(path))
		LTERR(err,ETLErrLoadPicDataXml,ETLErrSerious)

		StateChange(EGameStateMain);
		}
	}
void CLemonTangramContainer::StateInitDisplay(CFbsBitGc& gc)
	{
	if (iLogo)
		{
		int x = (iWidth-iLogo->SizeInPixels().iWidth) >> 1;
		int y = (iHeight-iLogo->SizeInPixels().iHeight)>> 1;
		gc.BitBlt(TPoint(x,y),iLogo);
		}	
	}

void CLemonTangramContainer::StateMainInit()
	{
	}

void CLemonTangramContainer::StateMainRelease()
{
	SAFE_DELETE(iMenu);
	SAFE_DELETE(iManager);
}
void CLemonTangramContainer::StateMainLoop()
	{}
void CLemonTangramContainer::StateMainDisplay(CFbsBitGc& gc)
	{
	iManager->Draw(gc);
	iMenu->Draw(gc);
	}

TKeyResponse CLemonTangramContainer::StateMainKey(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	TKeyResponse res = iMenu->OfferKeyEventL(aKeyEvent,aType);
	if (res == EKeyWasNotConsumed)
		return iManager->OfferKeyEventL(aKeyEvent,aType);
	else
		return res;
	}

void CLemonTangramContainer::HandMenuCommand(TInt aCommandId)
	{
	TInt err;
	switch (aCommandId)
		{
		case ECommandSaveProcess:
			SaveProcess();
			break;
		case ECommandReset:
			ResetProcess();
			break;
		case ECommandOpenProcess:
			OpenProcess();
			break;
		case ECommandSnapshot:
			SaveScreen();
			break;
		case ECommandSetting:
		case ECommandHelp:
		case ECommandExit:
			STATIC_CAST(CLemonTangramAppUi*,iEikonEnv->AppUi())->HandleCommandL(aCommandId);
			break;			
		default:
			//STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->Exit();
			break;
		}
	}

void CLemonTangramContainer::InitManager()
{
	TRAPD(err,iManager = CTangImageManager::NewL())

	LTERR(err,ETLErrLoadPicture,ETLErrSerious);
	
	TFileName setup;
	GetAppPath(setup);
	setup.Append(KSetupSaveFile);
	CConfiguration* config; 
	TRAP(err,config = CConfiguration::NewL(setup))
	if (err == KErrNone)
	{
		TFileName img;
		config->Get(KCfgSkinChoose,img);
		delete config;
	
		TRAP(err,iManager->LoadImageFromFileL(img))
	}
	else 
	{
		//配置文件丢失 读取默认
		LTERRFUN(ETLWarnConfigLost,ETLErrWarning);
		err == KErrNone;
		TRAP(err,iManager->LoadImageFromFileL(KNullDesC))
	}

	LTERR(err,ETLErrLoadPicFileXml,ETLErrSerious);
}

void CLemonTangramContainer::InitMenu()
{
	TRAPD(err,iMenu = CLemonMenu::NewL(this))
	LTERR(err,ETLErrLoadMenu,ETLErrSerious)
	
	TFileName file;
	GetAppPath(file);
	HBufC* textResource = StringLoader::LoadLC(R_RES_MAIN_MENU);
	file.Append(textResource->Des());
	CleanupStack::PopAndDestroy(textResource);

	TRAP(err,iMenu->LoadMenuL(file))
	LTERR(err,ETLErrLoadMenu,ETLErrSerious)
}


void CLemonTangramContainer::SaveProcess()
{
	TRAPD(err,iManager->SaveProcessL())
	LTERR(err,ETLWarnSaveProcess,ETLErrWarning);
}
void CLemonTangramContainer::ResetProcess()
{
	TRAPD(err,iManager->ResetProcessL())
	LTERR(err,ETLWarnResetProcess,ETLErrWarning);
}
void CLemonTangramContainer::OpenProcess()
{
	TRAPD(err,iManager->OpenProcessL())
	LTERR(err,ETLWarnOpenProcess,ETLErrWarning);
}
void CLemonTangramContainer::SaveScreen()
{
	TRAPD(err,iManager->SaveScreenL())
	LTERR(err,ETLWarnSaveScreen,ETLErrWarning);
}
// End of File  
