/*
============================================================================
 Name        : CommonUtils.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CCommonUtils implementation
============================================================================
*/

#include <aknmessagequerydialog.h> 
#include <AknUtils.h>
#include <charconv.h>
#include <utf.h> 
#include <mtmuibas.h>

#include <eikenv.h>
#include <w32std.h>
#include <apgtask.h>
#include <apgcli.h>
#include <Uri16.h>
#include <Uri8.h>
#include <aknnotewrappers.h> 
#include <e32math.h>


//#include "kiwiApp.h"
#include "CommonUtils.h"
#include "logfile.h"


CCommonUtils::CCommonUtils()
{
	// No implementation required
}


CCommonUtils::~CCommonUtils()
{
}

// 将应用程序带到前台
void CCommonUtils::ShowApplication()
{
	//RWsSession aWsSession = CEikonEnv::Static()->WsSession();
	//TApaTaskList taskList(aWsSession);
	//TApaTask aTask = taskList.FindApp(KUidkiwi);
	//aTask.BringToForeground();
}

// 隐藏应用程序
void CCommonUtils::HideApplication()
{
	RWsSession aWsSession = CEikonEnv::Static()->WsSession();
	TApaTask aTask(aWsSession);
	TInt aId = CEikonEnv::Static()->RootWin().Identifier();
	aTask.SetWgId(aId);
	if (aWsSession.GetFocusWindowGroup() == aId)
	{
		aTask.SendToBackground();
	}
}

TThreadId CCommonUtils::StartBroswerApp(const TDesC& aUrl)
{
	TThreadId id(0);
	if(aUrl.Length() <= 0)
		return id;

	const TInt KBrowserUid1 = 0x1020724D;
	const TInt KBrowserUid2 = 0x10008D39;

	RApaLsSession appArcSession;
	User::LeaveIfError(appArcSession.Connect()); // connect to AppArc server

	HBufC* param = HBufC::NewLC( aUrl.Length() + 8 );
	param->Des().Format( _L( "4 %S" ),&aUrl );

	// Wap Browser's constants UId
	TUid browserId( TUid::Uid( KBrowserUid1 ) );

	TApaAppInfo appInfo;
	if( appArcSession.GetAppInfo( appInfo, browserId ) != KErrNone )
	{
		browserId = TUid::Uid( KBrowserUid2 );
	}

	TApaTaskList taskList( CEikonEnv::Static()->WsSession() );
	TApaTask task = taskList.FindApp( browserId );
	if ( task.Exists() )
	{
		HBufC8* param8 = HBufC8::NewLC( param->Length() * 4 );
		param8->Des().Append( *param );
		task.SendMessage( TUid::Uid( 0 ), *param8 ); // Uid is not used
		CleanupStack::PopAndDestroy(); // param8
	}
	else
	{
		appArcSession.StartDocument( *param, browserId, id );
		//	appArcSession.Close();

		//	User::After(2*1000*1000);

		//	TApaTask task = taskList.FindApp( uid );

		//	if ( task.Exists() )
		//	{
		//		task.SendMessage( TUid::Uid(0), *pHtsUrl8 ); // UID is not used
		//	}
	}

	appArcSession.Close();
	CleanupStack::PopAndDestroy(); // param
	return id;
}

void CCommonUtils::CloseApp(const TUid& aUid )
{
	TApaTaskList taskList( CEikonEnv::Static()->WsSession() );
	TApaTask task = taskList.FindApp( aUid );

	if ( task.Exists() )
	{
		//task.EndTask();	
		task.KillTask();
	}
}

HBufC* CCommonUtils::UrlEncodeL(const TDesC& aUrl)
{
	_LIT(KFormatCode, "%%%02x");

	if (!aUrl.Length())
	{
		return NULL;
	}

	TBufC<100> sDontEncode = _L("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!-_.()*;/?:@&=+$[]!\\'()~");

	// Alloc to the maximum size of URL if every char are encoded
	HBufC *sEncoded = HBufC::NewL(aUrl.Length() * 3);

	// Parse a the chars in the url
	for (TInt i=0; i<aUrl.Length(); i++)
	{
		TChar cToFind = aUrl[i];
		if (KErrNotFound == sDontEncode.Locate(cToFind) )
		{
			// Char not found encode it.
			sEncoded->Des().AppendFormat(KFormatCode, cToFind);
		}
		else
		{
			// char found just copy it
			sEncoded->Des().Append(cToFind);
		}
	}

	// Reallocate to the real size of the encoded url.
	sEncoded->ReAllocL(sEncoded->Length());

	return sEncoded;
}

