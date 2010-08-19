/*
 * ==============================================================================
 *  Name        : Slideshow.cpp
 *  Part of     : OpenGLEx / Slideshow
 *
 *  Copyright (c) 2005-2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

// INCLUDE FILES

#include <aknnotewrappers.h>
#include <e32math.h>
#include "slideshow.h"
#include "ImageElement.h"

// MACROS
#define FRUSTUM_LEFT   -1.f     //left vertical clipping plane
#define FRUSTUM_RIGHT   1.f     //right vertical clipping plane
#define FRUSTUM_BOTTOM -1.f     //bottom horizontal clipping plane
#define FRUSTUM_TOP     1.f     //top horizontal clipping plane
#define FRUSTUM_NEAR    3.f     //near depth clipping plane
#define FRUSTUM_FAR  1000.f     //far depth clipping plane
#define tex(u,v) (GLbyte)( (u) - 128 ) , (GLbyte)( (v) - 128 )

#define	MAX_PARTICLES	10				// ��������������
bool rainbow = true; // �Ƿ�Ϊ�ʺ�ģʽ
bool sp; // �ո���Ƿ񱻰���
bool rp; // �س����Ƿ񱻰���
float slowdown = 2.0f; // ��������
float xspeed; // X������ٶ�
float yspeed; // Y������ٶ�
float zoom = -40.0f; // ��Z������
GLuint loop; // ѭ������
GLuint col; // ��ǰ����ɫ
GLuint delay; // �ʺ�Ч���ӳ�
typedef struct // �����������ݽṹ
	{
	bool active; // �Ƿ񼤻�
	float life; // ��������
	float fade; // ˥���ٶ�
	float r; // ��ɫֵ
	float g; // ��ɫֵ
	float b; // ��ɫֵ
	float x; // X λ��
	float y; // Y λ��
	float xi; // X ����
	float yi; // Y ����

	float xg; // X �����������ٶ�
	float yg; // Y �����������ٶ�
	} particles; // �������ݽṹ
particles particle[MAX_PARTICLES]; // ����1000�����ӵ�����

/** Vertice coordinates for the cube. */
static const GLbyte vertices[4 * 3] =
	{
	/* top */
//	-1, 1, 1, 1, 1, 1, 1, -1, 1, -1, -1, 1
	-5, 5, 1, 5, 5, 1, 5, -5, 1, -5, -5, 1
	};

static const GLubyte colorsAlpha[7] = 
{
		200,180,160,140,120,100,80
//		1,2,3,4,5,6,7
};

static const GLubyte colorsBox1[10 * 4] =
    {
    /* top */
    255,	255,   	255, 	colorsAlpha[EShapeTriangleBig1],
    255,   	255,   	255, 	colorsAlpha[EShapeTriangleRect],
    255,   	255,   	255, 	colorsAlpha[EShapeTriangleSmall1],
    255,   	255,   	255, 	colorsAlpha[EShapeTriangleSquare],
    255,   	255,   	255, 	255,
    255,   	255,   	255, 	colorsAlpha[EShapeTriangleSmall2],
    255,   	255,   	255, 	255,
    255,   	255,   	255, 	colorsAlpha[EShapeTriangleBig2],
    255,   	255,   	255, 	255,
    255,   	255,   	255, 	colorsAlpha[EShapeTriangleMid]
    };

/** Colors for vertices (Red, Green, Blue, Alpha). */
static GLfloat colors[12][3] = // �ʺ���ɫ
			{
				{
				1.0f, 0.5f, 0.5f
				},
				{
				1.0f, 0.75f, 0.5f
				},
				{
				1.0f, 1.0f, 0.5f
				},
				{
				0.75f, 1.0f, 0.5f
				},
				{
				0.5f, 1.0f, 0.5f
				},
				{
				0.5f, 1.0f, 0.75f
				},
				{
				0.5f, 1.0f, 1.0f
				},
				{
				0.5f, 0.75f, 1.0f
				},
				{
				0.5f, 0.5f, 1.0f
				},
				{
				0.75f, 0.5f, 1.0f
				},
				{
				1.0f, 0.5f, 1.0f
				},
				{
				1.0f, 0.5f, 0.75f
				}
			};

