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
	CScrollControl* iScroll;	//������
	
	CListBoxPainter* iPainter;	//���������С,item�߶ȵ�.
		
	TPoint 	iActualPoint;		//ʵ��ռ�ÿռ�,����ڿ�ʹ�ռ���˵
	TSize	iActualSize;
	
	TInt 	iSelectedIndex;		//ѡ������
	TBool	iEnableRing;		//�Ƿ��ƶ�,��������ײ���,��������,�����ƶ�������
	
	TInt 	iItemScrollFrame;
	
	TCallBack* iCallFunc;		//not own
	
	TSize	iOldSize;
	TInt 	iResizeOffset;
	};

#endif // LISTBOXCONTAINERCONTROL_H
