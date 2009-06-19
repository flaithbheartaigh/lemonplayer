/*
 ============================================================================
 Name		: TangImageManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageManager implementation
 ============================================================================
 */

#include "TangImageManager.h"
#include "ImageElement.h"
#include "MacroUtil.h"
#include <stdlib.h>
#include "TangImageDataReader.h"
#include "TangImageDataWriter.h"
#include "ImageRotator.h"
#include "TangElementUtil.h"
#include "Utils.h"
#include "TangImageSave.h"
#include "QueryDlgUtil.h"

#include <LemonTangram.mbg>
#include <eikenv.h>
#include <LemonTangram.rsg>
#include "TangFileDefine.h"
#include "Configuration.h"
#include "ConfigDefine.h"
#include <BAUTILS.H>


CTangImageManager::CTangImageManager() :
	iConverted(0), iConvertDown(0), iSelectedState(ESelectedStateChoose),
	iDataArray(NULL),iScreenSave(NULL)
	{
	// No implementation required
	}

CTangImageManager::~CTangImageManager()
	{
	SAFE_DELETE(iScreenSave);
	SAFE_DELETE(iDataArray);
	SAFE_DELETE(iBitmapArray);
	SAFE_DELETE_ARRAY(iBitmapFocus,EBitmapFocusTotal);
	SAFE_DELETE_ARRAY(iElements,EImageNumber);
	
	iLayer.Reset();
	iLayer.Close();
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
	iElements = (CImageElement**)malloc(sizeof(CImageElement*) * EImageNumber);
	for (TInt i=0; i<EImageNumber; i++)
		iElements[i] = CImageElement::NewL();
	
	iBitmapFocus = (CFbsBitmap**)malloc(sizeof(CFbsBitmap*) * EBitmapFocusTotal);
	}
void CTangImageManager::ConvertedOne()
	{
	iConverted++;
	}

void CTangImageManager::ConvertComplete()
	{
	CFbsBitmap** array = iBitmapArray->GetBitmapArray();
	int count = iBitmapArray->GetBitmapCount();
	//if (count != EImageNumber)
	//	return;
	for (TInt i=0; i<EImageNumber; i++)
		{
		iElements[i]->SetState(KImageStateLoad);
		iElements[i]->SetBitmapLoad(array[i]);
		iElements[i]->SetIndex(i);
		
		iLayer.Append(i);
		}
	iElements[6]->SetSelected(ETrue);
	iSelectedIndex = 6;
	iConvertDown = 1;
	
	//
	iBitmapFocus[EBitmapActive] = array[7];
	CTransparentBitmap *tran1 =  CTransparentBitmap::NewL(iBitmapFocus[EBitmapActive],
			iBitmapFocus[EBitmapActiveMask],KRgbMagenta);
	delete tran1;
	iBitmapFocus[EBitmapFocus] = array[8];
	CTransparentBitmap *tran2 =  CTransparentBitmap::NewL(iBitmapFocus[EBitmapFocus],
			iBitmapFocus[EBitmapFocusMask],KRgbMagenta);
	delete tran2;
	}

void CTangImageManager::LoadImageFromFileL(const TDesC& aFileName)
	{
	iBitmapArray = CImageArrayReader::NewL();
	iBitmapArray->SetNotify(this);

	iBitmapArray->LoadDataFromFile(aFileName);
	}

void CTangImageManager::LoadImageDataFileL(const TDesC& aFileName)
	{
	if (!iDataArray)
		iDataArray = CTangImageDataReader::NewL(iElements);
	iDataArray->LoadImageDataFileL(aFileName);
	}

