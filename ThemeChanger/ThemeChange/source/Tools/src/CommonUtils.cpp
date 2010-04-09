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
//	RWsSession aWsSession = CEikonEnv::Static()->WsSession();
//	TApaTask aTask(aWsSession);
//	TInt aId = CEikonEnv::Static()->RootWin().Identifier();
//	aTask.SetWgId(aId);
//	if (aWsSession.GetFocusWindowGroup() == aId)
//	{
//		aTask.SendToBackground();
// 	}
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

TBool CCommonUtils::IsPointInRect(TInt x,TInt y,TInt l,TInt t,TInt r,TInt b)
{
	return ((x>l) & (y>t) & (x<r) & (y<b));
}

TBool CCommonUtils::IsPointInRect(TInt x,TInt y,TRect rect)
{
	return IsPointInRect(x, y, rect.iTl.iX, rect.iTl.iY, rect.iBr.iX, rect.iBr.iY);
}

TBool CCommonUtils::IsPointInRect(TPoint aPoint,TRect rect)
	{
	return IsPointInRect(aPoint.iX, aPoint.iY, rect.iTl.iX, rect.iTl.iY, rect.iBr.iX, rect.iBr.iY);
	}

HBufC* CCommonUtils::AutoWrapText(const TDesC& aText,const CFont* aFont,TInt aWidth)
	{
	HBufC* text = aText.AllocL();
	HBufC* re = HBufC::NewL(aText.Length()*2);
	TInt index = 1;
	while (text->Length())
		{
		TInt len = aFont->TextCount(text->Des(),aWidth);
		re->Des().Append(text->Left(len));
		re->Des().Append('\n');
		text->Des().Delete(0,len);
		}
	
	delete text;
	return re;
	}
//


