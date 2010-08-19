/*
 ============================================================================
 Name		: LT3DEngine.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLT3DEngine declaration
 ============================================================================
 */

#ifndef LT3DENGINE_H
#define LT3DENGINE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <w32std.h>
#include <coecntrl.h>
#include <GLES\egl.h>
#include "Utils3d.h" // Utilities (texmanager, textures etc.)
#include "Glutils.h" // Misc GLU and GLUT functions

#define	MAX_PARTICLES	100				// ��������������

// CLASS DECLARATION
class CParticles;
/**
 *  CLT3DEngine
 * 
 */
class CLT3DEngine : public CFiniteStateMachine,public MTextureLoadingListener
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
	~CLT3DEngine();

	/**
	 * Two-phased constructor.
	 */
	static CLT3DEngine* NewL(CCoeControl* aParentControl,RWindow*	aParentWindow);

	/**
	 * Two-phased constructor.
	 */
	static CLT3DEngine* NewLC(CCoeControl* aParentControl,RWindow*	aParentWindow);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CLT3DEngine(CCoeControl* aParentControl,RWindow*	aParentWindow);

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	
private:
	void OnStartLoadingTexturesL() ;
	void OnEndLoadingTexturesL() ;
	
public:
	void SetRedererState();
	void Render();
	
	void Up();
	void Down();
	void Left();
	void Right();
	void Change();
	void RotateClockwise();
	void RotateAnticlockwise();
	
private:
	void DrawTangram();
	
	void InitParticles();
	void DrawParticles();
	
public:
	GLint iCameraDistance;
	GLint iRotate[7];
	GLint iTranslateX;
	GLint iTranslateY;
	GLint iTranslate[7][2];
	
private:
	CCoeControl* iParentControl;
	RWindow*	iParentWindow;	
	
	EGLDisplay    iEglDisplay;         // display where the graphics are drawn
	EGLContext    iEglContext;         // rendering context
	EGLSurface    iEglSurface;         // window where the graphics are blitted

	TInt iScreenWidth;
	TInt iScreenHeight;
	
	CTextureManager * iTextureManager;
	TTexture iOpenGLES;
	TTexture iStar;
	TTexture iTextureParticle;
	
	TBool iShow[7];
	TInt iShowIndex;
	
	TBool iIsActive;
	
//	CParticles* iParticles;
		float slowdown; // ��������
		float xspeed; // X������ٶ�
		float yspeed; // Y������ٶ�
		float zoom; // ��Z������
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
			float z; // Z λ��
			float xi; // X ����
			float yi; // Y ����
			float zi; // Z ����

			float xg; // X �����������ٶ�
			float yg; // Y �����������ٶ�
			float zg; // Z �����������ٶ�
			} particles; // �������ݽṹ
		particles particle[MAX_PARTICLES]; // ����1000�����ӵ�����
	};

#endif // LT3DENGINE_H