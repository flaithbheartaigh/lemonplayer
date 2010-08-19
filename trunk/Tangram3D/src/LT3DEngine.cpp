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
#include "Particles.h"

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
	iCameraDistance = -8;
	iScreenWidth = aParentControl->Rect().Width();
	iScreenHeight = aParentControl->Rect().Height();
	// No implementation required
	}

CLT3DEngine::~CLT3DEngine()
	{	
	delete iTextureManager;
//	delete iParticles;
	

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

	/* Choose the ‘best’ config and use that in the future */
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

//	iParticles = CParticles::NewL();
	iTextureManager = CTextureManager::NewL(iScreenWidth, iScreenHeight,
			FRUSTUM_TOP, FRUSTUM_BOTTOM, FRUSTUM_RIGHT, FRUSTUM_LEFT,
			FRUSTUM_NEAR, this);
	iTextureManager->SetScreenSize(iScreenWidth, iScreenHeight);

	}

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

/** Colors for vertices (Red, Green, Blue, Alpha). */
//static const GLubyte colors[8 * 4] =
//	{
//	0, 255, 0, 255, 0, 0, 255, 255, 0, 255, 0, 255, 255, 0, 0, 255,
//
//	0, 0, 255, 255, 255, 0, 0, 255, 0, 0, 255, 255, 0, 255, 0, 255
//	};
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

#define MATERIAL_MAX 1
#define LIGHT_MAX    1

static const GLint offsetTangram[7][2] = { {0,2},{-2,0},{1,0},{-2,-3},{3,-3},{0,-2},{3,1},};

//void CLT3DEngine::SetRedererState()
//	{
//	// Reinitialize viewport and projection.
//	glViewport(0, 0, iScreenWidth, iScreenHeight);
//
////	// Set the screen background color.
////	glClearColor(0.f, 0.f, 0.f, 1.f);
////
////	// Enable back face culling.
////	glEnable(GL_CULL_FACE);
////	glEnable(GL_TEXTURE_2D);
////
////	// Enable vertex arrays.
////	glEnableClientState(GL_VERTEX_ARRAY);
////	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
////	//     glEnableClientState( GL_NORMAL_ARRAY        );
//////	glShadeModel(GL_FLAT);
////	glShadeModel(GL_SMOOTH);
////
//////	glBlendFunc(GL_ONE, GL_ONE );
////    
////	// Do not use perspective correction
////	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
//	
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	GLfloat aspectRatio = (GLfloat) (iScreenWidth) / (GLfloat) (iScreenHeight);
//	glFrustumf(FRUSTUM_LEFT * aspectRatio, FRUSTUM_RIGHT * aspectRatio,
//			FRUSTUM_BOTTOM, FRUSTUM_TOP,
//			FRUSTUM_NEAR, FRUSTUM_FAR );
//	glMatrixMode(GL_MODELVIEW);
//
//	// Set the screen background color.
//	glClearColor(0.f, 0.f, 0.f, 1.f);
//
//	// Enable back face culling.
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_TEXTURE_2D);
//
//	// Enable vertex arrays.
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//
//	glMatrixMode(GL_TEXTURE);
//	glLoadIdentity();
//	glScalef(1.0f / 255.0f, 1.0f / 255.0f, 1.0f);
//	glTranslatef(128.0f, 128.0f, 0.0f);
//
//	glMatrixMode(GL_MODELVIEW);
//
//	// Set array pointers.
//	glVertexPointer(3, GL_BYTE, 0, vertices);
//	glTexCoordPointer(2, GL_BYTE, 0, nokTexCoords);
//
//	// Enable color arrays.
//	//glEnableClientState(GL_COLOR_ARRAY);
//
//	// Set color pointers.
//	//glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);
//
//	// Set the initial shading mode
//	glShadeModel(GL_FLAT);
//	//	glShadeModel(GL_SMOOTH);
//
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
//	
////	iParticles->Init();
//	_LIT(KOGLESTexture, "ogles.jpg");
//	iTextureManager->RequestToLoad(KOGLESTexture, &iOpenGLES);
////	_LIT(KStar, "Star.bmp");
////	iTextureManager->RequestToLoad(KStar, &iStar);
//	_LIT(KParticle, "Particle.jpg");
//	iTextureManager->RequestToLoad(KParticle, &iTextureParticle);
////	iParticles->InitTexture(iTextureManager);
//	iTextureManager->DoLoadL();
//	
//	InitParticles();
//	}

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

	// Enable vertex arrays.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(1.0f / 255.0f, 1.0f / 255.0f, 1.0f);
	glTranslatef(128.0f, 128.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);

	// Set array pointers.
	glVertexPointer(3, GL_BYTE, 0, vertices);
	glTexCoordPointer(2, GL_BYTE, 0, nokTexCoords);

	// Enable color arrays.
	//glEnableClientState(GL_COLOR_ARRAY);

	// Set color pointers.
	//glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);

	// Set the initial shading mode
	glShadeModel(GL_FLAT);
	//	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	//	glBlendFunc(GL_ONE, GL_ONE );
	_LIT(KOGLESTexture, "Particle.bmp");
	iTextureManager->RequestToLoad(KOGLESTexture, &iOpenGLES);
	iTextureManager->DoLoadL();

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

