/*
 ============================================================================
 Name		: UIManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIManager declaration
 ============================================================================
 */

#ifndef UIMANAGER_H
#define UIMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <coedef.h>
#include "UIInterface.h"
#include "LPDebug.h"
#include "AnimationEffectDefine.h"
// CLASS DECLARATION
class CUIViewData;
class MUIOperateInterface;
/**
 *  CUIManager
 * 
 */
class CUIManager : public CBase
	{
public:
	~CUIManager();
	static CUIManager* NewL();
	static CUIManager* NewLC();

private:
	CUIManager();
	void ConstructL();

public:
	TBool Update();
	void UpdateDisplay(CWindowGc& gc);
	void UpdateDisplay(CFbsBitGc& aBitGc);
	
	TKeyResponse KeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType, 
			EAnimationEffectType& aEffect);
	
	void DynInitMenuBarL(TInt aResourceId, CEikMenuBar* aMenuBar);
	void HandleCommandL(TInt aCommand);
	
private:
	void ConstructEcom();
	
private:
	CUIInterface** iUI;
	TInt iIndexCur;
	TInt iIndexTotal;
	
	CUIViewData *iData;
	MUIOperateInterface *iOperate;
	CFileLogger* iFileLogger;
	};

#endif // UIMANAGER_H
