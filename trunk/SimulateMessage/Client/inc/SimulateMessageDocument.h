/*
 ============================================================================
 Name		: SimulateMessageDocument.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __SIMULATEMESSAGEDOCUMENT_h__
#define __SIMULATEMESSAGEDOCUMENT_h__

// INCLUDES
#include <akndoc.h>
#ifdef EKA2
#include "IconFileProvider.h"
#endif
// FORWARD DECLARATIONS
class CSimulateMessageAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CSimulateMessageDocument application class.
 * An instance of class CSimulateMessageDocument is the Document part of the
 * AVKON application framework for the SimulateMessage example application.
 */
class CSimulateMessageDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CSimulateMessageDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CSimulateMessageDocument.
	 */
	static CSimulateMessageDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CSimulateMessageDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CSimulateMessageDocument.
	 */
	static CSimulateMessageDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CSimulateMessageDocument
	 * Virtual Destructor.
	 */
	virtual ~CSimulateMessageDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CSimulateMessageAppUi object and return a pointer to it.
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
	 * CSimulateMessageDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CSimulateMessageDocument(CEikApplication& aApp);

#ifdef EKA2
public:
	CIconFileProvider* GetIconFileProvider() {return iIconProvider;};
	void SetIconFileProvider(CIconFileProvider* aIconProvider) {iIconProvider = aIconProvider;};

private:
	CIconFileProvider* iIconProvider;
#endif
	};

#endif // __SIMULATEMESSAGEDOCUMENT_h__
// End of File
