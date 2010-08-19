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

// MACROS
#define FRUSTUM_LEFT   -1.f     //left vertical clipping plane
#define FRUSTUM_RIGHT   1.f     //right vertical clipping plane
#define FRUSTUM_BOTTOM -1.f     //bottom horizontal clipping plane
#define FRUSTUM_TOP     1.f     //top horizontal clipping plane
#define FRUSTUM_NEAR    3.f     //near depth clipping plane
#define FRUSTUM_FAR  1000.f     //far depth clipping plane
#define tex(u,v) (GLbyte)( (u) - 128 ) , (GLbyte)( (v) - 128 )

#define	MAX_PARTICLES	10				// 定义最大的粒子数
bool rainbow = true; // 是否为彩虹模式
bool sp; // 空格键是否被按下
bool rp; // 回车键是否被按下
float slowdown = 2.0f; // 减速粒子
float xspeed; // X方向的速度
float yspeed; // Y方向的速度
float zoom = -40.0f; // 沿Z轴缩放
GLuint loop; // 循环变量
GLuint col; // 当前的颜色
GLuint delay; // 彩虹效果延迟
typedef struct // 创建粒子数据结构
	{
	bool active; // 是否激活
	float life; // 粒子生命
	float fade; // 衰减速度
	float r; // 红色值
	float g; // 绿色值
	float b; // 蓝色值
	float x; // X 位置
	float y; // Y 位置
	float z; // Z 位置
	float xi; // X 方向
	float yi; // Y 方向
	float zi; // Z 方向

	float xg; // X 方向重力加速度
	float yg; // Y 方向重力加速度
	float zg; // Z 方向重力加速度
	} particles; // 粒子数据结构
particles particle[MAX_PARTICLES]; // 保存1000个粒子的数组

/** Vertice coordinates for the cube. */
static const GLbyte vertices[24 * 3] =
	{
	/* top */
	-1, 1, 1, 1, 1, 1, 1, -1, 1, -1, -1, 1,

	/* front */
	1, 1, 1, 1, 1, -1, 1, -1, -1, 1, -1, 1,

	/* right */
	-1, 1, 1, -1, 1, -1, 1, 1, -1, 1, 1, 1,

	/* left */
	1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, 1,

	/* back */
	-1, -1, 1, -1, -1, -1, -1, 1, -1, -1, 1, 1,

	/* bottom */
	-1, 1, -1, 1, 1, -1, 1, -1, -1, -1, -1, -1
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
static GLfloat colors[12][3] = // 彩虹颜色
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
tex	(0,255)
	};

static const GLbyte verticesTangram[10 * 3] =
	{
			-4,			4,			
			4,			4,			
			2,			2,			
			0,			0,			
			4,			0,			
			-2,			-2,			
			2,			-2,			
			-4,			-4,			
			0,			-4,			
			4,			-4,			

	};

static const GLubyte STTtriangleBig1[1 * 3] =
	{
	3, 1, 0,
	};

static const GLubyte STTtriangleBig2[1 * 3] =
	{
	3, 0, 7,
	};

static const GLubyte STTtriangleSmall1[1 * 3] =
	{
	3, 6, 2,
	};

static const GLubyte STTtriangleSmall2[1 * 3] =
	{
	7, 8, 5,
	};

static const GLubyte STTtriangleMid[1 * 3] =
	{
	4, 8, 9,
	};

static const GLubyte STSquare[2 * 3] =
	{
	5, 8, 3, 8, 6, 3,
	};

