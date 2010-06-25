/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
*       Defines implementation of CUniAddressHandler class methods.
*
*/



// ========== INCLUDE FILES ================================

#include "UniAddressHandler.h"

// MSV
#include <cmsvrecipientlist.h>  
#include <mtclbase.h>


// Base Editor
#include <MsgAddressControl.h>      // for CMsgAddressControl
#include <MsgRecipientItem.h>       // for CMsgRecipientItem
#include <MsgCheckNames.h>          // for CMsgCheckNames
//#include <contactmatcher.h>
//#include <MVPbkStoreContact.h>

// MUIU
//#include <MuiuMsvUiServiceUtilities.h>

#include <centralrepository.h>    // link against centralrepository.lib
//#include <telconfigcrkeys.h> // for Central Repository keys

// AVKON
#include <AknUtils.h>
#include <aknnotewrappers.h>
//#include <akninputblock.h>

// Common Components
#include <StringLoader.h>           // for StringLoader (load and foramt strings from resources)
#include <commonphoneparser.h>      // Common phone number validity checker
//#include <data_caging_path_literals.hrh> 

#include <bautils.h>                        // NearestLanguageFile

//#include <UniUtils.rsg>           // resources

//#include "UniUtils.h"

// ========== EXTERNAL DATA STRUCTURES =====================

// ========== EXTERNAL FUNCTION PROTOTYPES =================

// ========== CONSTANTS ====================================

const TInt KMaxDetailsLength = 64;   // Copy max this many chars to TMsvEntry iDetails
const TInt KDefaultCompareLength = 7;

_LIT( KAddressSeparator, ";" );

// ========== MACROS =======================================

// ========== LOCAL CONSTANTS AND MACROS ===================

// ========== MODULE DATA STRUCTURES =======================

// ========== LOCAL FUNCTION PROTOTYPES ====================

// ========== LOCAL FUNCTIONS ==============================

// ========== MEMBER FUNCTIONS =============================

// ---------------------------------------------------------
// CUniAddressHandler::CUniAddressHandler
//
// C++ constructor.
// ---------------------------------------------------------
//
CUniAddressHandler::CUniAddressHandler( CMsgAddressControl& aControl,
                                        CCoeEnv& aCoeEnv ) :
    iControl( aControl ),
    iCoeEnv( aCoeEnv ),
    iValidAddressType( CMsgCheckNames::EMsgTypeSms )
    {
    }

// ---------------------------------------------------------
// CUniAddressHandler::ConstructL
// ---------------------------------------------------------
//
void CUniAddressHandler::ConstructL()
    {
        iCheckNames = CMsgCheckNames::NewL();
    }

// ---------------------------------------------------------
// CUniAddressHandler::NewL
//
// Factory method.
// ---------------------------------------------------------
//
EXPORT_C CUniAddressHandler* CUniAddressHandler::NewL( CMsgAddressControl& aControl,
                                                       CCoeEnv& aCoeEnv )
    {
    CUniAddressHandler* self = new ( ELeave ) CUniAddressHandler( aControl, aCoeEnv );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }

// ---------------------------------------------------------
// CUniAddressHandler::~CUniAddressHandler
// ---------------------------------------------------------
//
CUniAddressHandler::~CUniAddressHandler()
    {
    
    delete iCheckNames;
    }

