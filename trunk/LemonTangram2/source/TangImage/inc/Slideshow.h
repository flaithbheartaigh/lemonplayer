/*
 * ==============================================================================
 *  Name        : Slideshow.h
 *  Part of     : OpenGLEx / Slideshow
 *
 *  Copyright (c) 2005-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

#ifndef __SLIDESHOWH__
#define __SLIDESHOWH__

//  INCLUDES

#include <e32base.h> // for CBase definition
#include <w32std.h>
#include <coecntrl.h>
#include <GLES\gl.h>      // OpenGL ES header file
#include <GLES\egl.h>
#include "Textureutils.h"
#include "Mathutils.h"
#include "Utils3d.h"
#include <coecntrl.h>
#include "Glutils.h" // Misc GLU and GLUT functions
#include "GestureDef.h"
#include "TangImageData.h"


// FORWARD DECLARATIONS
#define EShapeTriangleBig1 		0
#define EShapeTriangleBig2		1
#define EShapeTriangleSmall1	2
#define EShapeTriangleSmall2	3
#define EShapeTriangleMid		4	
#define EShapeTriangleSquare	5
#define EShapeTriangleRect		6
/**
 * Class that does the actual OpenGL ES rendering.
 * Subclass of CFiniteStateMachine because the application
 * needs to handle loading textures and running states.
 */
enum TSelectedState
	{
	ESelectedSame,
	ESelectedDiff,
	ESelectedEdge,
	};

class CSlideshow
	: public CFiniteStateMachine, public MTextureLoadingListener
	{
	public: // Constructors and destructor

        /**
         * Factory method for creating a new CSlideshow object.
		 * Calls the hidden constructors.
         */
		static CSlideshow* NewL( TUint aWidth, TUint aHeight );

        /**
         * Destructor. Does nothing.
         */
		virtual ~CSlideshow();
		
		static CSlideshow
				* NewL(CCoeControl* aParentControl, RWindow* aParentWindow);

		/**
		 * Two-phased constructor.
		 */
		static CSlideshow* NewLC(CCoeControl* aParentControl,
				RWindow* aParentWindow);

	private:

		/**
		 * Constructor for performing 1st stage construction
		 */
		CSlideshow(CCoeControl* aParentControl, RWindow* aParentWindow);

	protected: // Hidden constructors

        /**
         * Standard constructor that must never Leave.
         * Stores the given screen width and height.
         * @param aWidth Width of the screen.
         * @param aHeight Height of the screen.
         */
		CSlideshow( TUint aWidth, TUint aHeight );

        /**
         * Second phase constructor that can call methods that may leave. Does nothing.
         */
		void ConstructL( void );


	public: // New methods

        /**
         * Initializes OpenGL ES, sets the vertex and color
         * arrays and pointers. Also selects the shading mode and
         * creates the CTextureManager instance and starts loading
         * of required textures.
         */
		void AppInitL( void );

        /**
         * Called upon application exit. Destroys the CTextureManager
         * instance that was created in AppInitL() method.
         */
		void AppExit( void );

    	/**
    	 * Called when the finite state machine enters a new state.
    	 * Does nothing in this implementation.
    	 * @param aState State that is about to be entered.
    	 */
		void OnEnterStateL( TInt aState);

    	/**
    	 * Called when texture manager starts loading the textures.
    	 * Sets the current state to "loading textures".
    	 */
		void OnStartLoadingTexturesL();

    	/**
    	 * Called when texture manager has completed texture loading.
    	 * Changes the current state to "running".
    	 */
		void OnEndLoadingTexturesL();

        /**
         * Notifies that the screen size has dynamically changed during execution of
         * this program. Resets the viewport to this new size and sets this size
         * to the CTextureManager.
         * @param aWidth New width of the screen.
         * @param aHeight New height of the screen.
         */
        void SetScreenSize( TUint aWidth, TUint aHeight );
        
    	void SetRedererState();
    	void Render();
    	
    	void MouseSelected(TInt aX,TInt aY); 	
    	void MouseDrag(TGestureType aGuestrue,TPoint aStart,TPoint aEnd);
    	
    	void SetImageData(CTangImageData* aImageData) {iImageData = aImageData;};
    	
private: 	
		void DrawBackground();
    	void DrawTangram();
    	void DrawParticles();
    	
    	void DrawTangram(const TInt& aIndex);
    	
    	TInt GetSelected(TInt aX,TInt aY);
    	void InitConstellation();
    	TInt GetConstellation(TInt aMonth,TInt aDay);
    	
    	void MouseDragRotate(TGestureType aGuestrue,TPoint aStart,TPoint aEnd);
    	void MouseDragTranslate(TGestureType aGuestrue,TPoint aStart,TPoint aEnd);

	public: // Data
    	/**
    	 * Application states:
    	 * ELoadingTextures - indicates that the app. is loading textures.
    	 * ERunning - indicates that the app. is running.
    	 */
		enum
		    {
		    ELoadingTextures,
		    ERunning
		    };

        /**
         *  The ways one can navigate a slideshow.
         */
        enum TDirection
            {
            ENext,
            EPrevious,
            };

	private: // Data
		GLint iCameraDistance;
		
		CTangImageData* iImageData;
	
		
		CCoeControl* iParentControl;
		RWindow* iParentWindow;

		EGLDisplay iEglDisplay; // display where the graphics are drawn
		EGLContext iEglContext; // rendering context
		EGLSurface iEglSurface; // window where the graphics are blitted
		
    	/** Texture manager that is used to load the used textures. */
		CTextureManager* iTextureManager;
        /** Width of the screen */
        TUint iScreenWidth;
        /** Height of the screen */
        TUint iScreenHeight;

        /** Pictures to cycle */
        TTexture iPictures[2];
        TTexture iConstellationPictures[12];
        
        TInt iCurrentConstellation;
        
        TInt iSelectedState;
	};

#endif

// End of File

