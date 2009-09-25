/*
 ============================================================================
 Name		: AnimationEffectMgr.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAnimationEffectMgr declaration
 ============================================================================
 */

#ifndef ANIMATIONEFFECTMGR_H
#define ANIMATIONEFFECTMGR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <w32std.h>
#include "AnimationEffectAbstract.h"
#include "AnimationEffectDefine.h"

class CSwapBackground;
//class CTangramAnimation;
// CLASS DECLARATION

/**
 *  CAnimationEffectMgr
 * 
 */
class CAnimationEffectMgr : public CBase,
							public MEffectSwapNotify
	{
public:
	// Constructors and destructor

	~CAnimationEffectMgr();

	static CAnimationEffectMgr* NewL(MAnimationEffectNotify* aAnimationNotify);
	static CAnimationEffectMgr* NewLC(MAnimationEffectNotify* aAnimationNotify);

private:
	CAnimationEffectMgr(MAnimationEffectNotify* aAnimationNotify);
	void ConstructL();
	
public:
	//MEffectSwapNotify
	virtual void InitOrigBitmap(CFbsBitmap*& aBitmap);
	virtual void InitDestBitmap(CFbsBitGc& aBitGc);
	
public:
	TBool Update();
	void Draw(CWindowGc& gc);
	void UpdateDisplay();
	
public:
	void StartEffect(EAnimationEffectType aType);
	
public:
	void InitSwap(TInt aWidth,TInt aStep,ESwapMode aMode);
	void InitNormal();
	
private:
	void CopyScreenToBitmap(CFbsBitmap*& aBitmap);
	void UpdateScreen();
	void DrawScreen(CWindowGc& gc);
	void CleanScreen(CFbsBitGc& aBitGc);
	
private:
	EAnimationEffectType iEffectType;
	CSwapBackground* iSwap;
//	MEffectSwapNotify* iSwapNotify;
	
	MAnimationEffectNotify* iAnimationNotify;
	
	CFbsBitmap* 		iBitmap;
	
//	CTangramAnimation* iTangram;

	};

#endif // ANIMATIONEFFECTMGR_H
