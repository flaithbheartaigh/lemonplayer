/*
 ============================================================================
 Name		: SoundManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSoundManager declaration
 ============================================================================
 */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "MSoundInterface.h"
// CLASS DECLARATION
class CUIViewData;
/**
 *  CSoundManager
 * 
 */
class CSoundManager : public CBase,
					  public MSoundCallBack
	{
public:
	// Constructors and destructor
	~CSoundManager();
	static CSoundManager* NewL(CUIViewData *aData);
	static CSoundManager* NewLC(CUIViewData *aData);

public:
	//MSoundCallBack
	virtual void InitComplete();
	virtual void PlayComplete();
	
public:
	void StateChange();
	void VolumeChange();
	TInt LoadFile(const TDesC& aFileName);
	TInt PlayFile();
	
	void SetSoundCallBack(MSoundCallBack *aSoundCallBack)
		{iSoundCallBack = aSoundCallBack;};
	
private:
	CSoundManager(CUIViewData *aData);
	void ConstructL();
	
private:
	CUIViewData *iData;
	MSoundInterface *iPlayer;
	MSoundCallBack *iSoundCallBack;
	TBool iIsLoad;
	};

#endif // SOUNDMANAGER_H
