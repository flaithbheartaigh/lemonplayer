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

CLT3DEngine::CLT3DEngine(CCoeControl* aParentControl, RWindow* aParentWindow) :
	iParentControl(aParentControl), iParentWindow(aParentWindow), 
			iShowIndex(0),iIsActive(EFalse)
	{
	for (TInt i=0; i<7; i++)
		{
		iRotate[i] = 0;
		iShow[i] = ETrue;
		iTranslate[i][0] = 0;
		iTranslate[i][1] = 0;
		}
	iCameraDistance = -18;
	iScreenWidth = aParentControl->Rect().Width();
	iScreenHeight = aParentControl->Rect().Height();
	// No implementation required
	}

CLT3DEngine::~CLT3DEngine()
	{
	delete iTextureManager;

	eglMakeCurrent(iEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
	eglDestroySurface(iEglDisplay, iEglSurface);
	eglDestroyContext(iEglDisplay, iEglContext);
	eglTerminate(iEglDisplay); // release resources associated with EGL & OpenGL ES
	}

CLT3DEngine* CLT3DEngine::NewLC(CCoeControl* aParentControl,
		RWindow* aParentWindow)
	{
	CLT3DEngine* self = new (ELeave) CLT3DEngine(aParentControl, aParentWindow);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLT3DEngine* CLT3DEngine::NewL(CCoeControl* aParentControl,
		RWindow* aParentWindow)
	{
	CLT3DEngine* self = CLT3DEngine::NewLC(aParentControl, aParentWindow);
	CleanupStack::Pop(); // self;
	return self;
	}

void CLT3DEngine::ConstructL()
	{
	EGLConfig config; // config describing properties of EGLSurface
	EGLConfig *configList = NULL; // pointer for EGLConfigs
	int configSize = 0; // num of configs we want EGL to return
	int numOfConfigs = 0; // num of configs actually returned

	/* Get the display for drawing graphics */
	iEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	/* Initialize display */
	eglInitialize(iEglDisplay, NULL, NULL );

	/* Get the number of all possible EGLConfigs */
	eglGetConfigs(iEglDisplay, configList, configSize, &numOfConfigs);
	configSize = numOfConfigs;

	/* Allocate memory for configList */
	configList = (EGLConfig*) User::Alloc(sizeof(EGLConfig) * configSize);

	/* Define properties for the wanted EGLSurface.
	 To get the best possible performance, choose
	 an EGLConfig with a buffersize matching
	 the current window's display mode*/
	TDisplayMode DMode = iParentWindow->DisplayMode();
	TInt BufferSize = 0;

	switch (DMode)
		{
		case (EColor4K):
			BufferSize = 12;
			break;
		case (EColor64K):
			BufferSize = 16;
			break;
		case (EColor16M):
			BufferSize = 24;
			break;
		case (EColor16MU):
			BufferSize = 32;
			break;
		default:
			_LIT(KDModeError, "unsupported displaymode");
			User::Panic(KDModeError, 0);
			break;
		}

	const EGLint attrib_list[] =
		{
		EGL_BUFFER_SIZE, BufferSize, EGL_DEPTH_SIZE, 16, EGL_NONE
	};

	/* Choose those configs that fulfill the requirement in attrib_list */
	eglChooseConfig(iEglDisplay, attrib_list, configList, configSize,
			&numOfConfigs);

	/* Choose the ¡®best¡¯ config and use that in the future */
	config = configList[0]; // Choose the best EGLConfig. EGLConfigs
	// returned by eglChooseConfig are sorted so
	// that the best matching EGLconfig is first in
	// the list.	 

	User::Free(configList); // free configList, not used anymore

	/* Create a surface where the graphics are blitted */
	iEglSurface = eglCreateWindowSurface(iEglDisplay, config, iParentWindow,
			NULL );

	/* Create a rendering context */
	iEglContext = eglCreateContext(iEglDisplay, config, NULL, NULL );

	/* Make the context current. Binds to the current rendering thread and surface. Use the same surface for both drawing and reading */
	eglMakeCurrent(iEglDisplay, iEglSurface, iEglSurface, iEglContext);

	iTextureManager = CTextureManager::NewL(iScreenWidth, iScreenHeight,
			FRUSTUM_TOP, FRUSTUM_BOTTOM, FRUSTUM_RIGHT, FRUSTUM_LEFT,
			FRUSTUM_NEAR, this);
	iTextureManager->SetScreenSize(iScreenWidth, iScreenHeight);

	}

static const GLbyte verticesTangram[10 * 3] =
	{
			-4,			4,			1,
			4,			4,			1,
			2,			2,			1,
			0,			0,			1,
			4,			0,			1,
			-2,			-2,			1,
			2,			-2,			1,
			-4,			-4,			1,
			0,			-4,			1,
			4,			-4,			1,

	};

static const GLubyte STTtriangleBig1[1 * 3] =
	{
	1, 0, 3,
	};

static const GLubyte STTtriangleBig2[1 * 3] =
	{
	0, 7, 3,
	};

static const GLubyte STTtriangleSmall1[1 * 3] =
	{
	2, 3, 6,
	};

static const GLubyte STTtriangleSmall2[1 * 3] =
	{
	5, 7, 8,
	};

static const GLubyte STTtriangleMid[1 * 3] =
	{
	4, 8, 9,
	};

static const GLubyte STSquare[2 * 3] =
	{
	3, 5, 8, 3, 8, 6,
	};

static const GLubyte STRect[2 * 3] =
	{
	1, 2, 6, 1, 6, 4,
	};

static const GLubyte STActiveRect[2 * 3] =
	{
	1, 0, 7, 1, 7, 9,
	};

static const GLint centerTangram[7][2] = 
{
		{0,2},{-2,0},{1,0},
		{-2,-3},{3,-3},{0,-2},{3,1}		
};

/** Colors for vertices (Red, Green, Blue, Alpha). */
static const GLubyte colors[6 * 4] =
	{
	0, 255, 0, 255, 0, 0, 255, 255, 0, 255, 0, 255, 255, 0, 0, 255,

	0, 0, 255, 255, 255, 0, 0, 255,
	//    0  ,  0,255,255,
		//    0  ,255,  0,255
		};

static const GLbyte nokTexCoordsTangram[10 * 2] =
	{
	tex(0,0),
    tex(255,0),  
    tex(191,63),  
    tex(127,127),  

    tex(255,127),  
    tex(63,191),  
    tex(191,191),  

    tex(0,255),  
    tex(127,255),
    tex(255,255)
    
	};

/* Define normals for the cube */
static const GLbyte normals[24 * 3] =
	{
	/* top */
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,

	/* front */
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,

	/* right */
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,

	/* left */
	0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0,

	/* back */
	-1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0,

	/* bottom */
	0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1
	};
#define MATERIAL_MAX 1
#define LIGHT_MAX    1

#define MATERIALCOLOR(r, g, b, a)     \
       (GLfloat)(r * MATERIAL_MAX),   \
       (GLfloat)(g * MATERIAL_MAX),   \
       (GLfloat)(b * MATERIAL_MAX),   \
       (GLfloat)(a * MATERIAL_MAX)

#define LIGHTCOLOR(r, g, b, a)        \
       (GLfloat)(r * LIGHT_MAX),      \
       (GLfloat)(g * LIGHT_MAX),      \
       (GLfloat)(b * LIGHT_MAX),      \
       (GLfloat)(a * LIGHT_MAX)

/** Materials for the duck object. */
static const GLfloat objDiffuseDuck[4]  = { MATERIALCOLOR(0.8, 0.8, 0.2, 1.0) };
static const GLfloat objAmbientDuck[4]  = { MATERIALCOLOR(0.8, 0.8, 0.2, 1.0) };
static const GLfloat objSpecularDuck[4] = { MATERIALCOLOR(1.0, 1.0, 1.0, 1.0) };
static const GLfloat objEmissionDuck[4] = { MATERIALCOLOR(0.0, 0.0, 0.0, 1.0) };

/* Global ambient light. */
//static const GLfloat globalAmbient[4]   = { LIGHTCOLOR(0.0, 0.0, 0.0, 1.0) };
static const GLfloat globalAmbient[4]   = { LIGHTCOLOR(0.0, 0.0, 0.0, 1.0) };

/* Lamp parameters. */
static const GLfloat lightDiffuseLamp[4]   = { LIGHTCOLOR(0.7, 0.7, 0.7, 1.0) };
static const GLfloat lightAmbientLamp[4]   = { LIGHTCOLOR(0.3, 0.3, 0.3, 1.0) };
//static const GLfloat lightAmbientLamp[4]   = { LIGHTCOLOR(0.0, 0.0, 0.0, 1.0) };
static const GLfloat lightPositionLamp[4]  = { 0, 10, 10, 0 };
//static const GLfloat lightPositionLamp[4]  = { 0, 0, 10, 0 };

//static const GLfloat lightDiffuseLamp[4]   = { LIGHTCOLOR(1.0, 1.0, 1.0, 1.0) };
//static const GLfloat lightAmbientLamp[4]   = { LIGHTCOLOR(1.0, 1.0, 1.0, 1.0) };
//static const GLfloat lightPositionLamp[4]  = { 0, 10, 10, 0 };

/* Spotlight parameters. */
static const GLfloat lightDiffuseSpot[4]   = { LIGHTCOLOR(0.0, 0.0, 0.0, 1.0) };
static const GLfloat lightAmbientSpot[4]   = { LIGHTCOLOR(0.0, 0.0, 0.0, 1.0) };
static const GLfloat lightSpecularSpot[4]  = { LIGHTCOLOR(0.0, 0.0, 3.0, 1.0) };
static const GLfloat lightPositionSpot[4]  = {  0, -10, -1, 0 };
static const GLfloat lightDirectionSpot[4] = {  0,  10,  1, 1 };

static const GLint offsetTangram[7][2] = { {0,2},{-2,0},{1,0},{-2,-3},{3,-3},{0,-2},{3,1},};

void CLT3DEngine::SetRedererState()
	{
	// Reinitialize viewport and projection.
	glViewport(0, 0, iScreenWidth, iScreenHeight);

	// Recalculate the view frustrum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspectRatio = (GLfloat) (iScreenWidth) / (GLfloat) (iScreenHeight);
	glFrustumf(FRUSTUM_LEFT * aspectRatio, FRUSTUM_RIGHT * aspectRatio,
			FRUSTUM_BOTTOM, FRUSTUM_TOP,
			FRUSTUM_NEAR, FRUSTUM_FAR );
	glMatrixMode(GL_MODELVIEW);

	// Set the screen background color.
	glClearColor(0.f, 0.f, 0.f, 1.f);

	// Enable back face culling.
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable( GL_LIGHTING   );
	//     glEnable( GL_NORMALIZE  );

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(1.0f / 255.0f, 1.0f / 255.0f, 1.0f);
	glTranslatef(128.0f, 128.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);

	// Enable vertex arrays.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//     glEnableClientState( GL_NORMAL_ARRAY        );

    // Set up global ambient light.
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, globalAmbient );

    // Set up lamp.
    glEnable( GL_LIGHT0 );
    glLightfv(  GL_LIGHT0, GL_DIFFUSE,  lightDiffuseLamp  );
    glLightfv(  GL_LIGHT0, GL_AMBIENT,  lightAmbientLamp  );
    glLightfv(  GL_LIGHT0, GL_SPECULAR, lightDiffuseLamp  );
    glLightfv(  GL_LIGHT0, GL_POSITION, lightPositionLamp );

    // Set up spot.  Initially spot is disabled.
//    glLightfv(  GL_LIGHT1, GL_DIFFUSE,  lightDiffuseSpot  );
//    glLightfv(  GL_LIGHT1, GL_AMBIENT,  lightAmbientSpot  );
//    glLightfv(  GL_LIGHT1, GL_SPECULAR, lightSpecularSpot );
//    glLightfv(  GL_LIGHT1, GL_POSITION, lightPositionSpot );
//	
//    glLightf(   GL_LIGHT1, GL_CONSTANT_ATTENUATION,  1.5  );
//    glLightf(   GL_LIGHT1, GL_LINEAR_ATTENUATION,    0.5  );
//    glLightf(   GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.5  );
//
//    glLightf(   GL_LIGHT1, GL_SPOT_CUTOFF,   17.0                );
//    glLightf(   GL_LIGHT1, GL_SPOT_EXPONENT,  2.0                );
//    glLightfv(  GL_LIGHT1, GL_SPOT_DIRECTION, lightDirectionSpot );
    
    // Set duck material
//    glMaterialfv(   GL_FRONT_AND_BACK, GL_DIFFUSE,  objDiffuseDuck      );
//    glMaterialfv(   GL_FRONT_AND_BACK, GL_AMBIENT,  objAmbientDuck      );
//    glMaterialfv(   GL_FRONT_AND_BACK, GL_SPECULAR, objSpecularDuck     );
//    glMaterialfv(   GL_FRONT_AND_BACK, GL_EMISSION, objEmissionDuck     );
//    glMaterialx( GL_FRONT_AND_BACK, GL_SHININESS,   10 << 16         );
	    
	// Set array pointers.
	glVertexPointer(3, GL_BYTE, 0, verticesTangram);
	glTexCoordPointer(2, GL_BYTE, 0, nokTexCoordsTangram);
	//     glNormalPointer(   GL_BYTE, 0, normals         );

	// Enable color arrays.
	//     glEnableClientState( GL_COLOR_ARRAY );

	// Set color pointers.
	//     glColorPointer( 4, GL_UNSIGNED_BYTE, 0, colors );

	// Set the initial shading mode
//	glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	glBlendFunc(GL_ONE, GL_ONE );

    iLightingEnabled = ETrue;          // Lighting is enabled
    iLampEnabled     = ETrue;          // Lamp is enabled
    iSpotEnabled     = EFalse;         // Spot is disabled
    
	// Do not use perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
	_LIT(KOGLESTexture, "ogles.jpg");
	iTextureManager->RequestToLoad(KOGLESTexture, &iOpenGLES);
	_LIT(KStar, "Star.bmp");
	iTextureManager->RequestToLoad(KStar, &iStar);
	iTextureManager->DoLoadL();
	}

void CLT3DEngine::Render()
	{
	TInt aFrame = 0;
	//	   const GLint cameraDistance = 100;

	GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

	glClear(GL_COLOR_BUFFER_BIT);

	/* Animate and draw box */
//	glLoadIdentity();
//	glTranslatex(0, 0, iCameraDistance << 16);
	//	    glTranslatex( 0 , 0 , -cameraDistance << 16 );
	//	glRotatex(0, iRotate << 16, 0, 0);
	//	    glRotatex( iCameraDistance << 15,    0   , 1 << 16,    0    );
	//	    glRotatex( iCameraDistance << 14,    0   ,    0   , 1 << 16 );
	//	    
	//	    glScalef( 15.f, 15.f, 15.f  );

	//	    glDrawElements( GL_TRIANGLES, 8 * 3, GL_UNSIGNED_BYTE, triangles3 );
	//	    glDrawElements( GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, indices );	
	//	    glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
	//	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	//	    glDrawElements( GL_TRIANGLES, 8 * 3, GL_UNSIGNED_BYTE, triangles3 );
	//	    glDrawElements( GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, triangles2 );

	//	glTranslatex(0.f, 1.f, 0.f);
	if (ETrue)
		{
		glPushMatrix();
		glTranslatex(0, 0, iCameraDistance << 16);
//		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
//		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
//		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		
		glTranslatex(iTranslate[0][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[0][1] << 16, 0);
		
		glTranslatex(0, 2<<16, 0);
		glRotatex(iRotate[0] << 16, 0, 0, 1 << 16);
		glTranslatex(0, -2<<16, 0);
		//		glRotatex(0,iRotate<<16,0,0);
		//		glRotatex(0,0,iRotate<<16,0);

		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleBig1);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
		glTranslatex(0, 0, iCameraDistance << 16);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

				
		glTranslatex(iTranslate[1][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[1][1] << 16, 0);
		
		glTranslatex(-2<<16, 0, 0);
		glRotatex(iRotate[1] << 16, 0, 0, 1 << 16);
		glTranslatex(2<<16, 0, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleBig2);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
		glTranslatex(0, 0, iCameraDistance << 16);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

				
		glTranslatex(iTranslate[2][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[2][1] << 16, 0);
		
		glTranslatex(1<<16, 0, 0);
		glRotatex(iRotate[2] << 16, 0, 0, 1 << 16);
		glTranslatex(-1<<16, 0, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleSmall1);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
				glTranslatex(0, 0, iCameraDistance << 16);
				glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
				glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

				
		glTranslatex(iTranslate[3][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[3][1] << 16, 0);
		
		glTranslatex(-2<<16, -3<<16, 0);
		glRotatex(iRotate[3] << 16, 0, 0, 1 << 16);
		glTranslatex(2<<16, 3<<16, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleSmall2);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
				glTranslatex(0, 0, iCameraDistance << 16);
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
				glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

				
		glTranslatex(iTranslate[4][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[4][1] << 16, 0);
		
		glTranslatex(3<<16, -3<<16, 0);
		glRotatex(iRotate[4] << 16, 0, 0, 1 << 16);
		glTranslatex(-3<<16, 3<<16, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleMid);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
				glTranslatex(0, 0, iCameraDistance << 16);
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

		glTranslatex(iTranslate[5][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[5][1] << 16, 0);
		
		glTranslatex(0, -2<<16, 0);
		glRotatex(iRotate[5] << 16, 0, 0, 1 << 16);
		glTranslatex(0, 2<<16, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, STSquare);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
				glTranslatex(0, 0, iCameraDistance << 16);
//				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//				glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
//				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

				
		glTranslatex(iTranslate[6][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[6][1] << 16, 0);
		
		glTranslatex(3<<16, 1<<16, 0);
		glRotatex(iRotate[6] << 16, 0, 0, 1 << 16);
		glTranslatex(-3<<16, -1<<16, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, STRect);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
		glTranslatex(0, 0, iCameraDistance*16 << 16);
		//glTranslatex(0, 0, iCameraDistance << 16);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	
		//glTranslatex(iTranslateX << 16, 0, 0);
		//glTranslatex(0, iTranslateY << 16, 0);
		
		glTranslatex((centerTangram[iShowIndex][0]+iTranslate[iShowIndex][0])*16 << 16, 
				(centerTangram[iShowIndex][1]+iTranslate[iShowIndex][1])*16<<16, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iStar.iID );
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, STActiveRect);
		
		glPopMatrix();
		}
	
	eglSwapBuffers(iEglDisplay, iEglSurface);

	}

TKeyResponse CLT3DEngine::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
		TEventCode /*aType*/)
	{
	return EKeyWasNotConsumed;
	}

void CLT3DEngine::OnStartLoadingTexturesL()
	{
	SetStateL(ELoadingTextures);
	}

void CLT3DEngine::OnEndLoadingTexturesL()
	{
	if (GetState() == ELoadingTextures)
		{
		SetStateL(ERunning);
		}
	}

void CLT3DEngine::Up()
	{
	if (iIsActive)
		{
		iTranslate[iShowIndex][1]--;
		}
	else
		{
		Left();
		}
	}
void CLT3DEngine::Down()
	{
	if (iIsActive)
		{
		iTranslate[iShowIndex][1]++;
		}
	else
		{
		Right();
		}
	}

void CLT3DEngine::Left()
	{
	if (iIsActive)
		{
		iTranslate[iShowIndex][0]--;
		}
	else
		{
		if (--iShowIndex < 0)
			iShowIndex = 6;
		}
	}

void CLT3DEngine::Right()
	{
	if (iIsActive)
		{
		iTranslate[iShowIndex][0]++;
		}
	else
		{
		if (++iShowIndex > 6)
			iShowIndex = 0;
		}
	}

void CLT3DEngine::Change()
	{
	iIsActive = !iIsActive;
	}

void CLT3DEngine::RotateClockwise()
	{
	if (iIsActive)
		{
		iRotate[iShowIndex] += 5;
		}
	}
void CLT3DEngine::RotateAnticlockwise()
	{
	if (iIsActive)
		{
		iRotate[iShowIndex] -= 5;
		}
	}

void CLT3DEngine::ToggleLighting( void )
    {
    if ( iLightingEnabled)
        {
        iLightingEnabled = EFalse;
        glDisable( GL_LIGHTING );
        }
    else
        {
        iLightingEnabled = ETrue;
        glEnable( GL_LIGHTING );
        }
    }


// -----------------------------------------------------------------------------
// CSimpleLight::ToggleLamp
// Enable/Disable lamp from the application menu.
// -----------------------------------------------------------------------------
//
void CLT3DEngine::ToggleLamp( void )
    {
    if ( iLampEnabled )
        {
        iLampEnabled = EFalse;
        glDisable( GL_LIGHT0 );
        }
    else
        {
        iLampEnabled = ETrue;
        glEnable( GL_LIGHT0 );
        }
    }


// -----------------------------------------------------------------------------
// CSimpleLight::ToggleSpot
// Enable/Disable spot from the application menu.
// -----------------------------------------------------------------------------
//
void CLT3DEngine::ToggleSpot( void )
    {
    if ( iSpotEnabled )
        {
        iSpotEnabled = EFalse;
        glDisable( GL_LIGHT1 );
        }
    else
        {
        iSpotEnabled = ETrue;
        glEnable( GL_LIGHT1 );
        }
    /*
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX,winY,winZ;
    GLdouble object_x,object_y,object_z;
    int mouse_x,mouse_y;
    char str[80];
    
    glInitNames();
    
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    	            glGetDoublev(GL_PROJECTION_MATRIX, projection);
    	            glGetIntegerv(GL_VIEWPORT, viewport);
    				winX=(float)mouse_x;
    				winY=(float)viewport[3]-(float)mouse_y;
    				//glReadBuffer(GL_BACK);
    				glReadPixels(mouse_x,int(winY),1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winZ);
    				gluUnProject((GLdouble)winX,(GLdouble)winY,(GLdouble)winZ,modelview,projection,viewport,&object_x,&object_y,&object_z);
    				*/
    }
