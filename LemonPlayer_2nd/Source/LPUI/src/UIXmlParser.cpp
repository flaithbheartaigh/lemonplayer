/*
 ============================================================================
 Name		: UIXmlParser.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIXmlParser implementation
 ============================================================================
 */

#include "UIXmlParser.h"


#include <f32file.h>
#include <coemain.h>
#include <s32mem.h>

#include "CommonUtils.h"
#include "ImageConvertor.h"

CUIXmlParser::CUIXmlParser(CUIViewData *aData)
	{
	// No implementation required
	iData = aData;
	}

CUIXmlParser::~CUIXmlParser()
	{
	if (iDocHandler)
		{
		delete iDocHandler;
		iDocHandler = NULL;
		}
	}

CUIXmlParser* CUIXmlParser::NewLC(CUIViewData *aData)
	{
	CUIXmlParser* self = new (ELeave)CUIXmlParser(aData);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIXmlParser* CUIXmlParser::NewL(CUIViewData *aData)
	{
	CUIXmlParser* self=CUIXmlParser::NewLC(aData);
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIXmlParser::ConstructL()
	{
	iDocHandler = CUIXmlDocHandler::NewL(iData);
	}

TInt CUIXmlParser::LoadFile(const TDesC& aFileName)
	{
	CUIXmlDeclHandler *decl = CUIXmlDeclHandler::NewLC();

		CSyParser *syParser = CSyParser::NewLC(TPtrC());
		syParser->SetHandler(iDocHandler);
		syParser->SetHandler(decl);
		
		RFile file;
		TInt err = file.Open(CCoeEnv::Static()->FsSession(), aFileName, EFileRead);
			
		if (KErrNone == err)
		{
			CleanupClosePushL(file);
			//操作
			TBuf8<1024> ptr; 
			file.Read(ptr);
			syParser->Parse(ptr, ETrue);
			CleanupStack::PopAndDestroy(1);
		}
		CleanupStack::PopAndDestroy(2);
		
		iDocHandler->ConvertImage();
	}

/**************************************************/

CUIXmlDeclHandler::CUIXmlDeclHandler()
	{
	// No implementation required
	}

CUIXmlDeclHandler::~CUIXmlDeclHandler()
	{
	}

CUIXmlDeclHandler* CUIXmlDeclHandler::NewLC()
	{
	CUIXmlDeclHandler* self = new (ELeave)CUIXmlDeclHandler();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIXmlDeclHandler* CUIXmlDeclHandler::NewL()
	{
	CUIXmlDeclHandler* self=CUIXmlDeclHandler::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIXmlDeclHandler::ConstructL()
	{
	}

/******************************************/

CUIXmlDocHandler::CUIXmlDocHandler(CUIViewData *aData)
	{
	// No implementation required
	iData = aData;
	}

CUIXmlDocHandler::~CUIXmlDocHandler()
	{
	iArray.ResetAndDestroy();
	if (iConvertor)
		{
		delete iConvertor;
		iConvertor = NULL;
		}
	}

CUIXmlDocHandler* CUIXmlDocHandler::NewLC(CUIViewData *aData)
	{
	CUIXmlDocHandler* self = new (ELeave)CUIXmlDocHandler(aData);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIXmlDocHandler* CUIXmlDocHandler::NewL(CUIViewData *aData)
	{
	CUIXmlDocHandler* self=CUIXmlDocHandler::NewLC(aData);
	CleanupStack::Pop(); // self;
	return self;
	}

void CUIXmlDocHandler::ConstructL()
	{
	iConvertor = CImageConvertor::NewL();
	iConvertor->SetListener(this);
	}

void CUIXmlDocHandler::StartElement(const TQualified& aName, const 
RArray<TAttribute>& aAttributes)
	{
	TPtrC name = aName.iLocalName;
	if (name.Compare(KCtrlXmlElemControl) == 0)
		{
		FillControlData(aAttributes);
		}
	}

void CUIXmlDocHandler::FillControlData(const RArray<TAttribute>& aAttributes)
	{
	pControlViewData data = new ControlViewData();
	
	TInt index = KErrNotFound;
	data->isShow = ETrue;
	for(TInt i=0; i<aAttributes.Count(); i++)
		{
		TPtrC attrName = aAttributes[i].iName.iLocalName;
		TPtrC attrValue = aAttributes[i].iValue;
		
		if (attrName.Compare(KCtrlXmlAttrName) == 0)
			{
			if (attrValue.Compare(KCtrlXmlNamePlay) == 0)
				index = KCtrlIndexPlay;
			else if (attrValue.Compare(KCtrlXmlNamePause) == 0)
				index = KCtrlIndexPause;
			else if (attrValue.Compare(KCtrlXmlNameStop) == 0)
				index = KCtrlIndexStop;			
			else if (attrValue.Compare(KCtrlXmlNameVolumeItem) == 0)
				index = KCtrlIndexVolumeItem;			
			else if (attrValue.Compare(KCtrlXmlNameVolumeSlip) == 0)
				index = KCtrlIndexVolumeSlip;	
			data->index = index;
			}		
		else if (attrName.Compare(KCtrlXmlAttrX)==0)
			{
			data->x = CCommonUtils::StrToInt(attrValue);
			}
		else if(attrName.Compare(KCtrlXmlAttrY)==0)
			{
			data->y = CCommonUtils::StrToInt(attrValue);
			}
		else if(attrName.Compare(KCtrlXmlAttrImg)==0)
			{
			data->bitmap = NULL;
			pConvertFileStruct iFile = new ConvertFileStruct();
			iFile->index = index;
			iFile->filename.Copy(attrValue);
			iArray.AppendL(iFile);
			}
		else if (attrName.Compare(KCtrlXmlAttrSlip)==0)
			{
			data->iSlip = CCommonUtils::StrToFloat(attrValue);
			}
		}
	iData->SetData(index,data);
	}


void CUIXmlDocHandler::CopyBitmap(const CFbsBitmap &aBitmap,CFbsBitmap** destBitmap)
	{
	// 根据aBitmap的Header，构造出des系列的buffer
		// 运用流，实现bitmap的copy
	if (*destBitmap)
		{
		delete *destBitmap;
		*destBitmap = NULL;
		}

		RDesWriteStream writeStream;
		RDesReadStream readStream;

		HBufC8 *imgBuffer = HBufC8::NewLC(aBitmap.Header().iBitmapSize);
		TPtr8 ptr8ImgBuffer = imgBuffer->Des();
		writeStream.Open(ptr8ImgBuffer);
		writeStream.PushL();
		aBitmap.ExternalizeL(writeStream);
		writeStream.CommitL();
		writeStream.Pop();
		writeStream.Release();

		*destBitmap = new(ELeave) CFbsBitmap();
		readStream.Open(imgBuffer->Des());
		readStream.PushL();
		(*destBitmap)->InternalizeL(readStream);
		readStream.Pop();
		readStream.Release();

		CleanupStack::PopAndDestroy(imgBuffer);
	}

void CUIXmlDocHandler::EndElement(const TQualified& aName)
	{
	}

void CUIXmlDocHandler::CharacterData(const TDesC& aData)
	{
	}


void CUIXmlDocHandler::OnImageConvertedL(CFbsBitmap &aBitmap) 
	{	
	if (iArray.Count()<=0)
		return;
	TInt index = iArray[0]->index;
	CopyBitmap(aBitmap,&(iData->GetData(index)->bitmap));
//	iData->GetData(index)->bitmap = &aBitmap;
	iArray.Remove(0);
	ConvertImage();
	}

void CUIXmlDocHandler::OnImageConvertedL(const TDesC8 &aImgData) 
	{}
void CUIXmlDocHandler::OnConvertErrorL(TConvertResult aConvertResult) 
	{}

void CUIXmlDocHandler::ConvertImage()
	{
	if (iArray.Count()<=0)
		return;
	//得到文件名,进行转换
	iConvertor->DecodeFromFileL(iArray[0]->filename);
	}
