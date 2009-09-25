/**
*
* @brief Definition of Proxy
*
* Copyright (c) EMCC Software Ltd 2003
* @version 1.0
*/

//System Include
#include <e32std.h>
#include <implementationproxy.h>

//User Include
#include "UIMain.h"
#include "UIList.h"

const TImplementationProxy ImplementationTable[] =
	{
		{{0x0116C9D8},	CUIMain::NewL},
		{{0x0116C9D9},	CUIList::NewL}
	};



EXPORT_C const TImplementationProxy* ImplementationGroupProxy (TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
	return ImplementationTable;
	}

