/*
* Copyright (c) 2006,2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:   UniEditor header.
*
*/



// INCLUDE FILES

#include <eikrted.h>
#include <txtrich.h>                // CRichText

#include <centralrepository.h>    // link against centralrepository.lib
//#include <MuiuMsvUiServiceUtilities.h> 
 

#include <MsgExpandableControl.h>
#include <MsgAddressControl.h>
#include <MsgRecipientItem.h>

//#include <MsgMediaInfo.h>

//#include <UniEditor.rsg>
#include <uniaddresshandler.h>

#include "UniEditorHeader.h"


// ==========================================================

// EXTERNAL DATA STRUCTURES

// EXTERNAL FUNCTION PROTOTYPES

// CONSTANTS
const TInt KUniCharAt = '@';
const TInt  KUniMaxSubject  = 40;

// MACROS

// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// LOCAL FUNCTION PROTOTYPES

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CUniEditorHeader::NewL
//
// Two-phased constructor.
// ---------------------------------------------------------
//
CUniEditorHeader* CUniEditorHeader::NewL()
    {
    CUniEditorHeader* self = new ( ELeave ) CUniEditorHeader();
        
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    
    return self;
    }

// ---------------------------------------------------------
// CUniEditorHeader::CUniEditorHeader
//
// Constructor.
// ---------------------------------------------------------
//
CUniEditorHeader::CUniEditorHeader()
    {
    }

// ---------------------------------------------------------
// CUniEditorHeader::ConstructL
// ---------------------------------------------------------
//
void CUniEditorHeader::ConstructL()
    {     
//    iAddDelayed = EUniFeatureTo;
    }

// ---------------------------------------------------------
// CUniEditorHeader::~CUniEditorHeader
// ---------------------------------------------------------
//
CUniEditorHeader::~CUniEditorHeader()
    {
//    delete iHeaders[EHeaderAddressTo].iAddressHandler;
    }



// ---------------------------------------------------------
// CUniEditorHeader::AddRecipientL
// ---------------------------------------------------------
//
TBool CUniEditorHeader::AddRecipientL(  CMsgBaseControl* aFocusedControl,
                                        MObjectProvider* /*aParent*/,
                                        TBool            aIncludeEmailAddresses,
                                        TBool&           aInvalid )
    {
    TBool added = EFalse;
    
    // note order of for ()

            
        // if focus on any other control, add to To: recipient list
    if ( ! iHeaders[EHeaderAddressTo].iAddressHandler )
    	{
			iHeaders[EHeaderAddressTo].iAddressHandler  = CUniAddressHandler::NewL(*(static_cast<CMsgAddressControl*>(aFocusedControl)),*CCoeEnv::Static());
    	}
        if ( iHeaders[EHeaderAddressTo].iAddressHandler )
            {
            added = iHeaders[EHeaderAddressTo].iAddressHandler->AddRecipientL( aInvalid );
            }
        
    return added;
    }
    
    
    

//  End of File
