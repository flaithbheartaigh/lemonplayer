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

static const TInt TANGRAM_ELEMENT_MAX_ACCELERATION = 12;
static const TInt TANGRAM_ELEMENT_MOVE = 2;
static const TInt TANGRAM_ELEMENT_MOVE_X = 2;
static const TInt TANGRAM_ELEMENT_MOVE_Y = 2;
static const TInt TANGRAM_ELEMENT_OFFSET_ROTATOE_ACCELERATION = 5;
static const TInt TANGRAM_ELEMENT_MAX_ROTATOE_ACCELERATION = 20;
static const TInt TANGRAM_ELEMENT_ROTATOE_DEGREE = 5;

static const TInt TANGRAM_SCROLL_MOVE = 5; 

#endif 	//_TANGIMAGEDEFINE_H_