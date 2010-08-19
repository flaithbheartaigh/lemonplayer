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


TBool CCommonUtils::HexToDec(const TDesC& aHexDes, TInt& aDec)
	{
	TInt i, mid;
	TInt len = aHexDes.Length();//lstrlen( aHexDes ); 

	//if( len > 9 )//#00ff00ff? 
	//	return EFalse; 

	mid = 0;
	aDec = 0;
	for (i = 0; i < len; i++)
		{
		if ((aHexDes.Ptr())[i] >= '0' && (aHexDes.Ptr())[i] <= '9')
			{
			mid = (aHexDes.Ptr())[i] - '0';
			}
		else if ((aHexDes.Ptr())[i] >= 'a' && (aHexDes.Ptr())[i] <= 'f')
			{
			mid = (aHexDes.Ptr())[i] - 'a' + 10;
			}
		else if ((aHexDes.Ptr())[i] >= 'A' && (aHexDes.Ptr())[i] <= 'F')
			{
			mid = (aHexDes.Ptr())[i] - 'A' + 10;
			}
		else if ((aHexDes.Ptr())[i] == '#')
			{
			continue;
			}
		else
			{
			return EFalse;
			}

		mid <<= ((len - i - 1) << 2);
		aDec |= mid;

		}
	return ETrue;
	}

TBool CCommonUtils::HexToDec(const TDesC8& aHexDes, TInt& aDec)
	{
	TInt i, mid;
	TInt len = aHexDes.Length();//lstrlen( aHexDes ); 

	//if( len > 9 )//#00ff00ff? 
	//	return EFalse; 

	mid = 0;
	aDec = 0;
	for (i = 0; i < len; i++)
		{
		if ((aHexDes.Ptr())[i] >= '0' && (aHexDes.Ptr())[i] <= '9')
			{
			mid = (aHexDes.Ptr())[i] - '0';
			}
		else if ((aHexDes.Ptr())[i] >= 'a' && (aHexDes.Ptr())[i] <= 'f')
			{
			mid = (aHexDes.Ptr())[i] - 'a' + 10;
			}
		else if ((aHexDes.Ptr())[i] >= 'A' && (aHexDes.Ptr())[i] <= 'F')
			{
			mid = (aHexDes.Ptr())[i] - 'A' + 10;
			}
		else if ((aHexDes.Ptr())[i] == '#')
			{
			continue;
			}
		else
			{
			return EFalse;
			}

		mid <<= ((len - i - 1) << 2);
		aDec |= mid;

		}
	return ETrue;
	}

TText8* CCommonUtils::DecToHex(const TDesC8& aHexDes)
	{
	TInt len = aHexDes.Length() / 2;
	TText8* txt = new TText8[len + 1];

	for (TInt i = 0; i < len; i++)
		{
		TPtrC8 ptr = aHexDes.Mid(i * 2, 2);
		TInt value;
		HexToDec(ptr, value);
		txt[i] = (TText8) value;
		}
	txt[len] = 0;
	return txt;
	}

CDesCArray* CCommonUtils::SplitText(const TDesC& aText, const char& aSplitChar)
	{
	CDesCArray* tmpArray = new (ELeave) CDesCArrayFlat(5);
	CleanupStack::PushL(tmpArray);

	TInt len = aText.Length();
	TBuf<100> tmp;
	for (TInt i = 0; i < len; i++)
		{
		if (aText[i] == aSplitChar)
			{
			tmp.TrimAll();
			tmpArray->AppendL(tmp);
			tmp.Zero();
			}
		else
			tmp.Append(aText[i]);
		}
	if (tmp.Length() > 0)
		{
		tmp.TrimAll();
		tmpArray->AppendL(tmp);
		}

	CleanupStack::Pop(tmpArray);
	return tmpArray;
	}

