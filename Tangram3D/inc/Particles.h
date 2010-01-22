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

#define	MAX_PARTICLES	100				// ��������������
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
	//bool rainbow = true; // �Ƿ�Ϊ�ʺ�ģʽ
	//bool sp; // �ո���Ƿ񱻰���
	//bool rp; // �س����Ƿ񱻰���
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

#endif // PARTICLES_H
