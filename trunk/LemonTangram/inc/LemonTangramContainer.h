/*
 * ============================================================================
 *  Name     : CLemonPlayerContainer from LemonPlayerContainer.h
 *  Part of  : LemonPlayer
 *  Created  : 17.09.2008 by zengcity
 *  Description:
 *     Declares container control for application.
 *  Version  :
 *  Copyright: 
 * ============================================================================
 */

#ifndef LEMONPLAYERCONTAINER_H
#define LEMONPLAYERCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include "AnimationStruct.h"
#include "MLemonMenuNotify.h"
// FORWARD DECLARATIONS

// CLASS DECLARATION
class CUIManager;
class CTangImageManager;
class CLemonMenu;

enum TGameState
	{
	EGameStateLogo = 0,
	EGameStateInit,
	EGameStateMain
	};

/**
 *  CLemonPlayerContainer  container control class.
 *  
 */
class CLemonTangramContainer : 	public CCoeControl, MCoeControlObserver,
								public CAnimationStruct, public MLemonMenuNotify
	{
public:
	// Constructors and destructor
	void ConstructL(const TRect& aRect);
	~CLemonTangramContainer();

public:
	// New functions

public:
	// Functions from base classes
	virtual TBool Tick();
	virtual void Update();
	
	//MLemonMenuNotify
	virtual void HandMenuCommand(TInt aCommandId);
	
private:
	// Functions from base classes
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
	virtual TKeyResponse OfferKeyEventL(
	                    const TKeyEvent& aKeyEvent,TEventCode aType);
	
	void CreateDoubleBufferBitmapL();
	
	void StateLoop();
	void StateDisplay(CFbsBitGc& gc);
	void StateChange(TGameState aState);
	TKeyResponse StateKey(const TKeyEvent& aKeyEvent,TEventCode aType);
	
	void StateLogoInit();
	void StateLogoLoop();
	void StateLogoDisplay(CFbsBitGc& gc);
	void StateLogoRelease();

	void StateInitInit();
	void StateInitLoop();
	void StateInitDisplay(CFbsBitGc& gc);
	void StateInitRelease();
	
	void StateMainInit();
	void StateMainLoop();
	TKeyResponse StateMainKey(const TKeyEvent& aKeyEvent,TEventCode aType);
	void StateMainDisplay(CFbsBitGc& gc);
	void StateMainRelease();

	void InitManager();
	void InitMenu();

	void SaveProcess();
	void ResetProcess();
	void OpenProcess();
	void SaveScreen();
public:
	void HandleCommandL(TInt aCommand);
	
private:
	TGameState iGameState;
	
	TInt iLogoState;
	CFbsBitmap* iLogo;
	
	TInt iLoadState;
	
	TInt iWidth;
	TInt iHeight;
	CFbsBitmap* 			iDoubleBufferBmp;		// 位图缓冲,owned
	CFbsBitmapDevice*   	iDoubleBufferDevice;	// 位图缓冲关联的device,owned,
	CFbsBitGc*  			iDoubleBufferGc;		// 位图缓冲绘制环境,owned
	
	CTangImageManager* iManager;
	CLemonMenu* iMenu;
	};

#endif

// End of File
