/*
 ============================================================================
 Name		: Tangram3DAppView.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __TANGRAM3DAPPVIEW_h__
#define __TANGRAM3DAPPVIEW_h__

// INCLUDES
#include <coecntrl.h>

class CLT3DEngine;
// CLASS DECLARATION
class CTangram3DAppView : public CCoeControl
	{
public:
	// New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CTangram3DAppView object, which will draw itself to aRect.
	 * @param aRect The rectangle this view will be drawn to.
	 * @return a pointer to the created instance of CTangram3DAppView.
	 */
	static CTangram3DAppView* NewL(const TRect& aRect);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Create a CTangram3DAppView object, which will draw itself
	 * to aRect.
	 * @param aRect Rectangle this view will be drawn to.
	 * @return A pointer to the created instance of CTangram3DAppView.
	 */
	static CTangram3DAppView* NewLC(const TRect& aRect);

	/**
	 * ~CTangram3DAppView
	 * Virtual Destructor.
	 */
	virtual ~CTangram3DAppView();

public:
	// Functions from base classes

	/**
	 * From CCoeControl, Draw
	 * Draw this CTangram3DAppView to the screen.
	 * @param aRect the rectangle of this view that needs updating
	 */
	void Draw(const TRect& aRect) const;

	/**
	 * From CoeControl, SizeChanged.
	 * Called by framework when the view size is changed.
	 */
	virtual void SizeChanged();

	/**
	 * From CoeControl, HandlePointerEventL.
	 * Called by framework when a pointer touch event occurs.
	 * Note: although this method is compatible with earlier SDKs, 
	 * it will not be called in SDKs without Touch support.
	 * @param aPointerEvent the information about this event
	 */
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 * Perform the second phase construction of a
	 * CTangram3DAppView object.
	 * @param aRect The rectangle this view will be drawn to.
	 */
	void ConstructL(const TRect& aRect);

	/**
	 * CTangram3DAppView.
	 * C++ default constructor.
	 */
	CTangram3DAppView();
	
	static TInt DrawCallBack( TAny* aInstance );

private:
	CLT3DEngine* iEngine;
	CPeriodic*  iPeriodic;
	};

#endif // __TANGRAM3DAPPVIEW_h__
// End of File
