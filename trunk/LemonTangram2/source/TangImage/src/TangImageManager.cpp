/*
 ============================================================================
 Name		: TangImageManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageManager implementation
 ============================================================================
 */
#include <stdlib.h>
#include <eikenv.h>
#include <BAUTILS.H>

#include "TangImageManager.h"

#include <LemonTangram.mbg>
#include <LemonTangram.rsg>

#include "ImageElement.h"
#include "MacroUtil.h"
#include "TangImageDataReader.h"
#include "TangImageDataWriter.h"
#include "ImageRotator.h"
#include "TangElementUtil.h"
#include "Utils.h"
#include "TangImageSave.h"
#include "QueryDlgUtil.h"
#include "TangFileDefine.h"
#include "Configuration.h"
#include "ConfigDefine.h"
#include "TangErrDefine.h"
#include "LemonTangramAppUi.h"
#include "AlphaBackground.h"
#include "Slideshow.h"
#include "TangImageData.h"


CTangImageManager::CTangImageManager() :
	iSelectedState(ESelectedStateChoose),
	iDataArray(NULL),iScreenSave(NULL),
	iElements(NULL),iAcceleration(0),
	iScrollX(0),iScrollY(0)
	{
	// No implementation required
	}

CTangImageManager::~CTangImageManager()
	{
	SAFE_DELETE(iRender);	
	SAFE_DELETE(iScreenSave);
	SAFE_DELETE(iDataArray);
	
	SAFE_DELETE(iImageData);
	}

