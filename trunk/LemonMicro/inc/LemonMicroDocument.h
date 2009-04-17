/*
 ============================================================================
 Name		: LemonMicroDocument.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __LEMONMICRODOCUMENT_h__
#define __LEMONMICRODOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CLemonMicroAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CLemonMicroDocument application class.
 * An instance of class CLemonMicroDocument is the Document part of the
 * AVKON application framework for the LemonMicro example application.
 */
class CLemonMicroDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CLemonMicroDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CLemonMicroDocument.
	 */
	static CLemonMicroDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CLemonMicroDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CLemonMicroDocument.
	 */
	static CLemonMicroDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CLemonMicroDocument
	 * Virtual Destructor.
	 */
	virtual ~CLemonMicroDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CLemonMicroAppUi object and return a pointer to it.
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
	 * CLemonMicroDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CLemonMicroDocument(CEikApplication& aApp);

	};

#endif // __LEMONMICRODOCUMENT_h__
// End of File
