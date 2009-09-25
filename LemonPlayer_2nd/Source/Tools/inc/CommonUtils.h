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
		// ��Ӧ�ó������ǰ̨
		static void ShowApplication();
		// ����Ӧ�ó���
		static void HideApplication();

		static TThreadId StartBroswerApp(const TDesC& aAddr);
		//�رյ�ǰ��Ӧ�ó���
		static void CloseApp(const TUid& aUid );

		static HBufC* UrlEncodeL(const TDesC& aUrl);
		static HBufC* UrlDecodeL(const TDesC& aUrl); // ����ȫ��������&amp;

		// ���Ŀ¼�Ƿ����
		static TBool IsDirectoryExists(const TDesC &aDirName);

		// ��¼��־
		static void GlobalLogL(const TDesC &aLogText);
		static void GlobalLogL(const TDesC8 &aLogText);
		static void GlobalLogL(const TDesC &aDescription, TInt aNumber);
		static void GlobalLogL(const TDesC &aDescription, const TDesC &aLogText);
		static void GlobalLogL(const TDesC8 &aDescription, const TDesC8 &aLogText);
		static void GlobalLogL(const TDesC &aDescription, TDateTime aTime);

		static TBool HexToDec(const TDesC& aHexDes,TInt& aDec);


		//=====================================�ַ�����=====================================
		//�и��ַ���
		static CDesCArray* SplitText(const TDesC& aText,const char& aSplitChar);
		 
		//�ַ���ת��������
		static TInt StrToInt(const TDesC &aStr,TRadix aRadix=EDecimal );
		static TInt StrToInt(const TDesC8 &aStr,TRadix aRadix=EDecimal);
						
		static TReal32 StrToFloat(const TDesC &aStr,TChar aPoint=',' );
		static TReal32 StrToFloat(const TDesC8 &aStr,TChar aPoint=',');
		 
		//��Utf8ת����Unicode
		static HBufC16* ConvertToUnicodeFromUTF8(const TDesC8& aStr);
		//��Unicodeת����Utf8 	
		static HBufC8* ConvertToUTF8FromUnicode(const TDesC& aStr);
		 
		//�������ַ�ת����Unicode	
		static HBufC16* ConvertToUnicodeFromGBK(const TText8* aStr);
		
		//base64����
		static HBufC8* UrlEncodeL(const TDesC8& aUrl);
		
		//�õ�url aSrcUrl����Ϊhttp��ͷ,����·��;Ҳ���ܲ�Ϊhttp��ͷ,���·��
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
