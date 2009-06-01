/*
 ============================================================================
 Name		: TangImageDataWriter.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageDataWriter implementation
 ============================================================================
 */

#include "TangImageDataWriter.h"
#include "ImageElement.h"
#include "CommonUtils.h"
#include "TangImageXmlDefine.h"
#include <f32file.h>
#include <coemain.h>
#include <s32file.h>

CTangImageDataWriter::CTangImageDataWriter(CImageElement** aElements)
:iElements(aElements)
	{
	// No implementation required
	}

CTangImageDataWriter::~CTangImageDataWriter()
	{
	}

CTangImageDataWriter* CTangImageDataWriter::NewLC(CImageElement** aElements)
	{
	CTangImageDataWriter* self = new (ELeave)CTangImageDataWriter(aElements);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTangImageDataWriter* CTangImageDataWriter::NewL(CImageElement** aElements)
	{
	CTangImageDataWriter* self=CTangImageDataWriter::NewLC(aElements);
	CleanupStack::Pop(); // self;
	return self;
	}

void CTangImageDataWriter::ConstructL()
	{

	}

void CTangImageDataWriter::WriteL(const TDesC& aString, const TBool /*aIsRawData*/)
	{
	HBufC8 *pstrBuffer = CCommonUtils::ConvertToUTF8FromUnicode(aString);
	CleanupStack::PushL(pstrBuffer);

	if (iRequestXml)
		{
		iRequestXml = iRequestXml->ReAllocL(iRequestXml->Length()
				+pstrBuffer->Length());
		iRequestXml->Des().Append(*pstrBuffer);
		}
	else
		{
		iRequestXml = pstrBuffer->AllocL();
		}

	CleanupStack::PopAndDestroy(pstrBuffer);	
	}

void CTangImageDataWriter::SaveDataToFile(const TDesC& aFileName)
	{
	GenerateElementsData();
	
	int pos = aFileName.LocateReverse( '\\');
	if (pos!=KErrNotFound)
		{
		TPtrC dirName = aFileName.Left(pos+1);
		CCoeEnv::Static()->FsSession().MkDirAll(dirName);
		}
		
	RFile file;

	TInt err = file.Replace(CCoeEnv::Static()->FsSession(), aFileName, EFileWrite);
	CleanupClosePushL(file);
	if (KErrNone != err)
		{
		CleanupStack::PopAndDestroy(1); // file
		return;
		}

	RFileWriteStream outputFileStream(file);
	CleanupClosePushL(outputFileStream);
	outputFileStream.WriteL(iRequestXml->Des());

	CleanupStack::PopAndDestroy(2); // outputFileStream, file	
	}

void CTangImageDataWriter::GenerateElementsData()
	{
	CSyGenerator *pXmlGenerator = CSyGenerator::NewLC(*this);

	pXmlGenerator->StartElementL(KImageDataDomTagImage); // <image>

	for(TInt i=0; i<7; i++)
		{
		TBuf<10> temp;
		
		CImageElement* element = iElements[i];
		
		pXmlGenerator->StartElementL(KImageDataDomTagImg); // <img>
		
		temp.AppendNum(element->GetPositionX());	
		pXmlGenerator->SetAttributeL(KImageDataAttrX, temp); // x
		
		temp.Zero();
		temp.AppendNum(element->GetPositionY());
		pXmlGenerator->SetAttributeL(KImageDataAttrY, temp); // y
		
		temp.Zero();
		temp.AppendNum(element->GetDegree());
		pXmlGenerator->SetAttributeL(KImageDataAttrDegree, temp); // degree
		
		temp.Zero();
		temp.AppendNum(i);
		pXmlGenerator->SetAttributeL(KImageDataAttrIndex, temp); // index
		
		pXmlGenerator->EndElementL(); // </img>
		}

	pXmlGenerator->EndElementL(); // </image>

	CleanupStack::PopAndDestroy(pXmlGenerator);	
	}
