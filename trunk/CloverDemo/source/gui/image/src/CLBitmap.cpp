/*
 ============================================================================
 Name		: CLBitmap.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCLBitmap implementation
 ============================================================================
 */

#include "CLBitmap.h"
#include "MacroUtil.h"

typedef char Int8;
typedef unsigned char UInt8;
typedef short Int16;
typedef unsigned short UInt16;
typedef long Int32;
typedef unsigned long UInt32;

//图像数据区的描述信息
struct TPixels32Ref
	{
	TUint16* pdata; //图像数据区首地址  即 y==0行的颜色首地址
	long byte_width; //一行图像数据的字节宽度  正负值都有可能
	long width; //图像宽度
	long height; //图像高度
	};

void Bilinear_Fast_Common(TUint16* PColor0, TUint16* PColor1,
		unsigned long u_8, unsigned long v_8, TUint16* result)
	{
	unsigned long pm3_8 = (u_8 * v_8) >> 4;
	unsigned long pm2_8 = u_8 - pm3_8;
	unsigned long pm1_8 = v_8 - pm3_8;
	unsigned long pm0_8 = 16 - pm1_8 - pm2_8 - pm3_8;

	unsigned long Color = *(unsigned short*) (PColor0);//565
	unsigned long BR = (Color & 0xF81F) * pm0_8;
	unsigned long GA = ((Color & 0x7E0) >> 5) * pm0_8;
	Color = ((unsigned short*) (PColor0))[1];
	GA += ((Color & 0x7E0) >> 5) * pm2_8;
	BR += (Color & 0xF81F) * pm2_8;
	Color = *(unsigned short*) (PColor1);
	GA += ((Color & 0x7E0) >> 5) * pm1_8;
	BR += (Color & 0xF81F) * pm1_8;
	Color = ((unsigned short*) (PColor1))[1];
	GA += ((Color & 0x7E0) >> 5) * pm3_8;
	BR += (Color & 0xF81F) * pm3_8;

	*result = ((GA & 0x3F0) << 1) | ((BR & 0xF81F0) >> 4);
	}

void PicZoom_ftBilinear_Common(const TPixels32Ref& Dst, const TPixels32Ref& Src)
	{
	if ((0 == Dst.width) || (0 == Dst.height) || (2 > Src.width) || (2
			> Src.height))
		return;

	long xrIntdouble_16 = ((Src.width - 1) << 8) / Dst.width;
	long yrIntdouble_16 = ((Src.height - 1) << 8) / Dst.height;

	long dst_width = Dst.width;
	long Src_byte_width = Src.byte_width;
	TUint16* pDstLine = Dst.pdata;
	long srcy_16 = 0;
	for (long y = 0; y < Dst.height; ++y)
		{
		unsigned long v_8 = (srcy_16 & 0xFF) >> 4;//16位图时精度4位
		TUint16* PSrcLineColor = (TUint16*) ((UInt8*) (Src.pdata)
				+ Src_byte_width * (srcy_16 >> 8));
		long srcx_16 = 0;
		for (long x = 0; x < dst_width; ++x)
			{
			TUint16* PColor0 = &PSrcLineColor[srcx_16 >> 8];
			Bilinear_Fast_Common(PColor0, (TUint16*) ((UInt8*) (PColor0)
					+ Src_byte_width), (srcx_16 & 0xFF) >> 4, v_8, &pDstLine[x]);
			srcx_16 += xrIntdouble_16;
			}
		srcy_16 += yrIntdouble_16;
		((UInt8*&) pDstLine) += Dst.byte_width;
		}
	}

CCLBitmap::CCLBitmap() :
	iBitmap(NULL),iEmputy(ETrue)
	{
	// No implementation required
	}

CCLBitmap::~CCLBitmap()
	{
		SAFE_DELETE(iBitmap)
	}

