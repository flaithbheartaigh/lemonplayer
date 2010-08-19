/*
 ============================================================================
 Name		: AnimationFrame.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CAnimationFrame declaration
 ============================================================================
 */

#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CAnimationFrame
 * 
 */
class MAnimationNofity
	{
public:
	virtual void AnimationCallback() = 0;
	};

class CAnimationFrame
	{
public:
	// Constructors and destructor

	virtual ~CAnimationFrame();
	CAnimationFrame(MAnimationNofity& aNotify);
	
public:	
	TInt AppendAnimation(TCallBack* aFunc);
	void RemoveAnimation(const TInt& aIndex);
	void RemoveAnimation(TCallBack* aFunc);
	
	void StartTimer();
	TInt Animation();
	
private:
	static TInt Callback( TAny* aThis );

protected:
	MAnimationNofity& iNotify;
	
	CPeriodic* iAnimer;	
	RPointerArray<TCallBack>* iFuncs;
	};

#endif // ANIMATIONFRAME_H
