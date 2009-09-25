#include <StringLoader.h> 
#include <LemonTangram.rsg>
#include <AknQueryDialog.h> 
#include <AknGlobalNote.h> 
#include <aknnotewrappers.h> 

/**********
 * 
 * RESOURCE DIALOG r_confirmation_query
    {
    flags = EGeneralQueryFlags;
    buttons = R_AVKON_SOFTKEYS_YES_NO;
    items =
        {
        DLG_LINE
            {
            type = EAknCtQuery;
            id = EGeneralQuery;
            control = AVKON_CONFIRMATION_QUERY
                {
                layout = EConfirmationQueryLayout;
                label = STRING_r_contacts_con_label_text;
                };
            }
        };
    }

RESOURCE DIALOG r_dialog_input
    {
    flags = EGeneralQueryFlags;
    buttons = R_AVKON_SOFTKEYS_OK_CANCEL;
    items =
        {
        DLG_LINE
            {
            type = EAknCtQuery;
            id = EGeneralQuery;
            control = AVKON_DATA_QUERY
                {
                layout = EDataLayout;
                label = qtn_dialog_url;
                control = EDWIN
                    {
                    maxlength = 40;
                    };
                };
            }
        };
    }
 * 
 */

TBool ShowConfirmationQueryL( const TInt& aTextResourceId )
    {
    HBufC* prompt = StringLoader::LoadLC( aTextResourceId );

    CAknQueryDialog* dlg = CAknQueryDialog::NewL();

    dlg->SetPromptL( *prompt );
    TInt retCode( dlg->ExecuteLD( R_CONFIRMATION_QUERY ) );

    CleanupStack::PopAndDestroy(); //prompt
    return retCode;
    }

TInt StartWaitingDlg(const TInt& aTextResourceId)
	{
	HBufC* prompt = StringLoader::LoadLC( aTextResourceId );
	
	CAknGlobalNote* globalNote = CAknGlobalNote::NewL();   
	CleanupStack::PushL( globalNote );   
	TInt noteId = globalNote->ShowNoteL( EAknGlobalWaitNote, 
			prompt->Des() );   
	CleanupStack::PopAndDestroy(2);
	return noteId;
	}

void EndWaitingDlg(const TInt& aDlgId)
	{
	CAknGlobalNote * note = CAknGlobalNote::NewL();   
	CleanupStack::PushL( note );   
	note->CancelNoteL( aDlgId );   
	CleanupStack::PopAndDestroy();
	}

void ShowInfomationDlgL(const TInt& aTextResourceId)
	{
	HBufC* prompt = StringLoader::LoadLC( aTextResourceId );
	CAknInformationNote* iInfoNote = new (ELeave) CAknInformationNote;
	iInfoNote->ExecuteLD(prompt->Des());
	CleanupStack::PopAndDestroy();
	}

TBool ShowInputDlgL(const TInt& aTextResourceId,TDes& aText)
	{
	HBufC* prompt = StringLoader::LoadLC( aTextResourceId );
	CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( aText );
	
	dlg->SetPromptL(prompt->Des());
	dlg->SetMaxLength(KMaxName);
	TInt retCode( dlg->ExecuteLD( R_DIALOG_INPUT ));
	
	CleanupStack::PopAndDestroy(); //prompt
	return retCode;
	}

//TBool ShowModalInfoDlgL(const TInt& aTextResourceId)
//{
//    HBufC* prompt = StringLoader::LoadLC( aTextResourceId );
//
//    CEikonEnv::Static()->InfoWinL(_L("note:"), prompt->Des());  //任意使用
//
//    CleanupStack::PopAndDestroy(); //prompt
//
//    return ETrue;
// }

TBool ShowModalInfoDlgL(const TInt& aTextHeaderId,const TInt& aTextResourceId)
{
	HBufC* header = StringLoader::LoadLC( aTextHeaderId );
    HBufC* prompt = StringLoader::LoadLC( aTextResourceId );

    CEikonEnv::Static()->InfoWinL(header->Des(), prompt->Des());  //任意使用

    CleanupStack::PopAndDestroy(2); //prompt

    return ETrue;
}