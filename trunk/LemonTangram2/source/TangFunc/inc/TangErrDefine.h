#ifndef TANGERRDEFINE_H_
#define TANGERRDEFINE_H_



enum TTLErrState
{
	ETLErrNormal = 0,	//普通
	ETLErrWarning,		//提示
	ETLErrSerious ,		//严重退出
};

enum TTLErrInfo
{
	ETLErrNone = 0,
	ETLErrLoadPicture,			//初始化读取图片出错.
	ETLErrLoadPicFileXml,		//读取图片文件xml出错
	ETLErrLoadPicDataXml,		//读取图片数据xml出错
	ETLErrLoadMenu,

	ETLWarnConfigLost,
	ETLWarnLoadPicFileNextDefault,	//读取图片数据XML异常,开始读取默认,waring

	ETLWarnSettingInit,			//设置界面初始化出错
	ETLWarnSettingList,			//设置界面读取设置条出错

	ETLWarnSaveProcess,		//保存进度错误
	ETLWarnResetProcess,	//重置进度错误
	ETLWarnOpenProcess,		//打开进度错误
	ETLWarnSaveScreen,		//屏幕截图错误
};

#define LTERRFUN(a,b) STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->LTError(a,b);
#define LTERR(e,a,b) if (e!=KErrNone) STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->LTError(a,b);
#endif /*TANGERRDEFINE_H_*/
