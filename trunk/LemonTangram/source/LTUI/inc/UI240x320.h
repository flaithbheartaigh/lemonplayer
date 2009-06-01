/*
 ============================================================================
 Name		: UI240x320.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUI240x320 declaration
 ============================================================================
 */

#ifndef UI240X320_H
#define UI240X320_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "UIMgr.h"
// CLASS DECLARATION

/**
 *  CUI240x320
 * 
 */
class CUI240x320 : public MUIMgr
	{
public:
	// Constructors and destructor
	~CUI240x320();
	CUI240x320();

public:
	
	virtual TPoint BottomBarPos();
	
	virtual TPoint BottomLeftOption() ;
	virtual TPoint BottomRightOption() ;
	
	virtual TRect BottomState() ;
	virtual TPoint BottomTextEnd() ;
	virtual TPoint BottomTextReceive() ;
	virtual TPoint BottomTextConnect() ;
	
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
	
	virtual TPoint BMMenuPos() ;
	virtual TSize BMMenuSize() ;
		
	virtual TPoint DLMenuPos() ;
	virtual TSize DLMenuSize() ;
	virtual TInt DLSubMenuWidth() ;
	
	virtual TBool ChangeFontSize(const TInt aSize);
	
	virtual TSize DownloadItemRest();
	virtual TSize DownloadItemRun();
	
	virtual TRect IMEIconPos();
	
	virtual TSize DrawableSize();
	};

#endif // UI240X320_H
