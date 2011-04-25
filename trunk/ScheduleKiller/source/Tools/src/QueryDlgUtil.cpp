#include <StringLoader.h> 
#include <AknQueryDialog.h> 
#include <AknGlobalNote.h> 
#include <aknnotewrappers.h> 
#include <aknmessagequerydialog.h> 

#include "SHPlatform.h"

/**********
 * 
 * 
 RESOURCE DIALOG r_confirmation_query
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
    
RESOURCE DIALOG r_about_query_dialog
	{
	flags = EGeneralQueryFlags | EEikDialogFlagNoBorder | EEikDialogFlagNoShadow;
	buttons = R_AVKON_SOFTKEYS_OK_EMPTY;
	items=
		{
		DLG_LINE 
			{
			type = EAknCtPopupHeadingPane;
			id = EAknMessageQueryHeaderId;
			itemflags = EEikDlgItemNonFocusing;
			control = AVKON_HEADING
				{
				};
			},
		DLG_LINE
			{
			type = EAknCtMessageQuery;
			id = EAknMessageQueryContentId;
			control = AVKON_MESSAGE_QUERY
				{
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

TBool ShowConfirmationQueryL( const TDesC& aText )
	{
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();

    dlg->SetPromptL( aText );
    TInt retCode( dlg->ExecuteLD( R_CONFIRMATION_QUERY ) );

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

void ShowInfomationDlgL(const TDesC& aDes)
	{
	CAknInformationNote* iInfoNote = new (ELeave) CAknInformationNote;
	iInfoNote->ExecuteLD(aDes);
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

TBool ShowModalInfoDlgL(const TInt& aTextHeaderId,const TDesC& aDes)
{
    HBufC* prompt = StringLoader::LoadLC( aTextHeaderId );

    CEikonEnv::Static()->InfoWinL(prompt->Des(),aDes);  //任意使用

    CleanupStack::PopAndDestroy(); //prompt

    return ETrue;
 }

TBool ShowModalInfoDlgL(const TInt& aTextHeaderId,const TInt& aTextResourceId)
{
	HBufC* header = StringLoader::LoadLC( aTextHeaderId );
    HBufC* prompt = StringLoader::LoadLC( aTextResourceId );

    CEikonEnv::Static()->InfoWinL(header->Des(), prompt->Des());  //任意使用

    CleanupStack::PopAndDestroy(2); //prompt

    return ETrue;
}

TBool ShowModalAboutDlgL(const TInt& aTextHeaderId,const TInt& aTextResourceId)
{
	CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
	
	dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
	
	HBufC* title = StringLoader::LoadLC(aTextHeaderId);
	dlg->QueryHeading()->SetTextL(*title);
	CleanupStack::PopAndDestroy(); //title
	
	HBufC* msg = StringLoader::LoadLC(aTextResourceId);
	dlg->SetMessageTextL(*msg);
	CleanupStack::PopAndDestroy(); //msg
	
	dlg->RunLD();
	
	return ETrue;
}

TBool ShowModalAboutDlgL(const TInt& aTextHeaderId,const TDesC& aDes)
	{
	CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
	
	dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
	
	HBufC* title = StringLoader::LoadLC(aTextHeaderId);
	dlg->QueryHeading()->SetTextL(*title);
	CleanupStack::PopAndDestroy(); //title
		
	dlg->SetMessageTextL(aDes);
		
	dlg->RunLD();
		
	return ETrue;
	}

TBool ShowModalAboutLinkDlgL(const TInt& aTextHeaderId,const TDesC& aDes,TCallBack &aCallBack)
	{
	CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
	
	dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
	
	HBufC* title = StringLoader::LoadLC(aTextHeaderId);
	dlg->QueryHeading()->SetTextL(*title);
	CleanupStack::PopAndDestroy(); //title
		
	dlg->SetMessageTextL(aDes);
	
	dlg->SetLink(aCallBack);
		
	dlg->RunLD();
		
	return ETrue;	
	}

TBool ShowModalAboutLinkDlgL(const TInt& aTextHeaderId,const TDesC& aMsg,const TDesC& aLink,
		TCallBack &aCallBack)
	{
	CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
	
	dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
	
	HBufC* title = StringLoader::LoadLC(aTextHeaderId);
	dlg->QueryHeading()->SetTextL(*title);
	CleanupStack::PopAndDestroy(); //title
		
	HBufC* text = HBufC::NewL(aMsg.Length() + aLink.Length());
	text->Des().Format(aMsg,&aLink);
	dlg->SetMessageTextL(text->Des());
	delete text;
	
	dlg->SetLinkTextL(aLink);
	dlg->SetLink(aCallBack);
		
	dlg->RunLD();
		
	return ETrue;	
	}

TBool ShowModalAboutLinkDlgL(const TInt& aTitleHeaderId,const TDesC& aMsg,const TInt& aTextHeaderId,
		TCallBack &aCallBack)
	{
	CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
	
	dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
	
	HBufC* title = StringLoader::LoadLC(aTitleHeaderId);
	dlg->QueryHeading()->SetTextL(*title);
	CleanupStack::PopAndDestroy(); //title
		
	HBufC* msg = StringLoader::LoadL(aTextHeaderId);	
	HBufC* text = HBufC::NewL(aMsg.Length() + msg->Length() + 8);
	text->Des().Format(aMsg,msg);
	dlg->SetMessageTextL(text->Des());
	delete text;
	
	dlg->SetLinkTextL(msg->Des());
	delete msg;
	
	dlg->SetLink(aCallBack);
		
	dlg->RunLD();
		
	return ETrue;	
	}
