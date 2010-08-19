/*
 ============================================================================
 Name		: OpenGLParticles.pan
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __OPENGLPARTICLES_PAN__
#define __OPENGLPARTICLES_PAN__

/** OpenGLParticles application panic codes */
enum TOpenGLParticlesPanics
	{
	EOpenGLParticlesUi = 1
	// add further panics here
	};

inline void Panic(TOpenGLParticlesPanics aReason)
	{
	_LIT(applicationName, "OpenGLParticles");
	User::Panic(applicationName, aReason);
	}

#endif // __OPENGLPARTICLES_PAN__
