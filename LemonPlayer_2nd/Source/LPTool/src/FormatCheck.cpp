#include "FormatCheck.h"
#include "MacroUtil.h"
#include <LemonPlayer.rsg>
#include <coemain.h>

FormatCheck  *FormatCheck::iInstance = NULL;    // Attention £¡ 

FormatCheck::FormatCheck()
	{
	iFormatArray = NULL;
	}

FormatCheck::~FormatCheck()
	{
	iFormatArray->Reset();
	SAFE_DELETE(iFormatArray);
	}

FormatCheck* FormatCheck::GetInstance()
	{
	if (iInstance==NULL)
		{
		iInstance = new (ELeave) FormatCheck;
		iInstance->ConstructL();
		}
	return iInstance;
	}

void FormatCheck::ConstructL()
	{
	iFormatArray = CCoeEnv::Static()->ReadDesCArrayResourceL(R_ACCEPTED_SOUND_FORMAT);
	}

TBool FormatCheck::IsAllowedFormat(const TDesC& aExt)
	{
	for (TInt i=0; i<iFormatArray->Count(); i++)
			{
			TPtrC str = (*iFormatArray)[i];
			TInt pos = aExt.Find(str);
			if (pos!=KErrNotFound)
				{
				return ETrue;
				}
			}
		return EFalse;
	}