/*
 * Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
 * Description:   Alias name matching functionality.
 *
 */
// INCLUDE FILES
#include "MsgCheckNames.h"
#include <eiklbv.h>
#include <aknlistquerydialog.h>
#include <CPbkContactEngine.h>       // CPbkContactEngine
#include <CPbkIdleFinder.h>          // CPbkIdleFinder
#include <CPbkContactItem.h>         // Phonebook Contact
#include <cntdef.h>                  //CheckNames
#include <CPbkSmsAddressSelect.h>    //CheckNames
#include <CPbkEmailAddressSelect.h>  //CheckNames
#include <CPbkMmsAddressSelect.h>    //CheckNames
#include <MsgAddressControl.h>       // CMsgRecipientArray/CheckNames
#include <cpbkphonenumberselect.h> 		//CPbkPhoneNumberSelect 
//#include <MsgEditorAppUi.rsg>        // resource identifiers
//#include <VPbkContactStoreUris.h>
//#include <TVPbkFieldVersitProperty.h>
//#include <MVPbkContactFieldTextData.h>
//#include <MVPbkStoreContact.h>
//#include <RVPbkContactFieldDefaultPriorities.h>
//#include <TVPbkContactStoreUriPtr.h>
//#include <CPbk2StoreConfiguration.h>
//#include <MVPbkContactLink.h>
//#include <CVPbkFieldTypeRefsList.h>
//#include <CVPbkContactStoreUriArray.h>
//
//#include <CVPbkFieldTypeSelector.h>
//#include <VPbkContactViewFilterBuilder.h>
//#include <AiwContactSelectionDataTypes.h>
//
//#include <TVPbkWordParserCallbackParam.h>
//#include <AiwContactSelectionDataTypes.h>
//#include <RVPbkContactFieldDefaultPriorities.h>
#include <cpbkmultipleentryfetchdlg.h> 	//CPbkMultipleEntryFetchDlg
#include <rpbkviewresourcefile.h> 		//RPbkViewResourceFile
#include <cpbkcontactengine.h> 			//CPbkContactEngine
// MACROS
_LIT( KItemStart, "1\t" );
//For creation of checkbox list

const TUint KLatinCharEnd = 0xFF;
_LIT( KPanicText, "Check names -panic" );

// ============================= LOCAL FUNCTIONS ===============================


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CMsgCheckNames::CMsgCheckNames
//
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CMsgCheckNames::CMsgCheckNames()
	{
	}

// -----------------------------------------------------------------------------
// CMsgCheckNames::ConstructL
//
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CMsgCheckNames::ConstructL()
	{
	}

// -----------------------------------------------------------------------------
// CMsgCheckNames::NewL
//
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CMsgCheckNames* CMsgCheckNames::NewL()
	{
	CMsgCheckNames* self = CMsgCheckNames::NewLC();
	CleanupStack::Pop(self);

	return self;
	}

// -----------------------------------------------------------------------------
// CMsgCheckNames::NewLC
//
// Factory method
// -----------------------------------------------------------------------------
//
EXPORT_C CMsgCheckNames* CMsgCheckNames::NewLC()
	{
	CMsgCheckNames* self = new (ELeave) CMsgCheckNames();
	CleanupStack::PushL(self);

	self->ConstructL();

	return self;
	}

// -----------------------------------------------------------------------------
// CMsgCheckNames::~CMsgCheckNames
// -----------------------------------------------------------------------------
//
EXPORT_C CMsgCheckNames::~CMsgCheckNames()
	{
	}

// ----------------------------------------------------------------------------
// CMsgCheckNames::FetchRecipientsL
//
// Fetches the recipients, and searches the address from the selected recipients
// Starts input blocker to "eat" all key press events to editor during
// phonebook operations. If shudown flag is set leaves with KLeaveExit code
// to make the application to shutdown
// ----------------------------------------------------------------------------    
//
EXPORT_C void CMsgCheckNames::FetchRecipientsL(
		CMsgRecipientArray& aRecipientList,
		TMsgAddressSelectType aAddressSelectType)
	{
	RPbkViewResourceFile pbkrf(*CCoeEnv::Static());
	pbkrf.OpenL();

	// set up the params
	CPbkMultipleEntryFetchDlg::TParams params;
	CleanupStack::PushL(params); // uses the TCleanupItem() operator of the TParams class

	// make an instance of the contacts model
	CPbkContactEngine* iPbkContactEngine = CPbkContactEngine::NewL(
			&CCoeEnv::Static()->FsSession());
	CleanupStack::PushL(iPbkContactEngine);
	params.iContactView = &iPbkContactEngine->AllContactsView();

	// make the fetch dialog
	CPbkMultipleEntryFetchDlg* fetcher = CPbkMultipleEntryFetchDlg::NewL(
			params, *iPbkContactEngine);
	//fetcher->SetMopParent(this);

	// execute it, always fails here
	if (fetcher->ExecuteLD())
		{
		// do something with the entries...
		CContactIdArray* entries = params.iMarkedEntries;
		for (TInt i = 0; i < entries->Count(); i++)
			{
			const TContactItemId cid = (*params.iMarkedEntries)[i];

			// Open the selected contact using Phonebook engine,
			// choose correct number (launch list query if needed)
			CPbkContactItem* pbkItem = iPbkContactEngine->ReadContactLC(cid);
			TPtrC tempAddress;
			HBufC* title;

			TPbkContactItemField* tmp;
			tmp = pbkItem->FindField(EPbkFieldIdPhoneNumberMobile);
			//Using CPbkSmsAddressSelect dialog for user to choose between numbers
			CPbkPhoneNumberSelect* dlg = new (ELeave) CPbkPhoneNumberSelect();
			CPbkPhoneNumberSelect::TParams addparams(*pbkItem);
			TBool selected = dlg->ExecuteLD(addparams);
			if (selected)
				{
				const TPbkContactItemField* numtmp = addparams.SelectedField();
				tempAddress.Set(tmp->Text());
				}
			else
				{
				continue;
				}

			title = pbkItem->GetContactTitleL();

			CMsgRecipientItem *item = CMsgRecipientItem::NewL(title->Des(), tempAddress);
			aRecipientList.AppendL(item);

			delete title;
			CleanupStack::PopAndDestroy(); // pbkItem, 

			}
		}
	CleanupStack::PopAndDestroy(2);

	pbkrf.Close();
	}

// ---------------------------------------------------------
// CMsgCheckNames::ConfigurationChanged
// ---------------------------------------------------------
//
void CMsgCheckNames::ConfigurationChanged()
	{
	}

// ---------------------------------------------------------
// CMsgCheckNames::ConfigurationChangedComplete
// ---------------------------------------------------------
//
void CMsgCheckNames::ConfigurationChangedComplete()
	{
		TRAP_IGNORE( DoConfigurationChangedCompleteL() );
	}

// ---------------------------------------------------------
// CMsgCheckNames::DoConfigurationChangedCompleteL
//
// If store configuration has changed (i.e. used memories (phone, SIM etc.)).
// open the currently selected stores.
// ---------------------------------------------------------
//
void CMsgCheckNames::DoConfigurationChangedCompleteL()
	{
	}

//  End of File  
