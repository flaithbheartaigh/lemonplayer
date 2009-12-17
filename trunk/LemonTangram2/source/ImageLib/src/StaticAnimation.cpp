/*
 ============================================================================
 Name		: TangramImageManager.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangramImageManager implementation
 ============================================================================
 */
#include <stdlib.h>
#include <e32math.h>
#include "StaticAnimation.h"

#include "ImageBitmapReader.h"
#include "DefaultDeclHandler.h"
#include "StaticAnimationParseDef.h"
#include "CommonUtils.h"
#include "MacroUtil.h"
#include <coemain.h>
//#define TANGRAME_SIZE 7

CStaticAnimation::CStaticAnimation() :
	iInitComplete(EFalse)
	{
	// No implementation required
	}

CStaticAnimation::~CStaticAnimation()
	{
	SAFE_DELETE_ARRAY(iStruct,iImageCount);
	SAFE_DELETE_ARRAY(iOffset,iImageCount);
	SAFE_DELETE_ARRAY(iStruct,iImageCount);

	SAFE_DELETE(iFrameCount);
	SAFE_DELETE_ARRAY(iSpriteCount,iActionCount);
	}

CStaticAnimation* CStaticAnimation::NewLC()
	{
	CStaticAnimation* self = new (ELeave)CStaticAnimation();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CStaticAnimation* CStaticAnimation::NewL()
	{
	CStaticAnimation* self=CStaticAnimation::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CStaticAnimation::ConstructL()
	{
	//	iStruct = (PTangramImageStruct)malloc(sizeof(TangramImageStruct)
	//			*TANGRAME_SIZE);
	//	iOffset = (PTangramImageStruct)malloc(sizeof(TangramImageStruct)
	//			*TANGRAME_SIZE);
	//	iRotator = (CImageRotator**)malloc(sizeof(CImageRotator*)*TANGRAME_SIZE);
	}

void CStaticAnimation::LoadDataFromXml(const TDesC& aFileName)
	{
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
		//		TBuf8<1024> ptr;
		//		file.Read(ptr);
		//		syParser->Parse(ptr, ETrue);
		CleanupStack::PopAndDestroy(1);
		}
	CleanupStack::PopAndDestroy(2);
	iInitComplete = ETrue;
	}

void CStaticAnimation::Draw(CFbsBitGc& gc, TInt aX, TInt aY)
	{
	for (TInt i=0; i<iImageCount; i++)
		{
//		iRotator[i]->DrawCenter(gc, iStruct[i]->x+aX+iOffset[i]->x,
//				iStruct[i]->y +aY+iOffset[i]->y);
		}
	}

void CStaticAnimation::ChangeAction()
	{
	iCurAction = Math::Random()%iActionCount;
	iCurAction = iCurAction<0 ? -iCurAction : iCurAction;

	iCurFrame = 0;
	}

void CStaticAnimation::UpdataData()
	{
	if (!iInitComplete)
		{
		return;
		}
	for (TInt i=0; i<iImageCount; i++)
		{
		iOffset[i]->x = 0;
		iOffset[i]->y = 0;
		}

	if (iCurAction>=0)
		{
		for (TInt i=0; i<iSpriteCount[iCurAction][iCurFrame]; i++)
			{
			TInt index = iAnimation[iCurAction][iCurFrame][i].index;
			TInt x = iAnimation[iCurAction][iCurFrame][i].x;
			TInt y = iAnimation[iCurAction][iCurFrame][i].y;

			iOffset[index]->x = x;
			iOffset[index]->y = y;
			}

		if (++iCurFrame >= iFrameCount[iCurAction])
			{
			iCurAction = -1;
			}
		}

	}

void CStaticAnimation::SetSrcBitmap(CFbsBitmap** aBitmap, const TInt aCount)
	{
	iSrcBitmap = aBitmap;
	iSrcBitmapCount = aCount;
	}

void CStaticAnimation::ClearData()
	{
	ClearAction();
	ClearFrame();
	ClearSprite();
	}

void CStaticAnimation::ClearAction()
	{
	iParseAction = 0;
	}
void CStaticAnimation::ClearFrame()
	{
	iParseFrame = 0;
	}
void CStaticAnimation::ClearSprite()
	{
	iParseSprite = 0;
	}

void CStaticAnimation::IncreaseAction()
	{
	iParseAction++;
	}
void CStaticAnimation::IncreaseFrame()
	{
	iParseFrame++;
	}
void CStaticAnimation::IncreaseSprite()
	{
	iParseSprite++;
	}

void CStaticAnimation::StartElement(const TQualified& aName,
		const RArray<TAttribute>& aAttributes)
	{
	TInt num = ConvertNameToNumber(aName.iLocalName);
	switch (num)
		{
		case EStaticAniTagImage:
			ParseImage(aAttributes);
			break;
		case EStaticAniTagImg:
			ParseImg(aAttributes);
			break;
		case EStaticAniTagAnimation:
			ParseAnimation(aAttributes);
			break;
		case EStaticAniTagAction:
			ParseAction(aAttributes);
			break;
		case EStaticAniTagFrame:
			ParseFrame(aAttributes);
			break;
		case EStaticAniTagSprite:
			ParseSprite(aAttributes);
			break;
		default:
			break;
		}

	}
void CStaticAnimation::EndElement(const TQualified& aName)
	{
	TInt num = ConvertNameToNumber(aName.iLocalName);
	switch (num)
		{
		case EStaticAniTagAction:
			EndParseAction();
			break;
		case EStaticAniTagFrame:
			EndParseFrame();
			break;
		case EStaticAniTagSprite:
			EndParseSprite();
			break;
		default:
			break;
		}
	}

TInt CStaticAnimation::ConvertNameToNumber(const TDesC& aName)
	{
	HBufC* name = aName.AllocLC();
	name->Des().LowerCase();
	TInt num = EStaticAniTagNone;

	if (name->Compare(KStaticAniDomTagImage) == 0)
		{
		num = EStaticAniTagImage;
		}
	else
		if (name->Compare(KStaticAniDomTagImg) == 0)
			{
			num = EStaticAniTagImg;
			}
		else
			if (name->Compare(KStaticAniDomTagAnimation) == 0)
				{
				num = EStaticAniTagAnimation;
				}
			else
				if (name->Compare(KStaticAniDomTagAction) == 0)
					{
					num = EStaticAniTagAction;
					}
				else
					if (name->Compare(KStaticAniDomTagFrame) == 0)
						{
						num = EStaticAniTagFrame;
						}
					else
						if (name->Compare(KStaticAniDomTagSprite) == 0)
							{
							num = EStaticAniTagSprite;
							}
	CleanupStack::PopAndDestroy();
	return num;
	}

void CStaticAnimation::ParseImage(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KStaticAniAttrNumber) == 0)
			{
			TInt num = CCommonUtils::StrToInt(attrValue->Des());

			ConstructImageL(num);
			}
		CleanupStack::PopAndDestroy(2);
		}
	}

