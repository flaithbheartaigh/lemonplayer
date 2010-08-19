/*
 * GestureDef.h
 *
 *  Created on: 2010-2-1
 *      Author: johnzeng
 */

#ifndef GESTUREDEF_H_
#define GESTUREDEF_H_

enum TGestureType
{
	ENoneGesture = -1,
	EUpDown,
	EDownUp,
	ERightLeft,
	ELeftRight,
	ELeftUpRightDown,
	ELeftDownRightUp,
	ERightUpLeftDown,
	ERightDownLeftUp	
};

enum TPositionType
{
	ENonePosition = -1,
	EAreaA,
	EAreaB,
	EAreaC,
	EAreaD
};

#endif /* GESTUREDEF_H_ */
