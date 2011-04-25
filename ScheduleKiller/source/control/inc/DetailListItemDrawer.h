/*
 ============================================================================
 Name		: DetailListItemDrawer.h
 Author	  : JohnLZeng
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDetailListItemDrawer declaration
 ============================================================================
 */

#ifndef DETAILLISTITEMDRAWER_H
#define DETAILLISTITEMDRAWER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <eiklbi.h> 
#include <eiktxlbx.h> 
#include <GULICON.H>
// CLASS DECLARATION

/**
 *  CDetailListItemDrawer
 * 
 */
class CDetailListItemDrawer : public CListItemDrawer
	{
public:
	CDetailListItemDrawer(const CEikTextListBox& aListBox);
	~CDetailListItemDrawer();
	
private:
	// CListItemDrawer
	void DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect,
			TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed,
			TBool aItemIsSelected) const;

private:
	void InitIcons();
	
	void DrawClock(TInt aItemIndex,const TRect& aRect) const;
	void DrawApp(TInt aItemIndex,const TRect& aRect) const;
	void DrawClockDigital(TInt& aNumber,const TPoint& aPoint) const;
	void DrawDelButton(const TRect& aRect) const; 	
private:
	const CEikTextListBox& iListBox;
	RPointerArray<CGulIcon> *iClock;
	CGulIcon* iDeleteIcon;
	};

#endif // DETAILLISTITEMDRAWER_H
