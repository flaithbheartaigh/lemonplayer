/*
 ============================================================================
 Name		: UIManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIManager implementation
 ============================================================================
 */

#include "UIManager.h"
#include <libc\stdlib.h>
#include <mmf\common\mmfcontrollerpluginresolver.h>

#include "MacroUtil.h"
#include "UIData.h"
#include "UIMain.h"
#include "UIList.h"
#include "UIOperateImplement.h"


CUIManager::CUIManager()
	{
	// No implementation required
	}

CUIManager::~CUIManager()
	{
	for (TInt i=0; i<iIndexTotal; i++)
		{
		SAFE_DELETE(iUI[i]);
		}
	
	SAFE_DELETE(iFileLogger);
//	SAFE_DELETE(iData);
	}

CUIManager* CUIManager::NewLC()
	{
	CUIManager* self = new (ELeave)CUIManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIManager* CUIManager::NewL()
	{
	CUIManager* self=CUIManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIManager::ConstructL()
	{
//	iData = CUIViewData::NewL();
	iData = CUIViewData::GetInstance();
	iData->AddSelectFile(_L("c:\\lemonplayer\\voice.wav"));
	iOperate = CUIOperateImplement::NewL(iData);
	
	iFileLogger = CFileLogger::NewL(_L("C:\\UIManager.txt"));
//	ConstructEcom();
	iIndexTotal = 2;
	iIndexCur = 0;
	iUI = (CUIInterface**)malloc(sizeof(CUIInterface*)*iIndexTotal);
	iUI[0] = CUIMain::NewL(iData,iOperate);
	iUI[1] = CUIList::NewL(iData,iOperate);
	}

TBool CUIManager::Update()
	{
	return iUI[iIndexCur]->Update();
	}

void CUIManager::UpdateDisplay(CWindowGc& gc)
	{
	iUI[iIndexCur]->UpdateDisplay(gc);
	}

void CUIManager::UpdateDisplay(CFbsBitGc& aBitGc)
	{
	iUI[iIndexCur]->UpdateDisplay(aBitGc);
	}

TKeyResponse CUIManager::KeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType,
		EAnimationEffectType& aEffect)
	{
	if (iUI[iIndexCur]->IsOfferKey())
		{
		return iUI[iIndexCur]->KeyEventL(aKeyEvent, aType, aEffect);
		}
	else
		{
		if (aType == EEventKey)
			{
			switch (aKeyEvent.iCode)
				{
				case EKeyLeftArrow:
					if (--iIndexCur<0)
						{
						iIndexCur = iIndexTotal-1;
						}
					return EKeyWasConsumed;
				case EKeyRightArrow:
					if (++iIndexCur>=iIndexTotal)
						{
						iIndexCur = 0;
						}
					return EKeyWasConsumed;
				default:
					return iUI[iIndexCur]->KeyEventL(aKeyEvent, aType,aEffect);
				}
			}
		}
	return EKeyWasNotConsumed;
	}

#define PluginUIDArraySize         2 
const TUid PluginUIDArray[] =
	{
		
		{
		0x0116C9D4
		},
		{
		0x101FDA5D
		}
	};

void CUIManager::ConstructEcom()
	{
	for (TInt32 j=0; j<PluginUIDArraySize; j++)
		{
		RImplInfoPtrArray impArray;
		CleanupResetAndDestroyPushL(impArray);
		REComSession::ListImplementationsL(PluginUIDArray[j], impArray);
		iIndexTotal = impArray.Count();
		
		iFileLogger->WriteInt(PluginUIDArray[j].iUid);
		
		for (TInt i = 0; i < impArray.Count(); ++i)
			{
			iFileLogger->WriteStream(impArray[i]->DisplayName());

			_LIT(KText,"Implementation UID=%d");
			TBuf<64> text;
			text.Format(KText, impArray[i]->ImplementationUid());
			iFileLogger->WriteStream(text);
			}
		CleanupStack::PopAndDestroy(1);
		}
	}

void CUIManager::DynInitMenuBarL(TInt aResourceId, CEikMenuBar* aMenuBar)
	{
	iUI[iIndexCur]->DynInitMenuBarL(aResourceId,aMenuBar);
	}

void CUIManager::HandleCommandL(TInt aCommand)
	{
	iUI[iIndexCur]->HandleCommandL(aCommand);
	}