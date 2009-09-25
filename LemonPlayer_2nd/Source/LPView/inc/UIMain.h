/*
 ============================================================================
 Name		: UIMain.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIMain declaration
 ============================================================================
 */

#ifndef UIMAIN_H
#define UIMAIN_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <UIInterface.h>

// CLASS DECLARATION
class CUIDisplay;
class CUIXmlParser;
class CTangramAnimation;
class CMainCommand;
/**
 *  CUIMain
 * 
 */
class CUIMain : public CUIInterface
	{
public:
	static CUIMain* NewL(CUIViewData *aData=NULL,
			MUIOperateInterface *aOperate=NULL);
	~CUIMain();
private:
	CUIMain();
	void ConstructL(CUIViewData *aData=NULL,
			MUIOperateInterface *aOperate=NULL);
public:
	virtual TBool Update();
	virtual void UpdateDisplay(CWindowGc& gc);
	virtual void UpdateDisplay(CFbsBitGc& aBitGc);
	virtual TKeyResponse KeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType,
			EAnimationEffectType& aEffect);
	virtual TBool IsOfferKey();
	virtual void DynInitMenuBarL(TInt aResourceId, CEikMenuBar* aMenuBar);
	virtual void HandleCommandL(TInt aCommand);
	
private:
	CUIDisplay 		*iDisplay;
	CUIXmlParser 	*iParser;
	CTangramAnimation* iTangram;
	CMainCommand	*iCommand;
	};

#endif // UIMAIN_H
