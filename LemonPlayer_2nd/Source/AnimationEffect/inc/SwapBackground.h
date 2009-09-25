/*
 ============================================================================
 Name		: SwapBackground.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSwapBackground declaration
 ============================================================================
 */

#ifndef SWAPBACKGROUND_H
#define SWAPBACKGROUND_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <fbs.h>

#include "AnimationEffectAbstract.h"
#include "AnimationEffectDefine.h"
// CLASS DECLARATION

/**
 *  CSwapBackground
 * 
 */
class CSwapBackground : public CBase
	{
public:	
	// Constructors and destructor
	~CSwapBackground();
	static CSwapBackground* NewL(MEffectSwapNotify* aSwapNotify);
	static CSwapBackground* NewLC(MEffectSwapNotify* aSwapNotify);

private:
	CSwapBackground(MEffectSwapNotify* aSwapNotify);
	void ConstructL();
	
public:	
	void InitSwap(TInt aWidth,TInt aStep,ESwapMode aMode);
	
	TBool Update();
	void UpdateDisplay(CFbsBitGc& gc);	
	
private:
	void InitMove(TInt aWidth,TInt aStep);
	void InitMode(ESwapMode aMode);
	void InitBitmap();
	void InitDisplay();
	void CleanScreen(CFbsBitGc& aBitGc);
	
private:
	//背景,不进行改变的部分
//	CFbsBitmap* iBackground;  
	
	//交替显示的两张背景图片
	CFbsBitmap* iSwapBitmap[2];
	
	//移动宽度
	TInt iWidth;
	//移动步数
	TInt iStep;
	//每帧移动
	TInt iOffset;
	
	//当前位置
	TInt iCurrentPos;	
	
	ESwapMode iMode;
	
	MEffectSwapNotify* iSwapNotify;

	};

#endif // SWAPBACKGROUND_H
