//---------------------------------------------------------------------------
// Name:	utils.h
// Desc:	utils header file
// Author:	D.C
// Date:	2007-1-30
//---------------------------------------------------------------------------
#ifndef _UTILS_H_
#define _UTILS_H_

#include <e32std.h>
#include <e32base.h>


void GetFileNameByUrl(const TDesC& aUrl, TDes& aFileName);
void GetFileNameByPath(const TDesC& aFilePath, TDes& aFileName);
void GetFilePathByName(const TDesC& aFileName, TDes& aFilePath);
void GetExtNameFromFileName(const TDesC& aFileName, TDes& aExtName);
TInt GetRandomInterval(TInt aBeginMinutes, TInt64 aSeed);
void GetAppPath(TDes& aAppPath);
void GetResourcePath(TDes& aAppPath);

#endif