static const GLubyte STRect[2 * 3] =
	{
	 2, 6, 1, 6, 4, 1,
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

static const GLint offsetTangram[7][2] = { {0,2},{-2,0},{1,0},{-2,-3},{3,-3},{0,-2},{3,1},};
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
	: CFiniteStateMachine(),
      iCurrentPicture(0),
      iNextPicture(0),
      iRequestedPictureDelta(0),
      iTransitionRenderer(0),
      iTransitionTime(0)
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

	/* Choose the ‘best’ config and use that in the future */
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
	eglMakeCurrent(iEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroySurface(iEglDisplay, iEglSurface);
	eglDestroyContext(iEglDisplay, iEglContext);
	eglTerminate(iEglDisplay); // release resources associated with EGL & OpenGL ES
	}

CSlideshow::CSlideshow(CCoeControl* aParentControl, RWindow* aParentWindow) :CFiniteStateMachine(),
	iParentControl(aParentControl), iParentWindow(aParentWindow),iIsActive(EFalse),iCameraDistance(-8)
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
    
//    iPictureCount = sizeof(iPictures) / sizeof(iPictures[0]);
//
//    // Generate some masks
//    glGenTextures( 1, &iMasks[0].iID );
//    glGenTextures( 1, &iMasks[1].iID );
//
//    TUint8* maskData = new TUint8[64 * 64 * 4];
//    TUint8* maskDataPtr = maskData;
//    TInt x, y;
//
//    // The first mask has a band of colors in the middle
//    for (y = 0; y < 64; y++)
//        {
//        for (x = 0; x < 64; x++)
//            {
//            *maskDataPtr++ = Min(Max(Abs(24 - y) * 16, 0), 255);
//            *maskDataPtr++ = Min(Max(Abs(28 - y) * 16, 0), 255);
//            *maskDataPtr++ = Min(Max(Abs(32 - y) * 16, 0), 255);
//            *maskDataPtr++ = Min(Max((32 - y) * 16, 0), 255);
//            }
//        }
//
//    glBindTexture( GL_TEXTURE_2D, iMasks[0].iID );
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, maskData);
//
//    // The second mask has a wavy alpha threshold in the middle
//    maskDataPtr = maskData;
//    for (y = 0; y < 64; y++)
//        {
//        for (x = 0; x < 64; x++)
//            {
//            TReal s;
//            Math::Sin(s, x / 4.0);
//            TInt maskFactor = Min(Max((32 - y - s * 6) * 16, 0), 255);
//            *maskDataPtr++ = 255;
//            *maskDataPtr++ = 255;
//            *maskDataPtr++ = 255;
//            *maskDataPtr++ = maskFactor;
//            }
//        }
//    glBindTexture( GL_TEXTURE_2D, iMasks[1].iID );
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, maskData);
//
//    delete[] maskData;

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
    delete iTransitionRenderer;
	}


// ----------------------------------------------------------------------------
// CSlideshow::AppCycle
// Draws and animates the objects.
// aFrame = Number of the frame to be rendered.
// aTimeSecs = Seconds elapsed since the application started running.
// aDeltaTimeSecs = Seconds elapsed since last call to AppCycle().
// ----------------------------------------------------------------------------
//
void CSlideshow::AppCycle( TInt /*aFrame*/,
                       TReal /*aTimeSecs*/,
                       TReal aDeltaTimeSecs )
	{
	  // Make sure the timestep is non-zero, since otherwise the animation wouldn't progress at all.
	  if (aDeltaTimeSecs < 0.04)
	    aDeltaTimeSecs = 0.04;

    // Stop the transition if it's complete
    if (iTransitionRenderer && iTransitionTime <= 0)
        {
        delete iTransitionRenderer;
        iTransitionRenderer = 0;
        iCurrentPicture = iNextPicture;
        }

    // Advance the slideshow if we have been requested to
    if (iRequestedPictureDelta && !iTransitionRenderer)
        {
        iTransitionRenderer = CreateTransitionRenderer((iRequestedPictureDelta > 0) ? ENext : EPrevious);
        iTransitionTime = 1.0;

        TInt direction = (iRequestedPictureDelta > 0) ? 1 : -1;
        iNextPicture = (iCurrentPicture + direction + iPictureCount) % iPictureCount;
        iRequestedPictureDelta -= direction;
        }

    // Render the current picture. If there is no transition going on, enable
    // bilinear filtering to improve image quality.
    iStaticRenderer.Render(iPictures[iCurrentPicture], iTransitionRenderer == NULL);

    // Render the transition and the next picture
    if (iTransitionTime > 0 && iTransitionRenderer)
        {
        iTransitionRenderer->Render(iPictures[iNextPicture], iTransitionTime);
        // Accelerate the transition speed if we are many pictures behind
        iTransitionTime -= aDeltaTimeSecs * (Abs(iRequestedPictureDelta) + 1);
        }
	}

void CSlideshow::ShowNextPicture( void )
    {
    iRequestedPictureDelta++;
    }

