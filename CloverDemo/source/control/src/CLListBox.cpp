/*
 ============================================================================
 Name		: ListBox.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBox implementation
 ============================================================================
 */

#include "CLListBox.h"
#include "MacroUtil.h"

#include "BackgroundControl.h"
#include "ScrollControl.h"
#include "ListBoxContainerControl.h"

CCLListBox::CCLListBox(MAnimationNofity& aNotify)
:iBackground(NULL),iContainer(NULL),iScroll(NULL),CAnimationFrame(aNotify)
	{
	// No implementation required
	}

CCLListBox::~CCLListBox()
	{
	SAFE_DELETE(iBackground)
	SAFE_DELETE(iContainer)
	SAFE_DELETE(iScroll)
	}

CCLListBox* CCLListBox::NewLC(MAnimationNofity& aNotify)
	{
	CCLListBox* self = new (ELeave) CCLListBox(aNotify);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CCLListBox* CCLListBox::NewL(MAnimationNofity& aNotify)
	{
	CCLListBox* self = CCLListBox::NewLC(aNotify);
	CleanupStack::Pop(); // self;
	return self;
	}

void CCLListBox::ConstructL()
	{
	iFuncs = new RPointerArray<TCallBack>;
	iAnimer = CPeriodic::NewL(CActive::EPriorityIdle);
	
	iContainer = CListBoxContainerControl::NewL();
	iContainer->SetAnimation(this);
	}

void CCLListBox::Draw(CBitmapContext& gc) const
	{
	if (iBackground)
		iBackground->Draw(gc);
	
	if (iContainer)
		iContainer->Draw(gc);

	if (iScroll)
		iScroll->Draw(gc);
	}


void CCLListBox::SetRect(const TRect &aRect)
	{
	CBaseControl::SetRect(aRect);
	
	if (iContainer)
		iContainer->SetRect(aRect);
	}

void CCLListBox::ReSize(const TRect &aRect)
	{
	CBaseControl::ReSize(aRect);
	
	if (iContainer)
		iContainer->ReSize(aRect);
	}

TKeyResponse CCLListBox::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	if (iContainer)
		return iContainer->OfferKeyEventL(aKeyEvent,aType);
	return EKeyWasNotConsumed;
	}

void CCLListBox::AddItem(CListBoxItemControl* aItem)
	{
	if (iContainer)
		iContainer->AddItem(aItem);
	}

void CCLListBox::Init()
	{
	if (iContainer)
		iContainer->CheckMarquee();
	}