//void CLT3DEngine::Render()
//	{
//
//	glClear(GL_COLOR_BUFFER_BIT);	
//
////	DrawTangram();
//	DrawParticles();
//	
////	if (iParticles)
////		iParticles->Render();
//	
//	eglSwapBuffers(iEglDisplay, iEglSurface);
//
//	}

void CLT3DEngine::Render()
	{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatex(0, 0, iCameraDistance << 16);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存
	//	glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_CURRENT_BIT
	//		| GL_LIGHTING_BIT | GL_TRANSFORM_BIT | GL_TEXTURE_BIT);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glEnable(GL_TEXTURE_2D);

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

			glPushMatrix();

			glColor4f(particle[loop].r, particle[loop].g, particle[loop].b,
					particle[loop].life);

			glTranslatef(x, y, z);
			glBindTexture(GL_TEXTURE_2D, iOpenGLES.iID);
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
	col++;
	if (col > 11)
		col = 0;

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

void CLT3DEngine::DrawTangram()
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
	glColor4f(1.0f,1.0f,1.0f,1.0f);
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

		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
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
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
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
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
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
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
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
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
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
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
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
		
		glBindTexture(  GL_TEXTURE_2D, iOpenGLES.iID );
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, STRect);
		
		glPopMatrix();
		}
	
	}

void CLT3DEngine::InitParticles()
	{
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
void CLT3DEngine::DrawParticles()
	{
	// Recalculate the view frustrum
//	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存
//	
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	GLfloat aspectRatio = (GLfloat) (iScreenWidth) / (GLfloat) (iScreenHeight);
//	glFrustumf(FRUSTUM_LEFT * aspectRatio, FRUSTUM_RIGHT * aspectRatio,
//			FRUSTUM_BOTTOM, FRUSTUM_TOP,
//			FRUSTUM_NEAR, FRUSTUM_FAR );
//
//	// Enable back face culling.
//
//	glMatrixMode(GL_TEXTURE);
//	glLoadIdentity();
//	glScalef(1.0f / 255.0f, 1.0f / 255.0f, 1.0f);
//	glTranslatef(128.0f, 128.0f, 0.0f);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	
//	glVertexPointer(3, GL_BYTE, 0, vertices);
//	glTexCoordPointer(2, GL_BYTE, 0, nokTexCoords);
//	
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

//		glEnable(GL_TEXTURE_2D);
		
	// Set array pointers.
	
	//		glEnable(GL_TEXTURE_2D);

			//以上代码使黑色透明
	
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatex(0, 0, iCameraDistance << 16);
	
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存
	//	glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_CURRENT_BIT
	//		| GL_LIGHTING_BIT | GL_TRANSFORM_BIT | GL_TEXTURE_BIT);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glEnable(GL_TEXTURE_2D);

			//glLoadIdentity(); // 重置当前的模型观察矩阵
//	glLoadIdentity();
//	glTranslatex(0, 0, iCameraDistance << 16);
			/***********************************新添的代码***********************************************************************************/
			for (loop = 0; loop < MAX_PARTICLES; loop++) // 循环所有的粒子
				{
				if (particle[loop].active) // 如果粒子为激活的
					{
					float x = particle[loop].x; // 返回X轴的位置
					float y = particle[loop].y; // 返回Y轴的位置
					float z = particle[loop].z + zoom; // 返回Z轴的位置
					// 设置粒子颜色

					glPushMatrix();

					glColor4f(particle[loop].r, particle[loop].g, particle[loop].b,
							particle[loop].life);

					glTranslatef(x, y, z);
					glScalef(10.0f,10.0f,1.0f);
					glBindTexture(GL_TEXTURE_2D, iTextureParticle.iID);
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
			
			col++;
			if (col > 11)
				col = 0;
	}
