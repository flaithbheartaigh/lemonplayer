/*
 ============================================================================
 Name		: TangConfig.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTangConfig declaration
 ============================================================================
 */

#ifndef TANGCONFIG_H
#define TANGCONFIG_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "Configuration.h"
#include "ConfigDefine.h"
// CLASS DECLARATION

/**
 *  CTangConfig
 * 
 */
class CTangConfig : public CBase
	{
public:
	~CTangConfig();
	static CTangConfig* NewL(const TDesC& aConfigFilePath);
	static CTangConfig* NewLC(const TDesC& aConfigFilePath);

private:
	CTangConfig();
	void ConstructL(const TDesC& aConfigFilePath);
	
public:
//	TBool GetSkinFolder(TDes& aDes);
//	TBool SetSkinFolder(const TDesC& aDes);
	
//	TBool GetSaveFolder(TDes& aDes);
//	TBool SetSaveFolder(const TDesC& aDes);
	
	TBool SaveL();
	
private:
	CConfiguration* iConfig;
	};

#endif // TANGCONFIG_H
