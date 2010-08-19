/*
 ============================================================================
 Name		: ScheduleKillerDocument.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __SCHEDULEKILLERDOCUMENT_h__
#define __SCHEDULEKILLERDOCUMENT_h__

// INCLUDES
#include <akndoc.h>
#ifdef EKA2
#include "IconFileProvider.h"
#endif
// FORWARD DECLARATIONS
class CScheduleKillerAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CScheduleKillerDocument application class.
 * An instance of class CScheduleKillerDocument is the Document part of the
 * AVKON application framework for the ScheduleKiller example application.
 */
class CScheduleKillerDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CScheduleKillerDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CScheduleKillerDocument.
	 */
	static CScheduleKillerDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CScheduleKillerDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CScheduleKillerDocument.
	 */
	static CScheduleKillerDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CScheduleKillerDocument
	 * Virtual Destructor.
	 */
	virtual ~CScheduleKillerDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CScheduleKillerAppUi object and return a pointer to it.
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
	 * CScheduleKillerDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CScheduleKillerDocument(CEikApplication& aApp);
	
#ifdef EKA2
public:
	CIconFileProvider* GetIconFileProvider() {return iIconProvider;};
	void SetIconFileProvider(CIconFileProvider* aIconProvider) {iIconProvider = aIconProvider;};

private:
	CIconFileProvider* iIconProvider;
#endif
	};

#endif // __SCHEDULEKILLERDOCUMENT_h__
// End of File
