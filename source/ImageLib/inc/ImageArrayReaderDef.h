#ifndef IMAGEARRAYREADERDEF_H_
#define IMAGEARRAYREADERDEF_H_

#include "MacroUtil.h"

_LIT(KImageArrayDomTagImage,"image");
_LIT(KImageArrayDomTagImg,	"img");

_LIT(KImageArrayAttrNumber,	"number");
_LIT(KImageArrayAttrIndex,	"index");
_LIT(KImageArrayAttrFile,	"file");

enum TImageArrayTag
	{
	EImageArrayTagNone = 0,
	EImageArrayTagImage,
	EImageArrayTagImg,
	};

typedef struct _ImageArrayConvertStruct
	{
	TInt index;
	HBufC* filename;
	
	_ImageArrayConvertStruct()
		{
		filename = NULL;
		}
	
	~_ImageArrayConvertStruct()
		{
		SAFE_DELETE(filename);
		}
	}ImageArrayConvertStruct,*pImageArrayConvertStruct;
#endif /*IMAGEARRAYREADERDEF_H_*/
