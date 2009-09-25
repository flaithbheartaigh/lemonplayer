/*
* ============================================================================
*  Name     : CLemonPlayerDocument from LemonPlayerDocument.h
*  Part of  : LemonPlayer
*  Created  : 17.09.2008 by zengcity
*  Description:
*     Declares document for application.
*  Version  :
*  Copyright: 
* ============================================================================
*/

#ifndef LEMONPLAYERDOCUMENT_H
#define LEMONPLAYERDOCUMENT_H

// INCLUDES
#include <akndoc.h>
   
// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;

// CLASS DECLARATION

/**
*  CLemonPlayerDocument application class.
*/
class CLemonPlayerDocument : public CAknDocument
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CLemonPlayerDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CLemonPlayerDocument();

    public: // New functions

    public: // Functions from base classes
    protected:  // New functions

    protected:  // Functions from base classes

    private:

        /**
        * EPOC default constructor.
        */
        CLemonPlayerDocument(CEikApplication& aApp);
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CLemonPlayerAppUi "App UI" object.
        */
        CEikAppUi* CreateAppUiL();
    };

#endif

// End of File