// ----------------------------------------------------
// CUniAddressHandler::AddRecipientL
//
// Performs address(es) fetch operation.
// ----------------------------------------------------
//
EXPORT_C TBool CUniAddressHandler::AddRecipientL( TBool& aInvalid )
    {
    TBool addressesAdded( EFalse );
    aInvalid = EFalse;
    
    CMsgRecipientList* recipientList = CMsgRecipientList::NewL();
    CleanupStack::PushL( recipientList );

    CMsgRecipientArray* recipients = new ( ELeave ) CMsgRecipientArray( 10 );
    CleanupStack::PushL( TCleanupItem( CleanupRecipientArray, recipients ) );
    
    // Multiple entry fetch to get the contact    
    if ( !iCheckNames )
        {
        iCheckNames = CMsgCheckNames::NewL();
        }
        
    iCheckNames->FetchRecipientsL( *recipients, iValidAddressType );
    
    // Contacts now fetched, verify that valid address is given for every contact
    while ( recipients->Count() > 0 )
        {
        CMsgRecipientItem* recipient = recipients->At( 0 );
        
        TPtrC namePtr = recipient->Name()->Des();
        TPtrC addressPtr = recipient->Address()->Des();

        // Don't parse away chars here so this is consistent with 
        // addresses that user writes "-()" are saved to draft
        // but removed when sending
        if ( CheckSingleAddressL( addressPtr ) )
            {
            //  add it to the list of valid addresses
            recipient->SetValidated( ETrue );
            recipient->SetVerified( ( namePtr.Length() > 0 ? ETrue : EFalse ) );
            recipientList->AppendL( recipient );
            }
        else
            {
            aInvalid = ETrue;
            ShowAddressInfoNoteL( addressPtr, namePtr );
            delete recipient;
            }
        
        recipients->Delete( 0 );
        }
    
    if ( recipientList->Count() > 0 )
        {
        iControl.AddRecipientsL( *recipientList );
        addressesAdded = ETrue;
        }
 
    CleanupStack::PopAndDestroy( 2, recipientList );//recipients
    
    return addressesAdded;
    }
    
// ---------------------------------------------------------
// CUniAddressHandler::CheckSingleAddressL
// ---------------------------------------------------------
//
EXPORT_C TBool CUniAddressHandler::CheckSingleAddressL( const TDesC& aAddress )
    {
    if ( iValidAddressType != CMsgCheckNames::EMsgTypeMail &&
         CommonPhoneParser::IsValidPhoneNumber( aAddress, CommonPhoneParser::ESMSNumber ) )
        {
        return ETrue;
        }
        
    return EFalse;
    }
// ---------------------------------------------------------
// CUniAddressHandler::ShowAddressInfoNoteL
// ---------------------------------------------------------
//
void CUniAddressHandler::ShowAddressInfoNoteL( const TDesC& aAddress, const TDesC& aAlias )
    {
//    TInt cleanupCount = 0;
//    HBufC* string = NULL;
//
//    HBufC* convertedAddress = NumberConversionLC( aAddress, ETrue );
//    cleanupCount++;
//
//    if ( aAlias.Length() == 0 )
//        {
//        string = StringLoader::LoadLC( R_UNUT_INFO_FAIL_RECIPIENT_NO_ALIAS,
//                                       *convertedAddress,
//                                       &iCoeEnv );
//        cleanupCount++;
//        }
//    else
//        {
//        CDesCArrayFlat* stringArr = new ( ELeave ) CDesCArrayFlat( 2 );
//        CleanupStack::PushL( stringArr );
//        cleanupCount++;
//        
//        stringArr->AppendL( aAlias );    //First string
//        stringArr->AppendL( *convertedAddress );  //Second string
//        string = StringLoader::LoadLC( R_UNUT_INFO_FAIL_RECIPIENT,
//                                       *stringArr,
//                                       &iCoeEnv );
//        cleanupCount++;
//        }
//    
//    CAknInformationNote* note = new ( ELeave ) CAknInformationNote( ETrue );
//    note->ExecuteLD( *string );
//    
//    CleanupStack::PopAndDestroy( cleanupCount );  // string, (stringArr), convertedAddress
    }

// ----------------------------------------------------
// CUniAddressHandler::NumberConversionLC
// ----------------------------------------------------
//
HBufC* CUniAddressHandler::NumberConversionLC( const TDesC& aOrigNumber, TBool aDirection )
    {
    HBufC* addressCopy = aOrigNumber.AllocLC();
    TPtr tempTPtr = addressCopy->Des();
    if ( aDirection )
        {
        AknTextUtils::DisplayTextLanguageSpecificNumberConversion( tempTPtr );
        }
    else
        {
        AknTextUtils::ConvertDigitsTo( tempTPtr, EDigitTypeWestern );
        }

    return addressCopy;
    }

// ----------------------------------------------------
// CUniAddressHandler::NumberConversionLC
// ----------------------------------------------------
//
void CUniAddressHandler::CleanupRecipientArray( TAny* aArray )
    {
    CMsgRecipientArray* recipientArray = static_cast<CMsgRecipientArray*>( aArray );
    
    recipientArray->ResetAndDestroy();
    delete recipientArray;
    }


// ========== OTHER EXPORTED FUNCTIONS =====================

//  End of File
