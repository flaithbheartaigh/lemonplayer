/*
* ==============================================================================
*  Name        : ListboxSettingView.h
*  Part of     : Listbox example
*  Interface   :
*  Description :
*  Version     :
*
*  Copyright (c) 2007 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation.
* ==============================================================================
*/

#ifndef __LISTBOXSETTINGVIEW_H__
#define __LISTBOXSETTINGVIEW_H__


#include <aknview.h>

class CYCSettingList;
class CYCBrowserView;
class CYCSettingContainer;


/**
*  CListBoxSettingView class
*  This class is a view class for setting list container (CListboxSettingList).
*/
class CYCSettingView : public CAknView
    {
    
    public:
    
        /**
        * Two-phased constructor.
        */
        static CYCSettingView* NewL();
    
    public: //New functions
    
        /**
        * Called by HandleResourceChangeL() from CListboxAppUi when layout 
        * is changed.
        *
        * @param aType Type of resources that have changed
        */
        void HandleSizeChange( TInt aType );
    
    private:
    
        /**
        * From CAknView.
        * Returns views id.
        *
        * @return Id for this view.
        */
        TUid Id() const;
    
        /**
        * From CAknView.
        * Handles commands
        *
        * @param aCommand A command to be handled.
        */
        void HandleCommandL( TInt aCommand );
    
        /**
        * From CAknView.
        * Activates view
        *
        * @param aPrevViewId Specifies the view previously active.
        * @param aCustomMessageId Specifies the message type.
        * @param aCustomMessage The activation message.
        */
        void DoActivateL( const TVwsViewId& aPrevViewId,
                          TUid aCustomMessageId,
                          const TDesC8& aCustomMessage );
    
        /**
        * From CAknView.
        * Deactivates view.
        */
        void DoDeactivate();
        
        /**
        * From MEikMenuObserver, DynInitMenuPaneL.
        * This function is called by the EIKON framework just before it
        * displays a menu pane.
        * @param aResourceId The ID of command which defined in resource file.
        * @param aMenuPane Pointer to menu-pane object.
        */
        void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );
    
    private:
    
        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();
        
        /**
        * C++ default constructor.
        */
        CYCSettingView();
        
        /**
        * Destructor.
        */
        ~CYCSettingView();
    
    private: //Data
    
        /**
        * Container.
        * Own.
        */
        CYCSettingList* iContainer;
//    	CYCSettingContainer* iAppView;
    };

#endif // __LISTBOXSETTINGVIEW_H__
