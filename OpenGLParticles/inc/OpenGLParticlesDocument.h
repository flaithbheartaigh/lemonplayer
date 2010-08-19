/*
 ============================================================================
 Name		: OpenGLParticlesDocument.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __OPENGLPARTICLESDOCUMENT_h__
#define __OPENGLPARTICLESDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class COpenGLParticlesAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * COpenGLParticlesDocument application class.
 * An instance of class COpenGLParticlesDocument is the Document part of the
 * AVKON application framework for the OpenGLParticles example application.
 */
class COpenGLParticlesDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a COpenGLParticlesDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of COpenGLParticlesDocument.
	 */
	static COpenGLParticlesDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a COpenGLParticlesDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of COpenGLParticlesDocument.
	 */
	static COpenGLParticlesDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~COpenGLParticlesDocument
	 * Virtual Destructor.
	 */
	virtual ~COpenGLParticlesDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a COpenGLParticlesAppUi object and return a pointer to it.
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
	 * COpenGLParticlesDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	COpenGLParticlesDocument(CEikApplication& aApp);

	};

#endif // __OPENGLPARTICLESDOCUMENT_h__
// End of File
