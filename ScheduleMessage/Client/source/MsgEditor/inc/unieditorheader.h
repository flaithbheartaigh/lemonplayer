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



#ifndef __UNIEDITORHEADER_H
#define __UNIEDITORHEADER_H

// INCLUDES
#include <MsgEditorView.h>
#include <MsgEditor.hrh>    // TMsgControlId
#include <MsgAddressControl.h>  

#include "uniaddresshandler.h"
#include "unibaseheader.h"

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

class CMsgExpandableControl;
class CMsgBaseControl;
class CMsgEditorAppUi;
class CUniEditorDocument;

// CLASS DECLARATION

// ==========================================================

/**
* Unified Message editor header class
*
* @since 3.2
*/
class CUniEditorHeader : public CUniBaseHeader
    {
    public:  // Constructor and destructor

        /**
        * Two-phased constructor.
        *
        * @return new object
        */
        static CUniEditorHeader* NewL();

        /**
        * Destructor.
        */
        virtual ~CUniEditorHeader();

        /**
        * Add recipient.
        *
        * @param aFocusedControl currently focused control
        * @param aParent    IN  Parent control (normally iView)
        * @param aIncludeEmailAddress IN Specifies whether recipients with email
        *                                address should be included.
        * @param aInvalid   OUT ETrue if invalid addresses found
        *                       EFalse otherwise
        *
        * @return ETrue if something was added,
        *         EFalse otherwise
        */
        TBool AddRecipientL( CMsgBaseControl* aFocusedControl,
                             MObjectProvider* aParent, 
                             TBool aIncludeEmailAddresses,
                             TBool& aInvalid );

    
    private: // Constructors

        /**
        * C++ constructor.
        */
        CUniEditorHeader();

        /**
        * 2nd phase constructor.
        */
        void ConstructL();

        
    };

#endif // __UNIEDITORHEADER_H

// End of File
