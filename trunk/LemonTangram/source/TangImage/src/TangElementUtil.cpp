#include "TangElementUtil.h"

static const TInt MAJOR_VALUE = 10;
static const TInt NEXT_VALUE  = 5;
//Yæ‡¿Î◊Ó–°
int TangElementUtil::FindNearestHori(CImageElement** aElements,TInt aIndex,
		TImageMoveDirection aDirection)
	{
	TInt re = aIndex;
	TInt offset = 10000;
	TInt temp,temp2,temp3;
	for(TInt i=0; i<EImageNumber; i++)
		{
		if (aIndex != i)
			{
			if (aDirection == EMoveEast)
				{
				temp = aElements[i]->GetPositionX() - aElements[aIndex]->GetPositionX();
				}
			else if (aDirection == EMoveWest)
				{
				temp = aElements[aIndex]->GetPositionX() - aElements[i]->GetPositionX();
				}
			else
				return re;
			
			if (temp > 0)
				{
				temp2 = aElements[i]->GetPositionY() - aElements[aIndex]->GetPositionY();
				if (temp2<0)
					temp2 = -temp2;
				temp3 = temp * MAJOR_VALUE + temp2 * NEXT_VALUE;
				if (temp3 < offset)
					{
					offset = temp3;
					re = i;
					}
				}
			}
		}
	return re;
	}

int TangElementUtil::FindNearestVert(CImageElement** aElements,TInt aIndex,TImageMoveDirection aDirection)
	{
	TInt re = aIndex;
	TInt offset = 1000;
	TInt temp,temp2,temp3;
	for(TInt i=0; i<EImageNumber; i++)
		{
		if (aIndex != i)
			{
			if (aDirection == EMoveSouth)
				{
				temp = aElements[i]->GetPositionY() - aElements[aIndex]->GetPositionY();
				}
			else if (aDirection == EMoveNorth)
				{
				temp = aElements[aIndex]->GetPositionY() - aElements[i]->GetPositionY();
				}
			else
				return re;
			
			if (temp > 0)
				{
				temp2 = aElements[i]->GetPositionX() - aElements[aIndex]->GetPositionX();
				if (temp2<0)
					temp2 = -temp2;
				temp3 = temp * MAJOR_VALUE + temp2 * NEXT_VALUE;
				if (temp3 < offset)
					{
					offset = temp3;
					re = i;
					}
				}
			}
		}
	return re;	
	}