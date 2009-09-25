/*
 ============================================================================
 Name		: UIList.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIList declaration
 ============================================================================
 */

#ifndef UILIST_H
#define UILIST_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <UIInterface.h>
// CLASS DECLARATION
class CPlaylistMgr;
/**
 *  CUIList
 * 
 */
class CUIList : public CUIInterface
	{
public:
	static CUIList* NewL(CUIViewData *aData=NULL,
			MUIOperateInterface *aOperate=NULL);
	~CUIList();

private:
	CUIList();
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
	CPlaylistMgr* iList;
	};

#endif // UILIST_H
