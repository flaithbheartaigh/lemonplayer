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
* Description:   Header file of msgchecknames.cpp.
*                Includes alias name matching functions.
*
*/




#ifndef CMSGCHECKNAMES_H
#define CMSGCHECKNAMES_H

//  INCLUDES
#include <cntdb.h>                      //CheckNames
#include <CPbkContactEngine.h>          //CheckNames
#include <MsgRecipientItem.h>           //CheckNames

// Constants
const TInt KMaxRecipientLength = 100;
// FORWARD DECLARATIONS
class CContactDatabase;
class CContactTextDef;
class CPbk2StoreConfiguration;

// CLASS DECLARATION

/**
* Class, which provides check names functionality in message editors.
*
* @lib MsgEditorAppui.lib
* @since 2.0
*/
class CMsgCheckNames : public CBase
    {
    public:  // Constructors and destructor

        enum TMsgAddressSelectType
    		{
    		EMsgTypeSms,
            EMsgTypeMms,
            EMsgTypeMail,
            EMsgTypeAll
    		};
		
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CMsgCheckNames* NewL();
        
        /**
        * Two-phased constructor. 
        * Leaves object into cleanup stack.
        */
	    IMPORT_C static CMsgCheckNames* NewLC();
        
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CMsgCheckNames();

    public: // New functions
    
        
        /**
        * Fetches the recipients for the editors while hiding the asynchronous AIW handling
        * and the related parameters
        *
        * @since 3.1
        *
        * @param  aRecipientList - is the array that will be filled for the caller
        *         aAddressSelectType - defines the addresstype for selection
        */            
        IMPORT_C void FetchRecipientsL( CMsgRecipientArray& aRecipientList, 
                                        TMsgAddressSelectType aAddressSelectType );

        
    protected:
    
        

        /**
        * Puts the found contacts to the given array
        *
        * @since 3.1
        *
        * @param aRecipientArray - the array to which the recipients will be added
        *        aIndex - index of the array, this is where the adding should start
        */
        void PutContactsToArrayL( CMsgRecipientArray& aRecipientArray, TInt aIndex );
      


    public:        
        
        /**
        * From MAknInputBlockCancelHandler. See AknInputBlock.h
        *
        * @since S60 3.2
        */        
        void AknInputBlockCancel();
        
        /**
         * From MPbk2StoreConfigurationObserver Called when the store configuration changes.
         */
        void ConfigurationChanged();

        /**
         * From MPbk2StoreConfigurationObserver  Called when the configuration changed event
         * has been delivered to all observers.
         */
        void ConfigurationChangedComplete();
        
    private:

        /**
        * C++ default constructor.
        */
        CMsgCheckNames();

        /**
        * Symbian 2nd phase constructor.
        */
        void ConstructL();
        
        

        /**
        * Performs configuration change handling.
        */
        void DoConfigurationChangedCompleteL();
        
    private:    // Data

        TBool                      iShutdown;
        
        CPbk2StoreConfiguration*   iStoreConfiguration;
    };



#endif      // CMSGCHECKNAMES_H   
            
// End of File
