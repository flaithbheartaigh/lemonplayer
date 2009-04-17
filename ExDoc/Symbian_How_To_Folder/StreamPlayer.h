/*
 ============================================================================
 Name		: StreamPlayer.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CStreamPlayer declaration
 ============================================================================
 */

#ifndef STREAMPLAYER_H
#define STREAMPLAYER_H

// INCLUDES
#include <mda\common\audio.h>
#include <Mda\Client\Utility.h>
#include <Mda\Common\Resource.h>
#include <MdaAudioOutputStream.h>
#include <mmf\server\MmfCodec.h>
#include <mmf\server\mmfdatabuffer.h>
 
 
const TInt KPcmBufferSize = 10000;
 
class CStreamPlayer : public CBase, public MMdaAudioOutputStreamCallback
	{
public:
	CStreamPlayer(void);
	~CStreamPlayer();	
public:
	void PlayL(const TDesC8& aPlayBuffer);
    void Stop();
    TInt Volume(void){ return iVolume; }	
    void SetVolume(TInt aVol);
protected:
   virtual void MaoscOpenComplete(TInt aError);
   virtual void MaoscBufferCopied(TInt aError, const TDesC8& aBuffer);
   virtual void MaoscPlayComplete(TInt aError);
private:
    void ReadFromFromL(TInt aBufferIndex);   
private:
    TInt 	
	iVolume,iReadSize,iCurrIndex,iPlayError;   
	RPointerArray<TDes8> iBuffer;
	CMdaAudioOutputStream* 	iStream;
	TMdaAudioDataSettings 	iSettings;
	HBufC8* 		iPlayBuffer;
	TBool			iPlaying;
	};

#endif // STREAMPLAYER_H
