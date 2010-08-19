/*
 ============================================================================
 Name		: AppScreenContainer.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares container control for application.
 ============================================================================
 */

#ifndef APPSCREENCONTAINER_H
#define APPSCREENCONTAINER_H


// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <eikclb.h> 
#include <aknsfld.h> 

#include "LoadAppEngine.h"
// CLASS DECLARATION

/**
 *  CAppList
 * 
 */
class CAppScreenContainer : public CCoeControl, MCoeControlObserver , MLoadAppEngineNotify
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CAppScreenContainer();

	/**
	 * Two-phased constructor.
	 */
	static CAppScreenContainer* NewL(const TRect& aRect);

	/**
	 * Two-phased constructor.
	 */
	static CAppScreenContainer* NewLC(const TRect& aRect);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CAppScreenContainer();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL(const TRect& aRect);

public:
	// Functions from base classes
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	
	void Selected();
	
	//MLoadAppEngineNotify
	void GetAppInfo(CGulIcon* aIcon,const TDesC& aInfo,const TUid aUid);

private:
	// Functions from base classes
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

	void UpdateDisplay();
	void SetIconsL();

	TInt GetAppsL();
	
	CAknSearchField* CreateFindBoxL(CEikListBox* aListBox,
			CTextListBoxModel* aModel,
			CAknSearchField::TSearchFieldStyle aStyle);
private:
	//data
	CEikColumnListBox* iListBox;
	CAknSearchField* iFindBox;
	
	RArray<TUid>	iUids;
	
	CLoadAppEngine* iAppEngine;
	};

#endif

