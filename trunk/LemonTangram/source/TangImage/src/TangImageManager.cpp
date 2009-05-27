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
#include "ImageRotator.h"
#include "TangElementUtil.h"

#include <LemonTangram.mbg>
#include <eikenv.h>
_LIT(KFileMbm,"z:\\resource\\apps\\LemonTangram.mbm");

CTangImageManager::CTangImageManager() :
	iConverted(0), iConvertDown(0), iSelectedState(ESelectedStateChoose)
	{
	// No implementation required
	}

CTangImageManager::~CTangImageManager()
	{
	SAFE_DELETE(iDataArray);
	SAFE_DELETE(iBitmapArray);
	SAFE_DELETE_ARRAY(iElements,EImageNumber);
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

	}
void CTangImageManager::ConvertedOne()
	{
	iConverted++;
	}

void CTangImageManager::ConvertComplete()
	{
	CFbsBitmap** array = iBitmapArray->GetBitmapArray();
	int count = iBitmapArray->GetBitmapCount();
	if (count != EImageNumber)
		return;
	for (TInt i=0; i<EImageNumber; i++)
		{
		iElements[i]->SetState(KImageStateLoad);
		iElements[i]->SetBitmapLoad(array[i]);
		iElements[i]->SetIndex(i);
		}
	iElements[6]->SetSelected(ETrue);
	iSelectedIndex = 6;
	iConvertDown = 1;
	}

void CTangImageManager::LoadImageFromFileL(const TDesC& aFileName)
	{
	iBitmapArray = CImageArrayReader::NewL();
	iBitmapArray->SetNotify(this);

	iBitmapArray->LoadDataFromFile(aFileName);
	}

void CTangImageManager::LoadImageDataFileL(const TDesC& aFileName)
	{
	iDataArray = CTangImageDataReader::NewL(iElements);
	iDataArray->LoadImageDataFileL(aFileName);
	}

void CTangImageManager::Draw(CBitmapContext& aGc)
	{
	//EImageNumber
	for (TInt i=0; i<EImageNumber; i++)
		{
		if (iElements[i])
			iElements[i]->Draw(aGc);
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
				case EKeyUpArrow://
					index = TangElementUtil::FindNearestVert(iElements,
							iSelectedIndex,EMoveNorth);
					if (index != iSelectedIndex)
						{
						iElements[iSelectedIndex]->SetSelected(EFalse);
						iElements[index]->SetSelected(ETrue);						
						iSelectedIndex = index;		
						}
					return EKeyWasConsumed;					
					break;
				case '8'://down
				case EKeyDownArrow://ok
					index = TangElementUtil::FindNearestVert(iElements,
							iSelectedIndex,EMoveSouth);
					if (index != iSelectedIndex)
						{
						iElements[iSelectedIndex]->SetSelected(EFalse);
						iElements[index]->SetSelected(ETrue);						
						iSelectedIndex = index;		
						}
					return EKeyWasConsumed;					
					break;
				case '4'://left
				case EKeyLeftArrow://ok
					index = TangElementUtil::FindNearestHori(iElements,
							iSelectedIndex,EMoveWest);
					if (index != iSelectedIndex)
						{
						iElements[iSelectedIndex]->SetSelected(EFalse);
						iElements[index]->SetSelected(ETrue);
						iSelectedIndex = index;
						}
					return EKeyWasConsumed;
					break;
				case '6'://right
				case EKeyRightArrow://ok
					index = TangElementUtil::FindNearestHori(iElements,
							iSelectedIndex,EMoveEast);
					if (index != iSelectedIndex)
						{
						iElements[iSelectedIndex]->SetSelected(EFalse);
						iElements[index]->SetSelected(ETrue);						
						iSelectedIndex = index;		
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
