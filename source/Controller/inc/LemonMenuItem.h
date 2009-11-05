/*
 ============================================================================
 Name		: LemonMenuItem.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenuItem declaration
 ============================================================================
 */

#ifndef LEMONMENUITEM_H
#define LEMONMENUITEM_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <bitstd.h>

// CLASS DECLARATION
class CLemonMenuList;
/**
 *  CLemonMenuItem
 * 
 */
class CLemonMenuItem : public CBase
	{
public:
	// Constructors and destructor
	~CLemonMenuItem();
	static CLemonMenuItem* NewL(const CFont* aFont);
	static CLemonMenuItem* NewLC(const CFont* aFont);

private:
	CLemonMenuItem(const CFont* aFont);
	void ConstructL();
	
public:
	CLemonMenuItem* FindItemById(const TInt& aId);
	CLemonMenuList*& GetChildListAdd();
	CLemonMenuList* GetChildList();
	
	void Draw(CFbsBitGc& gc);
	
	void SetId(const TInt& aId){iId = aId;};
	TInt GetId()const {return iId;};
	void SetCommand(const TInt& aCommand){iCommand = aCommand;};
	TInt GetCommand() const {return iCommand;};
	void SetText(const TDesC& aText) {iText = aText.AllocL();};
	const TDesC& GetText() const {return *iText;};
	
	void Clear();
	
	void SetItemWidth(TInt aWidth){iItemWidth = aWidth;};
	TInt GetItemWidth(){return iItemWidth;};
	void SetItemHeight(TInt aHeight){iItemHeight = aHeight;};
	TInt GetItemHeight() {return iItemHeight;};
	void SetItemPosition(const TPoint& aPoint) {iItemPosition = aPoint;};
	TPoint GetItemPosition(){return iItemPosition;};
	
	void SetSelected(TBool aSelected) {iSelected = aSelected;};
	TBool GetSelected() const {return iSelected;};
private:
	TInt iId;
	TInt iCommand;
	HBufC* iText;
	CLemonMenuList* iChildList;
	
	TInt iItemWidth;
	TInt iItemHeight;
	TPoint iItemPosition;
	
	TRgb iTextColor;
	TRgb iSelectedColor;
	TRgb iUnSelectedColor;
	
	const CFont* iFont;
	
	TBool iSelected;
	
	};

#endif // LEMONMENUITEM_H
