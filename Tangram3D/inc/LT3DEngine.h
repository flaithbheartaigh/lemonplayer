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

#define	MAX_PARTICLES	100				// 定义最大的粒子数

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
		float slowdown; // 减速粒子
		float xspeed; // X方向的速度
		float yspeed; // Y方向的速度
		float zoom; // 沿Z轴缩放
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
	};

#endif // LT3DENGINE_H
