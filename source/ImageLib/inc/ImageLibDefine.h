#ifndef IMAGELIBDEFINE_H_
#define IMAGELIBDEFINE_H_

#include <fbs.h>

#include "MacroUtil.h"

typedef struct _UiImageStruct
	{
	TInt index;
	TInt x;
	TInt y;
	CFbsBitmap *bitmap;
	
	_UiImageStruct()
		{
		bitmap = NULL;
		}
	
	~_UiImageStruct()
		{
		SAFE_DELETE(bitmap);
		}
	
	} UiImageStruct, *PUiImageStruct;

typedef struct _TangramImageStruct
	{
	TInt index;
	TInt x;
	TInt y;
	} TangramImageStruct, *PTangramImageStruct;
	
#endif /*IMAGELIBDEFINE_H_*/
