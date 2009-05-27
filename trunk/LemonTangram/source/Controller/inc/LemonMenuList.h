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
	static CLemonMenuList* NewL();
	static CLemonMenuList* NewLC();

private:
	CLemonMenuList();
	void ConstructL();
	
public:
	CLemonMenuItem* FindItemById(const TInt& aId);
	CLemonMenuList*& FindListById(const TInt& aId);
	void AddItem(CLemonMenuItem* aItem);
	void Clear();
	
	void Draw(CFbsBitGc& gc);
	
	void SetPositon(const TPoint& aPosition) {iPosition = aPosition;};
	TPoint GetPosition() const {return iPosition;};
private:
	RPointerArray<CLemonMenuItem> iItems;
	TPoint iPosition;
	
	TInt iItemHeight;
	};

#endif // LEMONMENULIST_H
