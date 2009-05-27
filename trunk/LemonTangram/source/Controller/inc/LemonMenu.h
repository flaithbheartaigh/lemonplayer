/*
 ============================================================================
 Name		: LemonMenu.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLemonMenu declaration
 ============================================================================
 */

#ifndef LEMONMENU_H
#define LEMONMENU_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <COEDEF.H>
#include <BITSTD.H>
#include <W32STD.H>

#include "MLemonMenuNotify.h"
#include "DefaultDocHandler.h"

// CLASS DECLARATION
class CLemonMenuBar;
class CLemonMenuList;

/**
 *  CLemonMenu
 * 
 */
class CLemonMenu : public CBase, public CDefaultDocHandler
	{
public:
	// Constructors and destructor
	~CLemonMenu();
	static CLemonMenu* NewL(MLemonMenuNotify* aNotify);
	static CLemonMenu* NewLC(MLemonMenuNotify* aNotify);

private:
	CLemonMenu(MLemonMenuNotify* aNotify);
	void ConstructL();
	
public:
	//CDefaultDocHandler
	virtual void StartElement(const TQualified& aName,
			const RArray<TAttribute>& aAttributes);
	virtual void EndElement(const TQualified& aName);
	
	void LoadMenu(const TDesC& aFileName);
	void Draw(CFbsBitGc& gc);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	
private:
	TInt ConvertNameToNumber(const TDesC& aName);	
	
	void ParseMenu(const RArray<TAttribute>& aAttributes);
	void ParseItem(const RArray<TAttribute>& aAttributes);
	
	void FindListById(const TInt& aId);
private:
	MLemonMenuNotify* iNotify;
	CLemonMenuBar* iMenuBar;
	CLemonMenuList* iMenuList;
	CLemonMenuList*& iPtrList;	//no own,用于添加数据用
	};

#endif // LEMONMENU_H
