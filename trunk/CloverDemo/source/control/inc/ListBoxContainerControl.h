/*
 ============================================================================
 Name		: ListBoxContainerControl.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CListBoxContainerControl declaration
 ============================================================================
 */

#ifndef LISTBOXCONTAINERCONTROL_H
#define LISTBOXCONTAINERCONTROL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "BaseControl.h"

class CListBoxItemControl;
class CScrollControl;
class CListBoxPainter;
class CListBoxHighLightControl;
// CLASS DECLARATION

/**
 *  CListBoxContainerControl
 * 
 */
class CListBoxContainerControl : public CBaseControl
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CListBoxContainerControl();

	/**
	 * Two-phased constructor.
	 */
	static CListBoxContainerControl* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CListBoxContainerControl* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CListBoxContainerControl();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	//from base
	virtual void Draw(CBitmapContext& gc) const;
	
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	
	virtual void SetRect(const TRect &aRect);
	
	virtual void ReSize(const TRect &aRect);
	
	virtual void SetAnimation(CAnimationFrame* aAnimation); 
	
	//new func
	void AddItem(CListBoxItemControl* aItem);
	
	void StartAnimationScrollDown();	
	TInt AnimationScrollDown();	
	static TInt CallbackAnimationScrollDown( TAny* aThis );
	
	void StartAnimationScrollUp();	
	TInt AnimationScrollUp();	
	static TInt CallbackAnimationScrollUp( TAny* aThis );
	
	void StartAnimationResize();	
	TInt AnimationResize();	
	static TInt CallbackAnimationResize( TAny* aThis );
	
	void StopAnimation();
	
	void CheckMarquee();
	
private:
	RPointerArray<CListBoxItemControl> *iItems;
	CListBoxHighLightControl* iHighLight;
	CScrollControl* iScroll;	//滚动条
	
	CListBoxPainter* iPainter;	//控制字体大小,item高度等.
		
	TPoint 	iActualPoint;		//实际占用空间,相对于可使空间来说
	TSize	iActualSize;
	
	TInt 	iSelectedIndex;		//选中索引
	TBool	iEnableRing;		//是否环移动,即到达最底部后,继续向下,可以移动到顶部
	
	TInt 	iItemScrollFrame;
	
	TCallBack* iCallFunc;		//not own
	
	TSize	iOldSize;
	TInt 	iResizeOffset;
	};

#endif // LISTBOXCONTAINERCONTROL_H
