
//#include <string.h>
#ifdef EKA2
#include <e32cmn.h>
#else
#include <string.h>
#endif
#include <UTF.H> 
#include <e32base.h> 
#include "md5.h"

CMD5::CMD5()
{

}

CMD5::~CMD5()
{

}
void CMD5::MD5Init()
{
	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;

	bits[0] = 0;
	bits[1] = 0;
	memset(buffer,0,sizeof(buffer));
}

void  CMD5::MD5Update(const char* input,TUint len)
{
	TUint32 t = bits[0];

	if ((bits[0] = t + ((TUint32) len << 3)) < t)
		bits[1] ++;				//Carry from low to high 

	bits[1] += len >> 29;
	t = (t >> 3) & 0x3f;        //Bytes already in shsInfo->data
	
	//Handle any leading odd-sized chunks

	if (t) 
	{
		TUint8 *p = (TUint8 *) buffer + t;
		t = 64 - t;
		if (len < t) 
		{
			memcpy(p, input, len);
			return;
		}		
		memcpy(p, input, t);
		MD5Transform(state, (TUint32 *)buffer);
		input += t;
		len -= t;
	}
	
	//Process data in 64-byte chunks

	while (len >= 64) 
	{
		memcpy(buffer, input, 64);
		MD5Transform(state, (TUint32 const *) input);
		input += 64;
		len -= 64;
	}

	//Handle any remaining bytes of data.
	memcpy(buffer, input, len);
}

void  CMD5::MD5Final(TUint8 digest[16])
{
	TUint count;
	TUint8 *p;

	// Compute number of bytes mod 64 
	count = (bits[0] >> 3) & 0x3F;

	// Set the first char of padding to 0x80.  This is safe since there is	always at least one byte free 
	p = buffer + count;
	*p++ = 0x80;

	// Bytes of padding needed to make 64 bytes 
	count = 64 - 1 - count;

	// Pad out to 56 mod 64 
	if (count < 8) 
	{
		// Two lots of padding:  Pad the first block to 64 bytes 
		memset(p, 0, count);
		MD5Transform(state, (TUint32 *)buffer);

		// Now fill the next block with 56 bytes 
		memset(buffer, 0, 56);
	} else 
	{
		// Pad block to 56 bytes 
		memset(p, 0, count - 8);
	}

	// Append length in bits and transform 
	bytes_encode((TUint8*)((TUint32 *) buffer + 14), bits, 8);
	MD5Transform(state, (TUint32 *) buffer);
	bytes_encode(digest,state,16);   	
}

// The four core functions - F1 is optimized somewhat 
#define F1(x, y, z) (x & y | ~x & z) 
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | ~z))

// This is the central step in the MD5 algorithm. 
#define MD5STEP(f, w, x, y, z, data, s) \
	( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x ); 

