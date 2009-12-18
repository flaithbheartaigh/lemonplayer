/*
 ============================================================================
 Name		: Tangram3D.pan
 Author	  : 
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __TANGRAM3D_PAN__
#define __TANGRAM3D_PAN__

/** Tangram3D application panic codes */
enum TTangram3DPanics
	{
	ETangram3DUi = 1
	// add further panics here
	};

inline void Panic(TTangram3DPanics aReason)
	{
	_LIT(applicationName, "Tangram3D");
	User::Panic(applicationName, aReason);
	}

#endif // __TANGRAM3D_PAN__
