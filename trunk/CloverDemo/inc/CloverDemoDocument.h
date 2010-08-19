/*
 ============================================================================
 Name		: CloverDemoDocument.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __CLOVERDEMODOCUMENT_h__
#define __CLOVERDEMODOCUMENT_h__

// INCLUDES
#include <akndoc.h>
#ifdef EKA2
#include "IconFileProvider.h"
#endif
// FORWARD DECLARATIONS
class CCloverDemoAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CCloverDemoDocument application class.
 * An instance of class CCloverDemoDocument is the Document part of the
 * AVKON application framework for the CloverDemo example application.
 */
class CCloverDemoDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CCloverDemoDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CCloverDemoDocument.
	 */
	static CCloverDemoDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CCloverDemoDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CCloverDemoDocument.
	 */
	static CCloverDemoDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CCloverDemoDocument
	 * Virtual Destructor.
	 */
	virtual ~CCloverDemoDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CCloverDemoAppUi object and return a pointer to it.
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
	 * CCloverDemoDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CCloverDemoDocument(CEikApplication& aApp);

#ifdef EKA2
public:
	CIconFileProvider* GetIconFileProvider() {return iIconProvider;};
	void SetIconFileProvider(CIconFileProvider* aIconProvider) {iIconProvider = aIconProvider;};

private:
	CIconFileProvider* iIconProvider;
	//DEBUG(CFileLogger* iFileLogger)
#endif
	};

#endif // __CLOVERDEMODOCUMENT_h__
// End of File
