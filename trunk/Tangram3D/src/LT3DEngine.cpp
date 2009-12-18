/*
 ============================================================================
 Name		: LT3DEngine.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLT3DEngine implementation
 ============================================================================
 */

#include "LT3DEngine.h"

// MACROS
#define FRUSTUM_LEFT   -1.f     //left vertical clipping plane
#define FRUSTUM_RIGHT   1.f     //right vertical clipping plane
#define FRUSTUM_BOTTOM -1.f     //bottom horizontal clipping plane
#define FRUSTUM_TOP     1.f     //top horizontal clipping plane
#define FRUSTUM_NEAR    3.f     //near depth clipping plane
#define FRUSTUM_FAR  1000.f     //far depth clipping plane

#define tex(u,v) (GLbyte)( (u) - 128 ) , (GLbyte)( (v) - 128 )

CLT3DEngine::CLT3DEngine(CCoeControl* aParentControl,RWindow*	aParentWindow)
:iParentControl(aParentControl),iParentWindow(aParentWindow),iRotate(0)
	{
	iScreenWidth = aParentControl->Rect().Width();
	iScreenHeight = aParentControl->Rect().Height();
	// No implementation required
	}

CLT3DEngine::~CLT3DEngine()
	{
	delete iTextureManager;
	
	eglMakeCurrent( iEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
	eglDestroySurface( iEglDisplay, iEglSurface );
	eglDestroyContext( iEglDisplay, iEglContext );
	eglTerminate( iEglDisplay ); // release resources associated with EGL & OpenGL ES
	}

CLT3DEngine* CLT3DEngine::NewLC(CCoeControl* aParentControl,RWindow*	aParentWindow)
	{
	CLT3DEngine* self = new (ELeave) CLT3DEngine(aParentControl,aParentWindow);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLT3DEngine* CLT3DEngine::NewL(CCoeControl* aParentControl,RWindow*	aParentWindow)
	{
	CLT3DEngine* self = CLT3DEngine::NewLC(aParentControl,aParentWindow);
	CleanupStack::Pop(); // self;
	return self;
	}

void CLT3DEngine::ConstructL()
	{
	EGLConfig     config;              // config describing properties of EGLSurface
	EGLConfig     *configList  = NULL; // pointer for EGLConfigs
	int           configSize   = 0;    // num of configs we want EGL to return
	int           numOfConfigs = 0;    // num of configs actually returned
	
	/* Get the display for drawing graphics */
	iEglDisplay = eglGetDisplay( EGL_DEFAULT_DISPLAY );	 

	/* Initialize display */
	eglInitialize( iEglDisplay, NULL, NULL );
	
	/* Get the number of all possible EGLConfigs */
	eglGetConfigs( iEglDisplay, configList, configSize, &numOfConfigs );
	configSize = numOfConfigs;
	 

	/* Allocate memory for configList */
	configList = (EGLConfig*) User::Alloc( sizeof(EGLConfig)*configSize );


	/* Define properties for the wanted EGLSurface.
	   To get the best possible performance, choose
	   an EGLConfig with a buffersize matching
	   the current window's display mode*/ 
	TDisplayMode DMode = iParentWindow->DisplayMode();
	TInt BufferSize = 0;	 

	switch(DMode)
	{
	    case(EColor4K):
	        BufferSize = 12;
	        break;
	    case(EColor64K):
	        BufferSize = 16;
	        break;
	    case(EColor16M):
	        BufferSize = 24;
	        break;
	    case(EColor16MU):
	        BufferSize = 32;
	        break;
	    default:
	        _LIT(KDModeError, "unsupported displaymode");
	        User::Panic( KDModeError, 0 );
	        break;
	}	 

	const EGLint attrib_list[] = { EGL_BUFFER_SIZE,BufferSize,   
	                               EGL_DEPTH_SIZE,16,    
	                               EGL_NONE };	 

	/* Choose those configs that fulfill the requirement in attrib_list */
	eglChooseConfig( iEglDisplay, attrib_list, configList, configSize, &numOfConfigs );	 

	/* Choose the ¡®best¡¯ config and use that in the future */
	config = configList[0];             // Choose the best EGLConfig. EGLConfigs
	                                    // returned by eglChooseConfig are sorted so
	                                    // that the best matching EGLconfig is first in
	                                    // the list.	 

	User::Free( configList );           // free configList, not used anymore
	
	/* Create a surface where the graphics are blitted */
	iEglSurface = eglCreateWindowSurface( iEglDisplay, config, iParentWindow, NULL );	 

	/* Create a rendering context */
	iEglContext = eglCreateContext( iEglDisplay, config, NULL, NULL );	 

	/* Make the context current. Binds to the current rendering thread and surface. Use the same surface for both drawing and reading */
	eglMakeCurrent( iEglDisplay, iEglSurface, iEglSurface, iEglContext );

	iTextureManager = CTextureManager::NewL ( iScreenWidth, iScreenHeight,
	                                              FRUSTUM_TOP, FRUSTUM_BOTTOM, FRUSTUM_RIGHT, FRUSTUM_LEFT, FRUSTUM_NEAR,
	                                              this );
	iTextureManager->SetScreenSize( iScreenWidth, iScreenHeight );
	
	}

static const GLbyte vertices3_[3 * 3] =
{
           -1, -1, 0,
            1, -1, 0,
            0,  2, 0
};


static const GLubyte indices[1 * 3] =
{
           0, 1, 2
};

//void CLT3DEngine::SetRedererState()
//	{
//	/* Set the screen background color to black */
//	glClearColor( 0.f, 0.f, 0.f, 1.f );	 
//
//	/* Initialize viewport */
//	glViewport( 0, 0, iScreenWidth, iScreenHeight );	 
//
//	/* Set the projection matrix */
//	glMatrixMode( GL_PROJECTION );
//	glFrustumf( -1.f, 1.f, -1.f, 1.f, 3.f, 1000.f );
//	glMatrixMode( GL_MODELVIEW );	 
//
//	/* Enable vertex array */
//	glEnableClientState( GL_VERTEX_ARRAY );	 
//
//	/* Set vertex array pointer */
//	glVertexPointer( 3, GL_BYTE, 9, vertices );
//
//	/* Set the shading model */
//	glShadeModel( GL_FLAT );	
//	}
//
//void CLT3DEngine::Render()
//	{
//	/* Clear the color buffer */
//	glClear( GL_COLOR_BUFFER_BIT );	 
//
//	/* Move the camera, MatrixMode == GL_MODELVIEW */
//	glLoadIdentity();
//	glTranslatex( 0, 0, -100 << 16 ); // or glTranslatef( 0.0, 0.0, -100.0 ) 	 
//
//	/* Set current color for the triangle (red) */
//	glColor4f( 1.f, 0.f, 0.f, 1.f );	 
//
//	/* Scale the geometry */
//	glScalex( 15 << 16, 15 << 16, 15 << 16 ); // or glScalef( 15.0, 15.0, 15.0 )	 
//
//	/* Draw the triangle */
//	glDrawElements( GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, indices );	
//	
//	eglSwapBuffers( iEglDisplay, iEglSurface );
//
//	}

/** Vertice coordinates for the cube. */
//static const GLbyte vertices[8 * 3] =
//     {
//     -1,  1,  1,
//      1,  1,  1,
//      1, -1,  1,
//     -1, -1,  1,
//
//     -1,  1, -1,
//      1,  1, -1,
//      1, -1, -1,
//     -1, -1, -1
//     };
static const GLbyte vertices[24 * 3] =
{
    /* top */
    -1,  1,  1,
    1,  1,  1,
    1, -1,  1,
    -1, -1,  1,

    /* front */
    1,  1,  1,
    1,  1, -1,
    1, -1, -1,
    1, -1,  1,

    /* right */
    -1,  1,  1,
    -1,  1, -1,
    1,  1, -1,
    1,  1,  1,

    /* left */
    1, -1,  1,
    1, -1, -1,
    -1, -1, -1,
    -1, -1,  1,

    /* back */
    -1, -1,  1,
    -1, -1, -1,
    -1,  1, -1,
    -1,  1,  1,

    /* bottom */
    -1,  1, -1,
    1,  1, -1,
    1, -1, -1,
    -1, -1, -1
};

/** Colors for vertices (Red, Green, Blue, Alpha). */
static const GLubyte colors[6 * 4] =
    {
    0  ,255,  0,255,
    0  ,  0,255,255,
    0  ,255,  0,255,
    255,  0,  0,255,

    0  ,  0,255,255,
    255,  0,  0,255,
//    0  ,  0,255,255,
//    0  ,255,  0,255
    };


/**
 * Indices for drawing the triangles.
 * The color of the triangle is determined by
 * the color of the last vertex of the triangle.
 */
static const GLubyte triangles[12 * 3] =
    {
    /* front */
    1,0,3,
    1,3,2,

    /* right */
    2,6,5,
    2,5,1,

    /* back */
    7,4,5,
    7,5,6,

    /* left */
    0,4,7,
    0,7,3,

    /* top */
    5,4,0,
    5,0,1,

    /* bottom */
    3,7,6,
    3,6,2
    };

static const GLbyte vertices3[6 * 3] =
     {
     1,  0,  1,
     0,  1,  1,
     -1, 0,  1,
   
     1,  0,  -1,
     0,  1,  -1,
     -1, 0,  -1,
     };

static const GLubyte triangles3[8 * 3] =
    {
    /* front */
    0,1,2,

    /* right */    
    1,3,4,
    1,0,3,

    /* back */    
    4,3,5,

    /* left */
    1,4,5,
    1,5,2,

    /* bottom */
    0,2,5,
    0,5,3,
    };

static const GLbyte nokTexCoords3[24 * 2] =
{
    /* top, whole texture nasa_hubble.h */
    tex(0,0),
    tex(255,0),
    tex(255,255),
    tex(0,255),

    /* front, spiral with tail */
    tex(0,255),
    tex(127,255),
    tex(127,127),
    tex(0,127),

    /* right, red nebulae */
    tex(127,255),
    tex(255,255),
    tex(255,127),
    tex(127,127),

    /* left, plasma cloud */
    tex(0,127),
    tex(127,127),
    tex(127,0),
    tex(0,0),

    /* back, 2 spirals */
    tex(127,127),
    tex(255,127),
    tex(255,0),
    tex(127,0),

    /* bottom, whole texture ogles.jpg */
    tex(255,255),
    tex(255,0),
    tex(0,0),
    tex(0,255)
};

static const GLubyte triangles2[2 * 3] =
{
    /* bottom */
    21,22,23,
    21,23,20
};



/* Input texture coordinates for each of the object vertices.
   The coordinates are given in GLbyte [-128,127] format.
   Since the texture picture coordinates are between values
   [0,255] for both width and height, we have defined a macro
   to change the input coordinates into a appropriate form.
   It is easier to think the texture coordinates as corresponding
   image pixel coordinates. This alone is not enough because
   if texture coordinates are not given between values [0,1],
   texture wrapping will occur. Therefore we need to
   scale the texture coordinates with appropriate texture matrix,
   which is defined in AppInit(). */
static const GLbyte nokTexCoords[24 * 2] =
{
    /* top, whole texture nasa_hubble.h */
    tex(0,0),
    tex(255,0),
    tex(255,255),
    tex(0,255),

    /* front, spiral with tail */
    tex(0,255),
    tex(127,255),
    tex(127,127),
    tex(0,127),

    /* right, red nebulae */
    tex(127,255),
    tex(255,255),
    tex(255,127),
    tex(127,127),

    /* left, plasma cloud */
    tex(0,127),
    tex(127,127),
    tex(127,0),
    tex(0,0),

    /* back, 2 spirals */
    tex(127,127),
    tex(255,127),
    tex(255,0),
    tex(127,0),

    /* bottom, whole texture ogles.jpg */
    tex(255,255),
    tex(255,0),
    tex(0,0),
    tex(0,255)
};

/* Define normals for the cube */
static const GLbyte normals[24 * 3] =
{
    /* top */
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,

    /* front */
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,

    /* right */
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,

    /* left */
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,-1,0,

    /* back */
    -1,0,0,
    -1,0,0,
    -1,0,0,
    -1,0,0,

    /* bottom */
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,-1
};
void CLT3DEngine::SetRedererState()
	{
    // Reinitialize viewport and projection.
    glViewport( 0, 0, iScreenWidth, iScreenHeight );

    // Recalculate the view frustrum
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    GLfloat aspectRatio = (GLfloat)(iScreenWidth) / (GLfloat)(iScreenHeight);
    glFrustumf( FRUSTUM_LEFT * aspectRatio, FRUSTUM_RIGHT * aspectRatio,
                FRUSTUM_BOTTOM, FRUSTUM_TOP,
                FRUSTUM_NEAR, FRUSTUM_FAR );
    glMatrixMode( GL_MODELVIEW );
    
    // Set the screen background color.
     glClearColor( 0.f, 0.f, 0.f, 1.f );

     // Enable back face culling.
     glEnable( GL_CULL_FACE  );     
     glEnable( GL_TEXTURE_2D );
//     glEnable( GL_NORMALIZE  );
     
     glMatrixMode( GL_TEXTURE );
     glLoadIdentity();
     glScalef(     1.0f/255.0f, 1.0f/255.0f, 1.0f );
     glTranslatef( 128.0f,      128.0f,      0.0f );
     
     glMatrixMode( GL_MODELVIEW );

     // Enable vertex arrays.
     glEnableClientState( GL_VERTEX_ARRAY );
     glEnableClientState( GL_TEXTURE_COORD_ARRAY );
//     glEnableClientState( GL_NORMAL_ARRAY        );

     // Set array pointers.
     glVertexPointer( 3, GL_BYTE, 0, vertices3 );
//     glVertexPointer(   3, GL_BYTE, 0, vertices     );
     glTexCoordPointer( 2, GL_BYTE, 0, nokTexCoords );
//     glNormalPointer(   GL_BYTE, 0, normals         );

     // Enable color arrays.
//     glEnableClientState( GL_COLOR_ARRAY );

     // Set color pointers.
//     glColorPointer( 4, GL_UNSIGNED_BYTE, 0, colors );

     // Set the initial shading mode
     glShadeModel( GL_FLAT );

     glBlendFunc( GL_ONE, GL_ONE );
     
     // Do not use perspective correction
     glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
     
     _LIT(KOGLESTexture,  "ogles.jpg");
     iTextureManager->RequestToLoad(KOGLESTexture,  &iOpenGLES );
     iTextureManager->DoLoadL();
	}
void CLT3DEngine::Render()
	{
	TInt aFrame = 0;
//	   const GLint cameraDistance = 100;

	    glClear( GL_COLOR_BUFFER_BIT );

	    /* Animate and draw box */
	    glLoadIdentity();
	    glTranslatex( 0 , 0 , iCameraDistance << 16 );
//	    glTranslatex( 0 , 0 , -cameraDistance << 16 );
	    glRotatex( iRotate << 16, 1 << 16,    0   ,    0    );
//	    glRotatex( iCameraDistance << 15,    0   , 1 << 16,    0    );
//	    glRotatex( iCameraDistance << 14,    0   ,    0   , 1 << 16 );
//	    
//	    glScalef( 15.f, 15.f, 15.f  );
	    
//	    glDrawElements( GL_TRIANGLES, 8 * 3, GL_UNSIGNED_BYTE, triangles3 );
//	    glDrawElements( GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, indices );	
//	    glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
//	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glDrawElements( GL_TRIANGLES, 8 * 3, GL_UNSIGNED_BYTE, triangles3 );
//	    glDrawElements( GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, triangles2 );
	    
	    eglSwapBuffers( iEglDisplay, iEglSurface );

	}

//void CLT3DEngine::SetRedererState()
//	{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	}
//void CLT3DEngine::Render()
//	{
//	glDrawElements( GL_POINTS, 12 * 3, GL_UNSIGNED_BYTE, 0 );
//	}

//void CLT3DEngine::SetRedererState()
//void CLT3DEngine::Render()

TKeyResponse CLT3DEngine::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{}

void CLT3DEngine::OnStartLoadingTexturesL()
	{
    SetStateL( ELoadingTextures );
	}

void CLT3DEngine::OnEndLoadingTexturesL()
	{
	if ( GetState() == ELoadingTextures )
		{
		SetStateL( ERunning );
		}
	}
