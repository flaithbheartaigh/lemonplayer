#ifndef CUSTOMCONTROLDEFINE_H_
#define CUSTOMCONTROLDEFINE_H_

#include "MacroUtil.h"
#include "PlaylistDefine.h"

enum ECustomControlDirection
	{
	KCustomControlDirectionUp,
	KCustomControlDirectionDown
	};

//列表节点
typedef struct _ListItemStruct
	{
	TInt iIconIndex;	//icon
	HBufC* iShowName;	//显示名字
	TInt iHideIndex;	//保存索引
	HBufC* iHideInfo;	//保存信息
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
