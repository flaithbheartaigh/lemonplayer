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

	virtual TRect BottomState();
	virtual TPoint BottomTextEnd();
	virtual TPoint BottomTextReceive();
	virtual TPoint BottomTextConnect();
	
	//工具条长度
	virtual TSize TitleBarSize();
	virtual TSize BottomBarSize();
	virtual TRect TitleIconSize();
	virtual TPoint TitleTextPos();
	virtual TPoint TitleTimePos();
	virtual TInt   TitleTextPixels();

	virtual TPoint MainMenuPos();
	virtual TSize MainMenuSize();
	
	virtual TPoint BMMenuPos() ;
	virtual TSize BMMenuSize() ;
		
	virtual TPoint DLMenuPos() ;
	virtual TSize DLMenuSize() ;
	virtual TInt DLSubMenuWidth() ;
	
	virtual TInt SubMenuWidth(); 
	virtual TInt MainMenuItemHeight();
	
	virtual TBool ChangeFontSize(const TInt aSize);
	
	virtual TSize DownloadItemRest();
	virtual TSize DownloadItemRun();
	
	virtual TRect IMEIconPos();
	
	virtual TSize DrawableSize();
	};

#endif // UI176X208_H
