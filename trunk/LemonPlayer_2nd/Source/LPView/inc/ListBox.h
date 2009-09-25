/*
 ============================================================================
 Name		: ListBox.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBox declaration
 ============================================================================
 */

#ifndef LISTBOX_H
#define LISTBOX_H

// INCLUDES
#include <e32base.h>
#include <coecntrl.h>
#include "ListStructure.h"
#include "ViewNotify.h"

// CLASS DECLARATION
class CEikColumnListBox;
class CListEngine;
class CUIViewData;
class CFbsBitmap;
/**
 *  CListBox
 * 
 */
class CListBox : public CCoeControl
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CListBox();
	
	static CListBox* NewL(const TRect& aRect);
	static CListBox* NewLC(const TRect& aRect);

	
	void ConstructL(const TRect& aRect);
	
	void Draw(const TRect& aRect) const;
	
private:
	CListBox();		
	TInt CountComponentControls() const;
	CCoeControl *ComponentControl(TInt aIndex) const;
	void SizeChanged();
	TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType); 
	
private:
	void CreateListboxL();
	void AddItem(RPointerArray<TListItem>* aArray);
	void CleanItem();
	void SetupListIconsL();
	
public: 
	void SelectedItem();
	void AddItem(const TDesC &aItem);
	void DeleteItem();
	void OpenItem(const TDesC &aItem);
	
private:
	TBool OpenFile(const TDesC& aFile);
	TBool CheckFormat(const TDesC& aFormat);
	
public:
	void SetData(CUIViewData *aData){iData = aData;};
	void SetNotify(MListBoxViewNotify *aNotify){iNotify=aNotify;};
	
private:
	CEikColumnListBox* iListBox;
	CListEngine* iList;
	TFileName iCurrentPath;
	CUIViewData *iData;
	
	MListBoxViewNotify *iNotify;
	
	CDesCArray* iFormatArray;
	};

#endif // LISTBOX_H
