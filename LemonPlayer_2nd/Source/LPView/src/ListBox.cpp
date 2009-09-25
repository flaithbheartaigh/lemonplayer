/*
 ============================================================================
 Name		: ListBox.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBox implementation
 ============================================================================
 */

#include <aknlists.h> 
#include <barsread.h> 
#include <AknIconArray.h> 
#include <eikclb.h> 
#include <eikclbd.h>
#include <StringLoader.h>

#include <LemonPlayer.mbg>
#include <LemonPlayer.rsg>

#include "ListStructure.h"

#include "ListEngine.h"
#include "ListBox.h"
#include "UIData.h"
#include "CommonUtils.h"

_LIT(KItemText,"n\tHello");
_LIT(KListIcon,"\\resource\\apps\\LemonPlayer.mbm");

CListBox* CListBox::NewLC(const TRect& aRect)
	{
	CListBox* self = new (ELeave)CListBox;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

CListBox* CListBox::NewL(const TRect& aRect)
	{
	CListBox* self=CListBox::NewLC(aRect);
	CleanupStack::Pop(); // self;
	return self;
	}

CListBox::CListBox()
	{
	// No implementation required
	}

CListBox::~CListBox()
	{
	//	if( iListBox ) delete iListBox;  
	if (iFormatArray)
		{
		delete iFormatArray;
		iFormatArray = NULL;
		}
	}

void CListBox::ConstructL(const TRect& aRect)
	{
	iList = CListEngine::NewL();

	iFormatArray = iCoeEnv->ReadDesCArrayResourceL(R_ACCEPTED_SOUND_FORMAT);
	
	CreateWindowL(); // Creates window.        
	SetRect(aRect); // Sets rectangle of frame.

	CreateListboxL();
	SetupListIconsL();
	iListBox->SetRect(Rect());
	iListBox->MakeVisible(ETrue);
	iListBox->SetFocus(ETrue);

	ActivateL(); // Activates window. ( Ready to draw )     
	}

void CListBox::CreateListboxL()
	{
	iListBox = new ( ELeave ) CAknSingleGraphicStyleListBox;
//	iListBox = new ( ELeave ) CAknSingleNumberStyleListBox;
	iListBox->SetContainerWindowL( *this);

	iListBox->ConstructL(this);

	iListBox->CreateScrollBarFrameL(ETrue);
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,
			CEikScrollBarFrame::EAuto);
	}

TInt CListBox::CountComponentControls() const
	{
	return 1;
	}

CCoeControl* CListBox::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		case 0:
			return iListBox;
		default:
			return NULL;
		}
	}

void CListBox::SizeChanged()
	{
	if (iListBox)
		{
		iListBox->SetRect(Rect() );
		}
	}

TKeyResponse CListBox::OfferKeyEventL(const TKeyEvent &aKeyEvent,
		TEventCode aType)
	{
	if (aKeyEvent.iCode == EKeyDownArrow || aKeyEvent.iCode == EKeyUpArrow)
		// Forward key events to listbox                
		return iListBox->OfferKeyEventL(aKeyEvent, aType);
	if (aKeyEvent.iCode == EKeyDevice3)
		{
		SelectedItem();
		return EKeyWasConsumed;
		}

	return EKeyWasNotConsumed;
	//	return iListBox->OfferKeyEventL(aKeyEvent, aType);
	}


void CListBox::AddItem(const TDesC &aItem)
	{
	CDesCArray* itemArray = static_cast<CDesC16ArrayFlat*>(iListBox->Model()->ItemTextArray());
	itemArray->AppendL(aItem);
	iListBox->HandleItemAdditionL();
	}


void CListBox::AddItem(RPointerArray<TListItem>* aArray)
	{
	if (aArray == NULL)
		{
		return;
		}
	CDesCArray* itemArray = static_cast<CDesC16ArrayFlat*>(iListBox->Model()->ItemTextArray());

	TFileName kName1;
	kName1.AppendNum(EItemTypeDir);
	kName1.Append(_L("\t"));
	kName1.Append(_L(".."));
	itemArray->AppendL(kName1);

	for (TInt i=0; i<aArray->Count(); i++)
		{
		TFileName kName;
		TInt pref = (*aArray)[i]->iPref;
		if (pref==EItemTypeFile)
			{
			if (CheckFormat((*aArray)[i]->iName))
				{
				pref = EItemTypeMusic;
				}
			}
		kName.AppendNum(pref);
		kName.Append(_L("\t"));
		kName.Append((*aArray)[i]->iName);
		itemArray->AppendL(kName);
		}
	iListBox->HandleItemAdditionL();
	}

