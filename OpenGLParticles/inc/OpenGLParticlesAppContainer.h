/*
 ============================================================================
 Name		: OpenGLParticlesAppContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container class for application.
 ============================================================================
 */

#ifndef __OPENGLPARTICLESAPPCONTAINER_h__
#define __OPENGLPARTICLESAPPCONTAINER_h__

// INCLUDES
#include <coecntrl.h>
#include "Particles.h"
#include "Slideshow.h"
#include "GestureDef.h"
// CLASS DECLARATION
class COpenGLParticlesAppContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor		
	~COpenGLParticlesAppContainer();
	static COpenGLParticlesAppContainer* NewL(const TRect& aRect);
	static COpenGLParticlesAppContainer* NewLC(const TRect& aRect);

public:
	// New functions

public:
	// Functions from base classes
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

private:
	// Functions from base classes
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

	COpenGLParticlesAppContainer();
	void ConstructL(const TRect& aRect);
	
	static TInt DrawCallBack( TAny* aInstance );
	
	TGestureType GetGestureType(const TPoint& aStartPoint, const TPoint& aEndPoint);

private:
	//data
	CParticles* iEngine;
	CPeriodic*  iPeriodic;
	CSlideshow* iSlide;
	
	TPoint iPointStart;
	TInt iDragNumber;
	};

#endif // __OPENGLPARTICLESAPPVIEW_h__
// End of File
