#ifndef LPSETTING_H_
#define LPSETTING_H_

#include <e32std.h>
#include <e32base.h>
#include "FileOperate.h"

class LPSetting : public MFileOperateNotify
	{
public:
	~LPSetting();
	static LPSetting* GetInstance();
	
public:
	virtual void FileWriteData(RFileWriteStream& aStream);
	virtual void FileReadData(RFileReadStream& aStream);
	
private:
	void ConstructL();
	
	void LoadDataL();
	void SaveDataL();
	
private:
	static LPSetting* iInstance;
	CFileOperate* iOperate;
	};
#endif /*LPSETTING_H_*/
