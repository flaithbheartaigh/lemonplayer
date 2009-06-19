#ifndef TANGELEMENTUTIL_H_
#define TANGELEMENTUTIL_H_

#include "ImageElement.h"
#include "TangImageDefine.h"

class TangElementUtil
	{
public:
	static int FindNearestHori(CImageElement** aElements,TInt aIndex,TImageMoveDirection aDirection);
	static int FindNearestVert(CImageElement** aElements,TInt aIndex,TImageMoveDirection aDirection);
	};
#endif /*TANGELEMENTUTIL_H_*/