HBufC* CCommonUtils::UrlDecodeL(const TDesC& aUrl)
{
	// 找到 &amp; ,将 &amp; 替换成 &
	_LIT(KAmpStr, "&amp;");

	if (aUrl.Length() == 0)
		return NULL;

	TPtrC ptrcUrl = aUrl;

	// 存放Decode后的返回url
	HBufC *pRetUrl = HBufC::NewLC(aUrl.Length());
	// 用于修改pRetUrl
	TPtr ptrRetUrl = pRetUrl->Des();

	TInt ampPos = ptrcUrl.Find(KAmpStr);
	while (ampPos != KErrNotFound)
	{
		ptrRetUrl.Append(ptrcUrl.Left(ampPos));
		ptrRetUrl.Append('&');

		ptrcUrl.Set( ptrcUrl.Right(ptrcUrl.Length()-ampPos-KAmpStr().Length()) );

		ampPos = ptrcUrl.Find(KAmpStr);
	}

	if (ptrcUrl.Length() != 0)
	{
		ptrRetUrl.Append(ptrcUrl);
	}

	CleanupStack::Pop(pRetUrl);
	return pRetUrl;
}

TBool CCommonUtils::IsDirectoryExists(const TDesC &aDirName)
{
	CDir *dirList = NULL;
	RFs &aFs = CEikonEnv::Static()->FsSession();

	TInt err = aFs.GetDir(aDirName, KEntryAttMaskSupported, ESortByName, dirList);

	delete dirList;
	dirList = NULL;

	if ( err == KErrPathNotFound )
	{
		return EFalse;
	}
	else
	{
		return ETrue;
	}
}

void CCommonUtils::GlobalLogL(const TDesC &aLogText)
{
	TFileName logFileName;

#ifdef __WINS__
	logFileName.Copy(_L("c:\\GlobalLog.txt"));
#else
	logFileName.Copy(_L("GlobalLog.txt"));
	CompleteWithAppPath(logFileName);
#endif

	_LIT(KHtsLogFormatStr16, "%S - %S \r\n");
	TTime currTime;
	TBuf<32> timeStr;
	currTime.HomeTime();
	currTime.FormatL(timeStr, _L("%1-%2-%3 %H:%T:%S"));

	HBufC *pLogTxt = HBufC::NewLC(
		KHtsLogFormatStr16().Length()
		+aLogText.Length()
		+timeStr.Length());
	pLogTxt->Des().Format(KHtsLogFormatStr16, &timeStr, &aLogText);

	HBufC8 *pUtf8LogTxt = CnvUtfConverter::ConvertFromUnicodeToUtf8L(*pLogTxt);
	CleanupStack::PushL(pUtf8LogTxt);

	CLogFile::StaticLogL(logFileName, *pUtf8LogTxt);

	CleanupStack::PopAndDestroy(2, pLogTxt);
}

void CCommonUtils::GlobalLogL(const TDesC8 &aLogText)
{
	TFileName logFileName;

#ifdef __WINS__
	logFileName.Copy(_L("c:\\GlobalLog.txt"));
#else
	logFileName.Copy(_L("GlobalLog.txt"));
	CompleteWithAppPath(logFileName);
#endif

	TTime currTime;
	TBuf<32> timeStr;
	currTime.HomeTime();
	currTime.FormatL(timeStr, _L("%1-%2-%3 %H:%T:%S"));

	HBufC8 *pCurrTime = CnvUtfConverter::ConvertFromUnicodeToUtf8L(timeStr);
	CleanupStack::PushL(pCurrTime);

	_LIT8(KHtsLogFormatStr8, "%S - %S \r\n");
	HBufC8 *pLogTxt = HBufC8::NewLC(
		KHtsLogFormatStr8().Length()
		+aLogText.Length()
		+pCurrTime->Length());
	pLogTxt->Des().Format(KHtsLogFormatStr8, pCurrTime, &aLogText);

	CLogFile::StaticLogL(logFileName, *pLogTxt);

	CleanupStack::PopAndDestroy(2, pCurrTime); //pLogTxt, pCurrTime
}

void CCommonUtils::GlobalLogL(const TDesC &aDescription, TInt aNumber)
{
	_LIT(KGlobalLogNumberOutputText, "%S:%d");

	// +32 包括KGlobalLogNumberOutputText长度和大数字长度
	HBufC *outputText = HBufC::NewLC(aDescription.Length()+32); 
	outputText->Des().Format(KGlobalLogNumberOutputText, &aDescription, aNumber);

	CCommonUtils::GlobalLogL(*outputText);

	CleanupStack::PopAndDestroy(outputText);
}

void CCommonUtils::GlobalLogL(const TDesC &aDescription, const TDesC &aLogText)
{
	HBufC *outputText = HBufC::NewLC(aDescription.Length()+aLogText.Length()+1);
	outputText->Des().Copy(aDescription);
	outputText->Des().Append(':');
	outputText->Des().Append(aLogText);

	CCommonUtils::GlobalLogL(*outputText);

	CleanupStack::PopAndDestroy(outputText);
}

void CCommonUtils::GlobalLogL(const TDesC8 &aDescription, const TDesC8 &aLogText)
{
	HBufC8 *outputText = HBufC8::NewLC(aDescription.Length()+aLogText.Length()+1);
	outputText->Des().Copy(aDescription);
	outputText->Des().Append(':');
	outputText->Des().Append(aLogText);

	CCommonUtils::GlobalLogL(*outputText);

	CleanupStack::PopAndDestroy(outputText);
}

