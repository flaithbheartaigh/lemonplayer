/*
 ============================================================================
 Name		: LemonPlayerView.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonPlayerView implementation
 ============================================================================
 */

#include "LemonPlayerView.h"
#include "LemonPlayer.hrh"

#include "LemonPlayerContainer.h" 
#include "MacroUtil.h"

CLemonPlayerView::CLemonPlayerView()
:iAppContainer(NULL)
	{
	// No implementation required
	}

CLemonPlayerView::~CLemonPlayerView()
	{
	SAFE_DELETE(iAppContainer);
	}

CLemonPlayerView* CLemonPlayerView::NewLC()
	{
	CLemonPlayerView* self = new (ELeave)CLemonPlayerView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLemonPlayerView* CLemonPlayerView::NewL()
	{
	CLemonPlayerView* self=CLemonPlayerView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CLemonPlayerView::ConstructL()
	{
	iAppContainer = new (ELeave) CLemonPlayerContainer;
	iAppContainer->ConstructL(ClientRect() );
	}

TUid CLemonPlayerView::Id() const
	{
	return TUid::Uid(ELemonPlayerView);
	}

void CLemonPlayerView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	iAppContainer->SetMopParent( this);

	AppUi()->AddToStackL( *this, iAppContainer);

	iAppContainer->MakeVisible(ETrue);
	iAppContainer->SetRect(ClientRect() );
	iAppContainer->ActivateL();
	}

void CLemonPlayerView::DoDeactivate()
	{
	if (iAppContainer)
		AppUi()->RemoveFromViewStack( *this, iAppContainer );
	}

void CLemonPlayerView::DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane )
	{
	iAppContainer->DynInitMenuBarL(aResourceId,aMenuBar);
	}