CDesC8Array* CCommonUtils::SplitText(const TDesC8& aText, const char& aSplitChar)
	{
	CDesC8Array* tmpArray = new (ELeave) CDesC8ArrayFlat(5);
	CleanupStack::PushL(tmpArray);

	TInt len = aText.Length();
	TBuf8<100> tmp;
	for (TInt i = 0; i < len; i++)
		{
		if (aText[i] == aSplitChar)
			{
			tmp.TrimAll();
			tmpArray->AppendL(tmp);
			tmp.Zero();
			}
		else
			tmp.Append(aText[i]);
		}
	if (tmp.Length() > 0)
		{
		tmp.TrimAll();
		tmpArray->AppendL(tmp);
		}

	CleanupStack::Pop(tmpArray);
	return tmpArray;
	}

TInt CCommonUtils::StrToInt(const TDesC &aStr, TRadix aRadix)
	{
	TLex a(aStr);
	TUint num;
	if (a.Val(num, aRadix) == KErrNone)
		return num;
	else
		return -1;
	}

TInt CCommonUtils::StrToInt(const TDesC8 &aStr, TRadix aRadix)
	{
	TLex8 a(aStr);
	TUint num;
	if (a.Val(num, aRadix) == KErrNone)
		return num;
	else
		return -1;
	}

TReal32 CCommonUtils::StrToFloat(const TDesC &aStr, TChar aPoint)
	{
	TLex a(aStr);
	TReal32 num;
	if (a.Val(num, aPoint) == KErrNone)
		return num;
	else
		return -1;
	}

TReal32 CCommonUtils::StrToFloat(const TDesC8 &aStr, TChar aPoint)
	{
	TLex8 a(aStr);
	TReal32 num;
	if (a.Val(num, aPoint) == KErrNone)
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
	Converter->ConvertToUnicodeFromUtf8(ptr, aStr);
	delete Converter;

	CleanupStack::Pop(ret);
	return ret;
	}

//将Unicode转换成Utf8 	
HBufC8* CCommonUtils::ConvertToUTF8FromUnicode(const TDesC& aStr)
	{
	//	HBufC8* ret = HBufC8::NewLC(aStr.Length());		
	HBufC8* ret = HBufC8::NewLC(aStr.Length() * 3);
	CnvUtfConverter* Converter = new (ELeave) CnvUtfConverter();
	TPtr8 ptr = ret->Des();
	Converter->ConvertFromUnicodeToUtf8(ptr, aStr);
	delete Converter;

	CleanupStack::Pop(ret);
	return ret;
	}

