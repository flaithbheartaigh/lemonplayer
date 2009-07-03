/*
 ============================================================================
 Name		: UI176x208.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUI176x208 declaration
 ============================================================================
 */

#ifndef UI176X208_H
#define UI176X208_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "UIMgr.h"
// CLASS DECLARATION

/**
 *  CUI176x208
 * 
 */
class CUI176x208 : public MUIMgr
	{
public:
	// Constructors and destructor

	~CUI176x208();
	CUI176x208();

public:

	virtual TPoint BottomBarPos();

	virtual TPoint BottomLeftOption();
	virtual TPoint BottomRightOption();
	
	//工具条长度
	virtual TSize TitleBarSize();
	virtual TSize BottomBarSize();
	virtual TRect TitleIconSize();
	virtual TPoint TitleTextPos();
	virtual TPoint TitleTimePos();
	virtual TInt   TitleTextPixels();

	virtual TPoint MainMenuPos();
	virtual TSize MainMenuSize();
	
	virtual TInt SubMenuWidth(); 
	virtual TInt MainMenuItemHeight();
	
	virtual TBool ChangeFontSize(const TInt aSize);
	
	virtual TSize DrawableSize();
	};

#endif // UI176X208_H
