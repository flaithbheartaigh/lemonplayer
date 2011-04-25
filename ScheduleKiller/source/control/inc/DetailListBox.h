/*
 ============================================================================
 Name		: DetailListBox.h
 Author	  : JohnLZeng
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CDetailListBox declaration
 ============================================================================
 */

#ifndef DETAILLISTBOX_H
#define DETAILLISTBOX_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <eiktxlbx.h>
// CLASS DECLARATION
class MDetailListBoxNotify
	{
public:
	enum TEventType
		{
		EEventNone = 0,
		EEventRemove
		};
	
	virtual void HandleListEvent(TEventType aEvent) = 0;
	};
/**
 *  CDetailListBox
 * 
 */
class CDetailListBox : public CEikTextListBox
	{
protected: // from CEikTextListBox
	virtual void CreateItemDrawerL();
	
public:
	void OfferPointerEventL(const TPointerEvent& aPointerEvent);
	
	void SetNotify(MDetailListBoxNotify* aNotify) 
		{iNotify = aNotify;};
	void SetShowItems(TInt aItems) {iShowItems = aItems;};
	
	void SetListFocus(TBool aFocus);
	void UpdateScrollBar();
private:
	MDetailListBoxNotify* iNotify;
	TInt	iShowItems;			//可视区域内显示的列表数
	};

#endif // DETAILLISTBOX_H
