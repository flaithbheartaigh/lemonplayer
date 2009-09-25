/*
 ============================================================================
 Name		: FileListContainer.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileListContainer implementation
 ============================================================================
 */

#include "FileListContainer.h"

void CFileListContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);
    ActivateL();
    }

// Destructor
CFileListContainer::~CFileListContainer()
    {
    }

// ---------------------------------------------------------
// CSymbian1Container::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CFileListContainer::SizeChanged()
    {
    // TODO: Add here control resize code etc.
    }

// ---------------------------------------------------------
// CSymbian1Container::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CFileListContainer::CountComponentControls() const
    {
    return 0; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CSymbian1Container::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CFileListContainer::ComponentControl(TInt aIndex) const
    {
    switch ( aIndex )
        {
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CSymbian1Container::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CFileListContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    // TODO: Add your drawing code here
    // example code...
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbWhite );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------
// CSymbian1Container::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CFileListContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    // TODO: Add your control event handler code here
    }

