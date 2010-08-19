/*
 ============================================================================
 Name		: Particles.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CParticles declaration
 ============================================================================
 */

#ifndef PARTICLES_H
#define PARTICLES_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <w32std.h>
#include <coecntrl.h>
#include <GLES\egl.h>
#include "Utils3d.h" // Utilities (texmanager, textures etc.)
#include "Glutils.h" // Misc GLU and GLUT functions

//LIBRARY        libgles_cm.lib ws32.lib imageconversion.lib fbscli.lib

// CLASS DECLARATION

/**
 *  CParticles
 * 
 */
class CParticles : public CFiniteStateMachine,public MTextureLoadingListener
	{
public:
	// Constructors and destructor
	enum
		{
		ELoadingTextures,
		ERunning
		};
	
	/**
	 * Destructor.
	 */
	virtual ~CParticles();

	/**
	 * Two-phased constructor.
	 */
	static CParticles
			* NewL(CCoeControl* aParentControl, RWindow* aParentWindow);

	/**
	 * Two-phased constructor.
	 */
	static CParticles* NewLC(CCoeControl* aParentControl,
			RWindow* aParentWindow);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CParticles(CCoeControl* aParentControl, RWindow* aParentWindow);

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

private:
	void OnEnterStateL( TInt aState);
	void OnStartLoadingTexturesL() ;
	void OnEndLoadingTexturesL() ;
	
public:
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	
	void SetRedererState();
	void Render();
	
private:
	void SetScreenSize( TUint aWidth, TUint aHeight );
	
	void DrawTangram();
	void DrawGLScene();

public:
	GLint iCameraDistance;
	GLint iFrame;
	
	GLint iRotate[7];
	GLint iTranslateX;
	GLint iTranslateY;
	GLint iTranslate[7][2];
private:
	CCoeControl* iParentControl;
	RWindow* iParentWindow;

	EGLDisplay iEglDisplay; // display where the graphics are drawn
	EGLContext iEglContext; // rendering context
	EGLSurface iEglSurface; // window where the graphics are blitted

	TInt iScreenWidth;
	TInt iScreenHeight;
	
	CTextureManager * iTextureManager;
	TTexture iOpenGLES;
	TTexture iTextureParticle;

	};

#endif // Particles_H