void CStaticAnimation::ParseImg(const RArray<TAttribute>& aAttributes)
	{
	TInt index, degree, x, y;
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KStaticAniAttrIndex) == 0)
			{
			index = CCommonUtils::StrToInt(attrValue->Des());
			}
		if (attrName->Compare(KStaticAniAttrDegree) == 0)
			{
			degree = CCommonUtils::StrToInt(attrValue->Des());
			}
		if (attrName->Compare(KStaticAniAttrX) == 0)
			{
			x = CCommonUtils::StrToInt(attrValue->Des());
			}
		if (attrName->Compare(KStaticAniAttrY) == 0)
			{
			y = CCommonUtils::StrToInt(attrValue->Des());
			}
		CleanupStack::PopAndDestroy(2);
		}
	InitImageL(index, degree, x, y);
	}

void CStaticAnimation::ParseAnimation(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KStaticAniAttrNumber) == 0)
			{
			TInt num = CCommonUtils::StrToInt(attrValue->Des());
			ConstructAnimationL(num);
			}
		CleanupStack::PopAndDestroy(2);
		}
	}

void CStaticAnimation::ParseAction(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KStaticAniAttrNumber) == 0)
			{
			TInt num = CCommonUtils::StrToInt(attrValue->Des());
			ConstructAction(num);
			}
		CleanupStack::PopAndDestroy(2);
		}
	}

