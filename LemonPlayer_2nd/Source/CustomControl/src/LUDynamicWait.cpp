/*
 ============================================================================
 Name		: LUDynamicWait.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLUDynamicWait implementation
 ============================================================================
 */

#include "LUDynamicWait.h"
#include <avkon.rsg>

CLUDynamicWait::CLUDynamicWait()
	{
	// No implementation required
	}

CLUDynamicWait::~CLUDynamicWait()
	{
	if (iWaitDialog)
		{
		iWaitDialog->ProcessFinishedL();
//		TRAP_IGNORE( iWaitDialog->ProcessFinishedL() );
		}
	}

CLUDynamicWait* CLUDynamicWait::NewLC()
	{
	CLUDynamicWait* self = new (ELeave)CLUDynamicWait();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLUDynamicWait* CLUDynamicWait::NewL()
	{
	CLUDynamicWait* self=CLUDynamicWait::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CLUDynamicWait::ConstructL()
	{
	}

void CLUDynamicWait::DialogDismissedL(const TInt aButtonId)
	{
	TInt id = 0;
	id = aButtonId;
	}

void CLUDynamicWait::CloseWaitNoteL()
	{
	if (iWaitDialog)
		{
		iWaitDialog->ProcessFinishedL();
		}
	}

void CLUDynamicWait::OpenWaitNoteL(const TInt aResourceId)
	{
	CloseWaitNoteL();

	iWaitDialog = new (ELeave) CAknWaitDialog(
			reinterpret_cast<CEikDialog**>( &iWaitDialog ) );
	iWaitDialog->SetCallback( this);
	iWaitDialog->ExecuteLD(aResourceId);
	}

void CLUDynamicWait::UpdateTextL(const TDesC& aText)
	{
	if (iWaitDialog)
		iWaitDialog->SetTextL(aText);
	}

void CLUDynamicWait::Finished()
	{
//	UpdateCBA(R_AVKON_SOFTKEYS_OK_EMPTY);
	}
	
void CLUDynamicWait::UpdateCBA(const TInt aId)
	{
//	CEikButtonGroupContainer* cba = CEikButtonGroupContainer::Current();
//	cba->SetCommandSetL( aId );
//	iWaitDialog->ButtonGroupContainer().SetCommandSetL(aId);
//	iWaitDialog->ButtonGroupContainer().DrawNow();
	CEikButtonGroupContainer &cba = iWaitDialog->ButtonGroupContainer();

	cba.SetCommandSetL( aId );
	cba.DrawNow();
	}
