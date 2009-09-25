/*
 ============================================================================
 Name		: CustomControlList.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : 自定义列表
 ============================================================================
 */

#ifndef CUSTOMCONTROLLIST_H
#define CUSTOMCONTROLLIST_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "CustomControlDefine.h"
#include <w32std.h>
#include <gulicon.h>
#include "MacroUtil.h"


	
// CLASS DECLARATION
//上下左右边距	
#define CC_LIST_PADDING_UP 		1
#define CC_LIST_PADDING_DOWN 	1
#define CC_LIST_PADDING_LEFT 	1
#define CC_LIST_PADDING_RIGHT 	1
//文字间边距	
#define CC_LIST_MARGIN_HORI 1
#define CC_LIST_MARGIN_VERT 1
/**
 *  CCustomControlList
 * 
 */
class CCustomControlList : public CBase
	{
public:
	~CCustomControlList();
	static CCustomControlList* NewL();
	static CCustomControlList* NewLC();

private:
	CCustomControlList();
	void ConstructL();
	
public:
	//初始数据
	void LoadL();	
	//释放数据
	void Release();
	//初始化数据
	void InitData(TPoint aDisplayPoint, TSize aDisplaySize, TSize aOriginalSize);
	//绘制
	void Draw(CBitmapContext& gc);
	//上方向移动
	TInt Update(ECustomControlDirection aDirection);		
	
	void InitData();
	void AddItem(pListItemStruct aItem);
	void AddItem(const TDesC& aItem);
	void AddItem(const TDesC& aItem,TInt aHideIndex);
	void ClearItem();
	
	void ResetItem(RPointerArray<ListItemStruct>* aList);
	
	pListItemStruct GetCurrentItem();
private:
	//图标
	CArrayPtr<CGulIcon>* iIcons;
	//存储数据
	RPointerArray<ListItemStruct> *iList;
	//绘制位置
	TPoint iDisplayPoint;
	TSize iDisplaySize;
	
	TInt iRowHeight;
	TInt iFontHeight;
	
	TRgb iTextColor;
	TRgb iSelectTextColor;
	CFbsBitmap* iSelectBitmap;  
	
	TInt iSelectIndex;
	TPoint iSelectPoint;
	TSize iSelectSize;
	
	TInt iScrollSize;
	
	TPoint iDrawPoint;
	
	const CFont* iFont;
	};

#endif // CUSTOMCONTROLLIST_H
