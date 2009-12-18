/*
 ============================================================================
 Name		: Tangram3DDocument.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __TANGRAM3DDOCUMENT_h__
#define __TANGRAM3DDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CTangram3DAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CTangram3DDocument application class.
 * An instance of class CTangram3DDocument is the Document part of the
 * AVKON application framework for the Tangram3D example application.
 */
class CTangram3DDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CTangram3DDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CTangram3DDocument.
	 */
	static CTangram3DDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CTangram3DDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CTangram3DDocument.
	 */
	static CTangram3DDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CTangram3DDocument
	 * Virtual Destructor.
	 */
	virtual ~CTangram3DDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CTangram3DAppUi object and return a pointer to it.
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
	 * CTangram3DDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CTangram3DDocument(CEikApplication& aApp);

	};

#endif // __TANGRAM3DDOCUMENT_h__
// End of File
