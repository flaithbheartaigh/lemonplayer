#ifndef LISTSTRUCTURE_
#define LISTSTRUCTURE_

#include <e32base.h>

enum TFileItemType
	{
	EItemTypeDir = 0,
	EItemTypeMusic,
	EItemTypeFile,
	EItemTypeTotal
	};

struct TListItem
	{
	TFileName iFullpath;
	TFileName iName;
	TInt 	  iPref;
	};

#endif /*LISTSTRUCTURE_*/