void CCommonUtils::GlobalLogL(const TDesC &aDescription, TDateTime aTime)
{
	TTime timeLocal(aTime);
	TBuf<32> timeStr;
	timeLocal.FormatL(timeStr, _L("%1-%2-%3 %H:%T:%S"));

	CCommonUtils::GlobalLogL(aDescription, timeStr);
}


//HBufC* CCommonUtils::GetTcpCommandIdNameL(TCommandId aId)
//{
//	HBufC *pRetStr = GetTcpCommandIdNameLC(aId);
//	CleanupStack::Pop(pRetStr);
//	return pRetStr;
//}

//HBufC* CCommonUtils::GetTcpCommandIdNameLC(TCommandId aId)
//{
//	HBufC *pRetStr = NULL;
//	switch (aId)
//	{
//	    case ECommandNone:
//			pRetStr = (_L("ECommandNone")).AllocL();
//	        break;
//		case ELogin:
//			pRetStr = (_L("ELogin")).AllocL();
//			break;			
//		case EGetVerifyCode:
//			pRetStr = (_L("EGetVerifyCode")).AllocL();
//			break;
//		case ENewUserRegister:
//			pRetStr = (_L("ENewUserRegister")).AllocL();
//			break;
//		case ESendHeartThrob:
//			pRetStr = (_L("ESendHeartThrob")).AllocL();
//			break;
//		case ESendRecommend:
//			pRetStr = (_L("ESendRecommend")).AllocL();
//			break;
//		case ERegisterMode2:
//			pRetStr = (_L("ERegisterMode2")).AllocL();
//			break;
//		case EConfirmRegister2:
//			pRetStr = (_L("EConfirmRegister2")).AllocL();
//			break;
//		case EConfirmLogin:
//			pRetStr = (_L("EConfirmLogin")).AllocL();
//			break;
//		case EReturnUniqueId:
//			pRetStr = (_L("EReturnUniqueId")).AllocL();
//			break;
//		case ESendMessage:
//			pRetStr = (_L("ESendMessage")).AllocL();
//			break;
//		case ENewVersionPrompt:
//			pRetStr = (_L("ENewVersionPrompt")).AllocL();
//			break;	
//		case ESendSuggest:
//			pRetStr = (_L("ESendSuggest")).AllocL();
//			break;	
//		case ERequestSetting:
//			pRetStr = (_L("ERequestSetting")).AllocL();
//			break;	
//		case EReturnSetting:
//			pRetStr = (_L("EReturnSetting")).AllocL();
//			break;
//		case ESendSetting:
//			pRetStr = (_L("ESendSetting")).AllocL();
//			break;
//		case ERegisterByPwd:
//			pRetStr = (_L("ERegisterByPwd")).AllocL();
//			break;
//		case EUploadContact:
//			pRetStr = (_L("EUploadContact")).AllocL();
//			break;
//		case EDownloadContact:
//			pRetStr = (_L("EDownloadContact")).AllocL();
//			break;
//		case EReturnContact:
//			pRetStr = (_L("EReturnContact")).AllocL();
//			break;
//		case EQueryServicePoint:
//			pRetStr = (_L("EQueryServicePoint")).AllocL();
//			break;
//		case EReturnServicePoint:
//			pRetStr = (_L("EReturnServicePoint")).AllocL();
//			break;
//		case EQueryGetPointMethod:
//			pRetStr = (_L("EQueryGetPointMethod")).AllocL();
//			break;
//		case EReturnGetPointMethod:
//			pRetStr = (_L("EReturnGetPointMethod")).AllocL();
//			break;
//		case EGetOnlineContactSms:
//			pRetStr = (_L("EGetOnlineContactSms")).AllocL();
//			break;
//		case EGetRobots:
//			pRetStr = (_L("EGetRobots")).AllocL();
//			break;
//		case EReturnRobots:
//			pRetStr = (_L("EReturnRobots")).AllocL();
//			break;
//		case ERequestWebPage:
//			pRetStr = (_L("ERequestWebPage")).AllocL();
//			break;
//		case EReturnWebPage:
//			pRetStr = (_L("EReturnWebPage")).AllocL();
//			break;
//
//		case ESuccess:
//			pRetStr = (_L("ESuccess")).AllocL();
//			break;
//		case EServerBusy:
//			pRetStr = (_L("EServerBusy")).AllocL();
//			break;
//		case EMobileNotRegister:
//			pRetStr = (_L("EMobileNotRegister")).AllocL();
//			break;
//		case EServerMature:
//			pRetStr = (_L("EServerMature")).AllocL();
//			break;
//		case EServicePointNotEnough:
//			pRetStr = (_L("EServicePointNotEnough")).AllocL();
//			break;
//		case ERightNotEnough:
//			pRetStr = (_L("ERightNotEnough")).AllocL();
//			break;
//		case EStateError:
//			pRetStr = (_L("EStateError")).AllocL();
//			break;
//		case EUndentifiedMessage:
//			pRetStr = (_L("EUndentifiedMessage")).AllocL();
//			break;
//		case EOptionError:
//			pRetStr = (_L("EOptionError")).AllocL();
//			break;
//		case EBeKickedOut:
//			pRetStr = (_L("EBeKickedOut")).AllocL();
//			break;
//		case EExtendError:
//			pRetStr = (_L("EExtendError")).AllocL();
//			break;
//		case EInnerError:
//			pRetStr = (_L("EInnerError")).AllocL();
//			break;
//		case EHttpOneStepReg:
//			pRetStr = (_L("EHttpOneStepReg")).AllocL();
//			break;
//		case EHttpOneStepRegFail:
//			pRetStr = (_L("EHttpOneStepRegFail")).AllocL();
//			break;
//		case EHttpLogout:
//			pRetStr = (_L("EHttpLogout")).AllocL();
//			break;
//		case EHttpLogoutEnd:
//			pRetStr = (_L("EHttpLogoutEnd")).AllocL();
//			break;
//		case EHttpReadMessage:
//			pRetStr = (_L("EHttpReadMessage")).AllocL();
//			break;
//		case EHttpReadMessageEnd:
//			pRetStr = (_L("EHttpReadMessageEnd")).AllocL();
//			break;
//		case ESendMessageWithType:
//			pRetStr = (_L("ESendMessageWithType")).AllocL();
//			break;
//		case EHttpError:
//			pRetStr = (_L("EHttpError")).AllocL();
//			break;
//		case EHttpMologRequest:
//			pRetStr = (_L("EHttpMologRequest")).AllocL();
//			break;
//		case EHttpMologResponse:
//			pRetStr = (_L("EHttpMologResponse")).AllocL();
//			break;
//	    default:
//			pRetStr = (_L("other command id")).AllocL();
//	}
//
//	CleanupStack::PushL(pRetStr);
//	return pRetStr;
//}
//
//HBufC* CCommonUtils::GetSocketEngineStateNameL(TSocketEngineState aState)
//{
//	HBufC *pRetStr = GetSocketEngineStateNameLC(aState);
//	CleanupStack::Pop(pRetStr);
//	return pRetStr;
//}
//HBufC* CCommonUtils::GetSocketEngineStateNameLC(TSocketEngineState aState)
//{
//	HBufC *pRetStr = NULL;
//
//	switch (aState)
//	{
//	    case ENotConnected:
//			pRetStr = (_L("ENotConnected")).AllocL();
//	        break;
//		case EConnecting:
//			pRetStr = (_L("EConnecting")).AllocL();
//			break;
//		case EConnected:
//			pRetStr = (_L("EConnected")).AllocL();
//			break;
//		case ELookingUp:
//			pRetStr = (_L("ELookingUp")).AllocL();
//			break;
//		case EConnectTimeOut:
//			pRetStr = (_L("EConnectTimeOut")).AllocL();
//			break;
//		case ESending:
//			pRetStr = (_L("ESending")).AllocL();
//			break;
//		case ESended:
//			pRetStr = (_L("ESended")).AllocL();
//			break;
//		case ESendError:
//			pRetStr = (_L("ESendError")).AllocL();
//			break;
//		case ESendTimeOut:
//			pRetStr = (_L("ESendTimeOut")).AllocL();
//			break;
//		case EWaiting:
//			pRetStr = (_L("EWaiting")).AllocL();
//			break;
//		case EReadError:
//			pRetStr = (_L("EReadError")).AllocL();
//			break;
//		case EDisconnected:
//			pRetStr = (_L("EDisconnected")).AllocL();
//			break;
//	    default:
//	        pRetStr = (_L("other state")).AllocL();
//	}
//
//	CleanupStack::PushL(pRetStr);
//	return pRetStr;
//}

