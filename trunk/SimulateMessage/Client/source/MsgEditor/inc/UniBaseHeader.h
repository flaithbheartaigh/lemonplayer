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
* Description:   Unified Message Editor base header.
*
*/



#ifndef C_UNIBASEHEADER_H
#define C_UNIBASEHEADER_H

// INCLUDES
#include <MsgEditorView.h>
#include <MsgEditor.hrh>    // TMsgControlId
#include <MsgAddressControl.h>
#include <cmsvrecipientlist.h>

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

class CMsgExpandableControl;
class CUniAddressHandler;
class CMsgBaseControl;
class CMsgEditorAppUi;
class CBaseMtm;

// CLASS DECLARATION

// ==========================================================

/**
*  Unified Editor Base Header class declaration.
*  Class provides common services for editor and viewer header classes. 
*
*  @lib UniUtils.lib
*
*  @since S60 3.2
*/
class CUniBaseHeader : public CBase
    {
    public:  // Constructor and destructor

        enum THeaderFields
            {
            EHeaderAddressFrom = 0,
            EHeaderAddressTo
            };

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CUniBaseHeader();
        
        
    protected: // Constructors

//        enum
//            {
//            // For internal use of header class hierarchy
//            // This can be whatever bit excluding 
//            // EUniFeatureCc, EUniFeatureBcc and EUniFeatureSubject
//            EUniFeatureTo = 0x4000000,
//            EUniFeatureFrom = 0x8000000,
//            EUniFeatureAttachment = 0x10000000
//            };

        struct TAddressData
            {
            //CMsgExpandableControl*  iControl;
            //TBool                   iOwned;
            CUniAddressHandler*     iAddressHandler; // no address handler for subject
            //TMsgControlId           iControlType;
            //TMsvRecipientTypeValues iRecipientTypeValue;    // from msv api
            };

        /**
        * Hidden C++ default constructor.
        */
        IMPORT_C CUniBaseHeader();

    protected: //Data
//        TInt                    iAddHeadersVariation;
//        TInt                    iAddHeadersConfig;
        TAddressData            iHeaders[2];
        
        /// Derived class must remember to use flags EUniFeatureTo, EUniFeatureFrom, too
//        TInt                    iAddDelayed;
    };

#endif // C_UNIBASEHEADER_H
