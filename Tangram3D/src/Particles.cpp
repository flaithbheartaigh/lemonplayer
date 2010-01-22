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
	slowdown = 2.0f; // ��������
	float zoom = -40.0f; // ��Z������
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
			particle[loop].zi = float((Math::Random() % 50) - 25.0f) * 10.0f; // �������Z�᷽���ٶ�
			particle[loop].xg = float(Math::Random() % 50) / 1000.0f; // ����X�᷽����ٶ�Ϊ0
			particle[loop].yg = float(Math::Random() % 50) / 1000.0f; // ����Y�᷽����ٶ�Ϊ-0.8
			particle[loop].zg = float(Math::Random() % 50) / 1000.0f; // ����Z�᷽����ٶ�Ϊ0
			}
	}
	
void CParticles::Render()
	{
//	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); // �����Ļ����Ȼ���
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

		//���ϴ���ʹ��ɫ͸��

		//glLoadIdentity(); // ���õ�ǰ��ģ�͹۲����
		/***********************************����Ĵ���***********************************************************************************/
		for (loop = 0; loop < MAX_PARTICLES; loop++) // ѭ�����е�����
			{
			if (particle[loop].active) // �������Ϊ�����
				{
				float x = particle[loop].x; // ����X���λ��
				float y = particle[loop].y; // ����Y���λ��
				float z = particle[loop].z + zoom; // ����Z���λ��
				// ����������ɫ

				glPushMatrix();

				glColor4f(particle[loop].r, particle[loop].g, particle[loop].b,
						particle[loop].life);

				glTranslatef(x, y, z);
				glScalef(10.0f,10.0f,1.0f);
				glBindTexture(GL_TEXTURE_2D, iTexture.iID);
				glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_BYTE, triangles);

				glPopMatrix();

				//			glBegin(GL_TRIANGLE_STRIP);				// ���������δ�
				//				glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); 
				//				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); 
				//				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); 
				//				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); 
				//			glEnd();

				particle[loop].x += particle[loop].xi / (slowdown * 1000); // ����X�����λ��
				particle[loop].y += particle[loop].yi / (slowdown * 1000); // ����Y�����λ��
				particle[loop].z += particle[loop].zi / (slowdown * 1000); // ����Z�����λ��
				particle[loop].xi += particle[loop].xg; // ����X�᷽���ٶȴ�С
				particle[loop].yi += particle[loop].yg; // ����Y�᷽���ٶȴ�С
				particle[loop].zi += particle[loop].zg; // ����Z�᷽���ٶȴ�С
				particle[loop].life -= particle[loop].fade; // �������ӵ�����ֵ
				if (particle[loop].life < 0.0f) // �����������ֵС��0
					{
					particle[loop].life = 1.0f; // ����һ���µ�����
					particle[loop].fade = float(Math::Random() % 100) / 1000.0f
							+ 0.003f; // �������˥������
					particle[loop].x = 0.0f; // �����ӳ�������Ļ������
					particle[loop].y = 0.0f;
					particle[loop].z = 0.0f;
					
	//				particle[loop].xi = xspeed + float((Math::Random() % 60)
	//						- 32.0f); // ������������ٶ�
	//				particle[loop].yi = yspeed + float((Math::Random() % 60)
	//						- 30.0f);
	//				particle[loop].zi = float((Math::Random() % 60) - 30.0f);
					
					particle[loop].xi=float((Math::Random()%50)-25.0f)*10.0f;		// �������X�᷽���ٶ�
					particle[loop].yi=float((Math::Random()%50)-25.0f)*10.0f;		// �������Y�᷽���ٶ�
					particle[loop].zi=float((Math::Random()%50)-25.0f)*10.0f;		// �������Z�᷽���ٶ�
					particle[loop].xg=float(Math::Random()%50)/1000.0f;									// ����X�᷽����ٶ�Ϊ0
					particle[loop].yg=float(Math::Random()%50)/1000.0f;								// ����Y�᷽����ٶ�Ϊ-0.8
					particle[loop].zg=float(Math::Random()%50)/1000.0f;									// ����Z�᷽����ٶ�Ϊ0
							
					
					particle[loop].r = colors[col][0]; // ����������ɫ
					particle[loop].g = colors[col][1];
					particle[loop].b = colors[col][2];
					}
				}
			}
	}
