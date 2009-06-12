#include <StringLoader.h> 
#include <LemonTangram_0xEAE107BA.rsg>
#include <AknQueryDialog.h> 
#include <AknGlobalNote.h> 
#include <aknnotewrappers.h> 

TBool ShowConfirmationQueryL( const TInt aTextResourceId )
    {
    HBufC* prompt = StringLoader::LoadLC( aTextResourceId );

    CAknQueryDialog* dlg = CAknQueryDialog::NewL();

    dlg->SetPromptL( *prompt );
    TInt retCode( dlg->ExecuteLD( R_CONFIRMATION_QUERY ) );

    CleanupStack::PopAndDestroy(); //prompt
    return retCode;
    }

TInt StartWaitingDlg(const TInt aTextResourceId)
	{
	HBufC* prompt = StringLoader::LoadLC( aTextResourceId );
	
	CAknGlobalNote* globalNote = CAknGlobalNote::NewL();   
	CleanupStack::PushL( globalNote );   
	TInt noteId = globalNote->ShowNoteL( EAknGlobalWaitNote, 
			prompt->Des() );   
	CleanupStack::PopAndDestroy(2);
	return noteId;
	}

void EndWaitingDlg(const TInt aDlgId)
	{
	CAknGlobalNote * note = CAknGlobalNote::NewL();   
	CleanupStack::PushL( note );   
	note->CancelNoteL( aDlgId );   
	CleanupStack::PopAndDestroy();
	}

void ShowInfomationDlgL(const TInt aTextResourceId)
	{
	HBufC* prompt = StringLoader::LoadLC( aTextResourceId );
	CAknInformationNote* iInfoNote = new (ELeave) CAknInformationNote;
	iInfoNote->ExecuteLD(prompt->Des());
	CleanupStack::PopAndDestroy();
	}

TBool ShowInputDlgL(const TInt aTextResourceId,TDes& aText)
	{
	HBufC* prompt = StringLoader::LoadLC( aTextResourceId );
	CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( aText );
	
	dlg->SetPromptL(prompt->Des());
	dlg->SetMaxLength(KMaxName);
	TInt retCode( dlg->ExecuteLD( R_DIALOG_INPUT ));
	
	CleanupStack::PopAndDestroy(); //prompt
	return retCode;
	}