//保存文件不带路径的
//void CCommonUtils::SaveToFile(const TDesC &aStr,const TDesC& aFileName)
//{
//	HBufC8* tmp = ConvertToUTF8FromUnicode(aStr);
//	CleanupStack::PushL(tmp);
//	SaveToFile(tmp->Des(),aFileName);
//
//	CleanupStack::PopAndDestroy(tmp);
//}
//void CCommonUtils::SaveToFile(const TDesC8 &aStr,const TDesC& aFileName)
//{
//	TFileName fn;	
//#ifdef __WINS__
//	fn.Copy(_L("C:\\"));
//	fn.Append(aFileName);
//#else
//	fn.Copy(aFileName);
//	CompleteWithAppPath(fn);
//#endif	
//
//	SaveToFile(aStr,fn);
//}
//
//保存文件全路径的	
//void CCommonUtils::SaveToFile(const TDesC &aStr,const TFileName& aPathFileName)
//{
//	HBufC8* tmp = ConvertToUTF8FromUnicode(aStr);
//	CleanupStack::PushL(tmp);
//
//	SaveToFile(tmp->Des(),aPathFileName);
//
//	CleanupStack::PopAndDestroy(tmp);
//}
//
//void CCommonUtils::SaveToFile(const TDesC8 &aStr,const TFileName& aPathFileName)
//{
//	RFile aFile;
//	RFs aFs;
//	User::LeaveIfError(aFs.Connect());	
//
//	TInt aRes = aFile.Open(aFs, aPathFileName, EFileWrite | EFileShareAny | EFileStream);
//	if (aRes == KErrNotFound)
//	{
//		aFile.Create(aFs, aPathFileName, EFileWrite | EFileShareAny | EFileStream);			
//	}
//	aFile.SetSize(0);
//	aFile.Write(aStr);
//	aFile.Close();
//	aFs.Close();
//}
//
//读文件不带路径的
//HBufC* CCommonUtils::ReadFromFile(const TDesC& aFileName)
//{
//	HBufC8* tmp = Read8FromFile(aFileName);
//	if (tmp)
//	{
//		CleanupStack::PushL(tmp);
//		HBufC* ret = ConvertToUnicodeFromUTF8(tmp->Des());
//		CleanupStack::PopAndDestroy(tmp);
//		return ret;
//	}
//	else
//		return NULL;
//	
//}
//
//HBufC8* CCommonUtils::Read8FromFile(const TDesC& aFileName)
//{
//	TFileName fn;	
//#ifdef __WINS__
//	fn.Copy(_L("C:\\"));
//	fn.Append(aFileName);
//#else
//	fn.Copy(aFileName);
//	CompleteWithAppPath(fn);
//#endif	
//
//	return Read8FromFile(fn);
//}
//
//读文件全路径的
//HBufC*  CCommonUtils::ReadFromFile(const TFileName& aPathFileName)
//{
//	HBufC8* tmp = Read8FromFile(aPathFileName);
//	if (tmp)
//	{
//		CleanupStack::PushL(tmp);
//		HBufC* ret = ConvertToUnicodeFromUTF8(tmp->Des());		
//		CleanupStack::PopAndDestroy(tmp);
//		return ret;
//	}
//	else
//		return NULL;
//}
//
//HBufC8* CCommonUtils::Read8FromFile(const TFileName& aPathFileName)
//{
//	RFile aFile;
//	RFs aFs;
//	User::LeaveIfError(aFs.Connect());
//
//	TInt aRes = aFile.Open(aFs, aPathFileName, EFileRead| EFileShareAny );
//	if (aRes == KErrNotFound)
//	{
//		aFs.Close();
//		return NULL;
//	}
//
//	TInt size;		
//	HBufC8* tmp = NULL;
//	if (aFile.Size(size) == KErrNone)
//	{
//		tmp = HBufC8::NewL(size + 10);
//		aFile.Read(0,tmp->Des(),size);
//	}	
//
//	aFile.Close();
//	aFs.Close();
//
//	return tmp;
//}
//
TBool CCommonUtils::HexToDec(const TDesC& aHexDes,TInt& aDec)
{
	TInt i,mid; 
	TInt len = aHexDes.Length();//lstrlen( aHexDes ); 

	//if( len > 9 )//#00ff00ff? 
	//	return EFalse; 

	mid = 0; aDec = 0; 
	for( i = 0;i < len; i++ ) 
	{ 
		if( (aHexDes.Ptr())[i]>='0' && (aHexDes.Ptr())[i]<='9' ) 
		{
			mid = (aHexDes.Ptr())[i]-'0'; 
		}
		else if( (aHexDes.Ptr())[i]>='a'&& (aHexDes.Ptr())[i]<='f' ) 
		{
			mid = (aHexDes.Ptr())[i] -'a' +10; 
		}
		else if( (aHexDes.Ptr())[i]>='A'&& (aHexDes.Ptr())[i]<='F' ) 
		{
			mid = (aHexDes.Ptr())[i] -'A' +10;
		}
		else if ((aHexDes.Ptr())[i] == '#') 
		{
			continue;
		}
		else
		{
			return EFalse; 
		}

		mid <<= ((len-i-1)<<2); 
		aDec |= mid; 

	} 
	return ETrue; 


}
CDesCArray* CCommonUtils::SplitText(const TDesC& aText,const char& aSplitChar)
{
	CDesCArray* tmpArray = new(ELeave) CDesCArrayFlat(5);
	CleanupStack::PushL(tmpArray);

	TInt len = aText.Length();
	TBuf<100> tmp;
	for ( TInt i = 0; i < len ; i ++)
	{
		if(aText[i] == aSplitChar)
		{
			tmp.TrimAll();
			tmpArray->AppendL(tmp);
			tmp.Zero();
		}
		else
			tmp.Append(aText[i]);		
	}
	if (tmp.Length() > 0 )
	{
		tmp.TrimAll();
		tmpArray->AppendL(tmp);
	}	

	CleanupStack::Pop(tmpArray);
	return tmpArray;
}


