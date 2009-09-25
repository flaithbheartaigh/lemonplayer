/*
 ============================================================================
 Name		: UIDataSerialize.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIDataSerialize implementation
 ============================================================================
 */

#include "UIDataSerialize.h"

#include "UIData.h"
#include <f32file.h>
#include <coemain.h>
#include "FileUtils.h"
#include "CommonUtils.h"

CUIDataSerialize::CUIDataSerialize(CUIViewData *aData):iXmlBuffer(NULL)
	{
	// No implementation required
	iData = aData;
	}

CUIDataSerialize::~CUIDataSerialize()
	{
	ClearBuffer();
	}

CUIDataSerialize* CUIDataSerialize::NewLC(CUIViewData *aData)
	{
	CUIDataSerialize* self = new (ELeave)CUIDataSerialize(aData);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIDataSerialize* CUIDataSerialize::NewL(CUIViewData *aData)
	{
	CUIDataSerialize* self=CUIDataSerialize::NewLC(aData);
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIDataSerialize::ConstructL()
	{
	}

TInt CUIDataSerialize::LoadFile(const TDesC& aFileName)
	{
	CSyParser *syParser = CSyParser::NewLC(TPtrC());
	syParser->SetHandler(this);

	RFile file;
	TInt err = file.Open(CCoeEnv::Static()->FsSession(), aFileName, EFileRead);

	if (KErrNone == err)
		{
		CleanupClosePushL(file);
		//²Ù×÷
		TBuf8<1024> ptr;
		file.Read(ptr);
		syParser->Parse(ptr, ETrue);
		CheckData();
		CleanupStack::PopAndDestroy(1);
		}
	CleanupStack::PopAndDestroy(syParser);
	}

TInt CUIDataSerialize::WriteFile(const TDesC& aFileName)
	{	
	ClearBuffer();
	GenerateXml();
	WriteDesToFile(aFileName);
	}

void CUIDataSerialize::WriteDesToFile(const TDesC& aFileName)
	{
	CFileUtils::WriteFile(aFileName,iXmlBuffer->Des());
	}

void CUIDataSerialize::GenerateXml()
	{
	CSyGenerator *pXmlGenerator = CSyGenerator::NewLC(*this);
		GenerateFileList(pXmlGenerator);
		GeneratePlayModel(pXmlGenerator);
		GenerateCurSelectFile(pXmlGenerator);
		GenerateNextSelectFile(pXmlGenerator);
		GenerateVolume(pXmlGenerator);
	//	pXmlGenerator->StartElementL(KDataXmlTagFileList); // <request>
	//	pXmlGenerator->SetAttributeL(KDataXmlAtrValue, _L("")); // url
	//	pXmlGenerator->CharactersL(_L(""));
	//	pXmlGenerator->EndElementL(); // </url>
		CleanupStack::PopAndDestroy(pXmlGenerator);
	}

void CUIDataSerialize::GenerateFileList(CSyGenerator *pXmlGenerator)
	{
	CDesCArrayFlat *iArray = iData->GetSelectFileList();
	if (!iArray)
		{
		return;
		}
	for(TInt i=0; i<iArray->Count(); i++)
		{
		TPtrC value = (*iArray)[i];
		pXmlGenerator->StartElementL(KDataXmlTagFileList); // <filelist>
		pXmlGenerator->SetAttributeL(KDataXmlAtrValue, value); // 
		pXmlGenerator->EndElementL(); // </filelist>
		}
	}
void CUIDataSerialize::GeneratePlayModel(CSyGenerator *pXmlGenerator)
	{
	TBuf<4> value;
	value.AppendNum(iData->GetPlayModel());
	pXmlGenerator->StartElementL(KDataXmlTagPlayModel); // <playmode>
	pXmlGenerator->SetAttributeL(KDataXmlAtrValue, value); // 
	pXmlGenerator->EndElementL(); // </playmode>
	}
void CUIDataSerialize::GenerateCurSelectFile(CSyGenerator *pXmlGenerator)
	{
	TBuf<4> value;
	value.AppendNum(iData->GetCurSelectFile());
	pXmlGenerator->StartElementL(KDataXmlTagCurSelectFile); // <curselectfile>
	pXmlGenerator->SetAttributeL(KDataXmlAtrValue, value); // 
	pXmlGenerator->EndElementL(); // </curselectfile>
	}
void CUIDataSerialize::GenerateNextSelectFile(CSyGenerator *pXmlGenerator)
	{
	TBuf<4> value;
	value.AppendNum(iData->GetNextSelectFile());
	pXmlGenerator->StartElementL(KDataXmlTagNextSelectFile); // <nextselectfile>
	pXmlGenerator->SetAttributeL(KDataXmlAtrValue, value); // 
	pXmlGenerator->EndElementL(); // </nextselectfile>
	}
void CUIDataSerialize::GenerateVolume(CSyGenerator *pXmlGenerator)
	{
	TBuf<4> value;
	value.AppendNum(iData->GetDrawVolume());
	pXmlGenerator->StartElementL(KDataXmlTagVolume); // <volume>
	pXmlGenerator->SetAttributeL(KDataXmlAtrValue, value); // 
	pXmlGenerator->EndElementL(); // </volume>
	}

void CUIDataSerialize::StartElement(const TQualified& aName, const
RArray<TAttribute>& aAttributes)
	{
	TPtrC name = aName.iLocalName;
	if (name.Compare(KDataXmlTagFileList) == 0)
		{
		ParseFileList(aAttributes);
		}
	else if (name.Compare(KDataXmlTagPlayModel) == 0)
		{	
		ParsePlayModel(aAttributes);
		}
	else if (name.Compare(KDataXmlTagCurSelectFile) == 0)
		{
		ParseCurSelectFile(aAttributes);
		}
	else if (name.Compare(KDataXmlTagNextSelectFile) == 0)
		{	
		ParseNextSelectFile(aAttributes);
		}
	else if (name.Compare(KDataXmlTagVolume) == 0)
		{	
		ParseVolume(aAttributes);
		}
	}

void CUIDataSerialize::EndElement(const TQualified& aName)
	{
	}
void CUIDataSerialize::CharacterData(const TDesC& aData)
	{
	}

void CUIDataSerialize::ParseFileList(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
			{
			TPtrC attrName = aAttributes[i].iName.iLocalName;
			TPtrC attrValue = aAttributes[i].iValue;
			if (attrName == KDataXmlAtrValue)
				{
				iData->AddSelectFile(attrValue);
				}
			}
	}
void CUIDataSerialize::ParsePlayModel(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
				{
				TPtrC attrName = aAttributes[i].iName.iLocalName;
				TPtrC attrValue = aAttributes[i].iValue;
				if (attrName == KDataXmlAtrValue)
					{
					TInt model = CCommonUtils::StrToInt(attrValue);
					if (model==KPlayModelSequence)
						iData->SetPlayModel(KPlayModelSequence);
					else if (model==KPlayModelLoop)
						iData->SetPlayModel(KPlayModelLoop);
					else if (model==KPlayModelRandom)
						iData->SetPlayModel(KPlayModelRandom);					
					}
				}
	}
void CUIDataSerialize::ParseCurSelectFile(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
				{
				TPtrC attrName = aAttributes[i].iName.iLocalName;
				TPtrC attrValue = aAttributes[i].iValue;
				if (attrName == KDataXmlAtrValue)
					{
					TInt cur = CCommonUtils::StrToInt(attrValue);
					iData->SetCurSelectFile(cur);
					}
				}
	}

void CUIDataSerialize::ParseNextSelectFile(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
				{
				TPtrC attrName = aAttributes[i].iName.iLocalName;
				TPtrC attrValue = aAttributes[i].iValue;
				if (attrName == KDataXmlAtrValue)
					{
					TInt next = CCommonUtils::StrToInt(attrValue);
					iData->SetNextSelectFile(next);
					}
				}
	}
void CUIDataSerialize::ParseVolume(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
				{
				TPtrC attrName = aAttributes[i].iName.iLocalName;
				TPtrC attrValue = aAttributes[i].iValue;
				if (attrName == KDataXmlAtrValue)
					{
					TInt volume = CCommonUtils::StrToInt(attrValue);
					iData->SetVolume(volume);
					}
				}
	}

void CUIDataSerialize::CheckData()
	{
	iData->CheckSelectFileIndex();
	}

void CUIDataSerialize::WriteL(const TDesC& aString, const TBool aIsRawData)
	{
	HBufC8 *pstrBuffer = CCommonUtils::ConvertToUTF8FromUnicode(aString);
	CleanupStack::PushL(pstrBuffer);

		if (iXmlBuffer)
		{
		iXmlBuffer = iXmlBuffer->ReAllocL(iXmlBuffer->Length()+pstrBuffer->Length());
		iXmlBuffer->Des().Append(*pstrBuffer);
		}
		else
		{
		iXmlBuffer = pstrBuffer->AllocL();
		}

	CleanupStack::PopAndDestroy(pstrBuffer);
	}

void CUIDataSerialize::ClearBuffer()
	{
	if (iXmlBuffer)
		{
		delete iXmlBuffer;
		iXmlBuffer = NULL;
		}
	}