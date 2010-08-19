/*
 ============================================================================
 Name		: OpenGLParticlesAppContainer.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "OpenGLParticlesAppContainer.h"

#define ABS(x) ( (x)>0 ? (x) : -(x) )

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// COpenGLParticlesAppContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
COpenGLParticlesAppContainer* COpenGLParticlesAppContainer::NewL(
		const TRect& aRect)
	{
	COpenGLParticlesAppContainer* self = COpenGLParticlesAppContainer::NewLC(
			aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesAppContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
COpenGLParticlesAppContainer* COpenGLParticlesAppContainer::NewLC(
		const TRect& aRect)
	{
	COpenGLParticlesAppContainer* self =
			new (ELeave) COpenGLParticlesAppContainer;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesAppContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void COpenGLParticlesAppContainer::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();
	SetRect(aRect);
	
//	iEngine = CParticles::NewL(this,&Window());
//	iEngine->SetRedererState();
	
	iSlide = CSlideshow::NewL(this,&Window());
	iSlide->SetRedererState();
	
	EnableDragEvents();
	
	ActivateL();

	//add your code here ...
	iPeriodic = CPeriodic::NewL(CActive::EPriorityIdle); // Create an active object for
	// animating the scene
	iPeriodic->Start(100, 100, TCallBack(COpenGLParticlesAppContainer::DrawCallBack, this));
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesAppContainer::COpenGLParticlesAppContainer()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
COpenGLParticlesAppContainer::COpenGLParticlesAppContainer()
:iEngine(NULL),iSlide(NULL)
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesAppContainer::~COpenGLParticlesAppContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
COpenGLParticlesAppContainer::~COpenGLParticlesAppContainer()
	{
	delete iPeriodic;
	delete iEngine;
	if (iSlide)
		{
		iSlide->AppExit();
		delete iSlide;
		}
	// No implementation required
	}

// ---------------------------------------------------------
// COpenGLParticlesContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt COpenGLParticlesAppContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// COpenGLParticlesContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* COpenGLParticlesAppContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// COpenGLParticlesContainer::HandleControlEventL(
//	 CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void COpenGLParticlesAppContainer::HandleControlEventL(
		CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/)
	{
	// TODO: Add your control event handler code here
	}

//------------------------------------------------------------------
//COpenGLParticlesAppContainer::OfferKeyEventL(
// const TKeyEvent& aKeyEvent,	TEventCode aType)
//-------------------------------------------------------------------
//
TKeyResponse COpenGLParticlesAppContainer::OfferKeyEventL(
		const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	// See if we have a selection
	if (iEngine)
		return iEngine->OfferKeyEventL(aKeyEvent,aType);
	
	if (iSlide)
		{
		switch (aType)
			{
			case EEventKey:
				switch (aKeyEvent.iCode)
					{
					case EKeyUpArrow:
						iSlide->Up();
						break;
					case EKeyDownArrow:
						iSlide->Down();
						break;
					case EKeyLeftArrow:
						iSlide->Left();
						break;
					case EKeyRightArrow:
						iSlide->Right();
						break;
					case EKeyDevice3:
						iSlide->Change();
						break;
//					case '4':
//						iSlide->iTranslateX--;
//						break;
//					case '6':
//						iSlide->iTranslateX++;
//						break;
//					case '2':
//						iSlide->iTranslateY++;
//						break;
//					case '8':
//						iSlide->iTranslateY--;
//						break;
					case '7':
						iSlide->RotateClockwise();
						break;
					case '9':
						iSlide->RotateAnticlockwise();
						break;				
					}
				break;
			}
		return EKeyWasNotConsumed;
		}

	return EKeyWasNotConsumed;
	}

void COpenGLParticlesAppContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
		switch (aPointerEvent.iType)
		    {
				case TPointerEvent::EButton1Down:
					// Save tap position (because it could be the beginning of the gesture)
					iSlide->MouseSelected(aPointerEvent.iPosition.iX,aPointerEvent.iPosition.iY);
					iPointStart = aPointerEvent.iPosition;
					iDragNumber = 0;
				break;
			   
				case TPointerEvent::EButton1Up:
				break;
			 
				case TPointerEvent::EDrag:
					if (iDragNumber++ > 5)
						{
						iDragNumber = 0;
						TGestureType gesture = GetGestureType(iPointStart, aPointerEvent.iPosition);
						iSlide->MouseDrag(gesture,iPointStart,aPointerEvent.iPosition);
						iPointStart = aPointerEvent.iPosition;
						}
				break;
		 
		      default:
		      break;
		   }
	}
// -----------------------------------------------------------------------------
// COpenGLParticlesAppContainer::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void COpenGLParticlesAppContainer::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRect drawRect(Rect());
	gc.Clear(drawRect);

	//add your code here...
	if (iEngine)
		iEngine->Render();
	if (iSlide)
		{
	    if ( iSlide->GetState() != CSlideshow::ELoadingTextures )
	    	iSlide->Render();
		}
	}

// -----------------------------------------------------------------------------
// COpenGLParticlesAppContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void COpenGLParticlesAppContainer::SizeChanged()
	{
	DrawNow();
	}

TInt COpenGLParticlesAppContainer::DrawCallBack(TAny* aInstance)
	{
	COpenGLParticlesAppContainer* instance = (COpenGLParticlesAppContainer*) aInstance;

	instance->DrawNow();

	return 0;
	}

TGestureType COpenGLParticlesAppContainer::GetGestureType(const TPoint& aStartPoint, const TPoint& aEndPoint)
{
	// Default return value
	TGestureType returnValue = EUpDown;

	// Local copies of the passed positions
	TPoint startPoint = aStartPoint;
	TPoint endPoint = aEndPoint;
	
	// Control's extent
	TInt rectHalfWidth  = (ABS(aStartPoint.iX - aEndPoint.iX) + 5)/2;
	TInt rectHalfHeight = (ABS(aStartPoint.iY - aEndPoint.iY) + 5)/2;	
	
	rectHalfWidth  += Min(aStartPoint.iX , aEndPoint.iX);
	rectHalfHeight += Min(aStartPoint.iY , aEndPoint.iY);
	// Start point position type
	TInt startPointLocation = EAreaA;
	// End point position type
	TInt endPointLocation = EAreaA;
	
	// Determine in which logical part of the control is the start point
	if (aStartPoint.iX <= rectHalfWidth)
	{
		if (aStartPoint.iY <= rectHalfHeight)
		{
			startPointLocation = EAreaA;
		}
		else if (aStartPoint.iY > rectHalfHeight)
		{
			startPointLocation = EAreaD;
		}
	}
	else if (aStartPoint.iX > rectHalfWidth)
	{
		if (aStartPoint.iY <= rectHalfHeight)
		{
			startPointLocation = EAreaB;
		}
		else if (aStartPoint.iY > rectHalfHeight)
		{
			startPointLocation = EAreaC;
		}
	}
	
	// Determine in which logical part of the control is the end point
	if (aEndPoint.iX <= rectHalfWidth)
	{
		if (aEndPoint.iY <= rectHalfHeight)
		{
			endPointLocation = EAreaA;
		}
		else if (aEndPoint.iY > rectHalfHeight)
		{
			endPointLocation = EAreaD;
		}
	}
	else if (aEndPoint.iX > rectHalfWidth)
	{
		if (aEndPoint.iY <= rectHalfHeight)
		{
			endPointLocation = EAreaB;
		}
		else if (aEndPoint.iY > rectHalfHeight)
		{
			endPointLocation = EAreaC;
		}
	}
	
	// Calculate actual type of the gesture
	switch (startPointLocation)
	{
		case EAreaA:
			switch (endPointLocation)
			{
				case EAreaA:
					returnValue = ENoneGesture;
				break;
				
				case EAreaB:			
					returnValue = ELeftRight;
				break;
				
				case EAreaC:
					returnValue = ELeftUpRightDown;
				break;
				
				case EAreaD:		
					returnValue = EUpDown;
				break;
				
				default:
					returnValue = ENoneGesture;
				break;
			}
		break;
		
		case EAreaB:
			switch (endPointLocation)
			{
				case EAreaA:
					returnValue = ERightLeft;
				break;
				
				case EAreaB:
					returnValue = ENoneGesture;
				break;
				
				case EAreaC:
					returnValue = EUpDown;
				break;
				
				case EAreaD:
					returnValue = ERightUpLeftDown;
				break;
				
				default:
					returnValue = ENoneGesture;
				break;
			}
		break;
		
		case EAreaC:
			switch (endPointLocation)
			{
				case EAreaA:
					returnValue = ERightDownLeftUp;
				break;
				
				case EAreaB:
					returnValue = EDownUp;
				break;
				
				case EAreaC:
					returnValue = ENoneGesture;
				break;
				
				case EAreaD:
					returnValue = ERightLeft;
				break;
				
				default:
					returnValue = ENoneGesture;
				break;
			}
		break;
		
		case EAreaD:
			switch (endPointLocation)
			{
				case EAreaA:
					returnValue = EDownUp;
				break;
				
				case EAreaB:
					returnValue = ELeftDownRightUp;
				break;
				
				case EAreaC:
					returnValue = ELeftRight;
				break;
				
				case EAreaD:
					returnValue = ENoneGesture;
				break;
				
				default:
					returnValue = ENoneGesture;
				break;
			}
		break;
		
		default:
			returnValue = ENoneGesture;
		break;
	}
		
	return returnValue;
}

// End of File