TInt CCommonUtils::StrToInt(const TDesC &aStr,TRadix aRadix)
{
	TLex a(aStr);
	TUint num;
	if (a.Val(num,aRadix) == KErrNone)
		return num;
	else
		return -1;
}

TInt CCommonUtils::StrToInt(const TDesC8 &aStr,TRadix aRadix)
{
	TLex8 a(aStr);
	TUint num;
	if (a.Val(num,aRadix) == KErrNone)
		return num;
	else
		return -1;
}

TReal32 CCommonUtils::StrToFloat(const TDesC &aStr,TChar aPoint)
{
	TLex a(aStr);
	TReal32 num;
	if (a.Val(num,aPoint) == KErrNone)
		return num;
	else
		return -1;
}

TReal32 CCommonUtils::StrToFloat(const TDesC8 &aStr,TChar aPoint)
{
	TLex8 a(aStr);
	TReal32 num;
	if (a.Val(num,aPoint) == KErrNone)
		return num;
	else
		return -1;
}

//将Utf8转换成Unicode
HBufC16* CCommonUtils::ConvertToUnicodeFromUTF8(const TDesC8& aStr)
{
	HBufC16* ret = HBufC16::NewLC(aStr.Length());		

	CnvUtfConverter* Converter = new (ELeave) CnvUtfConverter();
	TPtr ptr = ret->Des();
	Converter->ConvertToUnicodeFromUtf8(ptr,aStr);
	delete Converter;

	CleanupStack::Pop(ret);
	return ret;	
}

