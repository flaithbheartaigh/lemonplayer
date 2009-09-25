/*
 ============================================================================
 Name		: PlaylistControl.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPlaylistControl declaration
 ============================================================================
 */

#ifndef PLAYLISTCONTROL_H
#define PLAYLISTCONTROL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <badesca.h>
#include <w32std.h>
#include "CustomControlDefine.h"
// CLASS DECLARATION
class CCustomControlList;
/**
 *  CPlaylistControl
 * 
 */
class CPlaylistControl : public CBase
	{
public:
	~CPlaylistControl();
	static CPlaylistControl* NewL();
	static CPlaylistControl* NewLC();

private:
	CPlaylistControl();
	void ConstructL();
	
public:
	void SetShowDesArray(CDesCArrayFlat& aDesArray);
	void SetShowDesArray(RPointerArray<ListItemStruct>* aList);
	void Draw(CBitmapContext& gc);
	
	TInt Update(ECustomControlDirection aDirection);
	
	void CleanList();
	void AddListItem(const TDesC& aName,TInt aIndex);
	void AddListItem(pListItemStruct aItem);
	
	//����ѡ��
	void SelectEvent();
	//��ǰѡ�������
	pListItemStruct GetCurrentItem();
	
private:
	CCustomControlList* iList;

	};

#endif // PLAYLISTCONTROL_H
