/*
 ============================================================================
 Name		: TangramAnimation.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangramAnimation implementation
 ============================================================================
 */

#include "TangramAnimation.h"

#include "ImageArrayReader.h"
#include "StaticAnimation.h"
#include "MacroUtil.h"
#include "Emulator.h"

_LIT(KTangramImage,"image.xml");
_LIT(KTangramAnimation,"tangram.xml");

CTangramAnimation::CTangramAnimation()
	{
	// No implementation required
	}

CTangramAnimation::~CTangramAnimation()
	{
	SAFE_DELETE(iAnimation);
	SAFE_DELETE(iBitmapArray);
	}

CTangramAnimation* CTangramAnimation::NewLC()
	{
	CTangramAnimation* self = new (ELeave)CTangramAnimation();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTangramAnimation* CTangramAnimation::NewL()
	{
	CTangramAnimation* self=CTangramAnimation::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CTangramAnimation::ConstructL()
	{
	iBitmapArray = CImageArrayReader::NewL();
	iBitmapArray->SetNotify(this);
	
	iAnimation = CStaticAnimation::NewL();
	}

void CTangramAnimation::Init()
	{
	TFileName file;
#ifndef __WINS__
	file.Copy(KTangramImage);
	CompleteWithAppPath(file);
#else
	file.Copy(KResourceDirction);
	file.Append(KTangramImage);
#endif	
	iBitmapArray->LoadDataFromFile(file);
	}

TBool CTangramAnimation::Update()
	{
	iAnimation->UpdataData();
	return ETrue;
	}

void CTangramAnimation::UpdateDisplay(CFbsBitGc& gc)
	{
	iAnimation->Draw(gc, 20, 20);
	}

void CTangramAnimation::ConvertComplete()
	{
	iAnimation->SetSrcBitmap(iBitmapArray->GetBitmapArray(),
			iBitmapArray->GetBitmapCount());
	TFileName file;
#ifndef __WINS__
	file.Append(KTangramAnimation);
	CompleteWithAppPath(file);
#else
	file.Copy(KResourceDirction);
	file.Append(KTangramAnimation);
#endif
	iAnimation->LoadDataFromXml(file);
	}