//将Unicode转换成Utf8 	
HBufC8* CCommonUtils::ConvertToUTF8FromUnicode(const TDesC& aStr)
{
//	HBufC8* ret = HBufC8::NewLC(aStr.Length());		
	HBufC8* ret = HBufC8::NewLC(aStr.Length()*3);		
	CnvUtfConverter* Converter = new (ELeave) CnvUtfConverter();
	TPtr8 ptr = ret->Des();
	Converter->ConvertFromUnicodeToUtf8(ptr,aStr);
	delete Converter;

	CleanupStack::Pop(ret);
	return ret;	
}

//
//将中文字符转换成Unicode	
HBufC16* CCommonUtils::ConvertToUnicodeFromGBK(const TText8* aStr)
{	
	CCnvCharacterSetConverter* converter = CCnvCharacterSetConverter::NewLC();

	if( converter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGbk,CEikonEnv::Static()->FsSession()) != CCnvCharacterSetConverter::EAvailable)
	{
		delete converter;
		return NULL;
	}

	//TText8  *str = (TText8*)"诺基亚7650C";
	TInt state= CCnvCharacterSetConverter::KStateDefault;

	TPtrC8 source( aStr );
	HBufC* ret = HBufC::NewLC( source.Length() );
	TPtr16 ptr = ret->Des();
	converter->ConvertToUnicode(ptr, source, state);
	CleanupStack::Pop(ret);

	return ret;
}

HBufC8* CCommonUtils::UrlEncodeL(const TDesC8& aUrl)
{
	_LIT8(KFormatCode8, "%%%02x");

	if (!aUrl.Length())
	{
		return KNullDesC8().AllocL();;
	}

	TBufC8<100> sDontEncode = _L8("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!-_.()*;/?:@&=+$[]!\\'()~");

	// Alloc to the maximum size of URL if every char are encoded
	HBufC8 *sEncoded = HBufC8::NewL(aUrl.Length() * 3);

	// Parse a the chars in the url
	for (TInt i = 0; i < aUrl.Length(); i++)
	{
		TChar cToFind = aUrl[i];
		if (KErrNotFound == sDontEncode.Locate(cToFind) )
		{
			// Char not found encode it.
			sEncoded->Des().AppendFormat(KFormatCode8, cToFind);
		}
		else
		{
			// char found just copy it
			sEncoded->Des().Append(cToFind);
		}
	}

	// Reallocate to the real size of the encoded url.
	sEncoded->ReAllocL(sEncoded->Length());

	return sEncoded;
}

HBufC* CCommonUtils::ConvertUrlL(const TDesC& aSrcUrl, const TDesC& aRootUrl)
	{
	TBuf<8> http;
	_LIT( KHTTPProtocol, "http://" );
	http.Copy(aSrcUrl.Left(7) );
	http.LowerCase();
	
	HBufC* url;
	HBufC* iUrl;
			
	if(http.Compare(KHTTPProtocol) == 0)
		{
		url = aSrcUrl.AllocL();
		}
	else
		{
		TInt pos = aRootUrl.LocateReverse('/');
		if (pos==(aRootUrl.Length()-1))
		{
			//以'/'结尾的url
			iUrl = HBufC::NewLC(aRootUrl.Length());
			iUrl->Des().Append(aRootUrl);
		}
		else if(pos < 7)
		{
			//没有'/'结尾,且没有文件目录的url
			iUrl = HBufC::NewLC(aRootUrl.Length()+1);
			iUrl->Des().Append(aRootUrl);
			iUrl->Des().Append('/');
		}
		else
			{
			//文件url
			iUrl = HBufC::NewLC(aRootUrl.Left(pos+1).Length());
			iUrl->Des().Append(aRootUrl.Left(pos+1));
			}
		url = HBufC::NewL(iUrl->Length()+aSrcUrl.Length());
		url->Des().Append(*iUrl);
		url->Des().Append(aSrcUrl);
						
		CleanupStack::PopAndDestroy(iUrl);
		}
		
	return url;
	}

