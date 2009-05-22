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

#include <LemonTangram.mbg>
#include <eikenv.h>
_LIT(KFileMbm,"z:\\resource\\apps\\LemonTangram.mbm");

CTangImageManager::CTangImageManager():
iConverted(0),iConvertDown(0)
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
	for(TInt i=0; i<EImageNumber; i++)
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
	for(TInt i=0; i<EImageNumber; i++)
		{
		iElements[i]->SetState(KImageStateLoad);
		iElements[i]->SetBitmapLoad(array[i]);
		}
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
	for(TInt i=0; i<EImageNumber; i++)
		{
		if (iElements[i])
			iElements[i]->Draw(aGc);
		}
	}

void CTangImageManager::Rotate(TInt aIndex,TInt aDegree)
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
			element->GetBitmapRotateAdd(),
			element->GetBitmapMaskAdd(),
			degree, KRgbMagenta);
	element->SetOffsetX(rotator->GetOffsetX());
	element->SetOffsetY(rotator->GetOffsetY());
	delete rotator;
	}
