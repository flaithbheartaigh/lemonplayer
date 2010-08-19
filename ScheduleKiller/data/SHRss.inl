RESOURCE AVKON_VIEW r_view_ok_back
    {    
    cba = r_cba_ok_back;
    }

RESOURCE AVKON_VIEW r_view_ok_exit
    {    
    cba = r_cba_ok_exit;
    }

RESOURCE AVKON_VIEW r_view_null_back
    {    
    cba = r_cba_null_back;
    }

RESOURCE CBA r_cba_ok_back
    {
    flags = 0;
    buttons =
        {
        CBA_BUTTON {id=EAknSoftkeyOk; 		txt=qtn_ok;},
        CBA_BUTTON {id=EAknSoftkeyBack; 	txt=qtn_back;}
        };
    }

RESOURCE CBA r_cba_change_back
    {
    flags = 0;
    buttons =
        {
        CBA_BUTTON {id=EAknSoftkeyOk; 		txt=qtn_change;},
        CBA_BUTTON {id=EAknSoftkeyBack; 	txt=qtn_back;}
        };
    }

RESOURCE CBA r_cba_ok_exit
    {
    flags = 0;
    buttons =
        {
        CBA_BUTTON {id=EAknSoftkeyOk; 		txt=qtn_ok;},
        CBA_BUTTON {id=EAknSoftkeyExit; 	txt=qtn_exit;}
        };
    }

RESOURCE CBA r_cba_null_back
    {
    flags = 0;
    buttons =
        {
        CBA_BUTTON {id=EAknSoftkeyOk; 		txt=qtn_null;},
        CBA_BUTTON {id=EAknSoftkeyBack; 	txt=qtn_back;}
        };
    }

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

RESOURCE TIME_AND_DATE_EDITOR r_editor_time_and_date
	{
	minTimeAndDate = TIME_AND_DATE
		{
		second = 0;
		minute = 0;
		hour = 0;
		day = 0;
		month = 0;
		year = 2000;
		};
	maxTimeAndDate = TIME_AND_DATE
		{
		second = 59;
		minute = 59;
		hour = 23;
		day = 30;
		month = 11;
		year = 2099;
		};
	interveningtext = " ";
	flags = EEikTimeWithoutSecondsField;
	}

RESOURCE TIME_EDITOR r_editor_time
	{
	minTime = TIME
		{
		second = 0;
		minute = 0;
		hour = 0;
		};
	maxTime = TIME
		{
		second = 59;
		minute = 59;
		hour = 23;
		};
	flags = EEikTimeWithoutSecondsField;
	}


RESOURCE TBUF32 r_caption_string			{buf=qtn_caption_string;}
RESOURCE TBUF32 r_about_dialog_title		{buf=qtn_about_dialog_title;}

RESOURCE TBUF r_help_file 			{buf=qtn_help_file;}
RESOURCE TBUF r_about_file 			{buf=qtn_about_file;}

RESOURCE TBUF r_text_dlg_exit_confirm		{ buf=qtn_dlg_exit_confirm; }