//void CCommonUtils::ConvertUrlToL(const TDesC& aDestUrl, HBufC** aUrl)
//	{
//	TBuf<8> http;
//	_LIT( KHTTPProtocol, "http://" );
//	http.Copy(aDestUrl.Left(7) );
//	http.LowerCase();
//	
////	HBufC* url;
//	HBufC* iUrl;
//	
//	HBufC* aRootUrl = (*aUrl)->AllocLC();
//	
//	//是否\开头
//	TInt start = aDestUrl.Locate('/')==0?0:1;
//	
//	if(*aUrl)
//		{
//		delete (*aUrl);
//		*aUrl = NULL;
//		}
//	
//			
//	if(http.Compare(KHTTPProtocol) == 0)
//		{
//		*aUrl = aDestUrl.AllocL();
//		}
//	else
//		{
//		if (start)
//			{
//			// 不以/开头
//		TInt pos = aRootUrl->LocateReverse('/');
//		if (pos==(aRootUrl->Length()-1))
//		{
//			//以'/'结尾的url
//			iUrl = HBufC::NewLC(aRootUrl->Length());
//			iUrl->Des().Append(*aRootUrl);
//		}
//		else if(pos < 7)
//		{
//			//没有'/'结尾,且没有文件目录的url
//			iUrl = HBufC::NewLC(aRootUrl->Length()+1);
//			iUrl->Des().Append(*aRootUrl);
//			iUrl->Des().Append('/');
//		}
//		else
//			{
//			//文件url
//			iUrl = HBufC::NewLC(aRootUrl->Left(pos+1).Length());
//			iUrl->Des().Append(aRootUrl->Left(pos+1));
//			}
//		*aUrl = HBufC::NewL(iUrl->Length()+aDestUrl.Length());
//		(*aUrl)->Des().Append(*iUrl);
//		(*aUrl)->Des().Append(aDestUrl);
//			}
//		else
//			{
//			// /开头
//			TInt pos = aRootUrl->Right(aRootUrl->Length()-7).Locate('/');
//					if (pos==KErrNotFound)
//						{
//						//没有'/'结尾
//						iUrl = aRootUrl->AllocLC();
//						}
//					else
//						{
//						iUrl = aRootUrl->Left(pos+7).AllocLC();
//						}
//					
//					*aUrl = HBufC::NewL(iUrl->Length()+aDestUrl.Length());
//					(*aUrl)->Des().Append(*iUrl);
//					(*aUrl)->Des().Append(aDestUrl);
//			}
//						
//		CleanupStack::PopAndDestroy(iUrl);
//		}
//	CleanupStack::PopAndDestroy(aRootUrl);
//	}
void CCommonUtils::ConvertUrlToL(const TDesC& aDestUrl, HBufC** aUrl)
	{
	TBuf<8> http;
	_LIT( KHTTPProtocol, "http://" );
	http.Copy(aDestUrl.Left(7) );
	http.LowerCase();
	
//	HBufC* url;
	HBufC* iUrl;
	
	HBufC* aRootUrl = (*aUrl)->AllocLC();
	
		
	if(*aUrl)
		{
		delete (*aUrl);
		*aUrl = NULL;
		}
	
			
	if(http.Compare(KHTTPProtocol) == 0)
		{
		*aUrl = aDestUrl.AllocL();
		}
	else
		{
		//是否\开头
		TBool start = aDestUrl.Locate('/')==0?ETrue:EFalse;		
		
		TUriParser16 parser;
		parser.Parse(*aRootUrl);
		iUrl = parser.Extract(EUriHost).AllocLC();
						
		if (start)
			{
			// /开头
			*aUrl = HBufC::NewL(iUrl->Length()+aDestUrl.Length()+7);
			(*aUrl)->Des().Append(KHTTPProtocol);
			(*aUrl)->Des().Append(*iUrl);
			(*aUrl)->Des().Append(aDestUrl);			
			}
		else
			{
			// 不以/开头	
			HBufC *iPath = parser.Extract(EUriPath).AllocL();
			TInt iPos =  iPath->LocateReverse('/')+1;
			HBufC *iDir = HBufC::NewL(iPos);
			iDir->Des().Append(iPath->Left(iPos));
			
			*aUrl = HBufC::NewL(iUrl->Length()+iDir->Length()+ aDestUrl.Length()+7);
			(*aUrl)->Des().Append(KHTTPProtocol);
			(*aUrl)->Des().Append(*iUrl);
			(*aUrl)->Des().Append(*iDir);
			(*aUrl)->Des().Append(aDestUrl);
			
			delete iDir;
			delete iPath;
			}
						
		CleanupStack::PopAndDestroy(iUrl);
		}
	CleanupStack::PopAndDestroy(aRootUrl);
	}