CCLBitmap* CCLBitmap::NewLC()
	{
	CCLBitmap* self = new (ELeave) CCLBitmap();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CCLBitmap* CCLBitmap::NewL()
	{
	CCLBitmap* self = CCLBitmap::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CCLBitmap::ConstructL()
	{

	}

TInt CCLBitmap::Create(const TSize &aSizeInPixels, TDisplayMode aDispMode)
	{
	TSize size = aSizeInPixels;
	if (size.iWidth%2)
		size.iWidth++;
	if (size.iHeight%2)
		size.iHeight++;
	iBitmap = new CFbsBitmap();
	CleanupStack::PushL(iBitmap);
	TInt err = iBitmap->Create(size, aDispMode);
	CleanupStack::Pop();
	return err;
	}

void CCLBitmap::Scale(CFbsBitmap* aSource)
	{
	TPixels32Ref srcPic;
	TPixels32Ref dstPic;

	if (aSource->DisplayMode() != EColor64K || iBitmap->DisplayMode() != EColor64K)
		return;
	
	if (aSource->IsLargeBitmap())
		aSource->LockHeap();
	srcPic.pdata = NULL;
	srcPic.width = aSource->SizeInPixels().iWidth;
	srcPic.height = aSource->SizeInPixels().iHeight;
	srcPic.byte_width = srcPic.width * sizeof(TUint16);
	if (srcPic.pdata)
		{
		delete[] (TUint16*) srcPic.pdata;
		srcPic.pdata = 0;
		}
	srcPic.pdata = (TUint16*) (new UInt8[srcPic.byte_width * srcPic.height]);
	memcpy(srcPic.pdata, aSource->DataAddress(), srcPic.byte_width
			* srcPic.height);
	if (aSource->IsLargeBitmap())
		aSource->UnlockHeap();

	if (iBitmap->IsLargeBitmap())
		iBitmap->LockHeap();
	dstPic.pdata = (TUint16*) (iBitmap->DataAddress());
	dstPic.width = iBitmap->SizeInPixels().iWidth;
	dstPic.height = iBitmap->SizeInPixels().iHeight;
	dstPic.byte_width = dstPic.width * sizeof(TUint16);

	PicZoom_ftBilinear_Common(dstPic, srcPic);
	if (iBitmap->IsLargeBitmap())
		iBitmap->UnlockHeap();
	if (srcPic.pdata)
		{
		delete[] (TUint16*) srcPic.pdata;
		srcPic.pdata = 0;
		}
	iEmputy = EFalse;
	}

CFbsBitmap* CCLBitmap::Scale(CFbsBitmap* aSource, const TSize &aSizeInPixels,
		TDisplayMode aDispMode)
	{
	if (aSource->SizeInPixels() == aSizeInPixels)
		return aSource;

	if (aSource->DisplayMode() != EColor64K )
		return aSource;
	
	CFbsBitmap* bitmap = new CFbsBitmap();

	TInt err = bitmap->Create(aSizeInPixels, aDispMode);

	TPixels32Ref srcPic;
	TPixels32Ref dstPic;

	if (aSource->IsLargeBitmap())
		aSource->LockHeap();
	srcPic.pdata = NULL;
	srcPic.width = aSource->SizeInPixels().iWidth;
	srcPic.height = aSource->SizeInPixels().iHeight;
	srcPic.byte_width = srcPic.width * sizeof(TUint16);
	if (srcPic.pdata)
		{
		delete[] (TUint16*) srcPic.pdata;
		srcPic.pdata = 0;
		}
	srcPic.pdata = (TUint16*) (new UInt8[srcPic.byte_width * srcPic.height]);
	memcpy(srcPic.pdata, aSource->DataAddress(), srcPic.byte_width
			* srcPic.height);
	if (aSource->IsLargeBitmap())
		aSource->UnlockHeap();

	if (bitmap->IsLargeBitmap())
		bitmap->LockHeap();
	dstPic.pdata = (TUint16*) (bitmap->DataAddress());
	dstPic.width = bitmap->SizeInPixels().iWidth;
	dstPic.height = bitmap->SizeInPixels().iHeight;
	dstPic.byte_width = dstPic.width * sizeof(TUint16);

	PicZoom_ftBilinear_Common(dstPic, srcPic);
	if (bitmap->IsLargeBitmap())
		bitmap->UnlockHeap();
	if (srcPic.pdata)
		{
		delete[] (TUint16*) srcPic.pdata;
		srcPic.pdata = 0;
		}
	
	return bitmap;
	}
