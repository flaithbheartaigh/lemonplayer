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
* Description:   Unified Message Editor Address Handler.
*
*/



#ifndef C_UNIADDRESSHANDLER_H
#define C_UNIADDRESSHANDLER_H

// ========== INCLUDE FILES ================================

#include <e32base.h>
#include "MsgCheckNames.h"
#include <ConeResLoader.h>

// ========== CONSTANTS ====================================

// ========== MACROS =======================================

// ========== FUNCTION PROTOTYPES ==========================

// ========== FORWARD DECLARATIONS =========================

class CCoeEnv;
class CMsgAddressControl;

// ========== DATA TYPES ===================================

// ========== CLASS DECLARATION ============================

/**
*  Unified Editor Address Handler class declaration.
*  Class provides services for address handling. 
*
*  @lib UniUtils.lib
*
*  @since S60 3.2
*/
NONSHARABLE_CLASS( CUniAddressHandler ) : public CBase
    {
    public:

        /**
        * Allocates and constructs a CUniAddressHandler object.
        *
        * @param aMtm       Client MTM
        * @param aControl   Address control to which this handler is connected
        * @param aCoeEnv    Handle to control environment
        *
        * @return Pointer to the new CUniAddressHandler object
        */
        IMPORT_C static CUniAddressHandler* NewL( CMsgAddressControl& aControl,
                                                  CCoeEnv& aCoeEnv );
        /**
        * Destructor
        */
        virtual ~CUniAddressHandler();


        /**
        * Add recipient.
        *
        * @since S60 3.2
        *
        * @param aInvalid               OUT ETrue if invalid addresses found
        *                                   EFalse otherwise
        * @return ETrue if something was added,
        *         EFalse otherwise
        */
        IMPORT_C TBool AddRecipientL( TBool& aInvalid );

        /** 
        * Checks address.
        *
        * @since S60 3.2
        *
        * @param aAddress, phonenumber or email
        * @return ETrue if address is valid, EFalse otherwise
        */        
        IMPORT_C TBool CheckSingleAddressL( const TDesC& aAddress );

         
        
   private:

        /**
        * Default C++ constructor.
        */
        CUniAddressHandler();
        
        /**
        * Constructor.
        */
        CUniAddressHandler( CMsgAddressControl& aControl,
                            CCoeEnv& aCoeEnv );

        /**
        * By default Symbian OS constructor is private.
        */
        void ConstructL();

        /**
        * Shows address info (error) note
        *
        * @param aAddress
        * @param aAlias
        */
        void ShowAddressInfoNoteL( const TDesC& aAddress, const TDesC& aAlias );


        /**
        * Converts number-strings to/from arabic-indic <-> western 
        * NOTE : Leaves string to CleanupStack
        * @param aOrigNumber contains the number to be converted
        * @param aDirection EFalse -> western, ETrue -> arabic-indic if needed
        * @return HBufC* buffer contains converted string
        */
        static HBufC* NumberConversionLC( const TDesC& aOrigNumber, TBool aDirection );

        /**
        * Performs proper recipient array cleanup.
        *
        * @param aArray CMsgRecipientArray pointer.
        */
        static void CleanupRecipientArray( TAny* aArray );
        
    private:        
        //
        CMsgAddressControl&     iControl;
        
        //
        CCoeEnv&                iCoeEnv;

        CMsgCheckNames*         iCheckNames;        
        
        // Valid address type.
        CMsgCheckNames::TMsgAddressSelectType iValidAddressType;
        
    };



#endif // C_UNIADDRESSHANDLER_H

// End of File
