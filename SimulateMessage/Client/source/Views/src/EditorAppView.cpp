/*
 ============================================================================
 Name		: TestEditorAppView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "EditorAppView.h"

#include "SHPlatform.h"

// ============================ MEMBER FUNCTIONS ===============================
CEditorAppView::CEditorAppView()
:iHeader(NULL)
	{
	// No implementation required
	iContainer = NULL;
	}

CEditorAppView::~CEditorAppView()
	{
	delete iHeader;
	DoDeactivate();	
	}

CEditorAppView* CEditorAppView::NewLC()
	{
	CEditorAppView* self = new (ELeave) CEditorAppView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CEditorAppView* CEditorAppView::NewL()
	{
	CEditorAppView* self = CEditorAppView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CEditorAppView::ConstructL()
	{
	BaseConstructL(R_VIEW_EDITOR);

	//add your code here...

	}
/**
 * 
 * */
TUid CEditorAppView::Id() const
	{
	return TUid::Uid(ESimulateMessageEditViewId);
	}
void CEditorAppView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ECommandInsertContact:
			iContainer->DoUserAddRecipientL();
			break;
		case EAknSoftkeyBack:
			SHChangeView(ESimulateMessageMainScreenViewId);
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}
void CEditorAppView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CEditorAppView::DoActivateL(const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
//		iContainer = CTestEditorAppContainer::NewL(ClientRect());
		iContainer = CMsgEditorView::NewL(*this,0);
		
	    TInt res( R_UNIEDITOR_TO );	    
	    iContainer->AddControlFromResourceL(  res, 
	                                    EMsgAddressControl, 
	                                    0, 
	                                    EMsgHeader );
	    
	    res =  R_UNIEDITOR_DATETIME;	    
	    iContainer->AddControlFromResourceL(  res, 
										EMsgDateTimeControl, 
	                                    EMsgAppendControl, 
	                                    EMsgHeader );
	    
		iContainer->ExecuteL(ClientRect(),0);
		
	    CMsgRecipientList* recipientList = CMsgRecipientList::NewL();
	    CleanupStack::PushL( recipientList );
	    
	    CMsgRecipientItem* recipient = CMsgRecipientItem::NewL(_L("Liang"),_L("13581817869")) ;
	        
	    recipientList->AppendL( recipient );
	       
		iContainer->SetNumberAndContent(*recipientList,_L("Hello"));
		
		CleanupStack::PopAndDestroy();//recipients

//		iContainer->SetMopParent(this);
		AppUi()->AddToStackL(*this, iContainer);

		iContainer->DrawNow();
		//add your init code ...

		}
	}
void CEditorAppView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}

CMsgBaseControl* CEditorAppView::CreateCustomControlL(TInt aControlType)
	{}
void CEditorAppView::EditorObserver(TMsgEditorObserverFunc aFunc, TAny* aArg1, TAny* aArg2, TAny* aArg3)
	{}


//void CEditorAppView::DoSelectionKeyL()
//    {
//    CMsgBaseControl* ctrl = iContainer->FocusedControl();
//
//    if ( ctrl )
//        {
//        switch ( ctrl->ControlId() )
//            {
//            case EMsgComponentIdTo:
//                {                    
//                // Check is there any recipients in address ctrl
//                TBool modified = EFalse;
//                    
//                if ( !modified )//else
//                    {
//                    // Nothing changed on the UI. Open PhoneBook.
//                    DoUserAddRecipientL();
//                    }                    
//                break;
//                }
//            case EMsgComponentIdDateTime:
//            	{            	
//            	}
//            	break;
//            default:
//                {
//                break;
//                }
//            }
//        }
//    }
//
//void CEditorAppView::DoUserAddRecipientL()
//    {
//    TBool invalid = EFalse;
//    // We remove this flag so that it can be shown after the adding operation
//
//    // add to current control or To control
//    TBool addressesAdded(EFalse);
//    
//    if ( !iHeader)
//    	{
//    	iHeader = CUniEditorHeader::NewL();
//    	}
//    TRAP_IGNORE( addressesAdded = iHeader->AddRecipientL(  iContainer->FocusedControl(), 
//													iContainer, 
//                                                    EFalse,
//                                                    invalid ));
//   
//    TInt returnFocusTo = EMsgComponentIdTo;
//    iContainer->SetFocus( returnFocusTo );
//    }

// End of File
