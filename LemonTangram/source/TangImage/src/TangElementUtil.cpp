#include "TangElementUtil.h"

//Yæ‡¿Î◊Ó–°
int TangElementUtil::FindNearestHori(CImageElement** aElements,TInt aIndex,TImageMoveDirection aDirection)
	{
	TInt re = aIndex;
	TInt offset = 1000;
	TInt temp;
	for(TInt i=0; i<EImageNumber; i++)
		{
		if (aIndex != i)
			{
			if (aDirection == EMoveEast)
				{
				temp = aElements[i]->GetPositionY() - aElements[aIndex]->GetPositionY();
				}
			else if (aDirection == EMoveWest)
				{
				temp = aElements[aIndex]->GetPositionY() - aElements[i]->GetPositionY();
				}
			else
				return re;
			
			if (temp >=0 && offset>temp)
				{
				offset = temp;
				re = i;
				}
			}
		}
	return re;
	}

int TangElementUtil::FindNearestVert(CImageElement** aElements,TInt aIndex,TImageMoveDirection aDirection)
	{
	TInt re = aIndex;
	TInt offset = 1000;
	TInt temp;
	for(TInt i=0; i<EImageNumber; i++)
		{
		if (aIndex != i)
			{
			if (aDirection == EMoveNorth)
				{
				temp = aElements[i]->GetPositionX() - aElements[aIndex]->GetPositionX();
				}
			else if (aDirection == EMoveSouth)
				{
				temp = aElements[aIndex]->GetPositionX() - aElements[i]->GetPositionX();
				}
			else
				return re;
			
			if (temp >=0 && offset>temp)
				{
				offset = temp;
				re = i;
				}
			}
		}
	return re;	
	}