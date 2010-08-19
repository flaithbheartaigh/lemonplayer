/*
 ============================================================================
 Name		: ListBox.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBox declaration
 ============================================================================
 */

#ifndef LISTBOX_H
#define LISTBOX_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "BaseControl.h"
#include "AnimationFrame.h"
// CLASS DECLARATION
class CBackgroundControl;
class CScrollControl;
class CListBoxContainerControl;
class CListBoxItemControl;
/**
 *  CListBox
 * 
 */
class CCLListBox : public CBaseControl ,CAnimationFrame
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CCLListBox();

	/**
	 * Two-phased constructor.
	 */
	static CCLListBox* NewL(MAnimationNofity& aNotify);

	/**
	 * Two-phased constructor.
	 */
	static CCLListBox* NewLC(MAnimationNofity& aNotify);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CCLListBox(MAnimationNofity& aNotify);

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	//from basic
	virtual void Draw(CBitmapContext& gc) const;
	
	virtual void SetRect(const TRect &aRect);
	
	virtual void ReSize(const TRect &aRect);
	
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	
	//new func
	void AddItem(CListBoxItemControl* aItem);
	
	void Init();
	
private:
	CListBoxContainerControl* iContainer;
	CBackgroundControl* iBackground;
	CScrollControl* iScroll;
	};

#endif // LISTBOX_H
