#include "LPSetting.h"
#include "MacroUtil.h"

LPSetting* LPSetting::iInstance = NULL;

_LIT(KSettingFile,"c:\\lemonplayer\\set.ini");

LPSetting::~LPSetting()
	{
	SAFE_DELETE(iOperate);
	}

LPSetting* LPSetting::GetInstance()
	{
	if (iInstance == NULL)
		{
		iInstance = new (ELeave) LPSetting;
		iInstance->ConstructL();
		}
	return iInstance;
	}

void LPSetting::ConstructL()
	{
	iOperate = CFileOperate::NewL(this);
	LoadDataL();
	}

void LPSetting::LoadDataL()
	{
	iOperate->ReadFileL(KSettingFile);
	}

void LPSetting::SaveDataL()
	{
	iOperate->WriteFileL(KSettingFile);
	}

void LPSetting::FileWriteData(RFileWriteStream& aStream)
	{}
void LPSetting::FileReadData(RFileReadStream& aStream)
	{}