/*
 ============================================================================
 Name		: MP3EncodeDLL.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : CMP3EncodeDLL DLL source
 ============================================================================
 */

//  Include Files  

#include "MP3EncodeDLL.h"	// CMP3EncodeDLL
#include "MP3EncodeDLL.pan"	  	// panic codes

//  Member Functions

EXPORT_C CMP3EncodeDLL* CMP3EncodeDLL::NewLC()
	{
	CMP3EncodeDLL* self = new (ELeave) CMP3EncodeDLL;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

EXPORT_C CMP3EncodeDLL* CMP3EncodeDLL::NewL()
	{
	CMP3EncodeDLL* self = CMP3EncodeDLL::NewLC();
	CleanupStack::Pop(self);
	return self;
	}

CMP3EncodeDLL::CMP3EncodeDLL()
// note, CBase initialises all member variables to zero
	{
	}

void CMP3EncodeDLL::ConstructL()
	{
	// second phase constructor, anything that may leave must be constructed here
	iString = new (ELeave) TMP3EncodeDLLExampleString;
	}

EXPORT_C CMP3EncodeDLL::~CMP3EncodeDLL()
	{
	delete iString;
	}

EXPORT_C TVersion CMP3EncodeDLL::Version() const
	{
	// Version number of example API
	const TInt KMajor = 1;
	const TInt KMinor = 0;
	const TInt KBuild = 1;
	return TVersion(KMajor, KMinor, KBuild);
	}

EXPORT_C void CMP3EncodeDLL::ExampleFuncAddCharL(const TChar& aChar)
	{
	__ASSERT_ALWAYS(iString != NULL, Panic(EMP3EncodeDLLNullPointer));

	if (iString->Length() >= KMP3EncodeDLLBufferLength)
		{
		User::Leave(KErrTooBig);
		}

	iString->Append(aChar);
	}

EXPORT_C void CMP3EncodeDLL::ExampleFuncRemoveLast()
	{
	__ASSERT_ALWAYS(iString != NULL, Panic(EMP3EncodeDLLNullPointer));

	if (iString->Length() > 0)
		{
		iString->SetLength(iString->Length() - 1);
		}
	}

EXPORT_C const TPtrC CMP3EncodeDLL::ExampleFuncString() const
	{
	__ASSERT_ALWAYS(iString != NULL, Panic(EMP3EncodeDLLNullPointer));
	return *iString;
	}

