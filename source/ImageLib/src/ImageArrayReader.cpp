/*
 ============================================================================
 Name		: ImageArrayReader.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CImageArrayReader implementation
 ============================================================================
 */

#include "ImageArrayReader.h"

#include <stdlib.h>
#include "MacroUtil.h"
#include "coemain.h"
#include "DefaultDeclHandler.h"
#include "ImageConvertor.h"

#include "CommonUtils.h"

CImageArrayReader::CImageArrayReader()
:iAdjustErr(0)
	{
	// No implementation required
	}

CImageArrayReader::~CImageArrayReader()
	{
	iArray.ResetAndDestroy();
	iArray.Close();

	SAFE_DELETE(iConvertor);
	SAFE_DELETE(iBitmap);
//	SAFE_DELETE_ARRAY(iBitmap,iBitmapCount);
//	SAFE_DELETE(iBitmap);
	}

CImageArrayReader* CImageArrayReader::NewLC()
	{
	CImageArrayReader* self = new (ELeave)CImageArrayReader();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CImageArrayReader* CImageArrayReader::NewL()
	{
	CImageArrayReader* self=CImageArrayReader::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CImageArrayReader::ConstructL()
	{
	iConvertor = CImageConvertor::NewL();
	iConvertor->SetListener(this);
	}

void CImageArrayReader::LoadDataFromFileL(const TDesC& aFileName)
	{
	iArray.ResetAndDestroy();

	CDefaultDeclHandler *decl = new (ELeave)CDefaultDeclHandler;
	CleanupStack::PushL(decl);

	CSyParser *syParser = CSyParser::NewLC(TPtrC());
	syParser->SetHandler(this);
	syParser->SetHandler(decl);

	RFile file;
	TInt err = file.Open(CCoeEnv::Static()->FsSession(), aFileName, EFileRead);

	User::LeaveIfError(err);

	if (KErrNone == err)
		{
		CleanupClosePushL(file);
		//操作
		TBuf8<512> strBuffer;
		iAdjustErr = 0;

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

	//打开文件错误
	User::LeaveIfError(err);

	if (iAdjustErr != 0x11)
		{
		//格式不正确 没有两个元素
		User::Leave(KErrNotSupported);
		}

	if (iArray.Count() != iBitmapCount)
		{
		//格式不正确 元素个数不符合
		User::Leave(KErrNotSupported);
		}
	
	ConvertImage();	
	
	}

void CImageArrayReader::OnImageConvertedL(CFbsBitmap& /*aBitmap*/)
	{
	}
void CImageArrayReader::OnImageConvertedL(const TDesC8& /*aImgData*/)
	{
	}
void CImageArrayReader::OnConvertErrorL(TConvertResult aConvertResult)
	{
	switch (aConvertResult)
		{
		case EConvertSucceed:
			ConvertNext();
			break;
		case EConvertError:
			break;
		default:
			break;
		}
	}

//CDefaultDocHandler
void CImageArrayReader::StartElement(const TQualified& aName,
		const RArray<TAttribute>& aAttributes)
	{
	TInt num = ConvertNameToNumber(aName.iLocalName);
	switch (num)
		{
		case EImageArrayTagImage:
			ParseImage(aAttributes);
			break;
		case EImageArrayTagImg:
			ParseImg(aAttributes);
			break;
		default:
			break;
		}
	}

void CImageArrayReader::EndElement(const TQualified& /*aName*/)
	{
	}

TInt CImageArrayReader::ConvertNameToNumber(const TDesC& aName)
	{
	HBufC* name = aName.AllocLC();
	name->Des().LowerCase();
	TInt num = EImageArrayTagNone;

	if (name->Compare(KImageArrayDomTagImage) == 0)
		{
		num = EImageArrayTagImage;
		}
	else
		if (name->Compare(KImageArrayDomTagImg) == 0)
			{
			num = EImageArrayTagImg;
			}
	CleanupStack::PopAndDestroy();
	return num;
	}

void CImageArrayReader::ParseImage(const RArray<TAttribute>& aAttributes)
	{
	iAdjustErr |= 0x01;
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KImageArrayAttrNumber) == 0)
			{
			TInt num = CCommonUtils::StrToInt(attrValue->Des());
			ConstructBitmapL(num);
			}
		CleanupStack::PopAndDestroy(2);
		}
	}
void CImageArrayReader::ParseImg(const RArray<TAttribute>& aAttributes)
	{
	iAdjustErr |= 0x10;
	pImageArrayConvertStruct item = new (ELeave)ImageArrayConvertStruct;
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KImageArrayAttrIndex) == 0)
			{
			TInt index = CCommonUtils::StrToInt(attrValue->Des());
			item->index = index;
			}
		if (attrName->Compare(KImageArrayAttrFile) == 0)
			{
			item->filename = attrValue->Des().AllocL();
			}
		CleanupStack::PopAndDestroy(2);
		}
	iArray.Append(item);
	}

void CImageArrayReader::ConstructBitmapL(const TInt aNumber)
	{
	iBitmapCount = aNumber;
	iBitmap = (CFbsBitmap**) malloc(sizeof(CFbsBitmap*)*aNumber);
	for(TInt i=0; i<aNumber; i++)
		{
		iBitmap[i] = NULL;
		}
	}

//void CImageArrayReader::SetBitmap(TInt index,CFbsBitmap*& aBitmap)
//	{
//	(iBitmap[index]) = aBitmap;
//	}

void CImageArrayReader::ConvertImage()
	{
	if (iArray.Count()<=0)
		{
		if (iNotify)
			iNotify->ConvertComplete();
		return;
		}
	//得到文件名,进行转换
	TInt index = iArray[0]->index;
	TPtr file = iArray[0]->filename->Des();
	iConvertor->DecodeFromFileL(file, iBitmap[index]);
	}

void CImageArrayReader::ConvertNext()
	{
	if (iArray.Count()<=0)
		{		
		return;
		}
	pImageArrayConvertStruct item = iArray[0];
	iArray.Remove(0);
	SAFE_DELETE(item);
	
	ConvertImage();
	}

CFbsBitmap** CImageArrayReader::GetBitmapArray() const
	{
	return iBitmap;
	}

const TInt CImageArrayReader::GetBitmapCount() const
	{
	return iBitmapCount;
	}
