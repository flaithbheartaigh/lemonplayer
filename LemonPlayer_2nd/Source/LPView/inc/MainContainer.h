/*
 ============================================================================
 Name		: FileListContainer.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileListContainer declaration
 ============================================================================
 */

#ifndef MAINCONTAINER_H
#define MAINCONTAINER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <coecntrl.h>
#include "MSoundInterface.h"
// CLASS DECLARATION
//class CUIViewData;
class CUIDisplay;
class CUIXmlParser;
class CUIKeyEvent;
class CSoundManager;
class CUIViewData;
class CUIDataSerialize;
/**
 *  CFileListContainer
 * 
 */
class CMainContainer : 	public CCoeControl, 
						public MCoeControlObserver,
						public MSoundCallBack
	{
public:
	~CMainContainer();
	void ConstructL(const TRect& aRect);
	
public:
	//MSoundCallBack
	virtual void InitComplete();
	virtual void PlayComplete();

private:
	// Functions from base classes

	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);	
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
				TEventCode aType);
	
public:
	void SetData(CUIViewData *aData){iData = aData;};
	void PlayFile();
	void SaveData();
	
private:
	CUIViewData 	*iData;
	CUIDisplay 		*iDisplay;
	CUIXmlParser 	*iParser;
	CUIKeyEvent		*iEvent;
	CSoundManager	*iSoundManager;
	CUIDataSerialize *iSerialize;
		
	};

#endif // MAINCONTAINER_H
