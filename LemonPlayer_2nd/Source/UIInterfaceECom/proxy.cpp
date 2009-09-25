/**
*
* @brief Definition of Proxy for ShapeResolver
*
* Copyright (c) EMCC Software Ltd 2003
* @version 1.0
*/

#include <e32std.h>
#include <ImplementationProxy.h>

#include "UIResolver.h"

const TImplementationProxy ImplementationTable[] =
	{
		{{0x0116C9D6},	CUIResolver::NewL}
	};




EXPORT_C const TImplementationProxy* ImplementationGroupProxy (TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);

	return ImplementationTable;
	}

