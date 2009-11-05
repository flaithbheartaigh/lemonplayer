/*
 ============================================================================
 Name		: UI320x240.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUI320x240 declaration
 ============================================================================
 */

#ifndef UI320X240_H
#define UI320X240_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "UIMgr.h"
// CLASS DECLARATION

/**
 *  CUI320x240
 * 
 */
class CUI320x240 : public MUIMgr
	{
public:
	// Constructors and destructor
	~CUI320x240();
	CUI320x240();
	
public:
	
	virtual TPoint BottomBarPos();
	
	virtual TPoint BottomLeftOption() ;
	virtual TPoint BottomRightOption() ;
	
	//工具条长度
	virtual TSize TitleBarSize();
	virtual TSize BottomBarSize();
	virtual TRect TitleIconSize();
	virtual TPoint TitleTextPos();
	virtual TPoint TitleTimePos();
	virtual TInt   TitleTextPixels();
	
	
	virtual TPoint MainMenuPos();
	virtual TSize MainMenuSize() ;	
	
	virtual TInt SubMenuWidth(); 
	virtual TInt MainMenuItemHeight();
	
	virtual TBool ChangeFontSize(const TInt aSize);
	
	virtual TSize DrawableSize();
	};

#endif // UI320X240_H
