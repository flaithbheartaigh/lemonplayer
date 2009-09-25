#ifndef CUSTOMCONTROLDEFINE_H_
#define CUSTOMCONTROLDEFINE_H_

#include "MacroUtil.h"
#include "PlaylistDefine.h"

enum ECustomControlDirection
	{
	KCustomControlDirectionUp,
	KCustomControlDirectionDown
	};

//�б�ڵ�
typedef struct _ListItemStruct
	{
	TInt iIconIndex;	//icon
	HBufC* iShowName;	//��ʾ����
	TInt iHideIndex;	//��������
	HBufC* iHideInfo;	//������Ϣ
	EPlaylistItemType iType;
	
	_ListItemStruct()
		{
		iShowName = NULL;
		iHideInfo = NULL;
		iHideIndex = KErrNotFound;
		}
	
	~_ListItemStruct()
		{
		SAFE_DELETE(iShowName);
		SAFE_DELETE(iHideInfo);
		}
	
	}ListItemStruct, *pListItemStruct;
	
#endif /*CUSTOMCONTROLDEFINE_H_*/
