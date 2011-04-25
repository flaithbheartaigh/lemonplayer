/*
 ============================================================================
 Name		: MainScreenContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container control for application.
 ============================================================================
 */

#ifndef MAINSCREENCONTAINER_H
#define MAINSCREENCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <GULICON.H>	//CGulIcon

#include <AknsBasicBackgroundControlContext.h> 
#include <aknsdrawutils.h>
#include <aknscontrolcontext.h>
#include <AknsSkinInstance.h>
#include <aknsutils.h>

#include <aknbutton.h>
#include <eikclb.h>

#include "TimeWorkManager.h"
#include "DetailListBox.h"
// FORWARD DECLARATIONS
class CMainScreenView;
// CLASS DECLARATION

/**
 *  CMainScreenContainer  container control class.
 *  
 */
class CMainScreenContainer : public CCoeControl
							,public MCoeControlObserver 
							,public MTimeWorkNotify
							,public MDetailListBoxNotify
	{
public:
	// Constructors and destructor		
	~CMainScreenContainer();
	static CMainScreenContainer* NewL(const TRect& aRect,CMainScreenView* aParent);
	static CMainScreenContainer* NewLC(const TRect& aRect,CMainScreenView* aParent);

private:
	enum TControls
		{
		ECtrlBtnAdd = 0,
		ECtrlBtnRemove,
		ECtrlBtnRules,
		ECtrlBtnAbout,
		ECtrlBtnExit,
		ECtrlList,
		ECtrlTotal,
		};
	// New functions
	void ConstructL(const TRect& aRect);
	CMainScreenContainer(CMainScreenView* aParent);

public:
	// Functions from base classes
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void HandleResourceChange( TInt aType );
	
	virtual void TimeOut();
	
	void HandleListEvent(MDetailListBoxNotify::TEventType aEvent);
	
	void RemoveTask();	
private:
	// Functions from base classes
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
	
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	
	void InitButtons();
	void ReleaseButtons();
	CAknButton* CreateButton(const TInt	aResourceId);
	
	void InitList();
	void ReleaseList();
	void UpdateDisplay();
	
	void Start();
	void Stop();
	static TInt Period( TAny* aPtr );
	void DoPeriodTask();	
	void Update();
	void Layout();
private:
	CPeriodic* iPeriodicTimer;
	
	CAknsBasicBackgroundControlContext* iBgContext;
	
	CAknButton*	iBtnAdd;
	CAknButton*	iBtnRemove;
	CAknButton*	iBtnRules;
	CAknButton*	iBtnAbout;
	CAknButton*	iBtnExit;
	
	CDetailListBox* iListBox;
	
	CMainScreenView* iParent;
	};

#endif

