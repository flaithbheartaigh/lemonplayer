/*
 ============================================================================
 Name		: StreamRecordAdapter.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CStreamRecordAdapter implementation
 ============================================================================
 */

#include "StreamRecordAdapter.h"
#include "MacroUtil.h"

#include "LemonMicro.pan"

const TInt KFrameSizePCM = 4096;
const TInt KFrameCountPCM = 10;

CStreamRecordAdapter::CStreamRecordAdapter():
iFrameSize(KFrameSizePCM), iFrameCount(KFrameCountPCM), iFramePtr(0,0)
	{
	// No implementation required
	iStreamSettings.iChannels=TMdaAudioDataSettings::EChannelsMono;
	iStreamSettings.iSampleRate=TMdaAudioDataSettings::ESampleRate8000Hz;
	
	iInputStatus = ERecorderAdapterNotReady;
	}

CStreamRecordAdapter::~CStreamRecordAdapter()
	{
	if (iInputStream)
		{
		if (iInputStatus != ERecorderAdapterRecording) 
			iInputStream->Stop();
		delete iInputStream;
	    iInputStream=NULL;
		}
	SAFE_DELETE(iStreamBuffer);
	DEBUG(delete iFileLogger;)
	}

CStreamRecordAdapter* CStreamRecordAdapter::NewLC()
	{
	CStreamRecordAdapter* self = new (ELeave)CStreamRecordAdapter();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CStreamRecordAdapter* CStreamRecordAdapter::NewL()
	{
	CStreamRecordAdapter* self=CStreamRecordAdapter::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CStreamRecordAdapter::ConstructL()
	{
	DEBUG(iFileLogger = CFileLogger::NewL(_L("c:\\CStreamRecordAdapter.txt"));)
	
	iInputStream = CMdaAudioInputStream::NewL(*this);
	iDefaultEncoding = iInputStream->DataType();
	
	iStreamBuffer = HBufC8::NewMaxL(iFrameSize * iFrameCount);
	}

void CStreamRecordAdapter::MaiscOpenComplete(TInt aError)
	{
	if (aError==KErrNone) 
		{
		// Input stream opened succesfully, set status
		iInputStatus = ERecorderAdapterRecording;
		// Set the data type (encoding)
		TRAPD(error, iInputStream->SetDataTypeL(iDefaultEncoding));
		PanicIfError(error);

		// set stream input gain to maximum
		iInputStream->SetGain(iInputStream->MaxGain());	
		// set stream priority to normal and time sensitive
		iInputStream->SetPriority(EPriorityNormal, EMdaPriorityPreferenceTime);				
		
		// Emtpy the buffer and issue ReadL() to read the first audio data block, 
		// subsequent calls to ReadL() will be issued 
		// in MMdaAudioInputStreamCallback::MaiscBufferCopied()
		iStreamBuffer->Des().FillZ(iFrameCount * iFrameSize);
		iStreamIdx=0;
		TRAPD(error2, iInputStream->ReadL(GetFrame(iStreamIdx)));
		PanicIfError(error2);
		} 
	else 
		{
		// input stream open failed
		iInputStatus = ERecorderAdapterNotReady;
		DEBUG
		(
		_LIT8(KErrText,"MaiscOpenComplete err:%d");
		TBuf8<30> errInfo;
		errInfo.Format(KErrText,aError);
		iFileLogger->WriteStream(errInfo);
		)
		}	
	}
void CStreamRecordAdapter::MaiscBufferCopied(TInt aError, const TDesC8& aBuffer)
	{
	if (aError==KErrNone) 
		{
		// stop recording if at the end of the buffer
		iStreamIdx++;
		if (iStreamIdx == iFrameCount)
		    {
			iInputStatus = ERecorderAdapterNotReady;
			
		    return;
		  	}		
		// issue ReadL() for next frame		
		TRAPD(error, iInputStream->ReadL(GetFrame(iStreamIdx)));
		PanicIfError(error);
		}
	else if (aError==KErrAbort) 
		{
		// Recording was aborted, due to call to CMdaAudioInputStream::Stop()
		// This KErrAbort will occur each time the Stop() method in this class is executed.
		// Also, MaiscRecordComplete() will be called after exiting this method.
	   iInputStatus = ERecorderAdapterNotReady;
	   DEBUGLOG(iFileLogger,_L8("MaiscBufferCopied KErrAbort"))
		}
	else 
		{
		DEBUG
		(
		_LIT8(KErrText,"MaiscBufferCopied err:%d");
		TBuf8<30> errInfo;
		errInfo.Format(KErrText,aError);
		iFileLogger->WriteStream(errInfo);
		)		
		iInputStatus = ERecorderAdapterNotReady;
		}	
	}
void CStreamRecordAdapter::MaiscRecordComplete(TInt aError)
	{
	iInputStatus = ERecorderAdapterNotReady;
	if (aError==KErrNone) 
		{
		// normal stream closure
		}
	else 
		{
		// completed with error(s)
		}

    // see comments in MaiscBufferCopied() regarding stopping the stream.
    iInputStream->Stop();	
	}

TPtr8& CStreamRecordAdapter::GetFrame(TUint aFrameIdx)
	{
	  __ASSERT_ALWAYS(aFrameIdx < iFrameCount, 
  									User::Panic(_L("AudioStreamEx"), 1));
  								
	  iFramePtr.Set((TUint8*)(iStreamBuffer->Ptr() + (aFrameIdx * iFrameSize)),
  								 iFrameSize,
  								 iFrameSize);
	  return iFramePtr;
	}

void CStreamRecordAdapter::Record()
	{
	if (iInputStatus != ERecorderAdapterNotReady ) 
	{
		return;
	}

	// Open input stream.
	// Upon completion will receive callback in 
	// MMdaAudioInputStreamCallback::MaiscOpenComplete().
	#ifndef __SERIES60_3X__  // Not 3rd Ed
		// Some 2nd Edition, FP2 devices (such as Nokia 6630) require the stream to be
		// reconstructed each time before calling Open() - otherwise the callback
		// never gets called.
		SAFE_DELETE(iInputStream);
		TRAPD(err, iInputStream = CMdaAudioInputStream::NewL(*this));
		PanicIfError(err);
	#endif
		
	iInputStream->Open(&iStreamSettings);	
	}

void CStreamRecordAdapter::Stop()
	{
	if (iInputStatus==ERecorderAdapterRecording) 
		{
		iInputStream->Stop();
		}		
	}
