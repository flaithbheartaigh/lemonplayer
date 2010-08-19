/*
 ============================================================================
 Name		: UIManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CUIManager declaration
 ============================================================================
 */

#ifndef UIMANAGER_H
#define UIMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <gdi.h>
// CLASS DECLARATION

/**
 *  CUIManager
 * 
 */
class CUIManager : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CUIManager();

	/**
	 * Two-phased constructor.
	 */
	static CUIManager* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CUIManager* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CUIManager();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	const CFont* GetFont();
	
	TBool CheckPenEnabled();	
	
	TInt GetContentHeight() const {return GetClockHeight()+GetPadding()+GetAppHeight();};
	
	TSize GetClockSingleDigtalSize() const {return iClockSingleDigitalSize;};
	TInt GetClockSingleDigitalWidth() const {return iClockSingleDigitalSize.iWidth;};
	TInt GetClockHeight() const {return iClockSingleDigitalSize.iHeight;};
	
	TSize GetClockColonSize() const {return iClockColonSize;};
	TInt GetClockColonWidth() const {return iClockColonSize.iWidth;};
	
	TInt GetPadding() const {return 5;};
	
	TSize GetIconSize() const {return iIconSize;};
	
	TInt GetAppHeight() const {return iIconSize.iHeight;};
	
private:
	TSize iClockSingleDigitalSize;
	TSize iClockColonSize;
	TSize iIconSize;

	};

#endif // UIMANAGER_H
