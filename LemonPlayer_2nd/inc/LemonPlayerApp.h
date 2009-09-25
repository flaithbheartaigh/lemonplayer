/*
* ============================================================================
*  Name     : CLemonPlayerApp from LemonPlayerApp.h
*  Part of  : LemonPlayer
*  Created  : 17.09.2008 by zengcity
*  Description:
*     Declares main application class.
*  Version  :
*  Copyright: 
* ============================================================================
*/

#ifndef LEMONPLAYERAPP_H
#define LEMONPLAYERAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidLemonPlayer = { 0x0116C9D3 };

// CLASS DECLARATION

/**
* CLemonPlayerApp application class.
* Provides factory to create concrete document object.
* 
*/
class CLemonPlayerApp : public CAknApplication
    {
    
    public: // Functions from base classes
    private:

        /**
        * From CApaApplication, creates CLemonPlayerDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication, returns application's UID (KUidLemonPlayer).
        * @return The value of KUidLemonPlayer.
        */
        TUid AppDllUid() const;
    };

#endif

// End of File

