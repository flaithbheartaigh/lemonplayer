/*
 ============================================================================
 Name		: FileListContainer.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileListContainer declaration
 ============================================================================
 */

#ifndef FILELISTCONTAINER_H
#define FILELISTCONTAINER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <coecntrl.h>

// CLASS DECLARATION

/**
 *  CFileListContainer
 * 
 */
class CFileListContainer : public CCoeControl, MCoeControlObserver
	{
public:
	~CFileListContainer();

	void ConstructL(const TRect& aRect);

private:
	// Functions from base classes

	/**
	 * From CoeControl,SizeChanged.
	 */
	void SizeChanged();

	/**
	 * From CoeControl,CountComponentControls.
	 */
	TInt CountComponentControls() const;

	/**
	 * From CCoeControl,ComponentControl.
	 */
	CCoeControl* ComponentControl(TInt aIndex) const;

	/**
	 * From CCoeControl,Draw.
	 */
	void Draw(const TRect& aRect) const;

	/**
	 * From MCoeControlObserver
	 * Acts upon changes in the hosted control's state. 
	 *
	 * @param	aControl	The control changing its state
	 * @param	aEventType	The type of control event 
	 */
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
	};

#endif // FILELISTCONTAINER_H
