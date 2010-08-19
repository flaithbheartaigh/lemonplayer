/*
 ============================================================================
 Name		: CloverDemoAppContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include <CloverDemo.mbg>
#include <STDLIB.H>
#include <akndef.h>
#include <aknutils.h>

#include "CloverDemoAppContainer.h"
#include "LMSvgUtil.h"
#include "MacroUtil.h"
#include "CLBitmap.h"
#include "QEasingCurve.h"

#include "CLListBox.h"
#include "ListBoxItemControl.h"

const static TInt COUNT = 5;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CCloverDemoAppContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCloverDemoAppContainer* CCloverDemoAppContainer::NewL(const TRect& aRect)
	{
	CCloverDemoAppContainer* self = CCloverDemoAppContainer::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CCloverDemoAppContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCloverDemoAppContainer* CCloverDemoAppContainer::NewLC(const TRect& aRect)
	{
	CCloverDemoAppContainer* self = new (ELeave) CCloverDemoAppContainer;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CCloverDemoAppContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CCloverDemoAppContainer::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();
	SetRect(aRect);
	
//	iBitmap = LMSvgUtil::GetImageFromResourceL(EMbmCloverdemoFromcont);
//	LMSvgUtil::SetIconSize(iBitmap,TSize(32,32));
//	
//	iCurve = new QEasingCurve(QEasingCurve::OutElastic);
//	
//	InitImgs();
//	
//	iPeriodicTimer = CPeriodic::NewL(CActive::EPriorityStandard);
	
	iListBox = CCLListBox::NewL(*this);
	iListBox->SetRect(aRect);
	
	for(TInt i=0; i<20; i++)
		{
		CListBoxItemControl* item = CListBoxItemControl::NewL();
		item->SetText(_L("The Sorcerer's Apprentice fizzles The Nicolas Cage adventure film is "));
		iListBox->AddItem(item);
		}
	iListBox->Init();
	
	ActivateL();
	
	//Start();
	//add your code here ...
	}

void CCloverDemoAppContainer::AnimationCallback()
	{
	this->DrawNow();
	}

// -----------------------------------------------------------------------------
// CCloverDemoAppContainer::CCloverDemoAppContainer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CCloverDemoAppContainer::CCloverDemoAppContainer()
:iBitmap(NULL),iFrame(0)
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CCloverDemoAppContainer::~CCloverDemoAppContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
CCloverDemoAppContainer::~CCloverDemoAppContainer()
	{
	// No implementation required
	SAFE_DELETE_ACTIVE(iPeriodicTimer)
	SAFE_DELETE_ARRAY(iImgs,COUNT)
	SAFE_DELETE(iCurve)
	SAFE_DELETE(iBitmap)
	
	SAFE_DELETE(iListBox)
	}

// ---------------------------------------------------------
// CCloverDemoContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CCloverDemoAppContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CCloverDemoContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CCloverDemoAppContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CCloverDemoContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CCloverDemoAppContainer::HandleControlEventL(CCoeControl* /*aControl*/,
		TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//CCloverDemoAppContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse CCloverDemoAppContainer::OfferKeyEventL(
		const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	// See if we have a selection
	if (iListBox)
		iListBox->OfferKeyEventL(aKeyEvent,aType);
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
// CCloverDemoAppContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CCloverDemoAppContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	gc.SetBrushColor( KRgbWhite );
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	iListBox->Draw(gc);
	//add your code here...
	//DrawImgs();
	}

// -----------------------------------------------------------------------------
// CCloverDemoAppContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CCloverDemoAppContainer::SizeChanged()
	{
	DrawNow();
	}

void CCloverDemoAppContainer::InitImgs()
	{
	iImgs = (CCLBitmap**) malloc (sizeof(CCLBitmap*) * COUNT);
	TReal offset = COUNT;
	offset = 1.0/offset;
	for(TInt i=0; i<COUNT; i++)
		{
		TSize size = iBitmap->SizeInPixels();
		
		TReal index = (TReal)(i+1) * offset;
		index = iCurve->valueForProgress(index);
		//index = ;
		
		size.iWidth *= index;
		size.iHeight *= index;
		
		iImgs[i] = CCLBitmap::NewL();
		iImgs[i]->Create(size,iBitmap->DisplayMode());
		iImgs[i]->Scale(iBitmap);
		}
	}
void CCloverDemoAppContainer::DrawImgs() const
	{
	CWindowGc& gc = SystemGc();
	TInt index = iFrame;
	if (iImgs && iImgs[index] && !iImgs[index]->IsEmputy())
		{
		CFbsBitmap* bitmap = iImgs[index]->Bitmap();
		if (bitmap)
			{
			TInt x = ((Rect().Width() - bitmap->SizeInPixels().iWidth) >> 1);
			TInt y = ((Rect().Height() - bitmap->SizeInPixels().iHeight) >> 1);
			gc.BitBlt(TPoint(x,y),bitmap);
			}
		}
	}

void CCloverDemoAppContainer::Start()
	{
	if (iPeriodicTimer && !iPeriodicTimer->IsActive() )
		{
		iPeriodicTimer->Start( 100000, 100000, TCallBack(
				CCloverDemoAppContainer::Period, this) );
		}
	}
void CCloverDemoAppContainer::Stop()
	{
	if (iPeriodicTimer && iPeriodicTimer->IsActive() )
		{
		iPeriodicTimer->Cancel();
		}
	}

TInt CCloverDemoAppContainer::Period(TAny* aPtr)
	{
	( static_cast<CCloverDemoAppContainer*>( aPtr ) )->DoPeriodTask();
	// Returning a value of TRUE indicates the callback should be done again
	return ETrue;
	}

void CCloverDemoAppContainer::DoPeriodTask()
	{	
	DrawNow();
	
	Update();
	}

void CCloverDemoAppContainer::Update()
	{
	
//	if (iFrame < COUNT-1)
//		iFrame ++;
	if (++iFrame >= COUNT)
		iFrame = 0;
	
	}

void CCloverDemoAppContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if  ( aType == KEikDynamicLayoutVariantSwitch )
    	{
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EScreen, rect);
//        SetRect(rect);
        
        if (iListBox)
        	iListBox->SetRect(rect);
        }
    }
// End of File
