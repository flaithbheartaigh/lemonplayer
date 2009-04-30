/*
 ============================================================================
 Name		: MP3Encode.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMP3Encode declaration
 ============================================================================
 */

#ifndef MP3ENCODE_H
#define MP3ENCODE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <f32file.h>

#include "MP3EncodeNotifier.h"
// CLASS DECLARATION

/**
 *  CMP3Encode
 * 
 */
class CMP3Encode : public CBase
	{
public:
	// Constructors and destructor
	~CMP3Encode();
	static CMP3Encode* NewL();
	static CMP3Encode* NewLC();
	
private:
	CMP3Encode();
	void ConstructL();
	
public:
	TInt Open(const TDesC& aFileWav, const TDesC& aFileMp3); // opens the stream
	TInt Open(MMP3EncodeNotifier* aNotifier,const TDesC& aFileMp3);
	TInt Close();
	
	TInt EncodeOneFrame();//直接保存到文件
	TInt EncodeOneFrame (TDes &aBuffer);  //保存到buffer里面,未实现
	TInt GetFileLength();
	TInt GetFilePosition();
	
protected:
	TInt CloseMP3 ();
	TInt InitMP3 ();

	int DecodeOneFrameFile();
	int DecodeOneFrameStream();
	
	char* descriptorToStringL(const TDesC8& aDescriptor);
	
private:
	TFileName iFileNameWav;
	TFileName iFileNameMp3;
	char* iCharFileWav;
	char* iCharFileMp3;
//	RFs *iFileSession;
	RFile iFile;

	MMP3EncodeNotifier* iNotifier;
	TBool iUseFile;
	TBool bFileOpened;
	
//#define OUTPUT_BUFFER_SIZE 8192	
//	
//	TInt16 OutputBuffer[2][OUTPUT_BUFFER_SIZE];
//	int	iOutputBufferLength[2];
//	int iOutputBufferCurrent;
	
//	TPtr8 *iInputBuf;
	
	};

#endif // MP3ENCODE_H