void CCommonUtils::ConvertUrlToL8(const TDesC8& aDestUrl, HBufC8** aUrl)
	{
	TBuf8<8> http;
	_LIT8( KHTTPProtocol, "http://" );
	http.Copy(aDestUrl.Left(7) );
	http.LowerCase();
	
//	HBufC* url;
	HBufC8* iUrl;
	
	HBufC8* aRootUrl = (*aUrl)->AllocLC();
	
		
	if(*aUrl)
		{
		delete (*aUrl);
		*aUrl = NULL;
		}
	
			
	if(http.Compare(KHTTPProtocol) == 0)
		{
		*aUrl = aDestUrl.AllocL();
		}
	else
		{
		//是否\开头
		TBool start = aDestUrl.Locate('/')==0?ETrue:EFalse;		
		
		TUriParser8 parser;
		parser.Parse(*aRootUrl);
		iUrl = parser.Extract(EUriHost).AllocLC();
						
		if (start)
			{
			// /开头
			*aUrl = HBufC8::NewL(iUrl->Length()+aDestUrl.Length()+7);
			(*aUrl)->Des().Append(KHTTPProtocol);
			(*aUrl)->Des().Append(*iUrl);
			(*aUrl)->Des().Append(aDestUrl);			
			}
		else
			{
			// 不以/开头	
			HBufC8 *iDir;
			HBufC8 *iPath = parser.Extract(EUriPath).AllocL();
			TInt iPos =  iPath->LocateReverse('/')+1;
			if (iPos!=0)
				{
				iDir = HBufC8::NewL(iPos);
				iDir->Des().Append(iPath->Left(iPos));
				}
			else
				{
				iDir = HBufC8::NewL(1);
				iDir->Des().Append('/');
				}
			
			*aUrl = HBufC8::NewL(iUrl->Length()+iDir->Length()+ aDestUrl.Length()+7);
			(*aUrl)->Des().Append(KHTTPProtocol);
			(*aUrl)->Des().Append(*iUrl);
			(*aUrl)->Des().Append(*iDir);
			(*aUrl)->Des().Append(aDestUrl);
			
			delete iDir;
			delete iPath;
			}
						
		CleanupStack::PopAndDestroy(iUrl);
		}
	CleanupStack::PopAndDestroy(aRootUrl);
	}

void CCommonUtils::ConvertUrlFromRootL(const TDesC& aDestUrl, HBufC** aUrl)
	{
	TBuf<8> http;
	_LIT( KHTTPProtocol, "http://" );
	http.Copy(aDestUrl.Left(7) );
	http.LowerCase();
	
	HBufC* iUrl;
	
	HBufC* aRootUrl = (*aUrl)->AllocLC();
	//是否\开头
	TInt start = aDestUrl.Locate('/')==0?0:1;
	
	if(*aUrl)
		{
		delete (*aUrl);
		*aUrl = NULL;
		}
	
			
	if(http.Compare(KHTTPProtocol) == 0)
		{
		*aUrl = aDestUrl.AllocL();
		}
	else
		{
		TInt pos = aRootUrl->Right(aRootUrl->Length()-7).Locate('/');
		if (pos==KErrNotFound)
			{
			//没有'/'结尾
			iUrl = aRootUrl->AllocLC();
			}
		else
			{
			iUrl = aRootUrl->Left(pos+7).AllocLC();
			}
		
		*aUrl = HBufC::NewL(iUrl->Length()+aDestUrl.Length()+start);
		(*aUrl)->Des().Append(*iUrl);
		if (start==1)
			{
			(*aUrl)->Des().Append('/');
			}
		(*aUrl)->Des().Append(aDestUrl);
						
		CleanupStack::PopAndDestroy(iUrl);
		}
	CleanupStack::PopAndDestroy(aRootUrl);
	}

HBufC8* CCommonUtils::ConvertDesTo8(const TDesC& aStr)
	{
	HBufC8* iStr;
	iStr = HBufC8::NewL(aStr.Length());
	iStr->Des().Append(aStr);
	return iStr;
	}

TInt CCommonUtils::Rand(TInt aMax,TInt aMin)
	{
	TTime now;
	now.HomeTime();
	TInt64 iSeed = now.Int64();
	
	TInt random = (Math::Rand(iSeed) % aMax) + aMin;
	return random;
	}
//


//**********************************************//
UITools::~UITools()
	{}
UITools::UITools()
	{}
void UITools::Alter(const TDesC& aText)
	{
	CAknInformationNote* informationNote;
	informationNote = new ( ELeave ) CAknInformationNote;				
	informationNote->ExecuteLD(aText);
	}