/**
 * Indices for drawing the triangles.
 * The color of the triangle is determined by
 * the color of the last vertex of the triangle.
 */
static const GLubyte triangles[2 * 3] =
	{
	/* front */
	1, 0, 3, 1, 3, 2
	};

static const GLbyte nokTexCoords[4 * 2] =
	{
	/* top, whole texture nasa_hubble.h */
	tex(0,0),
    tex(255,0), 
    tex(255,255), 
    tex(0,255), 
	};

//static const GLbyte verticesTangram[10 * 3] =
//	{
//			-4,			4,			
//			4,			4,			
//			2,			2,			
//			0,			0,			
//			4,			0,			
//			-2,			-2,			
//			2,			-2,			
//			-4,			-4,			
//			0,			-4,			
//			4,			-4,			
//
//	};

static const GLbyte verticesTangram[10 * 3] =
	{
			-100,		100,			
			100,		100,			
			50,			50,			
			0,			0,			
			100,		0,			
			-50,		-50,			
			50,			-50,			
			-100,		-100,			
			0,			-100,			
			100,		-100,			

	};

static const GLsizei STTtriangleNumber[7] = {3,3,3,3,3,6,6};

static const GLubyte STTtriangle[7][6] =
{
	{
	3, 1, 0,0,0,0
	},


	{
	3, 0, 7,0,0,0
	},


	{
	3, 6, 2,0,0,0
	},


	{
	7, 8, 5,0,0,0
	},


	{
	4, 8, 9,0,0,0
	},


	{
	5, 8, 3, 8, 6, 3,
	},


	{
	 2, 6, 1, 6, 4, 1,
	}
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

//static const GLint offsetTangram[7][2] = { {0,2},{-2,0},{1,0},{-2,-3},{3,-3},{0,-2},{3,1},};
static const GLint offsetTangram[7][2] = { {0,50},{-50,0},{25,0},{-50,-75},{75,-75},{0,-50},{75,25},};
// CONSTANTS

// ============================= MEMBER FUNCTIONS ==============================

// -----------------------------------------------------------------------------
// CSlideshow::NewL
// Symbian 2-phase constructor. Can leave.
// -----------------------------------------------------------------------------
//
CSlideshow* CSlideshow::NewL( TUint aWidth, TUint aHeight )
	{
    // Symbian 2-phase constructor. Calls both the default
    // C++ constructor and Symbian ConstructL methods
    CSlideshow* self = new (ELeave) CSlideshow( aWidth, aHeight );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
	}

// ----------------------------------------------------------------------------
// CSlideshow::CSlideshow
// C++ default constructor can NOT contain any code, that
// might leave.
// ----------------------------------------------------------------------------
//
CSlideshow::CSlideshow( TUint aWidth, TUint aHeight )
	: CFiniteStateMachine(),iImageData(NULL)
	{
    iScreenWidth  = aWidth;
    iScreenHeight = aHeight;
	}

// ----------------------------------------------------------------------------
// CSlideshow::ConstructL
// Symbian 2nd phase constructor can leave.
// ----------------------------------------------------------------------------
//
void CSlideshow::ConstructL( void )
	{
	EGLConfig config; // config describing properties of EGLSurface
	EGLConfig *configList = NULL; // pointer for EGLConfigs
	int configSize = 0; // num of configs we want EGL to return
	int numOfConfigs = 0; // num of configs actually returned

	/* Get the display for drawing graphics */
	iEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	/* Initialize display */
	eglInitialize(iEglDisplay, NULL, NULL);

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

	/* Choose the ��best�� config and use that in the future */
	config = configList[0]; // Choose the best EGLConfig. EGLConfigs
	// returned by eglChooseConfig are sorted so
	// that the best matching EGLconfig is first in
	// the list.	 

	User::Free(configList); // free configList, not used anymore

	/* Create a surface where the graphics are blitted */
	iEglSurface = eglCreateWindowSurface(iEglDisplay, config, iParentWindow,
			NULL);

	/* Create a rendering context */
	iEglContext = eglCreateContext(iEglDisplay, config, NULL, NULL);

	/* Make the context current. Binds to the current rendering thread and surface. Use the same surface for both drawing and reading */
	eglMakeCurrent(iEglDisplay, iEglSurface, iEglSurface, iEglContext);

//	iTextureManager = CTextureManager::NewL(iScreenWidth, iScreenHeight,
//			FRUSTUM_TOP, FRUSTUM_BOTTOM, FRUSTUM_RIGHT, FRUSTUM_LEFT,
//			FRUSTUM_NEAR, this);
//	iTextureManager->SetScreenSize(iScreenWidth, iScreenHeight);
	}

// ----------------------------------------------------------------------------
// CSlideshow::~CSlideshow()
// Destructor.
// ----------------------------------------------------------------------------
//
CSlideshow::~CSlideshow()
	{
	AppExit();
	
	eglMakeCurrent(iEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroySurface(iEglDisplay, iEglSurface);
	eglDestroyContext(iEglDisplay, iEglContext);
	eglTerminate(iEglDisplay); // release resources associated with EGL & OpenGL ES
	}

CSlideshow::CSlideshow(CCoeControl* aParentControl, RWindow* aParentWindow) :CFiniteStateMachine(),
	iParentControl(aParentControl), iParentWindow(aParentWindow),iCameraDistance(-8),iImageData(NULL)
	{
	iScreenWidth = aParentControl->Rect().Width();
	iScreenHeight = aParentControl->Rect().Height();
	// No implementation required
	}

CSlideshow* CSlideshow::NewLC(CCoeControl* aParentControl,
		RWindow* aParentWindow)
	{
	CSlideshow* self = new (ELeave) CSlideshow(aParentControl, aParentWindow);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSlideshow* CSlideshow::NewL(CCoeControl* aParentControl,
		RWindow* aParentWindow)
	{
	CSlideshow* self = CSlideshow::NewLC(aParentControl, aParentWindow);
	CleanupStack::Pop(); // self;
	return self;
	}

// ----------------------------------------------------------------------------
// CSlideshow::AppInit
// Application initialization code.
// ----------------------------------------------------------------------------
//
void CSlideshow::AppInitL( void )
	{
    // Construct a texture manager that uses the application's private
    // directory as the source location for all textures.
    iTextureManager = CTextureManager::NewL ( iScreenWidth, iScreenHeight, 0, 0, 0, 0, 0,
                                              this );
    // Initialize viewport and projection.
	SetScreenSize( iScreenWidth, iScreenHeight );

    // Set the screen background color.
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    // Enable back face culling.
    glDisable( GL_CULL_FACE  );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );

    // Disable lighting
    glDisable( GL_LIGHTING );

    // Initialize viewport and projection.
    glViewport( 0, 0, iScreenWidth, iScreenHeight );
    glMatrixMode( GL_PROJECTION );

    // Set best perspective correction
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Enable vertex arrays.
    glEnableClientState( GL_VERTEX_ARRAY );

    // Enable texture arrays.
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	_LIT(KOGLESTexture, "Particle.jpg");
	_LIT(KOGLESTexture1, "ogles.jpg");
    iTextureManager->RequestToLoad( KOGLESTexture,  &iPictures[0] );
    iTextureManager->RequestToLoad( KOGLESTexture1, &iPictures[1] );
    
//    char* constellation[] = {
//    		"Aquarius.jpg","Aries.jpg","Cancer.jpg","Capricorn.jpg","Gemini.jpg","Leo.jpg",
//    		"Libra.jpg","Pisces.jpg","Sagittarius.jpg","Scorpius.jpg","Taurus.jpg","Virgo.jpg"};
    

    
    _LIT(KConstellation1, "Aries.jpg");
    _LIT(KConstellation2, "Taurus.jpg");
    _LIT(KConstellation3, "Gemini.jpg");
    _LIT(KConstellation4, "Cancer.jpg");
    _LIT(KConstellation5, "Leo.jpg");
    _LIT(KConstellation6, "Virgo.jpg");  
    _LIT(KConstellation7, "Libra.jpg");
    _LIT(KConstellation8, "Scorpius.jpg");    
    _LIT(KConstellation9, "Sagittarius.jpg");
    _LIT(KConstellation10, "Capricorn.jpg");
    _LIT(KConstellation11, "Aquarius.jpg");
    _LIT(KConstellation12, "Pisces.jpg");    
    
    //for(TInt i=0; i<12; i++)
    //	iTextureManager->RequestToLoad( _L(constellation[i]),  &iConstellationPictures[i] );
    iTextureManager->RequestToLoad( KConstellation1,  &iConstellationPictures[0] );
    iTextureManager->RequestToLoad( KConstellation2,  &iConstellationPictures[1] );
    iTextureManager->RequestToLoad( KConstellation3,  &iConstellationPictures[2] );
    iTextureManager->RequestToLoad( KConstellation4,  &iConstellationPictures[3] );
    iTextureManager->RequestToLoad( KConstellation5,  &iConstellationPictures[4] );
    iTextureManager->RequestToLoad( KConstellation6,  &iConstellationPictures[5] );
    iTextureManager->RequestToLoad( KConstellation7,  &iConstellationPictures[6] );
    iTextureManager->RequestToLoad( KConstellation8,  &iConstellationPictures[7] );
    iTextureManager->RequestToLoad( KConstellation9,  &iConstellationPictures[8] );
    iTextureManager->RequestToLoad( KConstellation10,  &iConstellationPictures[9] );
    iTextureManager->RequestToLoad( KConstellation11,  &iConstellationPictures[10] );
    iTextureManager->RequestToLoad( KConstellation12,  &iConstellationPictures[11] );

    // Start to load the queued textures
    iTextureManager->DoLoadL();
	}

// ----------------------------------------------------------------------------
// CSlideshow::AppExit
// Application cleanup code.
// ----------------------------------------------------------------------------
//
void CSlideshow::AppExit( void )
	{
    delete iTextureManager;
	}

// ----------------------------------------------------------------------------
// CSlideshow::OnEnterState( TInt aState )
// Called by TFiniteStateMachine when the f.s.m enters a new state
// ----------------------------------------------------------------------------
//
void CSlideshow::OnEnterStateL( TInt /*aState*/ )
	{
	}

// ----------------------------------------------------------------------------
// CSlideshow::OnStartLoadingTextures()
// Called for a MTextureLoadingListener by the texture manager when texture
// loading operation starts
// ----------------------------------------------------------------------------
//
void CSlideshow::OnStartLoadingTexturesL()
	{
    SetStateL( ELoadingTextures );
	}

// ----------------------------------------------------------------------------
// CSlideshow::OnEndLoadingTextures()
// Called for a MTextureLoadingListener by the texture manager when texture
// loading operation is completed
// ----------------------------------------------------------------------------
void CSlideshow::OnEndLoadingTexturesL()
	{
	if ( GetState() == ELoadingTextures )
		{
        SetStateL( ERunning );
		}
	}

// ----------------------------------------------------------------------------
// CSlideshow::SetScreenSize
// Reacts to the dynamic screen size change during execution of this program.
// ----------------------------------------------------------------------------
//
void CSlideshow::SetScreenSize( TUint aWidth, TUint aHeight )
    {
    iScreenWidth  = aWidth;
    iScreenHeight = aHeight;

    // Notify the texture manager of screen size change
    iTextureManager->SetScreenSize( aWidth, aHeight );

    // Reinitialize viewport and projection.
    glViewport( 0, 0, iScreenWidth, iScreenHeight );
    }

void CSlideshow::SetRedererState()
	{
	AppInitL();
	
	InitConstellation();
	glShadeModel( GL_FLAT );
	
	for (loop = 0; loop < MAX_PARTICLES; loop++) //��ʼ�����е�����
		{
		particle[loop].active = true; // ʹ���е�����Ϊ����״̬
		particle[loop].life = 1.0f; // ���е���������ֵΪ���
		particle[loop].fade = float(Math::Random() % 100) / 1000.0f + 0.003f; // �������˥������
		particle[loop].r = colors[loop * (12 / MAX_PARTICLES)][0]; // ���ӵĺ�ɫ��ɫ
		particle[loop].g = colors[loop * (12 / MAX_PARTICLES)][1]; // ���ӵ���ɫ��ɫ
		particle[loop].b = colors[loop * (12 / MAX_PARTICLES)][2]; // ���ӵ���ɫ��ɫ
		particle[loop].xi = float((Math::Random() % 50) - 25.0f) * 10.0f; // �������X�᷽���ٶ�
		particle[loop].yi = float((Math::Random() % 50) - 25.0f) * 10.0f; // �������Y�᷽���ٶ�
		particle[loop].xg = float(Math::Random() % 50) / 1000.0f; // ����X�᷽����ٶ�Ϊ0
		particle[loop].yg = float(Math::Random() % 50) / 1000.0f; // ����Y�᷽����ٶ�Ϊ-0.8
		}
	}

void CSlideshow::Render()
	{
	glClear(GL_COLOR_BUFFER_BIT);
	
	DrawBackground();
	DrawTangram();
	DrawParticles();
	
	eglSwapBuffers( iEglDisplay, iEglSurface );
	}

void CSlideshow::DrawTangram()
	{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		
	GLint width,height;
	width = iScreenWidth  >> 1;
	height = iScreenHeight >> 1;
	glOrthof((float)-width, (float) width, (float)-height, (float) height, -1, 1); // set the same size as viewport
		

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(1.0f / 255.0f, 1.0f / 255.0f, 1.0f);
	glTranslatef(128.0f, 128.0f, 0.0f);
		
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	    
	glVertexPointer(2, GL_BYTE, 0, verticesTangram);
	glTexCoordPointer(2, GL_BYTE, 0, nokTexCoordsTangram);

	/* Animate and draw box */
	glEnableClientState( GL_COLOR_ARRAY ); // enable color array
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glColorPointer( 4, GL_UNSIGNED_BYTE, 0, colorsBox1 );
	
	if (iImageData)
		{
		RArray<TInt> layer = iImageData->GetLayer();
		for(TInt i=0; i<layer.Count(); i++)
			DrawTangram(layer[i]);	
		}
	}

void CSlideshow::DrawTangram(const TInt& aIndex)
	{
	glPushMatrix();
	
	if (iImageData)
		{
		CImageElement** elements = iImageData->GetElements();
		
		GLint x,y;
		TInt degree = elements[aIndex]->GetDegree();
		
		x = offsetTangram[aIndex][0]+elements[aIndex]->GetPositionX();
		y = offsetTangram[aIndex][1]+elements[aIndex]->GetPositionY();
		
		glTranslatex(x<<16,y<<16,0);
		glRotatex(degree<<16, 0, 0, 1 << 16);
//		glTranslatex(-x<<16,-y<<16,0);
//		
//		x = elements[aIndex]->GetPositionX();
//		y = elements[aIndex]->GetPositionY();
//		glTranslatex(x << 16, y << 16, 0);	
		
				
		x = offsetTangram[aIndex][0];
		y = offsetTangram[aIndex][1];
		glTranslatex(-x << 16, -y << 16, 0);	
		}	

	glBindTexture(  GL_TEXTURE_2D, iPictures[1].iID );		
	glDrawElements(GL_TRIANGLES, STTtriangleNumber[aIndex], GL_UNSIGNED_BYTE, STTtriangle[aIndex]);
	
	glPopMatrix();
	}

void CSlideshow::DrawParticles() // �����￪ʼ�������еĻ���
	{
	// Recalculate the view frustrum
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
//		GLfloat aspectRatio = (GLfloat) (iScreenWidth) / (GLfloat) (iScreenHeight);
//		glFrustumf(FRUSTUM_LEFT * aspectRatio, FRUSTUM_RIGHT * aspectRatio,
//				FRUSTUM_BOTTOM, FRUSTUM_TOP,
//				FRUSTUM_NEAR, FRUSTUM_FAR );
		GLint width,height;
		width = iScreenWidth  >> 1;
		height = iScreenHeight >> 1;
		glOrthof((float)-width, (float) width, (float)-height, (float) height, -1, 1); // set the same size as viewport
		
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glScalef(1.0f / 255.0f, 1.0f / 255.0f, 1.0f);
		glTranslatef(128.0f, 128.0f, 0.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Set array pointers.
		glVertexPointer(3, GL_BYTE, 0, vertices);
		glTexCoordPointer(2, GL_BYTE, 0, nokTexCoords);
			
		glMatrixMode(GL_MODELVIEW);
		
	glLoadIdentity();
//	glTranslatex(0, 0, iCameraDistance << 16);
//	glScalex(5 << 16, 5 << 16 , 1 << 16);
		
//	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); // �����Ļ����Ȼ���
	//	glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_CURRENT_BIT
	//		| GL_LIGHTING_BIT | GL_TRANSFORM_BIT | GL_TEXTURE_BIT);

//	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

//	glEnable(GL_TEXTURE_2D);

	//���ϴ���ʹ��ɫ͸��

	//glLoadIdentity(); // ���õ�ǰ��ģ�͹۲����
	/***********************************����Ĵ���***********************************************************************************/
	for (loop = 0; loop < MAX_PARTICLES; loop++) // ѭ�����е�����
		{
		if (particle[loop].active) // �������Ϊ�����
			{
			float x = particle[loop].x; // ����X���λ��
			float y = particle[loop].y; // ����Y���λ��
			float z = 0.0f; // ����Z���λ��
			// ����������ɫ
			
			if (iImageData)
				{
				TInt iShowIndex = iImageData->GetSelected();
				CImageElement** elements = iImageData->GetElements();
				x += offsetTangram[iShowIndex][0]+elements[iShowIndex]->GetPositionX();
				y += offsetTangram[iShowIndex][1]+elements[iShowIndex]->GetPositionY();
				}
			
			
//			x *= 5;
//			y *= 5;
//			x = 0.0f;
//			y = 0.0f;

			glPushMatrix();

			glColor4f(particle[loop].r, particle[loop].g, particle[loop].b,
					particle[loop].life);

			glTranslatef(x, y, z);
			
			glBindTexture(GL_TEXTURE_2D, iPictures[0].iID);
			glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, triangles);

			glPopMatrix();

			particle[loop].x += particle[loop].xi / (slowdown * 100); // ����X�����λ��
			particle[loop].y += particle[loop].yi / (slowdown * 100); // ����Y�����λ��
			particle[loop].xi += particle[loop].xg; // ����X�᷽���ٶȴ�С
			particle[loop].yi += particle[loop].yg; // ����Y�᷽���ٶȴ�С
			particle[loop].life -= particle[loop].fade; // �������ӵ�����ֵ
			if (particle[loop].life < 0.0f) // �����������ֵС��0
				{
				particle[loop].life = 1.0f; // ����һ���µ�����
				particle[loop].fade = float(Math::Random() % 100) / 1000.0f
						+ 0.003f; // �������˥������
				particle[loop].x = 0.0f; // �����ӳ�������Ļ������
				particle[loop].y = 0.0f;
				
				particle[loop].xi=float((Math::Random()%50)-25.0f)*10.0f;		// �������X�᷽���ٶ�
				particle[loop].yi=float((Math::Random()%50)-25.0f)*10.0f;		// �������Y�᷽���ٶ�
				particle[loop].xg=float(Math::Random()%50)/100.0f;								// ����X�᷽����ٶ�Ϊ0
				particle[loop].yg=float(Math::Random()%50)/100.0f;								// ����Y�᷽����ٶ�
				
				particle[loop].r = colors[col][0]; // ����������ɫ
				particle[loop].g = colors[col][1];
				particle[loop].b = colors[col][2];
				}
			}
		}
	
	glDisable(GL_BLEND);
	
	col++;
		if (col > 11)
			col = 0;
		
	}


void CSlideshow::MouseSelected(TInt aX,TInt aY)
	{
	TInt select = GetSelected(aX,aY);
	if (select != -1)
		{
		}
	else
		iSelectedState = ESelectedEdge;
	}

TInt CSlideshow::GetSelected(TInt aX,TInt aY)
	{
    GLuint aPixel;
    GLint x,y;
    
    x = aX - (iScreenWidth>>1);
    y = aY - (iScreenHeight >> 1);
    // At the moment GL_RGBA/GL_UNSIGNED_BYTE is the only supported combo.
    glReadPixels( aX, (iScreenHeight-aY), 1, 1, GL_RGBA,
                  GL_UNSIGNED_BYTE, &aPixel );

    GLuint select = aPixel >> 24; // get the alpha value of the pixel
    for (TInt i=0; i<7; i++)
    	if (select == colorsAlpha[i])
    		return i;
    return -1;
//    iSelectionIdx = aPixel >> 24; // get the alpha value of the pixel
	}

void CSlideshow::DrawBackground()
	{
	    
	    GLbyte texCoords2[] =
	    	{	    	
	        tex(0,255),  
	        tex(255,255),
	        tex(0,0),
	        tex(255,0),  
	        
	    	};
	    
	    GLfixed vertices[] =
	        {
	        0,       0,
	        1 << 16, 0,
	        0,       1 << 16,
	        1 << 16, 1 << 16,
	        };
	    

	    // Set orthogonal projection
	    glMatrixMode(GL_PROJECTION);
//	    glPushMatrix();
	    glLoadIdentity();
	    glOrthof(0, 1, 0, 1, -1, 1);
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glScalef(1.0f / 255.0f, 1.0f / 255.0f, 1.0f);
		glTranslatef(128.0f, 128.0f, 0.0f);
		
//	    glColor4f(0.0f,0.0f,0.0f,1.0f);
	    // Set texture parameters
	    glBindTexture(GL_TEXTURE_2D, iConstellationPictures[iCurrentConstellation].iID);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ETrue ? GL_LINEAR : GL_NEAREST);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ETrue ? GL_LINEAR : GL_NEAREST);

	    // Draw the textured quad
	    glEnableClientState(GL_VERTEX_ARRAY);
	    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	    glTexCoordPointer(2, GL_BYTE, 0, texCoords2);
//	    glTexCoordPointer( 2, GL_FIXED, 0, texCoords );
	    glVertexPointer( 2, GL_FIXED, 0, vertices );
	    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	}

