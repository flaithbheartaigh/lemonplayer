/* ============================================================================
*  Name     : CLemonPlayerApp from LemonPlayerApp.cpp
*  Part of  : LemonPlayer
*  Created  : 17.09.2008 by zengcity
* 
*  Implementation notes:
*
*     Initial content was generated by Series 60 Application Wizard.
*  Version  :
*  Copyright: 
* ============================================================================
*/

// INCLUDE FILES
#include    "LemonPlayerApp.h"
#include    "LemonPlayerDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CLemonPlayerApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CLemonPlayerApp::AppDllUid() const
    {
    return KUidLemonPlayer;
    }

   
// ---------------------------------------------------------
// CLemonPlayerApp::CreateDocumentL()
// Creates CLemonPlayerDocument object
// ---------------------------------------------------------
//
CApaDocument* CLemonPlayerApp::CreateDocumentL()
    {
    return CLemonPlayerDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CLemonPlayerApp
// Returns: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CLemonPlayerApp;
    }

// ---------------------------------------------------------
// E32Dll(TDllReason) 
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ---------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

// End of File  
