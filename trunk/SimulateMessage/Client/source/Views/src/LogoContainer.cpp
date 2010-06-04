/*
 ============================================================================
 Name		: LogoContainer.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLogoContainer implementation
 ============================================================================
 */

#include <coemain.h>
#include <akndef.h>
#include <aknutils.h>
#include "LogoContainer.h"
#include <fbs.h>
#include <SimulateMessage.mbg>
#include "Utils.h"
#include "MacroUtil.h"
#include "LMSvgUtil.h"

CLogoContainer::CLogoContainer()
:iLogo(NULL)
	{
	// No implementation required
	}

CLogoContainer::~CLogoContainer()
	{
	SAFE_DELETE(iLogo);
	}

CLogoContainer* CLogoContainer::NewLC(const TRect& aRect)
	{
	CLogoContainer* self = new (ELeave) CLogoContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

CLogoContainer* CLogoContainer::NewL(const TRect& aRect)
	{
	CLogoContainer* self = CLogoContainer::NewLC(aRect);
	CleanupStack::Pop(); // self;
	return self;
	}

void CLogoContainer::ConstructL(const TRect& aRect)
	{
	CreateWindowL();
	SetRect(aRect);
	iLogo = LMSvgUtil::GetImageFromResourceL(EMbmSimulatemessageLogo);
	
	ActivateL();
	}

// ---------------------------------------------------------
// CLogoContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CLogoContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CLogoContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CLogoContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CLogoContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CLogoContainer::HandleControlEventL(CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CLogoContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CLogoContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode /*aType*/)
	{
	// See if we have a selection
	TInt code = aKeyEvent.iCode;
	switch (code)
		{
		//add your code here...

		default:
			break;
		}
	return EKeyWasNotConsumed;
	}
// -----------------------------------------------------------------------------
// CLogoContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CLogoContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	if (iLogo)
		{
		TInt x = (Rect().Width() -  iLogo->SizeInPixels().iWidth)  >> 1;
		TInt y = (Rect().Height() - iLogo->SizeInPixels().iHeight) >> 1;
		gc.BitBlt(TPoint(x,y),iLogo);
		}
	//add your code here...
	}

// -----------------------------------------------------------------------------
// CLogoContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CLogoContainer::SizeChanged()
	{
	DrawNow();
	}

void CLogoContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if  ( aType == KEikDynamicLayoutVariantSwitch )
    	{
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EScreen, rect);
        SetRect(rect);
        }
    }
// End of File
