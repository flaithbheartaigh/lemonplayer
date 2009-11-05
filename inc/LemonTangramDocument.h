/*
 ============================================================================
 Name		: LemonTangramDocument.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __LEMONTANGRAMDOCUMENT_h__
#define __LEMONTANGRAMDOCUMENT_h__

// INCLUDES
#include <akndoc.h>
#ifdef EKA2
#include "IconFileProvider.h"
#endif
//#include "LPDebug.h"
// FORWARD DECLARATIONS
class CLemonTangramAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CLemonTangramDocument application class.
 * An instance of class CLemonTangramDocument is the Document part of the
 * AVKON application framework for the LemonTangram example application.
 */
class CLemonTangramDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CLemonTangramDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CLemonTangramDocument.
	 */
	static CLemonTangramDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CLemonTangramDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CLemonTangramDocument.
	 */
	static CLemonTangramDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CLemonTangramDocument
	 * Virtual Destructor.
	 */
	virtual ~CLemonTangramDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CLemonTangramAppUi object and return a pointer to it.
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
	 * CLemonTangramDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CLemonTangramDocument(CEikApplication& aApp);
#ifdef EKA2
public:
	CIconFileProvider* GetIconFileProvider() {return iIconProvider;};
	void SetIconFileProvider(CIconFileProvider* aIconProvider) {iIconProvider = aIconProvider;};


private:
	CIconFileProvider* iIconProvider;
	//DEBUG(CFileLogger* iFileLogger)
#endif
	};

#endif // __LEMONTANGRAMDOCUMENT_h__
// End of File