void CMD5::MD5Transform(TUint32 buf[4], const TUint32 cin[16])
{
	register TUint32 a, b, c, d;
	TUint32 in[16];

	bytes_decode(in, (TUint8 *) cin, 64);

	a = buf[0];
	b = buf[1];
	c = buf[2];
	d = buf[3];

	MD5STEP(F1, a, b, c, d, in[0] + 0xd76aa478, 7);
	MD5STEP(F1, d, a, b, c, in[1] + 0xe8c7b756, 12);
	MD5STEP(F1, c, d, a, b, in[2] + 0x242070db, 17);
	MD5STEP(F1, b, c, d, a, in[3] + 0xc1bdceee, 22);
	MD5STEP(F1, a, b, c, d, in[4] + 0xf57c0faf, 7);
	MD5STEP(F1, d, a, b, c, in[5] + 0x4787c62a, 12);
	MD5STEP(F1, c, d, a, b, in[6] + 0xa8304613, 17);
	MD5STEP(F1, b, c, d, a, in[7] + 0xfd469501, 22);
	MD5STEP(F1, a, b, c, d, in[8] + 0x698098d8, 7);
	MD5STEP(F1, d, a, b, c, in[9] + 0x8b44f7af, 12);
	MD5STEP(F1, c, d, a, b, in[10] + 0xffff5bb1, 17);
	MD5STEP(F1, b, c, d, a, in[11] + 0x895cd7be, 22);
	MD5STEP(F1, a, b, c, d, in[12] + 0x6b901122, 7);
	MD5STEP(F1, d, a, b, c, in[13] + 0xfd987193, 12);
	MD5STEP(F1, c, d, a, b, in[14] + 0xa679438e, 17);
	MD5STEP(F1, b, c, d, a, in[15] + 0x49b40821, 22);

	MD5STEP(F2, a, b, c, d, in[1] + 0xf61e2562, 5);
	MD5STEP(F2, d, a, b, c, in[6] + 0xc040b340, 9);
	MD5STEP(F2, c, d, a, b, in[11] + 0x265e5a51, 14);
	MD5STEP(F2, b, c, d, a, in[0] + 0xe9b6c7aa, 20);
	MD5STEP(F2, a, b, c, d, in[5] + 0xd62f105d, 5);
	MD5STEP(F2, d, a, b, c, in[10] + 0x02441453, 9);
	MD5STEP(F2, c, d, a, b, in[15] + 0xd8a1e681, 14);
	MD5STEP(F2, b, c, d, a, in[4] + 0xe7d3fbc8, 20);
	MD5STEP(F2, a, b, c, d, in[9] + 0x21e1cde6, 5);
	MD5STEP(F2, d, a, b, c, in[14] + 0xc33707d6, 9);
	MD5STEP(F2, c, d, a, b, in[3] + 0xf4d50d87, 14);
	MD5STEP(F2, b, c, d, a, in[8] + 0x455a14ed, 20);
	MD5STEP(F2, a, b, c, d, in[13] + 0xa9e3e905, 5);
	MD5STEP(F2, d, a, b, c, in[2] + 0xfcefa3f8, 9);
	MD5STEP(F2, c, d, a, b, in[7] + 0x676f02d9, 14);
	MD5STEP(F2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);

	MD5STEP(F3, a, b, c, d, in[5] + 0xfffa3942, 4);
	MD5STEP(F3, d, a, b, c, in[8] + 0x8771f681, 11);
	MD5STEP(F3, c, d, a, b, in[11] + 0x6d9d6122, 16);
	MD5STEP(F3, b, c, d, a, in[14] + 0xfde5380c, 23);
	MD5STEP(F3, a, b, c, d, in[1] + 0xa4beea44, 4);
	MD5STEP(F3, d, a, b, c, in[4] + 0x4bdecfa9, 11);
	MD5STEP(F3, c, d, a, b, in[7] + 0xf6bb4b60, 16);
	MD5STEP(F3, b, c, d, a, in[10] + 0xbebfbc70, 23);
	MD5STEP(F3, a, b, c, d, in[13] + 0x289b7ec6, 4);
	MD5STEP(F3, d, a, b, c, in[0] + 0xeaa127fa, 11);
	MD5STEP(F3, c, d, a, b, in[3] + 0xd4ef3085, 16);
	MD5STEP(F3, b, c, d, a, in[6] + 0x04881d05, 23);
	MD5STEP(F3, a, b, c, d, in[9] + 0xd9d4d039, 4);
	MD5STEP(F3, d, a, b, c, in[12] + 0xe6db99e5, 11);
	MD5STEP(F3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
	MD5STEP(F3, b, c, d, a, in[2] + 0xc4ac5665, 23);

	MD5STEP(F4, a, b, c, d, in[0] + 0xf4292244, 6);
	MD5STEP(F4, d, a, b, c, in[7] + 0x432aff97, 10);
	MD5STEP(F4, c, d, a, b, in[14] + 0xab9423a7, 15);
	MD5STEP(F4, b, c, d, a, in[5] + 0xfc93a039, 21);
	MD5STEP(F4, a, b, c, d, in[12] + 0x655b59c3, 6);
	MD5STEP(F4, d, a, b, c, in[3] + 0x8f0ccc92, 10);
	MD5STEP(F4, c, d, a, b, in[10] + 0xffeff47d, 15);
	MD5STEP(F4, b, c, d, a, in[1] + 0x85845dd1, 21);
	MD5STEP(F4, a, b, c, d, in[8] + 0x6fa87e4f, 6);
	MD5STEP(F4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
	MD5STEP(F4, c, d, a, b, in[6] + 0xa3014314, 15);
	MD5STEP(F4, b, c, d, a, in[13] + 0x4e0811a1, 21);
	MD5STEP(F4, a, b, c, d, in[4] + 0xf7537e82, 6);
	MD5STEP(F4, d, a, b, c, in[11] + 0xbd3af235, 10);
	MD5STEP(F4, c, d, a, b, in[2] + 0x2ad7d2bb, 15);
	MD5STEP(F4, b, c, d, a, in[9] + 0xeb86d391, 21);

	buf[0] += a;
	buf[1] += b;
	buf[2] += c;
	buf[3] += d;
}
void CMD5::bytes_encode(TUint8 *output, TUint32 *input, TUint len)
{
	TUint i, j;

	for (i = 0, j = 0; j < len; i++, j += 4) 
	{
		output[j]   = (TUint8)(input[i] & 0xff);
		output[j+1] = (TUint8)((input[i] >> 8) & 0xff);
		output[j+2] = (TUint8)((input[i] >> 16) & 0xff);
		output[j+3] = (TUint8)((input[i] >> 24) & 0xff);
	}
}

void CMD5::bytes_decode(TUint32 *output, TUint8 *input, TUint len)
{
	TUint i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
	{
		output[i] = ((TUint32)input[j]) |
					(((TUint32)input[j+1]) << 8) |
					(((TUint32)input[j+2]) << 16) |
					(((TUint32)input[j+3]) << 24);
	}
}

//½«Unicode×ª»»³ÉUtf8 	
HBufC8* CMD5::ConvertToUTF8FromUnicode(const TDesC& aStr)
{
	HBufC8 *ret = CnvUtfConverter::ConvertFromUnicodeToUtf8L(aStr);

	return ret;

	//HBufC8* ret = HBufC8::NewLC(aStr.Length());		
	//CnvUtfConverter* Converter = new (ELeave) CnvUtfConverter;
	//Converter->ConvertFromUnicodeToUtf8(ret->Des(),aStr);
	//delete Converter;

	//CleanupStack::Pop(ret);
	//return ret;	
}
HBufC8* CMD5::Print(TUint8 buf[16])
{
	HBufC8* ret = HBufC8::NewL(50);
	for (TUint i = 0; i < 16; i ++)
	{		
		ret->Des().Append((buf[i] >> 4) > 9 ? (buf[i] >> 4) + 55 : (buf[i] >> 4) + 48);
		ret->Des().Append((buf[i] & 0x0F) > 9 ? (buf[i] & 0x0F) + 55 : (buf[i] & 0x0F) + 48);
	}
	return ret;
}

HBufC8* CMD5::MD5Hash(const TDesC8& aMsg)
{
	TUint8 ret[16];
	HBufC8* tmp = HBufC8::NewL(aMsg.Length() + 10);
	tmp->Des().Copy(aMsg);
	
	MD5Init();
	MD5Update((const char*)tmp->Des().PtrZ(),aMsg.Length());
	MD5Final(ret);

	delete tmp;

	return Print(ret);	
}

HBufC* CMD5::MD5Hash(const TDesC& aMsg)
{
	TUint8 ret[16];
	HBufC8* tmp = HBufC8::NewL(aMsg.Length() + 10);
	tmp->Des().Copy(aMsg);
	CleanupStack::PushL(tmp);

	MD5Init();
	const char* s1 = (const char*)tmp->Des().PtrZ();
	TUint t2 = aMsg.Length();
	MD5Update(s1,t2);
	MD5Final(ret);
	
	CleanupStack::PopAndDestroy(tmp);

	
	HBufC8* md5code = Print(ret);	
	CleanupStack::PushL(md5code);

	HBufC* resut = HBufC::NewLC(md5code->Length());
	resut->Des().Copy(*md5code);
	
	CleanupStack::Pop(resut);
	CleanupStack::PopAndDestroy(md5code);

	return resut;	
}