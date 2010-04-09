/*
 ============================================================================
 Name		: ThemeManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CThemeManager declaration
 ============================================================================
 */

#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <AknSSrvClient.h>
#include <aknskinsinternalcrkeys.h>
#include <ThemeDef.h>
// CLASS DECLARATION

/**
 *  CThemeManager
 * 
 */
class CThemeManager : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CThemeManager();

	/**
	 * Two-phased constructor.
	 */
	static CThemeManager* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CThemeManager* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CThemeManager();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	TInt ChangeTheme();

	TInt DisplayAll(RArray<TThemeInfo>& aArray);
	TInt GetCurrentTheme(TAknsPkgIDBuf& aTheme);
	TInt GetCurrentTheme(TAknsPkgID& aTheme);
	TInt SetTheme(const TAknsPkgIDBuf& aTheme);
	TInt SetTheme(const TAknsPkgID& aTheme);
	
private:
	RAknsSrvSession iSession;
	TInt iCurrent;
	};

#endif // THEMEMANAGER_H
