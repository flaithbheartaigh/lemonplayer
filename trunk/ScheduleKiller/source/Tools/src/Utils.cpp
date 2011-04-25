//---------------------------------------------------------------------------
// Name:	utils.h
// Desc:	utils header file
// Author:	D.C
// Date:	2007-1-30
//---------------------------------------------------------------------------

#include "utils.h"

#include <e32math.h>
#include <e32std.h>
#include <aknutils.h>
#include <bautils.h>
#include <eikapp.h>
#include <apgtask.h>




//从文件路径拆分出文件名
void GetFileNameByUrl(const TDesC& aUrl, TDes& aFileName)
{
	TInt order = aUrl.LocateReverse('/');
	TInt sourceLength = aUrl.Length() - order -1; 
	aFileName = aUrl.Mid(order + 1, sourceLength);
}

//获取随机时间，返回距0时的分钟数
TInt GetRandomInterval(TInt aBeginMinutes, TInt64 aSeed)
{
	TInt randomNumber = Math::Rand(aSeed);
	float currentMinutes = aBeginMinutes;
	TInt interval = (1440 - currentMinutes) * randomNumber/KMaxTInt + currentMinutes;
	return interval;
}

void GetExtNameFromFileName(const TDesC& aFileName, TDes& aExtName)
{
	TInt order = aFileName.LocateReverse('.');
	TInt sourceLength = aFileName.Length() - order -1;
	aExtName = aFileName.Mid(order +1, sourceLength);
	aExtName.LowerCase();
}

void GetFilePathByName(const TDesC& aFileName, TDes& aFilePath)
{
	TInt filePathLength = aFileName.LocateReverse('\\') + 1;
	aFilePath = aFileName.Mid(0, filePathLength);
}

void GetFileNameByPath(const TDesC& aFilePath, TDes& aFileName)
{
	TInt filePathLength = aFileName.LocateReverse('\\') + 1;
	aFileName = aFileName.Mid(filePathLength);
}

void GetAppPath(TDes& aAppPath)
{
#if defined ( EKA2 )
	User::LeaveIfError(CEikonEnv::Static()->FsSession().PrivatePath(aAppPath));
    // insert the drive to the private path
    TParsePtrC parse((CEikonEnv::Static()->EikAppUi()->Application())->AppFullName());
    aAppPath.Insert(0, parse.Drive());
#else
    CompleteWithAppPath(aAppPath);

#endif
#ifdef __WINS__
	aAppPath[0] = 'c';
#endif	
}

void GetResourcePath(TDes& aAppPath)
{
#if defined ( EKA2 )
    TParsePtrC parse((CEikonEnv::Static()->EikAppUi()->Application())->ResourceFileName());
    aAppPath.Insert(0, parse.Drive());
#else
    CompleteWithAppPath(aAppPath);
#endif
#ifdef __WINS__
	aAppPath[0] = 'c';
#endif		
}

