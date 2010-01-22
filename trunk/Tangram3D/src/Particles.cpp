/*
 ============================================================================
 Name		: Particles.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CParticles implementation
 ============================================================================
 */

#include "Particles.h"

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

#define tex(u,v) (GLbyte)( (u) - 128 ) , (GLbyte)( (v) - 128 )

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

CParticles::CParticles()
	{
	// No implementation required
	slowdown = 2.0f; // 减速粒子
	float zoom = -40.0f; // 沿Z轴缩放
	}

CParticles::~CParticles()
	{
	}

CParticles* CParticles::NewLC()
	{
	CParticles* self = new (ELeave) CParticles();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CParticles* CParticles::NewL()
	{
	CParticles* self = CParticles::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CParticles::ConstructL()
	{

	}

_LIT(KTexture,"Particle.jpg");

void CParticles::InitTexture(CTextureManager* aManager)
	{	
	aManager->RequestToLoad(KTexture, &iTexture);
	}

//TTexture* CParticles::GetTexture()
//	{
//	return &iTexture;
//	}

void CParticles::Init()
	{
//	glMatrixMode(GL_MODELVIEW);
		
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
	
void CParticles::Render()
	{
//	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存
		//	glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_CURRENT_BIT
		//		| GL_LIGHTING_BIT | GL_TRANSFORM_BIT | GL_TEXTURE_BIT);
	
	// Set array pointers.
		glVertexPointer(3, GL_BYTE, 0, vertices);
		glTexCoordPointer(2, GL_BYTE, 0, nokTexCoords);

//		glDisable(GL_DEPTH_TEST);
//		glDisable(GL_LIGHTING);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);

//		glEnable(GL_TEXTURE_2D);

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
				glScalef(10.0f,10.0f,1.0f);
				glBindTexture(GL_TEXTURE_2D, iTexture.iID);
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
	}