CTangImageManager* CTangImageManager::NewLC()
	{
	CTangImageManager* self = new (ELeave)CTangImageManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTangImageManager* CTangImageManager::NewL()
	{
	CTangImageManager* self=CTangImageManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CTangImageManager::ConstructL()
	{
	iImageData = CTangImageData::NewL();
	iElements = iImageData->GetElements();
	}

void CTangImageManager::InitOpenGL(CCoeControl* aParentControl, RWindow* aParentWindow)
	{
	iRender = CSlideshow::NewL(aParentControl,aParentWindow);
	iRender->SetRedererState();
	iRender->SetImageData(iImageData);
	}

void CTangImageManager::LoadImageDataFileL(const TDesC& aFileName)
	{
	if (!iDataArray)
		iDataArray = CTangImageDataReader::NewL(iElements);
	iDataArray->LoadImageDataFileL(aFileName);
	}

void CTangImageManager::Draw(CBitmapContext& /*aGc*/) const
	{	
	if (iRender)
		{
	    if ( iRender->GetState() != CSlideshow::ELoadingTextures )
	    	iRender->Render();
		}
	}

TKeyResponse CTangImageManager::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	if (iSelectedState == ESelectedStateChoose)
		{
		return KeyChoose(aKeyEvent, aType);
		}
	else
		if (iSelectedState == ESelectedStateMove)
			{
			return KeyMove(aKeyEvent, aType);
			}
	return EKeyWasNotConsumed;
	}

TKeyResponse CTangImageManager::KeyChoose(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	TInt index;
	TInt iSelectedIndex = iImageData->GetSelected();
	switch (aType)
		{
		case EEventKeyUp:
			switch (aKeyEvent.iScanCode)
				{
				case '2'://up
				case EStdKeyUpArrow://
					index = TangElementUtil::FindNearestVert(iElements,
							iSelectedIndex,EMoveNorth);
//					if (index != iSelectedIndex)
					if (1)	
						{
						iImageData->SetSelected(index);
						}
					return EKeyWasConsumed;					
					break;
				case '8'://down
				case EStdKeyDownArrow://ok
					index = TangElementUtil::FindNearestVert(iElements,
							iSelectedIndex,EMoveSouth);
//					if (index != iSelectedIndex)
					if (1)		
						{
						iImageData->SetSelected(index);
						}
					return EKeyWasConsumed;					
					break;
				case '4'://left
				case EStdKeyLeftArrow://ok
					index = TangElementUtil::FindNearestHori(iElements,
							iSelectedIndex,EMoveWest);
//					if (index != iSelectedIndex)
					if (1)	
						{
						iImageData->SetSelected(index);
						}
					return EKeyWasConsumed;
					break;
				case '6'://right
				case EStdKeyRightArrow://ok
					index = TangElementUtil::FindNearestHori(iElements,
							iSelectedIndex,EMoveEast);
//					if (index != iSelectedIndex)
					if (1)
						{
						iImageData->SetSelected(index);
						}
					return EKeyWasConsumed;
					break;
				case '5':
				case EStdKeyDevice3:
					iSelectedState = ESelectedStateMove;
					return EKeyWasConsumed;
					break;
				}
			break;
			case EEventKey:
				return KeyScroll(aKeyEvent);
				break;
		}
	return EKeyWasNotConsumed;
	}

TKeyResponse CTangImageManager::KeyMove(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	TInt x,y;
	TInt iSelectedIndex = iImageData->GetSelected();
	x = iElements[iSelectedIndex]->GetPositionX();
	y = iElements[iSelectedIndex]->GetPositionY();
	
	switch (aType)
		{
		case EEventKey:
			switch (aKeyEvent.iCode)
				{
				case '2'://up
				case EKeyUpArrow://
					y += OffsetAccel();
					iElements[iSelectedIndex]->SetPointion(x,y);
					return EKeyWasConsumed;					
					break;
				case '8'://down
				case EKeyDownArrow://ok
					y -= OffsetAccel();
					iElements[iSelectedIndex]->SetPointion(x,y);
					return EKeyWasConsumed;					
					break;
				case '4'://left
				case EKeyLeftArrow://ok
					x -= OffsetAccel();
					iElements[iSelectedIndex]->SetPointion(x,y);
					return EKeyWasConsumed;
					break;
				case '6'://right
				case EKeyRightArrow://ok
					x += OffsetAccel();
					iElements[iSelectedIndex]->SetPointion(x,y);
					return EKeyWasConsumed;
					break;		
				case '*':
					Rotate(iSelectedIndex,OffsetDegreeAccel());
					return EKeyWasConsumed;
					break;
				case '#':
					Rotate(iSelectedIndex,-OffsetDegreeAccel());
					return EKeyWasConsumed;
					break;
				default:
					return KeyScroll(aKeyEvent);
					break;
				}
			break;
		case EEventKeyUp:
			switch (aKeyEvent.iScanCode)
				{
				case '2'://up
				case EStdKeyUpArrow://
				case '8'://down
				case EStdKeyDownArrow://ok
				case '4'://left
				case EStdKeyLeftArrow://ok
				case '6'://right
				case EStdKeyRightArrow://ok
					ResetAccel();
					return EKeyWasConsumed;
					break;
				case EStdKeyNkpAsterisk:
				case EStdKeyHash:
					ResetDegreeAccel();
					return EKeyWasConsumed;
					break;
				case '0':
					Flip(iSelectedIndex);
					return EKeyWasConsumed;
					break;
				case '5':
				case EStdKeyDevice3:
					iSelectedState = ESelectedStateChoose;
					return EKeyWasConsumed;
					break;					
				}
			break;
		}
	return EKeyWasNotConsumed;
	}

TKeyResponse CTangImageManager::KeyScroll(const TKeyEvent& aKeyEvent)
{
	switch (aKeyEvent.iScanCode)
	{
	case '3':
		//if (iScrollX > 0) 
			iScrollX -= TANGRAM_SCROLL_MOVE;
		return EKeyWasConsumed;
		break;
	case '1':
		iScrollX += TANGRAM_SCROLL_MOVE;
		return EKeyWasConsumed;
		break;
	case '9':
		//if (iScrollY > 0) 
			iScrollY -= TANGRAM_SCROLL_MOVE;
		return EKeyWasConsumed;
		break;
	case '7':
		iScrollY += TANGRAM_SCROLL_MOVE;
		return EKeyWasConsumed;
		break;
	}
	return EKeyWasNotConsumed;
}

TInt CTangImageManager::OffsetAccel(/*EImageElementState aDirection*/)
{
	if (iAcceleration < TANGRAM_ELEMENT_MAX_ACCELERATION) {
		iAcceleration++;
	}
	return TANGRAM_ELEMENT_MOVE + iAcceleration;
}

void CTangImageManager::ResetAccel()
{
	iAcceleration = 0;
}

TInt CTangImageManager::OffsetDegreeAccel(/*EImageElementState aDirection*/)
{
	if (iDegreeAcceleration < TANGRAM_ELEMENT_MAX_ROTATOE_ACCELERATION) {
		iDegreeAcceleration += TANGRAM_ELEMENT_OFFSET_ROTATOE_ACCELERATION;
	}
	return iDegreeAcceleration;
}

void CTangImageManager::ResetDegreeAccel()
{
	iDegreeAcceleration = 0;
}

void CTangImageManager::Rotate(TInt aIndex, TInt aDegree)
	{
	CImageElement* element = iElements[aIndex];
	int degree = element->GetDegree();
	degree += aDegree;
	TBool flip = element->GetFlip();

	element->SetDegree(degree);

	if (flip) {
		degree = -degree;
	}
	}

void CTangImageManager::Flip(TInt aIndex)
	{
	CImageElement* element = iElements[aIndex];
	
	int degree = element->GetDegree();
	TBool flip = element->GetFlip();
	flip = !flip;
	element->SetFlip(flip);
	}

void CTangImageManager::SaveProcessL()
	{
	if (ShowConfirmationQueryL(R_TEXT_DLG_CONFIRM_SAVE_PROGRESS))
		{
		TInt wait = StartWaitingDlg(R_TEXT_DLG_SAVE_PROGRESS);
		
		CTangImageDataWriter* writer = CTangImageDataWriter::NewLC(iElements);
		TFileName file;
		GetAppPath(file);
		file.Append(KSaveProcessFile);
		writer->SaveDataToFile(file);
		CleanupStack::PopAndDestroy(writer);
		
		EndWaitingDlg(wait);
		
		ShowInfomationDlgL(R_TEXT_DLG_SAVE_PROGRESS_SUCCESS);
		}
	}

void CTangImageManager::ResetProcessL()
	{
	if (ShowConfirmationQueryL(R_TEXT_DLG_CONFIRM_RESET_PROGRESS))
		{
		TInt wait = StartWaitingDlg(R_TEXT_DLG_RESET_PROGRESS);
		
		TFileName path;
		GetAppPath(path);
		path.Append(KFileTangram);
		LoadImageDataFileL(path);
		
		EndWaitingDlg(wait);
		}
	}

void CTangImageManager::OpenProcessL()
	{
	if (ShowConfirmationQueryL(R_TEXT_DLG_CONFIRM_OPEN_PROGRESS))
		{
		TInt wait = StartWaitingDlg(R_TEXT_DLG_OPEN_PROGRESS);
		
		TFileName file;
		GetAppPath(file);
		file.Append(KSaveProcessFile);
		LoadImageDataFileL(file);
		
		EndWaitingDlg(wait);
		}
	}

void CTangImageManager::SaveScreenL()
	{
	TBuf<KMaxName> name;
	name.Copy(KSaveScreenDefault);
	if (ShowInputDlgL(R_TEXT_DLG_SAVE_SCREEN_INPUT_NAME,name))
		{
		TFileName setup;
		GetAppPath(setup);
		setup.Append(KSetupSaveFile);
		CConfiguration* config = CConfiguration::NewL(setup);
		TFileName file;
		config->Get(KCfgSaveFolder,file);
		delete config;
		file.Append(name);
		file.Append(KSaveScreenFormat);	
		
		if (!BaflUtils::FileExists(CCoeEnv::Static()->FsSession(),file) || 
				ShowConfirmationQueryL(R_TEXT_DLG_OVERWRITE_FILE))
			{
				iWaitDlgId = StartWaitingDlg(R_TEXT_DLG_SAVE_SCREEN);
				
				SAFE_DELETE(iScreenSave);
				iScreenSave = CTangImageSave::NewL(file,this);
				Draw(iScreenSave->CreateBufferBitmapL());
				iScreenSave->StartSave();
			}
		}
	}

void CTangImageManager::SaveScreenL(CFbsBitmap *aBitmap)
	{
	TBuf<KMaxName> name;
	name.Copy(KSaveScreenDefault);
	if (ShowInputDlgL(R_TEXT_DLG_SAVE_SCREEN_INPUT_NAME,name))
		{
		TFileName setup;
		GetAppPath(setup);
		setup.Append(KSetupSaveFile);
		CConfiguration* config = CConfiguration::NewL(setup);
		TFileName file;
		config->Get(KCfgSaveFolder,file);
		delete config;
		file.Append(name);
		file.Append(KSaveScreenFormat);	
		
		if (!BaflUtils::FileExists(CCoeEnv::Static()->FsSession(),file) || 
				ShowConfirmationQueryL(R_TEXT_DLG_OVERWRITE_FILE))
			{
				iWaitDlgId = StartWaitingDlg(R_TEXT_DLG_SAVE_SCREEN);
				
				SAFE_DELETE(iScreenSave);
				iScreenSave = CTangImageSave::NewL(file,this);				
				iScreenSave->StartSave(aBitmap);
			}
		}	
	}

void CTangImageManager::SaveComplete()
	{
	EndWaitingDlg(iWaitDlgId);
	
	ShowInfomationDlgL(R_TEXT_DLG_SAVE_SCREEN_SUCCESS);
	}

TInt CTangImageManager::GetConvertDown()
	{
	return iRender->GetState() == CSlideshow::ERunning;
	}
