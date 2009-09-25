#include "UIData.h"
#include <stdlib.h>
#include <badesca.h>
#include <fbs.h>
#include "CommonUtils.h"
#include "MacroUtil.h"
#include "PlayingListData.h"
//#include "MusicInfoBean.h"

UIData::UIData()
{
}

UIData::~UIData()
{
}

////////////////////////////////////////////////

CUIViewData  *CUIViewData::iInstance = NULL;    // Attention £¡ 

CUIViewData::CUIViewData():iPlayerState(KPlayerStateStop)
	{
	// No implementation required
	}

CUIViewData::~CUIViewData()
	{
//	iPlaylistFileArray->ResetAndDestroy();
	SAFE_DELETE(iPlaylistFiles);
	
	SAFE_DELETE(iSelectFileList)
	}

CUIViewData* CUIViewData::NewLC()
	{
	CUIViewData* self = new (ELeave)CUIViewData();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CUIViewData* CUIViewData::NewL()
	{
	CUIViewData* self=CUIViewData::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

CUIViewData* CUIViewData::GetInstance()
	{
	if (iInstance == NULL)
		{
		iInstance = CUIViewData::NewL();
		}
	return iInstance;
	}

void CUIViewData::ConstructL()
	{
	iControlList = (ControlViewData**)malloc(sizeof(ControlViewData*)*KCtrlIndexTotal);
	for(TInt i=0; i<KCtrlIndexTotal; i++)
		{
		iControlList[i] = NULL;
		}
//	iSelectFile = KNullDesC().AllocL();
	
	iSelectFileList = new (ELeave)CDesCArrayFlat(10);	
	iPlayModel = KPlayModelRandom;
	
	iCurVolume = VOLUME_MAX/2;
	
	iPlaylistFiles = CPlayingListData::NewL();
//	iPlaylistFileArray = new (ELeave) RPointerArray<CMusicInfoBean>;
	}

void CUIViewData::SetData(TInt index,pControlViewData aData)
	{
	if (IsOutOfBound(index))
		return;
	ReleaseData(index);
	iControlList[index] = aData;
	}

pControlViewData CUIViewData::GetData(TInt index)
	{
	if (!IsOutOfBound(index))
		return iControlList[index];
	else
		return NULL;
	}

TBool CUIViewData::IsOutOfBound(TInt index)
	{
	if (index>=0 && index<KCtrlIndexTotal)
		return EFalse;
	else
		return ETrue;
	}

void CUIViewData::ReleaseData(TInt index)
	{
	if (IsOutOfBound(index))
		return;
	pControlViewData data = iControlList[index];
	if (data)
		{		
		if (data->bitmap)
			{
			delete data->bitmap;
			}
		delete data;
		}
		
	}

void CUIViewData::ResetSelectFile()
	{
	iSelectFileList->Reset();
	iCurSelectFile = 0;
	iNextSelectFile = 0;
	}

void CUIViewData::ReleaseSelectFile()
	{
	iSelectFileList->Reset();
	
	delete iSelectFileList;
	iSelectFileList = NULL;
	}
	
//void CUIViewData::SetSelectFile(const TDesC& aFileName)
//	{
//	iSelectFile = aFileName.AllocL();
//	}

void CUIViewData::AddSelectFile(const TDesC& aFileName)
	{
	iSelectFileList->AppendL(aFileName);
	}

const TPtrC CUIViewData::GetSelectFile()
	{
	iCurSelectFile = iNextSelectFile;
	
	if (NextSelectFile())
		{
		return (*iSelectFileList)[iCurSelectFile];		
		}
	else 
		{
		return KNullDesC().Ptr();
		}
	}

void CUIViewData::SetPlayModel(TPlayModel aModel)
	{
	iPlayModel = aModel;
	}

TPlayModel CUIViewData::GetPlayModel()
	{
	return iPlayModel;
	}

void CUIViewData::CheckSelectFileIndex()
	{
	TInt count = iSelectFileList->Count();
	if (iCurSelectFile >= count)
		{
		iCurSelectFile = count-1;
		}
	if (iNextSelectFile >= count)
		{
		iNextSelectFile = count-1;
		}
	}

TBool CUIViewData::NextSelectFile()
	{
	TBool result = ETrue;
	TInt count = iSelectFileList->Count();
	
	if (count <= 0)
		{
		return EFalse;
		}
	
	switch (iPlayModel)
			{
			case KPlayModelSequence:
				if (++iNextSelectFile>=count)
					{
					result = EFalse;
					}
				break;
			case KPlayModelLoop:
				if (++iNextSelectFile>=count)
					{
					iNextSelectFile = 0;
					}
				break;
			case KPlayModelRandom:
				iNextSelectFile = CCommonUtils::Rand(count);
				break;
			}
	return result;
	}

void CUIViewData::InitVolume(TInt aMax)
	{
	iAvgVolume = aMax / VOLUME_MAX;
	}

TInt CUIViewData::GetVolume()
	{
	return iAvgVolume*iCurVolume;
	}

TInt CUIViewData::GetDrawVolume()
	{
	return iCurVolume;
	}

void CUIViewData::SetVolume(TInt aVolume)
	{
	if (aVolume < 0)
		{
		iCurVolume = 0;
		}
	else if (aVolume > VOLUME_MAX)
		{
		iCurVolume = VOLUME_MAX;
		}
	else
		{
		iCurVolume = aVolume;
		}
	}

void CUIViewData::AddVolumeOneBlock()
	{
	SetVolume(iCurVolume+VOLUME_PER_BLOCK);
	}

void CUIViewData::DecVolumeOneBlock()
	{
	SetVolume(iCurVolume-VOLUME_PER_BLOCK);
	}

RPointerArray<CMusicInfoBean>* CUIViewData::GetPlaylistArray()
	{
	iPlaylistFiles->GetPlaylistArray();
	}