TInt CSlideshow::GetConstellation(TInt aMonth,TInt aDay)
	{
	/*
	 * 	������(03/21-04/19)
		��ţ��(04/20-05/20)
		˫����(05/21-06/21)
		��з��(06/22-07/22)
		ʨ����(07/23-08/22)
		��Ů��(08/23-09/22)
		�����(09/23-10/23)
		��Ы��(10/24-11/22��
		������(11/23-12/21)
		Ħ����(12/22-01/19)
		ˮƿ��(01/20-02/18)
		˫����(02/19-03/20)
	 */
	TInt date[12][4] = {{3,21,4,19},{4,20,5,20},{5,21,6,21},{6,22,7,22},{7,23,8,22},{8,23,9,22},
			{9,23,10,23},{10,24,11,22},{11,23,12,21},{12,22,1,19},{1,20,2,18},{2,19,3,20},};
	
	for(TInt i=0; i<12; i++)
		{
		if ((aMonth==date[i][0] && aDay >= date[i][1]) || (aMonth==date[i][2] && aDay <= date[i][3]))
			return i;
		}
	return -1;
	}

void CSlideshow::InitConstellation()
	{
	TInt month,day;
	
	TTime nowTime;
	nowTime.HomeTime();
	
	TDateTime dateTime;
	dateTime = nowTime.DateTime();
	
	month = dateTime.Month() + 1;  	//��0��ʼ
	day = dateTime.Day() + 1;		//0��ʼ
	iCurrentConstellation = GetConstellation(month,day);
	
	if (iCurrentConstellation < 0 || iCurrentConstellation > 11)
		iCurrentConstellation = 0;
	}

void CSlideshow::MouseDrag(TGestureType aGuestrue,TPoint aStart,TPoint aEnd)
	{
	if (iSelectedState != ESelectedEdge)
		{
		MouseDragTranslate(aGuestrue,aStart,aEnd);
		}
	else
		{
		MouseDragRotate(aGuestrue,aStart,aEnd);
		}
	}

void CSlideshow::MouseDragRotate(TGestureType aGuestrue,TPoint /*aStart*/,TPoint /*aEnd*/)
	{
	switch (aGuestrue)
		{
		case ELeftRight:
		case EUpDown:
		case ELeftUpRightDown:			
			break;
		case EDownUp:
		case ERightLeft:		
		case ERightDownLeftUp:
			break;
		}
	}

void CSlideshow::MouseDragTranslate(TGestureType /*aGuestrue*/,TPoint aStart,TPoint aEnd)
	{
//	iTranslate[iShowIndex][0] += (aEnd.iX - aStart.iX)/25;
//	iTranslate[iShowIndex][1] -= (aEnd.iY - aStart.iY)/25;
	}

// End of File

