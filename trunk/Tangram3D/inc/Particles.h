/*
 ============================================================================
 Name		: Particles.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CParticles declaration
 ============================================================================
 */

#ifndef PARTICLES_H
#define PARTICLES_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <GLES\egl.h>
#include "Utils3d.h" // Utilities (texmanager, textures etc.)
#include "Glutils.h" // Misc GLU and GLUT functions
// CLASS DECLARATION

#define	MAX_PARTICLES	100				// 定义最大的粒子数
/**
 *  CParticles
 * 
 */
class CParticles : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CParticles();

	/**
	 * Two-phased constructor.
	 */
	static CParticles* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CParticles* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CParticles();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	void Init();
	void InitTexture(CTextureManager* aManager);
//	TTexture* GetTexture();
	
	void Render();
	
private:
	TTexture iTexture;
	//bool rainbow = true; // 是否为彩虹模式
	//bool sp; // 空格键是否被按下
	//bool rp; // 回车键是否被按下
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

#endif // PARTICLES_H
