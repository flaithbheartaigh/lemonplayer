/*
 ============================================================================
 Name		: Tangram3DAppView.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "Tangram3DAppView.h"
#include "LT3DEngine.h"
#include <eikenv.h>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTangram3DAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTangram3DAppView* CTangram3DAppView::NewL(const TRect& aRect)
	{
	CTangram3DAppView* self = CTangram3DAppView::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CTangram3DAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTangram3DAppView* CTangram3DAppView::NewLC(const TRect& aRect)
	{
	CTangram3DAppView* self = new (ELeave) CTangram3DAppView;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CTangram3DAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTangram3DAppView::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	// Set the windows size
	SetRect(aRect);

	iEngine = CLT3DEngine::NewL(this, &Window());
	iEngine->SetRedererState();

	// Activate the window, which makes it ready to be drawn
	ActivateL();

	iPeriodic = CPeriodic::NewL(CActive::EPriorityIdle); // Create an active object for
	// animating the scene
	iPeriodic->Start(100, 100, TCallBack(CTangram3DAppView::DrawCallBack, this));
	}

// -----------------------------------------------------------------------------
// CTangram3DAppView::CTangram3DAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CTangram3DAppView::CTangram3DAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CTangram3DAppView::~CTangram3DAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CTangram3DAppView::~CTangram3DAppView()
	{
	// No implementation required
	delete iPeriodic;
	delete iEngine;
	}

// -----------------------------------------------------------------------------
// CTangram3DAppView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CTangram3DAppView::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();

	// Gets the control's extent
	TRect drawRect(Rect());

	// Clears the screen
	gc.Clear(drawRect);

	iEngine->Render();

//	gc.SetPenStyle(CGraphicsContext::ESolidPen);
//	gc.SetPenColor(KRgbRed);
//	gc.UseFont(CEikonEnv::Static()->LegendFont());
//	_LIT(KInfo1,"Trans x:%d y:%d,Rotate %d");
//	_LIT(KInfo2,"Light:%d Lamp:%d Spot:%d");
//	TBuf<64> number;
//	//number.Format(KInfo1,iEngine->iTranslateX,iEngine->iTranslateY,iEngine->iRotate);
//	//gc.DrawText(number, TPoint(30, 30));
//
//	
//	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
//	
//	TRect rect;
//	rect.SetSize(TSize(200,200));
//	rect.Move(((Rect().Width() - 200)>>1),((Rect().Height() - 200 )>>1));
//	gc.DrawRect(rect);
	}

// -----------------------------------------------------------------------------
// CTangram3DAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CTangram3DAppView::SizeChanged()
	{
	DrawNow();
	}

// -----------------------------------------------------------------------------
// CTangram3DAppView::HandlePointerEventL()
// Called by framework to handle pointer touch events.
// Note: although this method is compatible with earlier SDKs, 
// it will not be called in SDKs without Touch support.
// -----------------------------------------------------------------------------
//
void CTangram3DAppView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{

	// Call base class HandlePointerEventL()
	CCoeControl::HandlePointerEventL(aPointerEvent);
	}

TInt CTangram3DAppView::DrawCallBack(TAny* aInstance)
	{
	CTangram3DAppView* instance = (CTangram3DAppView*) aInstance;

	instance->DrawNow();

	return 0;
	}

TKeyResponse CTangram3DAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	switch (aType)
		{
		case EEventKey:
			switch (aKeyEvent.iCode)
				{
				case EKeyUpArrow:
					iEngine->Up();
					break;
				case EKeyDownArrow:
					iEngine->Down();
					break;
				case EKeyLeftArrow:
					iEngine->Left();
					break;
				case EKeyRightArrow:
					iEngine->Right();
					break;
				case EKeyDevice3:
					iEngine->Change();
					break;
				case '4':
					iEngine->iTranslateX--;
					break;
				case '6':
					iEngine->iTranslateX++;
					break;
				case '2':
					iEngine->iTranslateY++;
					break;
				case '8':
					iEngine->iTranslateY--;
					break;
				case '7':
					iEngine->RotateClockwise();
					break;
				case '9':
					iEngine->RotateAnticlockwise();
					break;				
				}
			break;
		}
	return EKeyWasNotConsumed;
	}

// End of File
