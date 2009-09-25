#ifndef MFILEOPERATE_H_
#define MFILEOPERATE_H_

#include <f32file.h>
#include <coemain.h>

class MFileOperateObserver
	{
public:
	virtual void FileOperateError(TInt aError) = 0;
	};

class MFileOperate
	{
public:
	virtual TInt ReadFile(const TDesC& aFileName)  = 0;
	virtual TInt WriteFile(const TDesC& aFileName) = 0;
	void SetObserver(MFileOperateObserver* aObserver) 
		{iObserver = aObserver;};
	void ObserverError(TInt aError)
		{if (iObserver) iObserver->FileOperateError(aError);};
private:
	MFileOperateObserver* iObserver;
	};

#endif /*MFILEOPERATE_H_*/
