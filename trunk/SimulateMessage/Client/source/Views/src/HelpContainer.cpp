/*
 ============================================================================
 Name		: HelpContainer.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CHelpContainer implementation
 ============================================================================
 */

#include <coemain.h>
#include <StringLoader.h> 
#include <eikenv.h>
#include <txtrich.h>
#include <aknutils.h>

#include "HelpContainer.h"
#include "MacroUtil.h"
#include "Utils.h"

#include <SimulateMessage_0xE70CE849.rsg>

#include "SHPlatform.h"

CHelpContainer::CHelpContainer() :
	iText(NULL),iRtEd(NULL)
	{
	// No implementation required
	}

CHelpContainer::~CHelpContainer()
	{
		//	SAFE_DELETE(iCaption);
		SAFE_DELETE(iRtEd);
		SAFE_DELETE(iText);

		SAFE_DELETE(iBgContext);
	}

CHelpContainer* CHelpContainer::NewLC(const TRect& aRect)
	{
	CHelpContainer* self = new (ELeave) CHelpContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

CHelpContainer* CHelpContainer::NewL(const TRect& aRect)
	{
	CHelpContainer* self = CHelpContainer::NewLC(aRect);
	CleanupStack::Pop(); // self;
	return self;
	}

void CHelpContainer::ConstructL(const TRect& aRect)
	{
	CreateWindowL();

	ReadTextL();

	iRtEd = new (ELeave) CEikRichTextEditor;

	Prepare();

	iRtEd->ConstructL(this, 0, 0, EEikEdwinAvkonDisableCursor|EEikEdwinReadOnly);
	iRtEd->SetFocus(ETrue);

	SetRect(aRect);

	TRgb color;
	AknsUtils::GetCachedColor(AknsUtils::SkinInstance(), color,
			KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG1/*EAknsCIQsnLineColorsCG1 */);

//	SetColor(color);
	const CFont* font = SHUI()->GetFont();
	SetFontAndColor(font,color);
	IntroL();
	ActivateL();
	SetupL();

	iBgContext = CAknsBasicBackgroundControlContext::NewL(
			KAknsIIDQsnBgAreaMain, aRect, ETrue);
	}

// ---------------------------------------------------------
// CHelpContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CHelpContainer::CountComponentControls() const
	{
	TInt count(0);
	if (iRtEd)
		count++;
	return count; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CHelpContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CHelpContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		case 0:
			return iRtEd;
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CHelpContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CHelpContainer::HandleControlEventL(CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CHelpContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CHelpContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	// See if we have a selection
	if (iRtEd)
		{
		switch (aType)
			{
			case EEventKey:
				switch (aKeyEvent.iCode)
					{
					case EKeyUpArrow:
						iRtEd->MoveCursorL(TCursorPosition::EFPageUp, EFalse);
						return EKeyWasConsumed;
					case EKeyDownArrow:
						iRtEd->MoveCursorL(TCursorPosition::EFPageDown, EFalse);
						return EKeyWasConsumed;
					default:
						break;
						//return iRtEd->OfferKeyEventL(aKeyEvent, aType);
					}
				break;
			}
		}
	return EKeyWasNotConsumed;
	}
// -----------------------------------------------------------------------------
// CHelpContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CHelpContainer::Draw(const TRect& aRect) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	MAknsControlContext* cc = AknsDrawUtils::ControlContext(this);
	AknsDrawUtils::Background(skin, cc, this, gc, aRect);
	//add your code here...
	}

// -----------------------------------------------------------------------------
// CHelpContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CHelpContainer::SizeChanged()
	{
	TRect rect = Rect();

#ifdef __SERIES60_3X__
	TRect ScrollBarRect = iRtEd->ScrollBarFrame()->VerticalScrollBar()->Rect();
	//In 3rd edition CEikRichTextEditor draw the view for the whole rect and
	//the scrollbar doesn't show. That is a reason why CEikRichTextEditor Width() is
	//rect.Width()-ScrollBarRect.Width()
	iRtEd->SetExtent(TPoint(0, 0), TSize(rect.Width() - ScrollBarRect.Width(),
			rect.Height()));
#else
	iRtEd->SetExtent(TPoint(0,StatusLineHeight),
			TSize(rect.Width(), rect.Height()-StatusLineHeight));
#endif

	if (iBgContext)
		{
		iBgContext->SetRect(Rect());
		if (&Window())
			{
			iBgContext->SetParentPos(PositionRelativeToScreen());
			}
		}

	}

TBool CHelpContainer::ReadTextL()
	{
	TFileName filename;
	GetAppPath(filename);
	HBufC* textResource = StringLoader::LoadLC(R_HELP_FILE);
	filename.Append(textResource->Des());
	CleanupStack::PopAndDestroy(textResource);

	RFile file;
	TInt nErr = file.Open(CEikonEnv::Static()->FsSession(), filename, EFileRead
			| EFileShareAny);
	if (nErr)
		{
		return EFalse;
		}

	TFileText fileText;
	fileText.Set(file);
	TBuf<128> linePtr;

	while (fileText.Read(linePtr) == KErrNone)
		{
		if (iText)
			{
			iText = iText->ReAllocL(iText->Length() + linePtr.Length() + 2);
			iText->Des().Append(linePtr);
			}
		else
			{
			iText = HBufC::NewL(linePtr.Length() + 2);
			iText->Des().Append(linePtr);
			}
		iText->Des().Append(CEditableText::ELineBreak);
		}
	file.Close();

	return ETrue;
	}

void CHelpContainer::Prepare()
	{

	// Lower Case 
	iRtEd->SetAknEditorCase(EAknEditorLowerCase);
	// Fixed case

	iRtEd->SetAknEditorFlags(EAknEditorFlagFixedCase| //Set up the Allowed Cases
			EAknEditorFlagEnableScrollBars // Set up the scroller
	);
	}

void CHelpContainer::SetupL()
	{
	// One way to remove the selection
	//iRtEd->ClearSelectionL();

	// Copy-Paste Support is allowed in Edwin but we can disable
	// to do that uncomment the following line
	//iRtEd->EnableCcpuSupportL(EFalse);
	iRtEd->EnableCcpuSupportL(ETrue);
	// Another way to remove the selection.
	iRtEd->SetCursorPosL(0, EFalse);

	iRtEd->UpdateScrollBarsL();
	SizeChanged();
	}

void CHelpContainer::IntroL()
	{
	SetAlignment(CParaFormat::ELeftAlign);

	//Set the text.
	iRtEd->SetTextL(iText);
	}

void CHelpContainer::SetAlignment(CParaFormat::TAlignment aAlignment)
	{
	CParaFormat paraFormat;
	TParaFormatMask paraFormatMask;

	paraFormatMask.SetAttrib(EAttAlignment); // set the mask
	paraFormat.iHorizontalAlignment = aAlignment;

	iRtEd->ApplyParaFormatL(&paraFormat, paraFormatMask);

	}

void CHelpContainer::SetColor(TRgb aColor)
	{
	TCharFormat charFormat;
	TCharFormatMask charFormatMask;

	charFormat.iFontPresentation.iTextColor = aColor;
	charFormatMask.SetAttrib(EAttColor);

	iRtEd->ApplyCharFormatL(charFormat, charFormatMask);

	//	iRtEd->SetBackgroundColorL(aColor); 
	//  It is possible to change the background color - if foreground and background 
	//  color is same, the text became invisible.
	}

void CHelpContainer::SetFontAndColor(const CFont* aFont, TRgb aColor)
	{
	TCharFormat charFormat;
	TCharFormatMask charFormatMask;

	charFormat.iFontPresentation.iTextColor = aColor;
	charFormatMask.SetAttrib(EAttColor);

	TFontSpec sFontSpec = aFont->FontSpecInTwips();
	charFormatMask.SetAttrib(EAttFontTypeface);
	charFormatMask.SetAttrib(EAttFontHeight);
	charFormat.iFontSpec.iTypeface = sFontSpec.iTypeface;
	charFormat.iFontSpec.iHeight = sFontSpec.iHeight;

	iRtEd->ApplyCharFormatL(charFormat, charFormatMask);
	}

TTypeUid::Ptr CHelpContainer::MopSupplyObject(TTypeUid aId)
	{
	if (iBgContext)
		{
		return MAknsControlContext::SupplyMopObject(aId, iBgContext);
		}
	return CCoeControl::MopSupplyObject(aId);
	}

void CHelpContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if  ( aType == KEikDynamicLayoutVariantSwitch )
    	{
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
        SetRect(rect);
        }
    }
// End of File