//
//将中文字符转换成Unicode	
HBufC16* CCommonUtils::ConvertToUnicodeFromGBK(const TText8* aStr)
	{
	CCnvCharacterSetConverter* converter = CCnvCharacterSetConverter::NewLC();

	if (converter->PrepareToConvertToOrFromL(KCharacterSetIdentifierGbk,
			CEikonEnv::Static()->FsSession())
			!= CCnvCharacterSetConverter::EAvailable)
		{
		delete converter;
		return NULL;
		}

	//TText8  *str = (TText8*)"诺基亚7650C";
	TInt state = CCnvCharacterSetConverter::KStateDefault;

	TPtrC8 source(aStr);
	HBufC* ret = HBufC::NewLC(source.Length());
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

TInt CCommonUtils::Rand(TInt aMax, TInt aMin)
	{
	TTime now;
	now.HomeTime();
	TInt64 iSeed = now.Int64();

	TInt random = (Math::Rand(iSeed) % aMax) + aMin;
	return random;
	}

TBool CCommonUtils::IsPointInRect(TInt x, TInt y, TInt l, TInt t, TInt r,
		TInt b)
	{
	return ((x > l) & (y > t) & (x < r) & (y < b));
	}

TBool CCommonUtils::IsPointInRect(TInt x, TInt y, TRect rect)
	{
	return IsPointInRect(x, y, rect.iTl.iX, rect.iTl.iY, rect.iBr.iX,
			rect.iBr.iY);
	}

TBool CCommonUtils::IsPointInRect(TPoint aPoint, TRect rect)
	{
	return IsPointInRect(aPoint.iX, aPoint.iY, rect.iTl.iX, rect.iTl.iY,
			rect.iBr.iX, rect.iBr.iY);
	}

//HBufC* CCommonUtils::AutoWrapText(const TDesC& aText,const CFont* aFont,TInt aWidth)
//	{
//	HBufC* text = aText.AllocL();
//	HBufC* re = HBufC::NewL(aText.Length()*2);
//	TInt index = 1;
//	while (text->Length())
//		{
//		TInt len = aFont->TextCount(text->Des(),aWidth);
//		re->Des().Append(text->Left(len));
//		re->Des().Append('\n');
//		text->Des().Delete(0,len);
//		}
//	
//	delete text;
//	return re;
//	}
//

#define FOMART_FILL_TO_TOW(a,b) if (a < 10) b.AppendNum(0);

void CCommonUtils::TimeFormat(const TTime& aTime,TDes& aDes)
	{
	TDateTime time = aTime.DateTime();
	TInt year,month,day,hour,minute,secend;
	year = time.Year() ;
	month = time.Month() + 1;
	day = time.Day() + 1;
	hour = time.Hour() ;
	minute = time.Minute() ;
	secend = time.Second() ;
	aDes.AppendNum(year);
	FOMART_FILL_TO_TOW(month,aDes)
	aDes.AppendNum(month);
	FOMART_FILL_TO_TOW(day,aDes)
	aDes.AppendNum(day);
	aDes.Append(':');
	FOMART_FILL_TO_TOW(hour,aDes)
	aDes.AppendNum(hour);
	FOMART_FILL_TO_TOW(minute,aDes)
	aDes.AppendNum(minute);
	FOMART_FILL_TO_TOW(secend,aDes)
	aDes.AppendNum(secend);	
	}

void CCommonUtils::TimeFormatWithoutOffset(const TTime& aTime,TDes& aDes)
	{
	TDateTime time = aTime.DateTime();
	TInt year,month,day,hour,minute,secend;
	year = time.Year() ;
	month = time.Month() ;
	day = time.Day() ;
	hour = time.Hour() ;
	minute = time.Minute() ;
	secend = time.Second() ;
	aDes.AppendNum(year);
	FOMART_FILL_TO_TOW(month,aDes)
	aDes.AppendNum(month);
	FOMART_FILL_TO_TOW(day,aDes)
	aDes.AppendNum(day);
	aDes.Append(':');
	FOMART_FILL_TO_TOW(hour,aDes)
	aDes.AppendNum(hour);
	FOMART_FILL_TO_TOW(minute,aDes)
	aDes.AppendNum(minute);
	FOMART_FILL_TO_TOW(secend,aDes)
	aDes.AppendNum(secend);	
	}

void CCommonUtils::TimeSet(const TDesC& aDes,TTime& aTime)
	{
	TTime time;
	time.Set(aDes);
	TDateTime date;
	date = time.DateTime();
	TDateTime param;
	param.SetYear(date.Year());
	param.SetMonth((TMonth)(date.Month() - 1));
	param.SetDay(date.Day() - 1);
	param.SetHour(date.Hour() );
	param.SetMinute(date.Minute() );
	param.SetSecond(date.Second() );
	
	aTime = TTime(param);
	}

TTime CCommonUtils::TimeCreate(const TTime& aTime,const TInt& aOffsetMinutes)
	{
	TDateTime date = aTime.DateTime();
	
	TDateTime param;
	param.SetYear(date.Year());
	param.SetMonth(date.Month());
	param.SetDay(date.Day());
	param.SetHour(date.Hour() );
	param.SetMinute(date.Minute() );
	param.SetSecond(0);
	param.SetMicroSecond(0);	
	
	TInt64 ms = TTime(param).Int64();
	ms += ((TInt64)aOffsetMinutes)*((TInt64)60000000);
	
	return TTime(ms);
	}

