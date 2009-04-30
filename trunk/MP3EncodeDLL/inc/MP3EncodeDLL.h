/*
 ============================================================================
 Name		: MP3EncodeDLL.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : MP3EncodeDLL.h - CMP3EncodeDLL class header
 ============================================================================
 */

// This file defines the API for MP3EncodeDLL.dll

#ifndef __MP3ENCODEDLL_H__
#define __MP3ENCODEDLL_H__

//  Include Files

#include <e32base.h>	// CBase
#include <e32std.h>	 // TBuf

//  Constants

const TInt KMP3EncodeDLLBufferLength = 15;
typedef TBuf<KMP3EncodeDLLBufferLength> TMP3EncodeDLLExampleString;

//  Class Definitions

class CMP3EncodeDLL : public CBase
	{
public:
	// new functions
	IMPORT_C static CMP3EncodeDLL* NewL();
	IMPORT_C static CMP3EncodeDLL* NewLC();
	IMPORT_C ~CMP3EncodeDLL();

public: // new functions, example API
	IMPORT_C TVersion Version() const;
	IMPORT_C void ExampleFuncAddCharL(const TChar& aChar);
	IMPORT_C void ExampleFuncRemoveLast();
	IMPORT_C const TPtrC ExampleFuncString() const;

private: // new functions
	CMP3EncodeDLL();
	void ConstructL();

private: // data
	TMP3EncodeDLLExampleString* iString;
	};

#endif  // __MP3ENCODEDLL_H__

