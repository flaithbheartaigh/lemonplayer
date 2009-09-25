/*
 ============================================================================
 Name		: CustomControlList.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : �Զ����б�
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
//�������ұ߾�	
#define CC_LIST_PADDING_UP 		1
#define CC_LIST_PADDING_DOWN 	1
#define CC_LIST_PADDING_LEFT 	1
#define CC_LIST_PADDING_RIGHT 	1
//���ּ�߾�	
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
	//��ʼ����
	void LoadL();	
	//�ͷ�����
	void Release();
	//��ʼ������
	void InitData(TPoint aDisplayPoint, TSize aDisplaySize, TSize aOriginalSize);
	//����
	void Draw(CBitmapContext& gc);
	//�Ϸ����ƶ�
	TInt Update(ECustomControlDirection aDirection);		
	
	void InitData();
	void AddItem(pListItemStruct aItem);
	void AddItem(const TDesC& aItem);
	void AddItem(const TDesC& aItem,TInt aHideIndex);
	void ClearItem();
	
	void ResetItem(RPointerArray<ListItemStruct>* aList);
	
	pListItemStruct GetCurrentItem();
private:
	//ͼ��
	CArrayPtr<CGulIcon>* iIcons;
	//�洢����
	RPointerArray<ListItemStruct> *iList;
	//����λ��
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
