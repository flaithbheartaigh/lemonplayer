/*
 ============================================================================
 Name		: LemonTangramAppView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "LemonTangramAppView.h"
#include "TangImageManager.h"
#include "LemonTangramContainer.h"
#include "LemonTangram.hrh"
#include "LemonTangramContainer.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLemonTangramAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLemonTangramAppView* CLemonTangramAppView::NewL(const TRect& aRect)
	{
	CLemonTangramAppView* self = CLemonTangramAppView::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CLemonTangramAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLemonTangramAppView* CLemonTangramAppView::NewLC(const TRect& aRect)
	{
	CLemonTangramAppView* self = new ( ELeave ) CLemonTangramAppView;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CLemonTangramAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLemonTangramAppView::ConstructL(const TRect& /*aRect*/)
	{
	BaseConstructL();
	}

// -----------------------------------------------------------------------------
// CLemonTangramAppView::CLemonTangramAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLemonTangramAppView::CLemonTangramAppView():
iBWContainer(NULL)
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLemonTangramAppView::~CLemonTangramAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CLemonTangramAppView::~CLemonTangramAppView()
	{
	if(iBWContainer)
	{
		AppUi()->RemoveFromStack(iBWContainer) ;
		delete iBWContainer;
		iBWContainer = NULL ;
	}
	// No implementation required
	}


void  CLemonTangramAppView::DoActivateL (const TVwsViewId &/*aPrevViewId*/, 
		TUid /*aCustomMessageId*/, const TDesC8 &/*aCustomMessage*/) 
{
	if (!iBWContainer)
		{
		iBWContainer = new (ELeave) CLemonTangramContainer;
		iBWContainer->ConstructL(ClientRect() );
		}
	if (iBWContainer)
		{
		iBWContainer->SetMopParent( this);
		AppUi()->AddToStackL( *this, iBWContainer);
	
		iBWContainer->MakeVisible(ETrue);
		iBWContainer->SetRect(ClientRect() );
		iBWContainer->ActivateL();
		}
}

void  CLemonTangramAppView::DoDeactivate () 
{
	if(iBWContainer)
	{
		AppUi()->RemoveFromStack(iBWContainer) ;
		iBWContainer->MakeVisible(EFalse);
	}
	
}

void  CLemonTangramAppView::HandleCommandL (TInt /*aCommand*/)
	{
	
	}

TUid  CLemonTangramAppView::Id () const
{
	return TUid::Uid(ELemonViewMain);;
}
// End of File