void CSlideshow::ShowPreviousPicture( void )
    {
    iRequestedPictureDelta--;
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

MTransitionRenderer* CSlideshow::CreateTransitionRenderer(TDirection dir)
    {
    // Choose a transition renderer class randomly
    switch (Math::Random() % 3)
        {
        case 0:
            {
            // Choose a sweep style randomly
            const CMaskTransition::TSweepStyle s[] =
                {
                CMaskTransition::ESweepCurved,
                CMaskTransition::ESweepCurved2,
                CMaskTransition::ESweepHorizontal,
                CMaskTransition::ESweepVertical
                };
            return new CMaskTransition(iMasks[Math::Random() % (sizeof(iMasks) / sizeof(iMasks[0]))],
                                       s[Math::Random() % (sizeof(s) / sizeof(s[0]))]);
            }
        case 1:
            if (dir == ENext)
                return new CWhiskTransition(CWhiskTransition::ERight);
            else
                return new CWhiskTransition(CWhiskTransition::ELeft);
        case 2:
            if (dir == ENext)
                return new CCurtainTransition(CCurtainTransition::ERight);
            else
                return new CCurtainTransition(CCurtainTransition::ELeft);
        }
    return 0;
    }

void CSlideshow::SetRedererState()
	{
	AppInitL();
	
	InitConstellation();
	glShadeModel( GL_FLAT );
	
	for (loop = 0; loop < MAX_PARTICLES; loop++) //初始化所有的粒子
		{
		particle[loop].active = true; // 使所有的粒子为激活状态
		particle[loop].life = 1.0f; // 所有的粒子生命值为最大
		particle[loop].fade = float(Math::Random() % 100) / 1000.0f + 0.003f; // 随机生成衰减速率
		particle[loop].r = colors[loop * (12 / MAX_PARTICLES)][0]; // 粒子的红色颜色
		particle[loop].g = colors[loop * (12 / MAX_PARTICLES)][1]; // 粒子的绿色颜色
		particle[loop].b = colors[loop * (12 / MAX_PARTICLES)][2]; // 粒子的蓝色颜色
		particle[loop].xi = float((Math::Random() % 50) - 25.0f) * 10.0f; // 随机生成X轴方向速度
		particle[loop].yi = float((Math::Random() % 50) - 25.0f) * 10.0f; // 随机生成Y轴方向速度
		particle[loop].zi = float((Math::Random() % 50) - 25.0f) * 10.0f; // 随机生成Z轴方向速度
		particle[loop].xg = float(Math::Random() % 50) / 1000.0f; // 设置X轴方向加速度为0
		particle[loop].yg = float(Math::Random() % 50) / 1000.0f; // 设置Y轴方向加速度为-0.8
		particle[loop].zg = float(Math::Random() % 50) / 1000.0f; // 设置Z轴方向加速度为0
		}
	}

void CSlideshow::Render()
	{
	glClear(GL_COLOR_BUFFER_BIT);
	
	DrawBackground();
	DrawTangram();
	DrawGLScene();
	
//	AppCycle();
	
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
	if (ETrue)
		{
		glPushMatrix();
//		glTranslatex(0, 0, iCameraDistance << 16);
		
		glRotatex(iRotate[0] << 16, 0, 0, 1 << 16);
		
		glScalex(25 << 16, 25<<16 ,1 << 16);
		
		glTranslatex(iTranslate[0][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[0][1] << 16, 0);		
		
//		glTranslatex(0, 2<<16, 0);
//		glRotatex(iRotate[0] << 16, 0, 0, 1 << 16);
//		glTranslatex(0, -2<<16, 0);
		
		//		glRotatex(0,iRotate<<16,0,0);
		//		glRotatex(0,0,iRotate<<16,0);

		glBindTexture(  GL_TEXTURE_2D, iPictures[1].iID );		
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleBig1);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
//		glTranslatex(0, 0, iCameraDistance << 16);
		glScalex(25 << 16, 25<<16 ,1 << 16);
				
		glTranslatex(iTranslate[1][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[1][1] << 16, 0);
		
		glTranslatex(-2<<16, 0, 0);
		glRotatex(iRotate[1] << 16, 0, 0, 1 << 16);
		glTranslatex(2<<16, 0, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iPictures[1].iID );
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleBig2);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
//		glTranslatex(0, 0, iCameraDistance << 16);

		glScalex(25 << 16, 25<<16 ,1 << 16);
		
		glTranslatex(iTranslate[2][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[2][1] << 16, 0);
		
		glTranslatex(1<<16, 0, 0);
		glRotatex(iRotate[2] << 16, 0, 0, 1 << 16);
		glTranslatex(-1<<16, 0, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iPictures[1].iID );
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleSmall1);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
//		glTranslatex(0, 0, iCameraDistance << 16);

		glScalex(25 << 16, 25<<16 ,1 << 16);
		
		glTranslatex(iTranslate[3][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[3][1] << 16, 0);
		
		glTranslatex(-2<<16, -3<<16, 0);
		glRotatex(iRotate[3] << 16, 0, 0, 1 << 16);
		glTranslatex(2<<16, 3<<16, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iPictures[1].iID );
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleSmall2);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
//		glTranslatex(0, 0, iCameraDistance << 16);

		glScalex(25 << 16, 25<<16 ,1 << 16);
		
		glTranslatex(iTranslate[4][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[4][1] << 16, 0);
		
		glTranslatex(3<<16, -3<<16, 0);
		glRotatex(iRotate[4] << 16, 0, 0, 1 << 16);
		glTranslatex(-3<<16, 3<<16, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iPictures[1].iID );
		glDrawElements(GL_TRIANGLES, 1 * 3, GL_UNSIGNED_BYTE, STTtriangleMid);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
//		glTranslatex(0, 0, iCameraDistance << 16);

		glScalex(25 << 16, 25<<16 ,1 << 16);
		
		glTranslatex(iTranslate[5][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[5][1] << 16, 0);
		
		glTranslatex(0, -2<<16, 0);
		glRotatex(iRotate[5] << 16, 0, 0, 1 << 16);
		glTranslatex(0, 2<<16, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iPictures[1].iID );
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, STSquare);
		
		glPopMatrix();
		}

	if (ETrue)
		{
		glPushMatrix();
//		glTranslatex(0, 0, iCameraDistance << 16);

		glScalex(25 << 16, 25<<16 ,1 << 16);
		
		glTranslatex(iTranslate[6][0] << 16, 0, 0);
		glTranslatex(0, iTranslate[6][1] << 16, 0);
		
		glTranslatex(3<<16, 1<<16, 0);
		glRotatex(iRotate[6] << 16, 0, 0, 1 << 16);
		glTranslatex(-3<<16, -1<<16, 0);
		
		glBindTexture(  GL_TEXTURE_2D, iPictures[1].iID );
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, STRect);
		
		glPopMatrix();
		}
	
	}
void CSlideshow::DrawGLScene() // 从这里开始进行所有的绘制
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

		// Set array pointers.
		glVertexPointer(3, GL_BYTE, 0, vertices);
		glTexCoordPointer(2, GL_BYTE, 0, nokTexCoords);
			
		glMatrixMode(GL_MODELVIEW);
		
	glLoadIdentity();
//	glTranslatex(0, 0, iCameraDistance << 16);
	glScalex(5 << 16, 5 << 16 , 1 << 16);
		
//	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存
	//	glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_CURRENT_BIT
	//		| GL_LIGHTING_BIT | GL_TRANSFORM_BIT | GL_TEXTURE_BIT);

//	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

//	glEnable(GL_TEXTURE_2D);

	//以上代码使黑色透明

	//glLoadIdentity(); // 重置当前的模型观察矩阵
	/***********************************新添的代码***********************************************************************************/
	for (loop = 0; loop < MAX_PARTICLES; loop++) // 循环所有的粒子
		{
		if (particle[loop].active) // 如果粒子为激活的
			{
			float x = particle[loop].x; // 返回X轴的位置
			float y = particle[loop].y; // 返回Y轴的位置
			float z = particle[loop].z + zoom; // 返回Z轴的位置
			// 设置粒子颜色
			
			x += offsetTangram[iShowIndex][0]+iTranslate[iShowIndex][0];
			y += offsetTangram[iShowIndex][1]+iTranslate[iShowIndex][1];
			
			x *= 5;
			y *= 5;
//			x = 0.0f;
//			y = 0.0f;
			z = 0.0f;

			glPushMatrix();

			glColor4f(particle[loop].r, particle[loop].g, particle[loop].b,
					particle[loop].life);

			glTranslatef(x, y, z);
			
			glBindTexture(GL_TEXTURE_2D, iPictures[0].iID);
			glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, triangles);

			glPopMatrix();

			//			glBegin(GL_TRIANGLE_STRIP);				// 绘制三角形带
			//				glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); 
			//				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); 
			//				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); 
			//				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); 
			//			glEnd();

			particle[loop].x += particle[loop].xi / (slowdown * 1000); // 更新X坐标的位置
			particle[loop].y += particle[loop].yi / (slowdown * 1000); // 更新Y坐标的位置
			particle[loop].z += particle[loop].zi / (slowdown * 1000); // 更新Z坐标的位置
			particle[loop].xi += particle[loop].xg; // 更新X轴方向速度大小
			particle[loop].yi += particle[loop].yg; // 更新Y轴方向速度大小
			particle[loop].zi += particle[loop].zg; // 更新Z轴方向速度大小
			particle[loop].life -= particle[loop].fade; // 减少粒子的生命值
			if (particle[loop].life < 0.0f) // 如果粒子生命值小于0
				{
				particle[loop].life = 1.0f; // 产生一个新的粒子
				particle[loop].fade = float(Math::Random() % 100) / 1000.0f
						+ 0.003f; // 随机生成衰减速率
				particle[loop].x = 0.0f; // 新粒子出现在屏幕的中央
				particle[loop].y = 0.0f;
				particle[loop].z = 0.0f;
				
//				particle[loop].xi = xspeed + float((Math::Random() % 60)
//						- 32.0f); // 随机生成粒子速度
//				particle[loop].yi = yspeed + float((Math::Random() % 60)
//						- 30.0f);
//				particle[loop].zi = float((Math::Random() % 60) - 30.0f);
				
				particle[loop].xi=float((Math::Random()%50)-25.0f)*10.0f;		// 随机生成X轴方向速度
				particle[loop].yi=float((Math::Random()%50)-25.0f)*10.0f;		// 随机生成Y轴方向速度
				particle[loop].zi=float((Math::Random()%50)-25.0f)*10.0f;		// 随机生成Z轴方向速度
				particle[loop].xg=float(Math::Random()%50)/1000.0f;									// 设置X轴方向加速度为0
				particle[loop].yg=float(Math::Random()%50)/1000.0f;								// 设置Y轴方向加速度为-0.8
				particle[loop].zg=float(Math::Random()%50)/1000.0f;									// 设置Z轴方向加速度为0
						
				
				particle[loop].r = colors[col][0]; // 设置粒子颜色
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
void CSlideshow::Up()
	{
	if (iIsActive)
		{
		iTranslate[iShowIndex][1]++;
		}
	else
		{
		Left();
		}
	}
void CSlideshow::Down()
	{
	if (iIsActive)
		{
		iTranslate[iShowIndex][1]--;
		}
	else
		{
		Right();
		}
	}

void CSlideshow::Left()
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

void CSlideshow::Right()
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

void CSlideshow::Change()
	{
	iIsActive = !iIsActive;
	}

void CSlideshow::RotateClockwise()
	{
	if (iIsActive)
		{
		iRotate[iShowIndex] += 5;
		}
	}
void CSlideshow::RotateAnticlockwise()
	{
	if (iIsActive)
		{
		iRotate[iShowIndex] -= 5;
		}
	}

void CSlideshow::MouseSelected(TInt aX,TInt aY)
	{
	TInt select = GetSelected(aX,aY);
	if (select != -1)
		{
		iIsActive = ETrue;
		
		if (select != iShowIndex)
			{
			iShowIndex = select;
			iSelectedState = ESelectedDiff;
			}
		else
			iSelectedState = ESelectedSame;
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

//	    glMatrixMode( GL_PROJECTION );
//	    glPopMatrix();
//	    glMatrixMode( GL_MODELVIEW);	
	}

TInt CSlideshow::GetConstellation(TInt aMonth,TInt aDay)
	{
	/*
	 * 	白羊座(03/21-04/19)
		金牛座(04/20-05/20)
		双子座(05/21-06/21)
		巨蟹座(06/22-07/22)
		狮子座(07/23-08/22)
		处女座(08/23-09/22)
		天秤座(09/23-10/23)
		天蝎座(10/24-11/22）
		射手座(11/23-12/21)
		摩羯座(12/22-01/19)
		水瓶座(01/20-02/18)
		双鱼座(02/19-03/20)
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
	
	month = dateTime.Month() + 1;  	//从0开始
	day = dateTime.Day() + 1;		//0开始
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
			RotateClockwise();
			break;
		case EDownUp:
		case ERightLeft:		
		case ERightDownLeftUp:
			RotateAnticlockwise();
			break;
		}
	}

void CSlideshow::MouseDragTranslate(TGestureType /*aGuestrue*/,TPoint aStart,TPoint aEnd)
	{
	iTranslate[iShowIndex][0] += (aEnd.iX - aStart.iX)/25;
	iTranslate[iShowIndex][1] -= (aEnd.iY - aStart.iY)/25;
	}

// End of File

