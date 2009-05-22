#ifndef _TANGIMAGEDEFINE_H_
#define	_TANGIMAGEDEFINE_H_

enum EImageElementsName
	{
	KImageBigTriangle1 = 0,
	KImageBigTriangel2,
	KImageMidTriange,
	KImageSmallTriangle1,
	KImageSmallTriangle2,
	EImageRect,
	EImageSquare,
	EImageNumber
	};
enum EImageElementState
	{
	KImageStateNone = 0,
	KImageStateLoad,
	KImageStateRotate
	};

enum TImageMoveDirection
	{
	EMoveNorth = 0,
	EMoveEast,
	EMoveSouth,
	EMoveWest
	};


#endif 	//_TANGIMAGEDEFINE_H_