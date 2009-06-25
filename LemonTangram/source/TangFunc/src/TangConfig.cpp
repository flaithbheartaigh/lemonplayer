/*
 ============================================================================
 Name		: TangConfig.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangConfig implementation
 ============================================================================
 */

#include "TangConfig.h"
#include "MacroUtil.h"

CTangConfig::CTangConfig()
	{
	// No implementation required
	}

CTangConfig::~CTangConfig()
	{
	SAFE_DELETE(iConfig);
	}

CTangConfig* CTangConfig::NewLC(const TDesC& aConfigFilePath)
	{
	CTangConfig* self = new (ELeave)CTangConfig();
	CleanupStack::PushL(self);
	self->ConstructL(aConfigFilePath);
	return self;
	}

CTangConfig* CTangConfig::NewL(const TDesC& aConfigFilePath)
	{
	CTangConfig* self=CTangConfig::NewLC(aConfigFilePath);
	CleanupStack::Pop(); // self;
	return self;
	}

void CTangConfig::ConstructL(const TDesC& aConfigFilePath)
	{
	iConfig = CConfiguration::NewL(aConfigFilePath);
	}

//TBool CTangConfig::GetSkinFolder(TDes& aDes)
//	{
//	return iConfig->Get(KCfgSkinFolder,aDes);
//	}
//TBool CTangConfig::SetSkinFolder(const TDesC& aDes)
//	{
//	return iConfig->Set(KCfgSkinFolder,aDes);
//	}
//
//TBool CTangConfig::GetSaveFolder(TDes& aDes)
//	{
//	return iConfig->Get(KCfgSaveFolder,aDes);
//	}
//TBool CTangConfig::SetSaveFolder(const TDesC& aDes)
//	{
//	return iConfig->Set(KCfgSaveFolder,aDes);
//	}

TBool CTangConfig::SaveL()
	{
	return iConfig->SaveL();
	}
