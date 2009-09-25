/**
*
* @brief Definition of CShapeResolver
*
* Copyright (c) EMCC Software Ltd 2003
* @version 1.0
*/

// Class Includes
#include "UIResolver.h"

// System Includes
#include <ecom.h>
#include <ecomerrorcodes.h>
#include <ecomresolverparams.h>
#include <implementationinformation.h>
#include <publicregistry.h>


CUIResolver* CUIResolver::NewL (MPublicRegistry& aRegistry)
	{
	return new(ELeave) CUIResolver (aRegistry);
	}




CUIResolver::~CUIResolver()
	{
	}




CUIResolver::CUIResolver (MPublicRegistry& aRegistry) :
	CResolver (aRegistry)
	{
	}




TUid CUIResolver::IdentifyImplementationL (TUid aInterfaceUid,
	const TEComResolverParams& aAdditionalParameters) const
	{
	RImplInfoArray& implementationsInfo = iRegistry.ListImplementationsL (aInterfaceUid);
	TUid found = KNullUid;

	if (implementationsInfo.Count())
		{
		found = Resolve (implementationsInfo, aAdditionalParameters);
		}
	return found;
	}




TUid CUIResolver::Resolve (const RImplInfoArray& aImplementationsInfo,
	const TEComResolverParams& aAdditionalParameters) const
	{
	const TInt count = aImplementationsInfo.Count();
	for (TInt i = 0; i < count; ++i)
		{
		const CImplementationInformation& impData = *aImplementationsInfo[i];

		if (Match (impData.DataType(), aAdditionalParameters.DataType(),
			aAdditionalParameters.IsWildcardMatch()))
			{
			return impData.ImplementationUid();
			}
		}

	return KNullUid;
	}




RImplInfoArray* CUIResolver::ListAllL (TUid aInterfaceUid,
	const TEComResolverParams& aAdditionalParameters) const
	{
	RImplInfoArray* retList = new(ELeave) RImplInfoArray;
	CleanupStack::PushL (retList);

	RImplInfoArray& fullList = iRegistry.ListImplementationsL (aInterfaceUid);

	const TBool useWildcards = aAdditionalParameters.IsWildcardMatch();
	const TDesC8& matchType = aAdditionalParameters.DataType();
	const TInt numImps = fullList.Count();

	for (TInt i = 0; i < numImps; ++i)
		{
		if (Match (fullList[i]->DataType(), matchType, useWildcards))
			{
			User::LeaveIfError (retList->Append (fullList[i]));
			}
		}

	CleanupStack::Pop (retList);

	return retList;
	}




TBool CUIResolver::Match (const TDesC8& aImplementationType,
	const TDesC8& aMatchType, TBool aUseWildcards) const
	{
	TInt matchPos = KErrNotFound;

	if (aUseWildcards)
			matchPos = aImplementationType.MatchF (aMatchType);
	else
			matchPos = aImplementationType.CompareF (aMatchType);

	return matchPos != KErrNotFound;
	}


