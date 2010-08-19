/*
 ============================================================================
 Name		: OpenGLParticlesAppView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "OpenGLParticlesAppView.h"

#include <OpenGLParticles_0xEC9DD319.rsg>
#include "OpenGLParticles.hrh"

// ============================ MEMBER FUNCTIONS ===============================
COpenGLParticlesAppView::COpenGLParticlesAppView()
	{
	// No implementation required
	iContainer = NULL;
	}

COpenGLParticlesAppView::~COpenGLParticlesAppView()
	{
	DoDeactivate();
	}

COpenGLParticlesAppView* COpenGLParticlesAppView::NewLC()
	{
	COpenGLParticlesAppView* self = new (ELeave) COpenGLParticlesAppView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

COpenGLParticlesAppView* COpenGLParticlesAppView::NewL()
	{
	COpenGLParticlesAppView* self = COpenGLParticlesAppView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void COpenGLParticlesAppView::ConstructL()
	{
	BaseConstructL(R_VIEW_APP);

	//add your code here...

	}
/**
 * 
 * */
TUid COpenGLParticlesAppView::Id() const
	{
	return TUid::Uid(EOpenGLParticlesAppViewId);
	}
void COpenGLParticlesAppView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void COpenGLParticlesAppView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void COpenGLParticlesAppView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
//		iContainer = COpenGLParticlesAppContainer::NewL(ClientRect());
		iContainer = COpenGLParticlesAppContainer::NewL(AppUi()->ApplicationRect());
		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		//add your init code ...

		}
	}
void COpenGLParticlesAppView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}
// End of File
