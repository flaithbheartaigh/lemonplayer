/*
 ============================================================================
 Name		: TangImageData.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageData implementation
 ============================================================================
 */

#include "TangImageData.h"

#include <stdlib.h>
#include <eikenv.h>
#include <BAUTILS.H>

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

CTangImageData::CTangImageData()
	{
	// No implementation required
	}

CTangImageData::~CTangImageData()
	{
	iLayer.Reset();
	iLayer.Close();
	
	SAFE_DELETE_ARRAY(iElements,EImageNumber);
	}

CTangImageData* CTangImageData::NewLC()
	{
	CTangImageData* self = new (ELeave) CTangImageData();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTangImageData* CTangImageData::NewL()
	{
	CTangImageData* self = CTangImageData::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CTangImageData::ConstructL()
	{
	iElements = (CImageElement**)malloc(sizeof(CImageElement*) * EImageNumber);
	for (TInt i=0; i<EImageNumber; i++)
		{
		iElements[i] = CImageElement::NewL();
		iLayer.InsertL(i,0);
		}
	}

void CTangImageData::SetSelected(const TInt& aIndex)
	{
	iElements[iSelectedIndex]->SetSelected(EFalse);
	iElements[aIndex]->SetSelected(ETrue);						
	iSelectedIndex = aIndex;	
	
	ChangeLayer();
	}

void CTangImageData::ChangeLayer()
	{
	TInt index = iLayer.Find(iSelectedIndex);
	
	if (index != KErrNotFound)
		{
		iLayer.Remove(index);
		iLayer.Append(iSelectedIndex);
		}
	}