void CListBox::DeleteItem()
	{
	if (iListBox->Model()->NumberOfItems() < 1)
		return;

	TInt oldIndex = iListBox->View()->CurrentItemIndex();
	// Item array. By default iListBox owns the item array, so no deletion is
	// needed.
	CDesCArray* itemArray = static_cast<CDesC16ArrayFlat*>(iListBox->Model()->ItemTextArray());

	// Remove highlighted item from the listbox.
	itemArray->Delete(iListBox->View()->CurrentItemIndex() );

	// If focused item is out of range, bring it forth
	if ( (oldIndex > (itemArray->Count()-1 )) && ( (itemArray->Count()-1) >= 0 ))
		{
		iListBox->View()->SetCurrentItemIndex(itemArray->Count()-1);
		}

	// Update the listbox
	iListBox->HandleItemAdditionL();
	}

void CListBox::SelectedItem()
	{
	if (iListBox->Model()->NumberOfItems() < 1)
		return;

	TInt index = iListBox->View()->CurrentItemIndex();
	// Item array. By default iListBox owns the item array, so no deletion is
	// needed.
	if (index == 0)
		{
		TFileName dir;
		TInt iPos = iCurrentPath.Left(iCurrentPath.Length()-1).LocateReverse('\\');
		if (iPos == KErrNotFound)
			{
			return;
			}
		dir.Append(iCurrentPath.Left(iPos));
		dir.Append(_L("\\"));
		OpenItem(dir);
		}
	else
		{
		CDesCArray* itemArray = static_cast<CDesCArrayFlat*>(iListBox->Model()->ItemTextArray());

		TPtrC file = itemArray->MdcaPoint(index);
		TPtrC type = file.Left(1);
		TInt pos = file.Locate('\t');
		TPtrC name = file.Mid(pos+1);
		if (type.Compare(_L("0"))==0)
			{
			TFileName dir;
			dir.Append(iCurrentPath);
			dir.Append(name);
			dir.Append(_L("\\"));
			OpenItem(dir);
			}
		else
			{
			TFileName file;
			file.Append(iCurrentPath);
			file.Append(name);
			OpenFile(file);
			}
		}
	}

void CListBox::OpenItem(const TDesC &aItem)
	{
	iCurrentPath.Zero();
	iCurrentPath.Append(aItem);
	RPointerArray<TListItem>* iArray;
	iArray = iList->ScanDir(aItem);

	CleanItem();
	AddItem(iArray);

	iArray->ResetAndDestroy();
	iArray->Close();
	}

TBool CListBox::OpenFile(const TDesC& aFile)
	{
	if (CheckFormat(aFile))
		{
		//可以
		iData->AddSelectFile(aFile);
		iNotify->OnListBoxViewNotify();
		return ETrue;
		}
	else 
		{
		//不可以
		HBufC* textResource = StringLoader::LoadLC(R_ERROR_UNACCEPTED_FORMAT);
		UITools::Alter(*textResource);
		CleanupStack::PopAndDestroy(textResource);
		return EFalse;
		}
	}

TBool CListBox::CheckFormat(const TDesC& aFormat)
	{
//	TInt pos;
//	TInt result = iFormatArray->Find(aFormat,pos);
//	return result==KErrNone?ETrue:EFalse;
	
	for(TInt i=0; i<iFormatArray->Count(); i++)
		{
		TPtrC str = (*iFormatArray)[i];
		TInt pos = aFormat.Find(str);
		if (pos!=KErrNotFound)
			{
			return ETrue;
			}
		}
	return EFalse;
	}
void CListBox::CleanItem()
	{
	CDesCArray* itemArray = static_cast<CDesC16ArrayFlat*>(iListBox->Model()->ItemTextArray());

	itemArray->Reset();
	}

void CListBox::SetupListIconsL()
	{
	// Get the name of the file containing the icons	
	//	HBufC* iconFileName;
	//	iconFileName = StringLoader::LoadLC(R_ICON_FILE_NAME);	// Pushes iconFileName onto the Cleanup Stack.

	// Create an array of icons, reading them from the file
	CArrayPtr<CGulIcon>* icons = new(ELeave) CAknIconArray(EItemTypeTotal);
	CleanupStack::PushL(icons);
	icons->AppendL(iEikonEnv->CreateIconL(KListIcon, EMbmLemonplayerListfolder, EMbmLemonplayerListmask));
	icons->AppendL(iEikonEnv->CreateIconL(KListIcon, EMbmLemonplayerListmusic, EMbmLemonplayerListmask));
	icons->AppendL(iEikonEnv->CreateIconL(KListIcon, EMbmLemonplayerListfile, EMbmLemonplayerListmask));
	CleanupStack::Pop(icons);
	//	CleanupStack::PopAndDestroy(iconFileName);

	iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons); // passing ownership of icons
	}

void CListBox::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    // TODO: Add your drawing code here
    // example code...
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbBlack );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    
    }