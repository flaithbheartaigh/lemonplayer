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

enum TGameState
	{
	EGameStateLogo = 0,
	EGameStateInit,
	EGameStateMain
	};

class CLemonMicroAppView : public CCoeControl
	{
public:
	// New methods

	static CLemonMicroAppView* NewL(const TRect& aRect);
	static CLemonMicroAppView* NewLC(const TRect& aRect);
	virtual ~CLemonMicroAppView();

public:
	void Draw(const TRect& aRect) const;
	virtual void SizeChanged();

private:
	// Constructors
	void ConstructL(const TRect& aRect);
	CLemonMicroAppView();
	
	void StateLoop();
	void StateDisplay();
	void StateKey();
	
private:
	TGameState iGameState;

	};

#endif // __LEMONMICROAPPVIEW_h__
// End of File
