/*
 ============================================================================
 Name		: LemonMenuList.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenuList declaration
 ============================================================================
 */

#ifndef LEMONMENULIST_H
#define LEMONMENULIST_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <bitstd.h>

// CLASS DECLARATION
class CLemonMenuItem;
/**
 *  CLemonMenuList
 * 
 */
class CLemonMenuList : public CBase
	{
public:
	// Constructors and destructor
	~CLemonMenuList();
	static CLemonMenuList* NewL(const CFont* aFont);
	static CLemonMenuList* NewLC(const CFont* aFont);

private:
	CLemonMenuList(const CFont* aFont);
	void ConstructL();
	
public:
	CLemonMenuItem* FindItemById(const TInt& aId);
	CLemonMenuList*& FindListById(const TInt& aId);
	void AddItem(CLemonMenuItem* aItem);
	void Clear();
	
	void Draw(CBitmapContext& gc);
	
	void SetPositon(const TPoint& aPosition) {iPosition = aPosition;};
	TPoint GetPosition() const {return iPosition;};
	void SetListSize(const TSize& aSize) {iSize = aSize;};
	TSize GetListSize(){return iSize;};
	
	void SetItemHeight(const TInt& aHeight) {iItemHeight = aHeight;};
	TInt GetItemHeight(){return iItemHeight;};
	void RecordItemWidth(TInt aWidth);
	void OffsetItem();
	
	void ResetSelectedIndex();
	void SetSelectedIndex(const TInt& aIndex);
	void IncreaseSelected();
	void DecreaseSelected();
	
	TInt GetSelectedCommand();
	
private:
	void DrawFrame(CBitmapContext& gc);
private:
	RPointerArray<CLemonMenuItem> iItems;
	TPoint iPosition;
	TSize  iSize;
	TRgb iFrameColor;
	TRgb iBackgroundColor;
	
	TInt iItemWidth;
	TInt iItemHeight;
	
	const CFont* iFont;
	
	TInt iSelectedIndex;

	};

#endif // LEMONMENULIST_H
