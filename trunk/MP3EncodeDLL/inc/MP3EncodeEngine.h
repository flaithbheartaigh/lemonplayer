/*
 ============================================================================
 Name		: MP3EncodeEngine.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMP3EncodeEngine declaration
 ============================================================================
 */

#ifndef MP3ENCODEENGINE_H
#define MP3ENCODEENGINE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION
class CMP3Encode;
class MMP3EncodeNotifier;
/**
 *  CMP3EncodeEngine
 * 
 */
class CMP3EncodeEngine : public CBase
	{
public:
	// Constructors and destructor
	~CMP3EncodeEngine();
	IMPORT_C static CMP3EncodeEngine* NewL();
	IMPORT_C static CMP3EncodeEngine* NewLC();
	
	IMPORT_C TInt Open(const TDesC& aFileWav, const TDesC& aFileMp3); // opens the stream
	IMPORT_C TInt Open(MMP3EncodeNotifier* aNotifier,const TDesC& aFileMp3);
	IMPORT_C TInt Close();
	
	IMPORT_C TInt EncodeOneFrame();//直接保存到文件
	IMPORT_C TInt GetFileLength();
	IMPORT_C TInt GetFilePosition();

private:
	CMP3EncodeEngine();
	void ConstructL();
	
private:
	CMP3Encode* iMp3Encoder;

	};

#endif // MP3ENCODEENGINE_H
