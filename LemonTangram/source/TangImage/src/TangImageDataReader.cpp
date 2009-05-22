/*
 ============================================================================
 Name		: TangImageDataReader.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageDataReader implementation
 ============================================================================
 */

#include <coemain.h>
#include <stdlib.h>

#include "TangImageDataReader.h"
#include "ImageRotator.h"
#include "CommonUtils.h"
#include "ImageElement.h"
#include "DefaultDeclHandler.h"

CTangImageDataReader::CTangImageDataReader(CImageElement** aElements)
:iElements(aElements)
	{
	// No implementation required
	}

CTangImageDataReader::~CTangImageDataReader()
	{
	}

CTangImageDataReader* CTangImageDataReader::NewLC(CImageElement** aElements)
	{
	CTangImageDataReader* self = new (ELeave)CTangImageDataReader(aElements);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTangImageDataReader* CTangImageDataReader::NewL(CImageElement** aElements)
	{
	CTangImageDataReader* self=CTangImageDataReader::NewLC(aElements);
	CleanupStack::Pop(); // self;
	return self;
	}

void CTangImageDataReader::ConstructL()
	{

	}

void CTangImageDataReader::LoadImageDataFileL(const TDesC& aFileName)
	{
//	iRotator = (CImageRotator**)malloc(sizeof(CImageRotator*)*7);
	
	CDefaultDeclHandler *decl = new (ELeave)CDefaultDeclHandler;
	CleanupStack::PushL(decl);

	CSyParser *syParser = CSyParser::NewLC(TPtrC());
	syParser->SetHandler(this);
	syParser->SetHandler(decl);

	RFile file;
	TInt err = file.Open(CCoeEnv::Static()->FsSession(), aFileName, EFileRead);

	if (KErrNone == err)
		{
		CleanupClosePushL(file);
		//²Ù×÷
		TBuf8<512> strBuffer;

		file.Read(strBuffer);
		while (strBuffer.Length() != 0)
			{
			syParser->Parse(strBuffer, EFalse);
			file.Read(strBuffer);
			}
		syParser->Parse(strBuffer, ETrue);
		CleanupStack::PopAndDestroy(1);
		}
	CleanupStack::PopAndDestroy(2);	
	}

//CDefaultDocHandler
void CTangImageDataReader::StartElement(const TQualified& aName,
		const RArray<TAttribute>& aAttributes)
	{
	TInt num = ConvertNameToNumber(aName.iLocalName);
	switch (num)
		{
		case EImageDataTagImg:
			ParseImg(aAttributes);
			break;
		default:
			break;
		}	
	}
void CTangImageDataReader::EndElement(const TQualified& /*aName*/)
	{
	
	}

TInt CTangImageDataReader::ConvertNameToNumber(const TDesC& aName)
	{
	HBufC* name = aName.AllocLC();
	name->Des().LowerCase();
	TInt num = EImageDataTagNone;

	if (name->Compare(KImageDataDomTagImage) == 0)
		{
		num = EImageDataTagImage;
		}
	else
		if (name->Compare(KImageDataDomTagImg) == 0)
			{
			num = EImageDataTagImg;
			}
	CleanupStack::PopAndDestroy();
	return num;
	}

void CTangImageDataReader::ParseImg(const RArray<TAttribute>& aAttributes)
	{
	TInt x,y,degree,index;
	index = -1;
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KImageDataAttrIndex) == 0)
			{
			index = CCommonUtils::StrToInt(attrValue->Des());
			}
		if (attrName->Compare(KImageDataAttrX) == 0)
			{
			x = CCommonUtils::StrToInt(attrValue->Des());
			}
		if (attrName->Compare(KImageDataAttrY) == 0)
			{
			y = CCommonUtils::StrToInt(attrValue->Des());
			}
		if (attrName->Compare(KImageDataAttrDegree) == 0)
			{
			degree = CCommonUtils::StrToInt(attrValue->Des());
			}
		CleanupStack::PopAndDestroy(2);
		}
	if (index > -1 && index < 7)
		{
		iElements[index]->SetPointion(x,y);
		iElements[index]->SetDegree(degree);
		CImageRotator* rotator = CImageRotator::NewL(iElements[index]->GetBitmapLoad(), 
				iElements[index]->GetBitmapRotateAdd(),
				iElements[index]->GetBitmapMaskAdd(),
				degree, KRgbMagenta);
		iElements[index]->SetOffsetX(rotator->GetOffsetX());
		iElements[index]->SetOffsetY(rotator->GetOffsetY());
		delete rotator;
		}
	}
