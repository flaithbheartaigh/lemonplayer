/*
============================================================================
 Name        : CommonUtils.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CCommonUtils declaration
============================================================================
*/

#ifndef COMMONUTILS_H
#define COMMONUTILS_H

// INCLUDES
#include <e32std.h>
#include <badesca.h> 

//#include "AsyncSocketCommon.h"

// CLASS DECLARATION

/**
*  CCommonUtils
* 
*/
class CCommonUtils
{
	public: // Constructors and destructor
		// 将应用程序带到前台
		static void ShowApplication();
		// 隐藏应用程序
		static void HideApplication();

		static TThreadId StartBroswerApp(const TDesC& aAddr);
		//关闭当前的应用程序
		static void CloseApp(const TUid& aUid );

		static HBufC* UrlEncodeL(const TDesC& aUrl);
		static HBufC* UrlDecodeL(const TDesC& aUrl); // 不完全，仅过滤&amp;

		// 检查目录是否存在
		static TBool IsDirectoryExists(const TDesC &aDirName);

		// 记录日志
		static void GlobalLogL(const TDesC &aLogText);
		static void GlobalLogL(const TDesC8 &aLogText);
		static void GlobalLogL(const TDesC &aDescription, TInt aNumber);
		static void GlobalLogL(const TDesC &aDescription, const TDesC &aLogText);
		static void GlobalLogL(const TDesC8 &aDescription, const TDesC8 &aLogText);
		static void GlobalLogL(const TDesC &aDescription, TDateTime aTime);

		static TBool HexToDec(const TDesC& aHexDes,TInt& aDec);


		//=====================================字符操作=====================================
		//切割字符串
		static CDesCArray* SplitText(const TDesC& aText,const char& aSplitChar);
		 
		//字符串转换成整数
		static TInt StrToInt(const TDesC &aStr,TRadix aRadix=EDecimal );
		static TInt StrToInt(const TDesC8 &aStr,TRadix aRadix=EDecimal);
						
		static TReal32 StrToFloat(const TDesC &aStr,TChar aPoint=',' );
		static TReal32 StrToFloat(const TDesC8 &aStr,TChar aPoint=',');
		 
		//将Utf8转换成Unicode
		static HBufC16* ConvertToUnicodeFromUTF8(const TDesC8& aStr);
		//将Unicode转换成Utf8 	
		static HBufC8* ConvertToUTF8FromUnicode(const TDesC& aStr);
		 
		//将中文字符转换成Unicode	
		static HBufC16* ConvertToUnicodeFromGBK(const TText8* aStr);
		
		//base64编码
		static HBufC8* UrlEncodeL(const TDesC8& aUrl);
		
		//得到url aSrcUrl可能为http开头,绝对路径;也可能不为http开头,相对路径
		static HBufC* ConvertUrlL(const TDesC& aSrcUrl, const TDesC& aRootUrl);
		static void ConvertUrlToL(const TDesC& aDestUrl, HBufC** aUrl);
		static void ConvertUrlToL8(const TDesC8& aDestUrl, HBufC8** aUrl);
		static void ConvertUrlFromRootL(const TDesC& aDestUrl, HBufC** aUrl);
		
		static HBufC8* ConvertDesTo8(const TDesC& aStr);
		
		static TInt Rand(TInt aMax,TInt aMin=0);

	private:
		~CCommonUtils();    
		CCommonUtils();
};

class UITools
	{
public:
	static void Alter(const TDesC& aText);
private:
	~UITools();
	UITools();
	};

#endif // COMMONUTILS_H
