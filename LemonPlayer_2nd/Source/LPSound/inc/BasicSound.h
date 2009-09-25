/*
 ============================================================================
 Name		: BasicSound.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CBasicSound declaration
 ============================================================================
 */

#ifndef BASICSOUND_H
#define BASICSOUND_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <MdaAudioSamplePlayer.h>
#include "MSoundInterface.h"
// CLASS DECLARATION

/**
 *  CBasicSound
 * 
 */
class CBasicSound : public CBase, 
					public MSoundInterface,
					public MMdaAudioPlayerCallback
	{
public:
	~CBasicSound();
	static CBasicSound* NewL();
	static CBasicSound* NewLC();

public:
	//from MSoundInterface
	virtual TInt Play();
	virtual TInt Stop();
	virtual TInt Pause();
	
	virtual void SetVolume(TInt aVolume);
	virtual TInt GetVolume(TInt& aVolume);
	virtual TInt MaxVolume();

	virtual TInt LoadFile(const TDesC& aFileName);

public:
	//from MMdaAudioPlayerCallback
	virtual void MapcInitComplete(TInt aError,
			const TTimeIntervalMicroSeconds& aDuration);
	virtual void MapcPlayComplete(TInt aError);
	
public:
	virtual void SetListerner(MSoundCallBack *aNotify);

private:
	CBasicSound();
	void ConstructL();

private:
	enum TState
		{
		ENotReady,
		EReady,
		EPlaying,
		EPause
		};

	TState iState;
	CMdaAudioPlayerUtility* iMdaPlayer;
	MSoundCallBack *iNotify;
	TInt iVolume;
	TInt iMaxVolume;
	};

#endif // BASICSOUND_H
