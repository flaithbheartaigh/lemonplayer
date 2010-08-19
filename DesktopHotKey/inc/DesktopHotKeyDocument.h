/*
 ============================================================================
 Name		: DesktopHotKeyDocument.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __DESKTOPHOTKEYDOCUMENT_h__
#define __DESKTOPHOTKEYDOCUMENT_h__

// INCLUDES
#include <akndoc.h>
#ifdef EKA2
#include "IconFileProvider.h"
#endif
// FORWARD DECLARATIONS
class CDesktopHotKeyAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CDesktopHotKeyDocument application class.
 * An instance of class CDesktopHotKeyDocument is the Document part of the
 * AVKON application framework for the DesktopHotKey example application.
 */
class CDesktopHotKeyDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CDesktopHotKeyDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CDesktopHotKeyDocument.
	 */
	static CDesktopHotKeyDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CDesktopHotKeyDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CDesktopHotKeyDocument.
	 */
	static CDesktopHotKeyDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CDesktopHotKeyDocument
	 * Virtual Destructor.
	 */
	virtual ~CDesktopHotKeyDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CDesktopHotKeyAppUi object and return a pointer to it.
	 * The object returned is owned by the Uikon framework.
	 * @return Pointer to created instance of AppUi.
	 */
	CEikAppUi* CreateAppUiL();

private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CDesktopHotKeyDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CDesktopHotKeyDocument(CEikApplication& aApp);
	
#ifdef EKA2
public:
	CIconFileProvider* GetIconFileProvider() {return iIconProvider;};
	void SetIconFileProvider(CIconFileProvider* aIconProvider) {iIconProvider = aIconProvider;};

private:
	CIconFileProvider* iIconProvider;
#endif
	};

#endif // __DESKTOPHOTKEYDOCUMENT_h__
// End of File
