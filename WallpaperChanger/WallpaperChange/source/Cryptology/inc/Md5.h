#ifndef MD5_H
#define MD5_H

#include <e32std.h>

class CMD5
{
public://构造函数
	CMD5();
	~CMD5();

public:	//对外方法
	HBufC8* MD5Hash(const TDesC8& aMsg);
	HBufC* MD5Hash(const TDesC& aMsg);

private:
	void MD5Init();
	void MD5Update(const char *input,TUint len);
	void MD5Final(TUint8 digest[16]);

	void MD5Transform(TUint32 buf[4], const TUint32 cin[16]);	
	void bytes_encode(TUint8 *output, TUint32 *input, TUint len);
	void bytes_decode(TUint32 *output, TUint8 *input, TUint len);	
	HBufC8* ConvertToUTF8FromUnicode(const TDesC& aStr);

	HBufC8* Print(TUint8 buf[16]);
private:
	TUint32 state[4];
	TUint32 bits[2];
	TUint8  buffer[64];
};

#endif /* !MD5_H */

