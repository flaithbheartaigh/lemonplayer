/*
 ============================================================================
 Name		: MainScreenContainer.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMainScreenContainer declaration
 ============================================================================
 */

#ifndef MAINSCREENCONTAINER_H
#define MAINSCREENCONTAINER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <eikclb.h> 
#include <eikfrlb.h> 
#include "SimMsgStruct.h"
// CLASS DECLARATION

/**
 *  CMainScreenContainer
 * 
 */
class CMainScreenContainer : public CCoeControl, MCoeControlObserver
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CMainScreenContainer();

	/**
	 * Two-phased constructor.
	 */
	static CMainScreenContainer* NewL(const TRect& aRect);

	/**
	 * Two-phased constructor.
	 */
	static CMainScreenContainer* NewLC(const TRect& aRect);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CMainScreenContainer();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL(const TRect& aRect);

public:
	// Functions from base classes
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

	void RemoveSelectedTask();
	void EditSelectedTask();
	
private:
	// Functions from base classes
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

	void UpdateDisplay();
	void SetIconsL();
	

private:
	//data
//	CEikColumnListBox* iListBox;
	CEikFormattedCellListBox* iListBox;
	RSimMsgDataArray* iTaskArray;
	};

#endif // MAINSCREENCONTAINER_H
