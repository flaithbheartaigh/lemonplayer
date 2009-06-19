/*
 ============================================================================
 Name		: TangImageSave.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangImageSave implementation
 ============================================================================
 */

#include "TangImageSave.h"
#include "ImageConvertor.h"
#include "MacroUtil.h"

#include <eikenv.h>
#include <f32file.h>
#include <coemain.h>
#include <s32file.h>
#include "UIMgr.h"
#include "LemonTangramAppUi.h"

CTangImageSave::CTangImageSave(MSaveScreenNotify* aNotify)
:iNotify(aNotify)
	{
	// No implementation required
	}

CTangImageSave::~CTangImageSave()
	{
	SAFE_DELETE(iDoubleBufferGc);
	SAFE_DELETE(iDoubleBufferDevice);
	SAFE_DELETE(iDoubleBufferBmp);
	SAFE_DELETE(iConvertor);
	}

CTangImageSave* CTangImageSave::NewLC(const TDesC& aFileName,MSaveScreenNotify* aNotify)
	{
	CTangImageSave* self = new (ELeave)CTangImageSave(aNotify);
	CleanupStack::PushL(self);
	self->ConstructL(aFileName);
	return self;
	}

CTangImageSave* CTangImageSave::NewL(const TDesC& aFileName,MSaveScreenNotify* aNotify)
	{
	CTangImageSave* self=CTangImageSave::NewLC(aFileName,aNotify);
	CleanupStack::Pop(); // self;
	return self;
	}

void CTangImageSave::ConstructL(const TDesC& aFileName)
	{
	iConvertor = CImageConvertor::NewL();
	iConvertor->SetListener(this);

	iFileName.Copy(aFileName);
	}

void CTangImageSave::OnImageConvertedL(CFbsBitmap& /*aBitmap*/)
	{
	}
void CTangImageSave::OnImageConvertedL(const TDesC8 &aImgData)
	{
	int pos = iFileName.LocateReverse( '\\');
	if (pos!=KErrNotFound)
		{
		TPtrC dirName = iFileName.Left(pos+1);
		CCoeEnv::Static()->FsSession().MkDirAll(dirName);
		}

	RFile file;

	TInt err = file.Replace(CCoeEnv::Static()->FsSession(), iFileName, EFileWrite);
	CleanupClosePushL(file);
	if (KErrNone != err)
		{
		CleanupStack::PopAndDestroy(1); // file
		return ;
		}

	RFileWriteStream outputFileStream(file);
	CleanupClosePushL(outputFileStream);
	outputFileStream.WriteL(aImgData);

	CleanupStack::PopAndDestroy(2); // outputFileStream, file
	
	iNotify->SaveComplete();
	}
void CTangImageSave::OnConvertErrorL(TConvertResult /*aConvertResult*/)
	{
	}

CFbsBitGc& CTangImageSave::CreateBufferBitmapL()
{
	SAFE_DELETE(iDoubleBufferGc);
	SAFE_DELETE(iDoubleBufferDevice);
	SAFE_DELETE(iDoubleBufferBmp);
	
	TDisplayMode displayMode = CEikonEnv::Static()->ScreenDevice()->DisplayMode();
	
	iDoubleBufferBmp = new(ELeave) CFbsBitmap();
	CleanupStack::PushL(iDoubleBufferBmp);
	
	MUIMgr* uiMgr = STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->GetUIMgr();
	TInt nErr =	iDoubleBufferBmp->Create(uiMgr->DrawableSize(),displayMode);
	if (nErr != KErrNone)
	{
		CleanupStack::PopAndDestroy(iDoubleBufferBmp);
		iDoubleBufferBmp =NULL;
		return;
	}
	// 创建离屏位图设备。
	iDoubleBufferDevice = CFbsBitmapDevice::NewL(iDoubleBufferBmp);	
	CleanupStack::PushL(iDoubleBufferDevice);
	nErr = iDoubleBufferDevice->CreateContext(iDoubleBufferGc);
	if (nErr != KErrNone)
	{
		CleanupStack::PopAndDestroy(2);
		iDoubleBufferDevice =NULL;
		iDoubleBufferBmp =NULL;
		return;
	}	
	iDoubleBufferGc->SetBrushColor(KRgbWhite);
	iDoubleBufferGc->SetBrushStyle(CGraphicsContext::ENullBrush);
	iDoubleBufferGc->Clear();
	CleanupStack::Pop(2);
	
	return *iDoubleBufferGc;
}

void CTangImageSave::StartSave()
	{
	if(iDoubleBufferBmp)
		iConvertor->EncodeToDesL(*iDoubleBufferBmp);
	}
