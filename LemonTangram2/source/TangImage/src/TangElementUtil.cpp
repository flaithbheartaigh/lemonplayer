#include "TangElementUtil.h"

static const TInt MAJOR_VALUE = 10;
static const TInt NEXT_VALUE  = 5;
//Y¾àÀë×îÐ¡

static const TInt offsetTangram[7][2] = { {0,50},{-50,0},{25,0},{-50,-75},{75,-75},{0,-50},{75,25},};

int TangElementUtil::FindNearestHori(CImageElement** aElements,TInt aIndex,
		TImageMoveDirection aDirection)
	{
	TInt re = aIndex;
	TInt offset = 10000;
	TInt temp,temp2,temp3;
	TInt x,y,ox,oy;
		
	ox = aElements[aIndex]->GetPositionX() + offsetTangram[aIndex][0];
	oy = aElements[aIndex]->GetPositionY() + offsetTangram[aIndex][1];
		
	for(TInt i=0; i<EImageNumber; i++)
		{
		
		x = aElements[i]->GetPositionX() + offsetTangram[i][0];
		y = aElements[i]->GetPositionY() + offsetTangram[i][1];
		
		if (aIndex != i)
			{
			if (aDirection == EMoveEast)
				{
				temp = x - ox;
				}
			else if (aDirection == EMoveWest)
				{
				temp = ox - x;
				}
			else
				return re;
			
			if (temp > 0)
				{
//				temp2 = aElements[i]->GetPositionY() - aElements[aIndex]->GetPositionY();
//				if (temp2<0)
//					temp2 = -temp2;
//				temp3 = temp * MAJOR_VALUE + temp2 * NEXT_VALUE;
				temp3 = temp;
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
	TInt x,y,ox,oy;
	
	ox = aElements[aIndex]->GetPositionX() + offsetTangram[aIndex][0];
	oy = aElements[aIndex]->GetPositionY() + offsetTangram[aIndex][1];
	
	for(TInt i=0; i<EImageNumber; i++)
		{
		x = aElements[i]->GetPositionX() + offsetTangram[i][0];
		y = aElements[i]->GetPositionY() + offsetTangram[i][1];
		
		if (aIndex != i)
			{
			if (aDirection == EMoveSouth)
				{
				temp = y - oy;
				}
			else if (aDirection == EMoveNorth)
				{
				temp = oy - y;
				}
			else
				return re;
			
			if (temp > 0)
				{
//				temp2 = aElements[i]->GetPositionX() - aElements[aIndex]->GetPositionX();
//				if (temp2<0)
//					temp2 = -temp2;
//				temp3 = temp * MAJOR_VALUE + temp2 * NEXT_VALUE;
				temp3 = temp;
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
