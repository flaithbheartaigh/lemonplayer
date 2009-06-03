/*
* ==============================================================================
*  Name        : ListboxSettingView.cpp
*  Part of     : Listbox example
*  Interface   :
*  Description :
*  Version     :
*
*  Copyright (c) 2007 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation.
* ==============================================================================
*/

#include "YCSettingView.h"
#include "YCSettingList.h"
#include "LemonTangram.hrh"
#include "MacroUtil.h"
#include <akncontext.h>
#include <aknViewAppUi.h> 
#include <LemonTangram_0xEAE107BA.rsg>

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CListboxSettingView::NewL()
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CYCSettingView* CYCSettingView::NewL()
    {
    CYCSettingView* self = new (ELeave) CYCSettingView;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ---------------------------------------------------------------------------
// CListboxSettingView::CListboxSettingView()
// C++ default constructor
// ---------------------------------------------------------------------------
//
CYCSettingView::CYCSettingView()
    {
    }

// ---------------------------------------------------------------------------
// CListboxSettingView::~CListboxSettingView()
// Destructor
// ---------------------------------------------------------------------------
//
CYCSettingView::~CYCSettingView()
	{
	if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        delete iContainer;
        }    
	}

// ---------------------------------------------------------------------------
// CListboxSettingView::Id()
// Returns views id.
// ---------------------------------------------------------------------------
//
TUid CYCSettingView::Id() const 
    { 
    return TUid::Uid( ESettingView ); 
    }

// ---------------------------------------------------------------------------
// CListboxSettingView::HandleCommandL()
// Handles commands.
// ---------------------------------------------------------------------------
//
void CYCSettingView::HandleCommandL( TInt aCommand )
    {
    switch( aCommand )
        {
        default:
            AppUi()->HandleCommandL(aCommand);  
            break;
        }
    }

// ---------------------------------------------------------------------------
// CListboxSettingView::DoActivateL()
// Activates this view.
// ---------------------------------------------------------------------------
//
void CYCSettingView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                      TUid /*aCustomMessageId*/,
                      const TDesC8& /*aCustomMessage*/ )
    {    
    iContainer = CYCSettingList::NewL();
    
    iContainer->SetMopParent( this );
    iContainer->ConstructFromResourceL( R_LISTBOX_SETTING_ITEM_LIST );
    AppUi()->AddToStackL( *this, iContainer );
    
    iContainer->MakeVisible( ETrue );
    iContainer->SetRect( ClientRect() );
    iContainer->ActivateL();
    }

// ---------------------------------------------------------------------------
// CListboxSettingView::DoDeactivate()
// Deactivates this view
// ---------------------------------------------------------------------------
//
void CYCSettingView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromViewStack( *this, iContainer );
        delete iContainer;
        iContainer = NULL;
        }    
    }

// ---------------------------------------------------------------------------
// CListboxSettingView::ConstructL()
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CYCSettingView::ConstructL()
{
    BaseConstructL(R_LISTBOX_SETTINGS_VIEW);
}

// ---------------------------------------------------------------------------
// CListboxSettingView::DynInitMenuPaneL()
// This function is called by the EIKON framework just before it displays a 
// menu pane.
// ---------------------------------------------------------------------------
//
void CYCSettingView::DynInitMenuPaneL( TInt aResourceId, 
                                           CEikMenuPane* aMenuPane )
    {
//    if( aResourceId == R_LISTBOX_CHANGE_SUBMENU )
//        {   
//        aMenuPane->SetItemDimmed( EListboxCommandToSetting, ETrue );  
//        }
    }   

// -----------------------------------------------------------------------------
// CListboxSettingView::HandleSizeChange()
// Called by HandleResourceChangeL() from CListboxAppUi when layout is 
// changed.
// -----------------------------------------------------------------------------
//
void CYCSettingView::HandleSizeChange( TInt aType )
    {
    if( iContainer )
        {
        iContainer->HandleResourceChange( aType );
        
        if( aType==KEikDynamicLayoutVariantSwitch )
            {        
            TRect rect;
            AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
            iContainer->SetRect(rect);
            }
        }         
    } 
