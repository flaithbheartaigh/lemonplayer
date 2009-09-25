
#ifndef __SHAPERESOLVER_H__
#define __SHAPERESOLVER_H__

#include <resolver.h>

/**
*
* @class	CShapeResolver ShapeResolver.h
* @brief	This is a custome resolver class for the EComShape example
*
* Copyright (c) EMCC Software Ltd 2003
* @version	1.0
*
*/

class CUIResolver : public CResolver
	{
	public:

	static CUIResolver* NewL (MPublicRegistry& aRegistry);

	virtual ~CUIResolver();

	virtual TUid IdentifyImplementationL (TUid aInterfaceUid,
		const TEComResolverParams& aAdditionalParameters) const;

	virtual RImplInfoArray* ListAllL (TUid aInterfaceUid,
		const TEComResolverParams& aAdditionalParameters) const;

private:
	CUIResolver (MPublicRegistry& aRegistry);

	TUid Resolve (const RImplInfoArray& aImplementationsInfo,
		const TEComResolverParams& aAdditionalParameters) const;

	TBool Match (const TDesC8& aImplementationType,  const TDesC8& aMatchType,
		TBool aUseWildcards) const;

	};

#endif

