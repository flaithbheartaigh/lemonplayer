/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*       Defines implementation of CUniBaseHeader class methods.
*
*/



// INCLUDE FILES
#include "UniBaseHeader.h"

#include <eikrted.h>
#include <txtrich.h>                // CRichText
#include <mtclbase.h>

#include <centralrepository.h>    // link against centralrepository.lib


#include <MsgExpandableControl.h>
#include <MsgAddressControl.h>

#include <uniaddresshandler.h>


// ==========================================================

// EXTERNAL DATA STRUCTURES

// EXTERNAL FUNCTION PROTOTYPES

// CONSTANTS

// MACROS

// LOCAL CONSTANTS AND MACROS

// MODULE DATA STRUCTURES

// LOCAL FUNCTION PROTOTYPES

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CUniBaseHeader::CUniBaseHeader
//
// Constructor.
// ---------------------------------------------------------
//
EXPORT_C CUniBaseHeader::CUniBaseHeader() 
    {
    //iHeaders[EHeaderAddressFrom].iControlType = EMsgComponentIdFrom;
    //iHeaders[EHeaderAddressTo].iControlType = EMsgComponentIdTo;    
    //iHeaders[EHeaderAddressTo].iRecipientTypeValue = EMsvRecipientTo;
    }

// ---------------------------------------------------------
// CUniBaseHeader::~CUniBaseHeader
// ---------------------------------------------------------
//
EXPORT_C CUniBaseHeader::~CUniBaseHeader()
    {
    for (TInt i = EHeaderAddressFrom; i <= EHeaderAddressTo; i++ )
        {
//        if ( iHeaders[i].iOwned )
//            {
//            delete iHeaders[i].iControl;
//            }
        delete iHeaders[i].iAddressHandler;
        }
    }


//  End of File
