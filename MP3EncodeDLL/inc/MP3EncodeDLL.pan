/*
 ============================================================================
 Name		: MP3EncodeDLL.pan
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Panic codes
 ============================================================================
 */

#ifndef __MP3ENCODEDLL_PAN__
#define __MP3ENCODEDLL_PAN__

//  Data Types

enum TMP3EncodeDLLPanic
	{
	EMP3EncodeDLLNullPointer
	};

//  Function Prototypes

GLREF_C void Panic(TMP3EncodeDLLPanic aPanic);

#endif  // __MP3ENCODEDLL_PAN__

