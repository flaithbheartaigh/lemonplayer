/*
 ============================================================================
 Name		: StreamRecordAdapter.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CStreamRecordAdapter declaration
 ============================================================================
 */

#ifndef STREAMRECORDADAPTER_H
#define STREAMRECORDADAPTER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <MdaAudioInputStream.h>
#include <mda\common\audio.h>
#include "RecorderDefine.h"
#include "LPDebug.h"

// CLASS DECLARATION

/**
 *  CStreamRecordAdapter
 * 
 */
class CStreamRecordAdapter : public CBase,public MMdaAudioInputStreamCallback
	{
public:
	// Constructors and destructor

	~CStreamRecordAdapter();
	static CStreamRecordAdapter* NewL();
	static CStreamRecordAdapter* NewLC();

private:
	CStreamRecordAdapter();
	void ConstructL();
	
public:
	//from MMdaAudioInputStreamCallback
	virtual void MaiscOpenComplete(TInt aError);
	virtual void MaiscBufferCopied(TInt aError, const TDesC8& aBuffer);
	virtual void MaiscRecordComplete(TInt aError);
	
public:
	void Record();
	void Stop();
	
private:
	TPtr8& GetFrame(TUint aFrameIdx);
	
private:
	CMdaAudioInputStream* iInputStream;
	TMdaAudioDataSettings iStreamSettings;
	TFourCC iDefaultEncoding;
	TRecorderAdapterStatus iInputStatus;
	
	HBufC8* iStreamBuffer;	
	TPtr8 iFramePtr;
	
	TUint iStreamIdx;
	TUint iFrameSize;
	TUint iFrameCount;
	
	
	
	DEBUG(CFileLogger* iFileLogger;)

	};

#endif // STREAMRECORDADAPTER_H
