#ifndef MSOUNDINTERFACE_H_
#define MSOUNDINTERFACE_H_

class MSoundCallBack
	{
public:
	virtual void InitComplete() = 0;
	virtual void PlayComplete() = 0;
	};

class MSoundInterface
{
public:
	//play control
	virtual TInt Play() = 0;
	virtual TInt Stop() = 0;
	virtual TInt Pause() = 0;
	
	//sound control
	virtual void SetVolume(TInt aVolume) = 0;
	virtual TInt GetVolume(TInt& aVolume) = 0;
	virtual TInt MaxVolume() = 0;
	
	//file control
	virtual TInt LoadFile(const TDesC& aFileName) = 0;
	
	//notify
	virtual void SetListerner(MSoundCallBack *aNotify) = 0;
};

#endif /*MSOUNDINTERFACE_H_*/
