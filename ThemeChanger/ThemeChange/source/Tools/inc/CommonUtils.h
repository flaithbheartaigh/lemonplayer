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

		// 检查目录是否存在
		static TBool IsDirectoryExists(const TDesC &aDirName);

		
		static TBool HexToDec(const TDesC& aHexDes,TInt& aDec);
		static TBool HexToDec(const TDesC8& aHexDes,TInt& aDec);
		static TText8* DecToHex(const TDesC8& aHexDes);


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
		
		
		static HBufC8* ConvertDesTo8(const TDesC& aStr);
		
		static TInt Rand(TInt aMax,TInt aMin=0);
		
		static TBool IsPointInRect(TInt x,TInt y,TInt l,TInt t,TInt r,TInt b);
		static TBool IsPointInRect(TInt x,TInt y,TRect rect);
		static TBool IsPointInRect(TPoint aPoint,TRect rect);
		
//		static HBufC* AutoWrapText(const TDesC& aText,const CFont* aFont,TInt aWidth);

	private:
		~CCommonUtils();    
		CCommonUtils();
};



#endif // COMMONUTILS_H
