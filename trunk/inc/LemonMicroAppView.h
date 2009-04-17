/*
 ============================================================================
 Name		: LemonMicroAppView.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __LEMONMICROAPPVIEW_h__
#define __LEMONMICROAPPVIEW_h__

// INCLUDES
#include <coecntrl.h>

// CLASS DECLARATION
class CLemonMicroAppView : public CCoeControl
	{
public:
	// New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CLemonMicroAppView object, which will draw itself to aRect.
	 * @param aRect The rectangle this view will be drawn to.
	 * @return a pointer to the created instance of CLemonMicroAppView.
	 */
	static CLemonMicroAppView* NewL(const TRect& aRect);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Create a CLemonMicroAppView object, which will draw itself
	 * to aRect.
	 * @param aRect Rectangle this view will be drawn to.
	 * @return A pointer to the created instance of CLemonMicroAppView.
	 */
	static CLemonMicroAppView* NewLC(const TRect& aRect);

	/**
	 * ~CLemonMicroAppView
	 * Virtual Destructor.
	 */
	virtual ~CLemonMicroAppView();

public:
	// Functions from base classes

	/**
	 * From CCoeControl, Draw
	 * Draw this CLemonMicroAppView to the screen.
	 * @param aRect the rectangle of this view that needs updating
	 */
	void Draw(const TRect& aRect) const;

	/**
	 * From CoeControl, SizeChanged.
	 * Called by framework when the view size is changed.
	 */
	virtual void SizeChanged();

private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 * Perform the second phase construction of a
	 * CLemonMicroAppView object.
	 * @param aRect The rectangle this view will be drawn to.
	 */
	void ConstructL(const TRect& aRect);

	/**
	 * CLemonMicroAppView.
	 * C++ default constructor.
	 */
	CLemonMicroAppView();

	};

#endif // __LEMONMICROAPPVIEW_h__
// End of File
