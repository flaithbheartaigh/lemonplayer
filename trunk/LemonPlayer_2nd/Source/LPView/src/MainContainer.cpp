/*
 ============================================================================
 Name		: FileListContainer.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileListContainer implementation
 ============================================================================
 */

#include "MainContainer.h"

#include "UIData.h"
#include "UIView.h"
#include "UIXmlParser.h"
#include "UIKeyEvent.h"
#include "SoundManager.h"
#include "UIDataSerialize.h"

_LIT(KFile,"c:\\lemonplayer\\defaultui.xml");
_LIT(KFileSound,"c:\\test.wav");

void CMainContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);
    
    iDisplay = CUIDisplay::NewL(iData);
    iParser = CUIXmlParser::NewL(iData);
    iParser->LoadFile(KFile);
    iEvent = CUIKeyEvent::NewL(iData);
    iSoundManager = CSoundManager::NewL(iData);
    iSoundManager->SetSoundCallBack(this);
    iSerialize = CUIDataSerialize::NewL(iData);
    iSerialize->LoadFile(_L("C:\\data.xml"));
        
    ActivateL();
    }

// Destructor
CMainContainer::~CMainContainer()
    {
//    delete 	iData;
    delete 	iDisplay;
    delete 	iParser;
    delete 	iEvent;
    delete 	iSoundManager;
    delete  iSerialize;
    }

// ---------------------------------------------------------
// CSymbian1Container::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CMainContainer::SizeChanged()
    {
    // TODO: Add here control resize code etc.
    }

// ---------------------------------------------------------
// CSymbian1Container::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CMainContainer::CountComponentControls() const
    {
    return 0; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CSymbian1Container::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CMainContainer::ComponentControl(TInt aIndex) const
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
void CMainContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    // TODO: Add your drawing code here
    // example code...
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    
    iDisplay->Draw(gc);
    }

// ---------------------------------------------------------
// CSymbian1Container::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CMainContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    // TODO: Add your control event handler code here
    }

TKeyResponse CMainContainer::OfferKeyEventL(
		const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	TInt result = iEvent->OfferKeyEventL(aKeyEvent,aType);
	if (result != KUIKeyEventNone)
		{
		switch (result)
			{
			case KUIKeyEventState:
				iSoundManager->StateChange();	
				break;
			case KUIKeyEventVolume:
				iSoundManager->VolumeChange();
				break;
			}
		DrawNow();	
		return EKeyWasConsumed;
		}
	else
		{
		return EKeyWasNotConsumed;
		}
	}

void CMainContainer::PlayFile()
	{
	iSoundManager->PlayFile();
	}

void CMainContainer::InitComplete()
	{
	DrawNow();
	}

void CMainContainer::PlayComplete()
	{}

void CMainContainer::SaveData()
	{
	iSerialize->WriteFile(_L("C:\\data.xml"));
	}
