/*
 ============================================================================
 Name		: MsgDataTimeControl.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMsgDataTimeControl implementation
 ============================================================================
 */

#include "MsgDataTimeControl.h"
#include <aknsutils.h> 
#include <BARSREAD.H>
#include "SHPlatform.h"

CMsgDataTimeControl::CMsgDataTimeControl(
		MMsgBaseControlObserver& aBaseControlObserver) :
	CMsgExpandableControl(aBaseControlObserver)
	{
	// No implementation required
	}

CMsgDataTimeControl::~CMsgDataTimeControl()
	{
//	iEikonEnv->EikAppUi()->RemoveFromStack(iTimeAndDateEditor);
	AknsUtils::DeregisterControlPosition(iTimeAndDateEditor);
	delete iTimeAndDateEditor;
	}

void CMsgDataTimeControl::ConstructFromResourceL(TInt aResourceId)
	{
	CMsgExpandableControl::ConstructFromResourceL(aResourceId);

	TResourceReader reader;
	// Create editor
	iTimeAndDateEditor = new (ELeave) CEikTimeAndDateEditor;
//	iTimeAndDateEditor = new (ELeave) CEikTimeEditor;
//	iTimeAndDateEditor->SetContainerWindowL(*this);
	iEikonEnv->CreateResourceReaderLC(reader, R_EDITOR_TIME_AND_DATE);
	iTimeAndDateEditor->ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy(); // reader internal state

	TRgb textColor;
	if (AknsUtils::GetCachedColor(AknsUtils::SkinInstance(), textColor,
			KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6) != KErrNone)
		{
		textColor = AKN_LAF_COLOR_STATIC( 215 );
		}
//	iTimeAndDateEditor->SetUseOverrideColors(ETrue);
//	iTimeAndDateEditor->OverrideColorL(EColorControlText, textColor);//覆盖了颜色后 背景消失
	iTimeAndDateEditor->SetFont(iCaptionLayout.Font());
	
	iTimeAndDateEditor->ActivateL();
//	iTimeAndDateEditor->DrawNow();
//	iTimeAndDateEditor->SetSuppressBackgroundDrawing(EFalse);

	iTimeAndDateEditor->SetTimeAndDate(TTime(TDateTime(2000, EJanuary, 0, 0, 0,
			0, 0)));
	
//	iEikonEnv->EikAppUi()->AddToStackL(
//			iTimeAndDateEditor);
	}

TKeyResponse CMsgDataTimeControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	//	if (iTimeAndDateEditor->IsFocused())
		return iTimeAndDateEditor->OfferKeyEventL(aKeyEvent, aType);	
	}

// ---------------------------------------------------------
// CMsgBodyControl::CountComponentControls
//
// Returns a number of controls.
// ---------------------------------------------------------
//
TInt CMsgDataTimeControl::CountComponentControls() const
	{
	CCoeControl* controls[] =
		{
		iCaption, iTimeAndDateEditor
		};

	TInt count = 0;
	for (TUint ii = 0; ii < sizeof(controls) / sizeof(CCoeControl*); ii++)
		{
		if (controls[ii])
			{
			count++;
			}
		}

	return count;
	}

// ---------------------------------------------------------
// CMsgBodyControl::ComponentControl
//
// Returns a control of index aIndex.
// ---------------------------------------------------------
//
CCoeControl* CMsgDataTimeControl::ComponentControl(TInt aIndex) const
	{
	CCoeControl* controls[] =
		{
		iCaption, iTimeAndDateEditor
		};

	return controls[aIndex];
	//	for (TUint ii = 0; ii < sizeof(controls) / sizeof(CCoeControl*); ii++)
	//		{
	//		if (controls[ii] && aIndex-- == 0)
	//			{
	//			return controls[ii];
	//			}
	//		}
	//
	//	return NULL;
	}

// ---------------------------------------------------------
// CMsgBodyControl::SizeChanged
//
// Sets position for the editor.
// ---------------------------------------------------------
//
//void CMsgDataTimeControl::SizeChanged()
//	{
//	TPoint editorPosition(Position());
//	editorPosition.iY += iEditorTop;
//	iTimeAndDateEditor->SetExtent(editorPosition, iTimeAndDateEditor->Size());
//
//	AknsUtils::RegisterControlPosition(this);
//	AknsUtils::RegisterControlPosition(iTimeAndDateEditor);
//	}

void CMsgDataTimeControl::SizeChanged()
	{
	// TODO: No point to do all these calculations every time!
	if (iControlModeFlags & EMsgControlModeSizeChanging)
		{
		}
	else
		{
		TPoint editorPosition(iEditorLayout.TextRect().iTl.iX, iPosition.iY
				+ iEditorTop);

		TPoint captionPosition(iCaptionLayout.TextRect().iTl.iX, iPosition.iY
				+ iCaptionTop);

		iCaption->SetPosition(captionPosition);
		iCaption->MakeVisible(captionPosition.iY >= 0);

		TSize editorSize(iEditorLayout.TextRect().Width(),
				iEditorLayout.TextRect().Height());
		iTimeAndDateEditor->SetSize(editorSize);

		TRect editorRect(editorPosition, iTimeAndDateEditor->Size());

		if (editorRect != iTimeAndDateEditor->Rect())
			{
			iTimeAndDateEditor->SetRect(editorRect); // SetPosition cannot be used here
			}

		AknsUtils::RegisterControlPosition(this);
		AknsUtils::RegisterControlPosition(iCaption);

		AknsUtils::RegisterControlPosition(iTimeAndDateEditor);
		}

	}

// ---------------------------------------------------------
// CMsgExpandableControl::SetAndGetSizeL
//
// Sets sizes for the caption and control according to aSize.
// ---------------------------------------------------------
//
//void CMsgDataTimeControl::SetAndGetSizeL( TSize& aSize )
//    {   
//    iCaption->SetSize( iCaptionLayout.TextRect().Size() );
//    
//    TSize editorSize( iEditorLayout.TextRect().Width(),
//                      iBaseControlObserver->ViewRect().Height() );        
//
//    iTimeAndDateEditor->SetSize( editorSize );   
//
//    }

// ---------------------------------------------------------
// CMsgBodyControl::FocusChanged
//
// This is called when the focus of the control is changed.
// ---------------------------------------------------------
//
void CMsgDataTimeControl::FocusChanged(TDrawNow aDrawNow)
	{
	// For automatic highlight
	iTimeAndDateEditor->SetFocus(IsFocused(), aDrawNow);
//	if (aDrawNow == EDrawNow)
//		{
//		DrawDeferred();
//		}
	}

// ---------------------------------------------------------
// CMsgBodyControl::SetContainerWindowL
//
// Sets container window.
// ---------------------------------------------------------
//
void CMsgDataTimeControl::SetContainerWindowL(const CCoeControl& aContainer)
	{
	CMsgExpandableControl::SetContainerWindowL(aContainer);

	iTimeAndDateEditor->SetContainerWindowL(*this);
	}

void CMsgDataTimeControl::Draw(const TRect& /*aRect*/) const
	{
	//	CWindowGc& gc = SystemGc();
	//	TRect drawRect(Rect());
	//	gc.Clear(drawRect);
	//
	//	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	//	gc.SetPenColor(KRgbRed);
	//	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	//	gc.SetBrushColor(KRgbGray);
	//	gc.DrawRect(iTimeAndDateEditor->Rect());
	}
