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
	static CLemonMenuItem* NewL();
	static CLemonMenuItem* NewLC();

private:
	CLemonMenuItem();
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
private:
	TInt iId;
	TInt iCommand;
	HBufC* iText;
	CLemonMenuList* iChildList;
	
	};

#endif // LEMONMENUITEM_H