void CTangImageManager::Draw(CBitmapContext& aGc)
	{
	//EImageNumber
	for(TInt i=0; i<iLayer.Count(); i++)
		{
		TInt index = iLayer[i];
		if (iElements[index])
			iElements[index]->Draw(aGc);
		}
//	for (TInt i=0; i<EImageNumber; i++)
//		{
//		if (iElements[i])
//			iElements[i]->Draw(aGc);
//		}
	
	CImageElement* element = iElements[iSelectedIndex];
	TInt x = element->GetPositionX();
	TInt y = element->GetPositionY();
	if (iSelectedState == ESelectedStateChoose)
		{
		x -= (iBitmapFocus[EBitmapFocus]->SizeInPixels().iWidth >> 1);
		y -= (iBitmapFocus[EBitmapFocus]->SizeInPixels().iHeight >> 1);
		TRect rect( TPoint( 0,0 ),iBitmapFocus[EBitmapFocus]->SizeInPixels() );
		aGc.BitBltMasked(TPoint(x,y),iBitmapFocus[EBitmapFocus],
				rect,iBitmapFocus[EBitmapFocusMask],ETrue);
		}
	else if (iSelectedState == ESelectedStateMove)
		{
		x -= (iBitmapFocus[EBitmapActive]->SizeInPixels().iWidth >> 1);
		y -= (iBitmapFocus[EBitmapActive]->SizeInPixels().iHeight >> 1);
		TRect rect( TPoint( 0,0 ),iBitmapFocus[EBitmapActive]->SizeInPixels() );
		aGc.BitBltMasked(TPoint(x,y),iBitmapFocus[EBitmapActive],
				rect,iBitmapFocus[EBitmapActiveMask],ETrue);		
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
	switch (aType)
		{
		case EEventKeyUp:
			switch (aKeyEvent.iScanCode)
				{
				case '2'://up
				case EStdKeyUpArrow://
					index = TangElementUtil::FindNearestVert(iElements,
							iSelectedIndex,EMoveNorth);
					if (index != iSelectedIndex)
						{
						iElements[iSelectedIndex]->SetSelected(EFalse);
						iElements[index]->SetSelected(ETrue);						
						iSelectedIndex = index;		
						ChangeLayer();
						}
					return EKeyWasConsumed;					
					break;
				case '8'://down
				case EStdKeyDownArrow://ok
					index = TangElementUtil::FindNearestVert(iElements,
							iSelectedIndex,EMoveSouth);
					if (index != iSelectedIndex)
						{
						iElements[iSelectedIndex]->SetSelected(EFalse);
						iElements[index]->SetSelected(ETrue);						
						iSelectedIndex = index;		
						ChangeLayer();
						}
					return EKeyWasConsumed;					
					break;
				case '4'://left
				case EStdKeyLeftArrow://ok
					index = TangElementUtil::FindNearestHori(iElements,
							iSelectedIndex,EMoveWest);
					if (index != iSelectedIndex)
						{
						iElements[iSelectedIndex]->SetSelected(EFalse);
						iElements[index]->SetSelected(ETrue);
						iSelectedIndex = index;
						ChangeLayer();
						}
					return EKeyWasConsumed;
					break;
				case '6'://right
				case EStdKeyRightArrow://ok
					index = TangElementUtil::FindNearestHori(iElements,
							iSelectedIndex,EMoveEast);
					if (index != iSelectedIndex)
						{
						iElements[iSelectedIndex]->SetSelected(EFalse);
						iElements[index]->SetSelected(ETrue);						
						iSelectedIndex = index;		
						ChangeLayer();
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
		}
	return EKeyWasNotConsumed;
	}

TKeyResponse CTangImageManager::KeyMove(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	TInt x,y;
	x = iElements[iSelectedIndex]->GetPositionX();
	y = iElements[iSelectedIndex]->GetPositionY();
	
	switch (aType)
		{
		case EEventKey:
			switch (aKeyEvent.iCode)
				{
				case '2'://up
				case EKeyUpArrow://
					y -= TANGRAM_ELEMENT_MOVE_Y;
					iElements[iSelectedIndex]->SetPointion(x,y);
					return EKeyWasConsumed;					
					break;
				case '8'://down
				case EKeyDownArrow://ok
					y += TANGRAM_ELEMENT_MOVE_Y;
					iElements[iSelectedIndex]->SetPointion(x,y);
					return EKeyWasConsumed;					
					break;
				case '4'://left
				case EKeyLeftArrow://ok
					x -= TANGRAM_ELEMENT_MOVE_X;
					iElements[iSelectedIndex]->SetPointion(x,y);
					return EKeyWasConsumed;
					break;
				case '6'://right
				case EKeyRightArrow://ok
					x += TANGRAM_ELEMENT_MOVE_Y;
					iElements[iSelectedIndex]->SetPointion(x,y);
					return EKeyWasConsumed;
					break;		
				case '*':
					Rotate(iSelectedIndex,TANGRAM_ELEMENT_ROTATOE_DEGREE);
					return EKeyWasConsumed;
					break;
				case '#':
					Rotate(iSelectedIndex,-TANGRAM_ELEMENT_ROTATOE_DEGREE);
					return EKeyWasConsumed;
					break;
				}
			break;
		case EEventKeyUp:
			switch (aKeyEvent.iScanCode)
				{
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

void CTangImageManager::Rotate(TInt aIndex, TInt aDegree)
	{
	CImageElement* element = iElements[aIndex];
	CFbsBitmap* rota = element->GetBitmapRotate();
	CFbsBitmap* mask = element->GetBitmapMask();
	int degree = element->GetDegree();
	degree += aDegree;

	SAFE_DELETE(rota);
	SAFE_DELETE(mask);

	element->SetDegree(degree);

	CImageRotator* rotator = CImageRotator::NewL(element->GetBitmapLoad(),
			element->GetBitmapRotateAdd(), element->GetBitmapMaskAdd(), degree, 
			KRgbMagenta);
	element->SetOffsetX(rotator->GetOffsetX());
	element->SetOffsetY(rotator->GetOffsetY());
	delete rotator;
	}

void CTangImageManager::SaveProcess()
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

void CTangImageManager::ResetProcess()
	{
	if (ShowConfirmationQueryL(R_TEXT_DLG_CONFIRM_RESET_PROGRESS))
		{
		TInt wait = StartWaitingDlg(R_TEXT_DLG_RESET_PROGRESS);
		
		LoadImageDataFileL(KFileTangram);
		
		EndWaitingDlg(wait);
		}
	}

void CTangImageManager::OpenProcess()
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

void CTangImageManager::SaveScreen()
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

void CTangImageManager::ChangeLayer()
	{
	TInt index = iLayer.Find(iSelectedIndex);
	
	if (index != KErrNotFound)
		{
		iLayer.Remove(index);
		iLayer.Append(iSelectedIndex);
		}
	}

void CTangImageManager::SaveComplete()
	{
	EndWaitingDlg(iWaitDlgId);
	
	ShowInfomationDlgL(R_TEXT_DLG_SAVE_SCREEN_SUCCESS);
	}
