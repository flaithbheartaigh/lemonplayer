/*
 ============================================================================
 Name		: CustomControlList.cpp
 Author	  	: zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCustomControlList implementation
 ============================================================================
 */

#include "CustomControlList.h"
#include <AknIconArray.h> 
#include <CCList.mbg>
#include <eikenv.h>
#include <aknutils.h>

_LIT(KListIcon,"CCList.mbm");

CCustomControlList::CCustomControlList()
	{
	// No implementation required
	}

CCustomControlList::~CCustomControlList()
	{
	Release();
	}

CCustomControlList* CCustomControlList::NewLC()
	{
	CCustomControlList* self = new (ELeave)CCustomControlList();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CCustomControlList* CCustomControlList::NewL()
	{
	CCustomControlList* self=CCustomControlList::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CCustomControlList::ConstructL()
	{
	LoadL();
	InitData();
	}

void CCustomControlList::LoadL()
	{
	iIcons = new(ELeave) CAknIconArray(5);
	CleanupStack::PushL(iIcons);
	TFileName file(KListIcon);
	User::LeaveIfError(CompleteWithAppPath(file));
	iIcons->AppendL(CEikonEnv::Static()->CreateIconL(file, EMbmCclistListfile, EMbmCclistListmask));
	iIcons->AppendL(CEikonEnv::Static()->CreateIconL(file, EMbmCclistListfolder, EMbmCclistListmask));
	iIcons->AppendL(CEikonEnv::Static()->CreateIconL(file, EMbmCclistListmusic, EMbmCclistListmask));
	CleanupStack::Pop(iIcons);

	iSelectBitmap = new (ELeave) CFbsBitmap();
	CleanupStack::PushL(iSelectBitmap);
	iSelectBitmap->Load(file, EMbmCclistListmask);
	CleanupStack::Pop(iSelectBitmap);

	iList = new (ELeave) RPointerArray<ListItemStruct>;
	}

void CCustomControlList::Release()
	{
	iList->ResetAndDestroy();
	delete iList;

	delete iSelectBitmap;

	iIcons->ResetAndDestroy();
	delete iIcons;
	}

void CCustomControlList::InitData(TPoint aDisplayPoint, TSize aDisplaySize,
		TSize aOriginalSize)
	{
	iDisplayPoint = aDisplayPoint;
	iDisplaySize = aDisplaySize;

	iSelectSize = TSize(aDisplaySize.iWidth, iRowHeight);

	iScrollSize = aDisplaySize.iHeight / iRowHeight / 2;
	if (aDisplaySize.iHeight / iRowHeight % 2)
		{
		iScrollSize++;
		}
	}

void CCustomControlList::Draw(CBitmapContext& gc)
	{
	TInt x = iDrawPoint.iX + iDisplayPoint.iX;
	TInt x2 = iDrawPoint.iX + iDisplayPoint.iX + 16;
	TInt y;
	TInt dy = iDrawPoint.iY;
	for (TInt i=0; i<iList->Count(); i++)
		{
		if (dy < 0)
			{
			dy += iRowHeight;
			continue;
			}
		if (dy >= iDisplaySize.iHeight)
			{
			break;
			}
		y = dy + iDisplayPoint.iY;
		pListItemStruct item = (*iList)[i];
		CGulIcon* icon = (*iIcons)[item->iIconIndex];
		CFbsBitmap* bitmap = icon->Bitmap();
		gc.BitBlt(TPoint(x, y), bitmap);

		gc.UseFont(iFont);
		if (i!=iSelectIndex)
			{
			gc.SetPenColor(iTextColor);
			//			HBufC* text = item->iShowName;
			//			gc.DrawText(*(item->iShowName), TPoint(x2, y));
			}
		else
			{
			gc.SetPenColor(iSelectTextColor);
			//			HBufC* text = item->iShowName;
			//			gc.DrawText(*(item->iShowName), TPoint(x2, y));
			}
		y += iFontHeight;
		gc.DrawText(*(item->iShowName), TPoint(x2, y));
		gc.DiscardFont();

		dy += iRowHeight;
		}
	}

TInt CCustomControlList::Update(ECustomControlDirection aDirection)
	{
	if (aDirection == KCustomControlDirectionUp)
		{
		if (--iSelectIndex<0)
			{
			iSelectIndex = 0;
			return EKeyWasNotConsumed;
			}
		TInt high = iSelectIndex+1;
		TInt low = iList->Count()-iSelectIndex-1;
		//		if (high < iScrollSize || low < iScrollSize)
		if (high >= iScrollSize && low >= iScrollSize)
			{
			iDrawPoint.iY += iRowHeight;
			}

		TInt h=(iList->Count()-iSelectIndex)*iRowHeight;
		TInt h2 = iSelectIndex*iRowHeight;
		TInt dh = iDisplaySize.iHeight/2;
		if (h2 < dh)
			{
			iSelectPoint.iY -= iRowHeight;
			}
		else
			if (h<dh)
				{
				iSelectPoint.iY -= iRowHeight;
				}
			else
				{
				//				iDrawPoint.iY += iRowHeight;
				}
		return EKeyWasConsumed;
		}
	if (aDirection == KCustomControlDirectionDown)
		{
		if (++iSelectIndex>=iList->Count())
			{
			iSelectIndex = iList->Count()-1;
			return EKeyWasNotConsumed;
			}
		TInt high = iSelectIndex;
		TInt low = iList->Count()-iSelectIndex;
		//		if (high < iScrollSize || low < iScrollSize)
		if (high >= iScrollSize && low >= iScrollSize)
			{
			iDrawPoint.iY -= iRowHeight;
			}

		TInt h=(iList->Count()-iSelectIndex+1)*iRowHeight;
		TInt h2 = (iSelectIndex-1)*iRowHeight;
		TInt dh = iDisplaySize.iHeight/2;
		if (h2 <= dh)
			{
			iSelectPoint.iY += iRowHeight;
			}
		else
			if (h<=dh)
				{
				iSelectPoint.iY += iRowHeight;
				}
			else
				{
				//				iDrawPoint.iY -= iRowHeight;
				}
		return EKeyWasConsumed;
		}
		return EKeyWasNotConsumed;
	}

void CCustomControlList::InitData()
	{
	iFont = CEikonEnv::Static()->NormalFont();

	TInt fontAscent = iFont->AscentInPixels();
	TInt fontDescent = iFont->DescentInPixels();
	iRowHeight = fontAscent+fontDescent;
	iFontHeight = fontAscent+fontDescent;

	iTextColor = TRgb(0xFF0000);
	iSelectTextColor = TRgb(0x00FF00);

	iSelectIndex = 0;
	iSelectPoint = TPoint(0, 0);

	iDrawPoint = TPoint(0, 0);

	}
void CCustomControlList::AddItem(pListItemStruct aItem)
	{
	iList->Append(aItem);
	}

void CCustomControlList::AddItem(const TDesC& aItem)
	{
	pListItemStruct item = new (ELeave) ListItemStruct;
	item->iIconIndex = 0;
	item->iShowName = aItem.AllocL();
	item->iHideInfo = NULL;
	iList->Append(item);
	}

void CCustomControlList::AddItem(const TDesC& aItem, TInt aHideIndex)
	{
	pListItemStruct item = new (ELeave) ListItemStruct;
	item->iIconIndex = 0;
	item->iShowName = aItem.AllocL();
	item->iHideIndex = aHideIndex;
	item->iHideInfo = NULL;
	iList->Append(item);
	}

void CCustomControlList::ClearItem()
	{
	iList->ResetAndDestroy();
	}

void CCustomControlList::ResetItem(RPointerArray<ListItemStruct>* aList)
	{
	iList->ResetAndDestroy();
	SAFE_DELETE(iList);
	
	iList = aList;
	}

pListItemStruct CCustomControlList::GetCurrentItem()
	{
	return (*iList)[iSelectIndex];
	}