void CStaticAnimation::ParseFrame(const RArray<TAttribute>& aAttributes)
	{
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();

		if (attrName->Compare(KStaticAniAttrNumber) == 0)
			{
			TInt num = CCommonUtils::StrToInt(attrValue->Des());
			ConstructFrame(num);
			}
		CleanupStack::PopAndDestroy(2);
		}
	}

void CStaticAnimation::ParseSprite(const RArray<TAttribute>& aAttributes)
	{
	TInt index, x, y;
	for (TInt i = 0; i < aAttributes.Count(); i++)
		{
		HBufC *attrName = aAttributes[i].iName.iLocalName.AllocLC();
		HBufC *attrValue = aAttributes[i].iValue.AllocLC();
		if (attrName->Compare(KStaticAniAttrIndex) == 0)
			{
			index = CCommonUtils::StrToInt(attrValue->Des());
			}
		if (attrName->Compare(KStaticAniAttrX) == 0)
			{
			x = CCommonUtils::StrToInt(attrValue->Des());
			}
		if (attrName->Compare(KStaticAniAttrY) == 0)
			{
			y = CCommonUtils::StrToInt(attrValue->Des());
			}
		CleanupStack::PopAndDestroy(2);
		}
	ConstructSprite(index, x, y);
	}

void CStaticAnimation::EndParseAction()
	{
	ClearFrame();
	IncreaseAction();
	}

void CStaticAnimation::EndParseFrame()
	{
	ClearSprite();
	IncreaseFrame();
	}

void CStaticAnimation::EndParseSprite()
	{
	IncreaseSprite();
	}

void CStaticAnimation::ConstructImageL(TInt aNumber)
	{
	iImageCount = aNumber;

	iStruct
			= (TangramImageStruct**)malloc(sizeof(PTangramImageStruct) *aNumber);
	iOffset
			= (TangramImageStruct**)malloc(sizeof(PTangramImageStruct) *aNumber);

	for (TInt i=0; i<aNumber; i++)
		{
		iStruct[i] = new (ELeave)TangramImageStruct;
		iOffset[i] = new (ELeave)TangramImageStruct;
		}
	iRotator = (CImageRotator**)malloc(sizeof(CImageRotator*)*aNumber);
	}

void CStaticAnimation::InitImageL(TInt aIndex, TInt aDegree, TInt aX, TInt aY)
	{
	if (aIndex >= iImageCount || aIndex < 0)
		{
		return;
		}
	iStruct[aIndex]->x = aX;
	iStruct[aIndex]->y = aY;

//	iRotator[aIndex] = CImageRotator::NewL(iSrcBitmap[aIndex], NULL,aDegree, 
//	KRgbMagenta);
//	iRotator[aIndex]->SetRetateCenter();
	}

void CStaticAnimation::ConstructAnimationL(TInt aNumber)
	{
	iAnimation = (UiImageStruct***)malloc(sizeof(UiImageStruct**)*aNumber);

	iActionCount = aNumber;
	iFrameCount = (TInt*)malloc(sizeof(TInt)*aNumber);
	iSpriteCount = (TInt**)malloc(sizeof(TInt*)*aNumber);
	}

void CStaticAnimation::ConstructAction(TInt aNumber)
	{
	iFrameCount[iParseAction] = aNumber;
	iAnimation[iParseAction] = (UiImageStruct**)malloc(sizeof(UiImageStruct*)
			*aNumber);
	iSpriteCount[iParseAction] = (TInt*)malloc(sizeof(TInt)*aNumber);
	}

void CStaticAnimation::ConstructFrame(TInt aNumber)
	{
	iSpriteCount[iParseAction][iParseFrame] = aNumber;
	iAnimation[iParseAction][iParseFrame]
			= (UiImageStruct*)malloc(sizeof(UiImageStruct)*aNumber);
	}

void CStaticAnimation::ConstructSprite(TInt aIndex, TInt aX, TInt aY)
	{
	iAnimation[iParseAction][iParseFrame][iParseSprite].x = aX;
	iAnimation[iParseAction][iParseFrame][iParseSprite].y = aY;
	iAnimation[iParseAction][iParseFrame][iParseSprite].index = aIndex;
	}