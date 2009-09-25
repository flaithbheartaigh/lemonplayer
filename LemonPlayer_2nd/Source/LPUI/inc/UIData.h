#ifndef UIDATA_H_
#define UIDATA_H_

#include <e32std.h>
#include <e32base.h>
#include <badesca.h>
#include "MacroUtil.h"

class UIXmlParser;
class CFbsBitmap;
class CMusicInfoBean;
class CPlayingListData;

typedef struct _ControlViewData
	{
	TInt index;
	TInt x;
	TInt y;
	CFbsBitmap* bitmap;
	TBool isShow;
	TReal32 iSlip;
	
	_ControlViewData()
		{
		bitmap = NULL;
		}
	
	~_ControlViewData()
		{
		SAFE_DELETE(bitmap);
		}
	}ControlViewData,*pControlViewData;
	
class UIData
{
public:
	UIData();
	virtual ~UIData();
};

_LIT(KCtrlXmlElemControl,"control");
		
_LIT(KCtrlXmlAttrName,"name");
_LIT(KCtrlXmlNamePlay,"play");
_LIT(KCtrlXmlNamePause,"pause");
_LIT(KCtrlXmlNameStop,"stop");
_LIT(KCtrlXmlNameVolumeItem,"volumeitem");
_LIT(KCtrlXmlNameVolumeSlip,"volumeslip");

_LIT(KCtrlXmlAttrX,"x");
_LIT(KCtrlXmlAttrY,"y");
_LIT(KCtrlXmlAttrImg,"img");
_LIT(KCtrlXmlAttrSlip,"slip");

enum TControlIndex
	{
	KCtrlIndexPlay = 0,
	KCtrlIndexPause,
	KCtrlIndexStop,
	KCtrlIndexVolumeItem,
	KCtrlIndexVolumeSlip,
	KCtrlIndexTotal
	};

enum TPlayerState
	{
	KPlayerStatePlay = 0,
	KPlayerStatePause,
	KPlayerStateStop
	};

enum TPlayModel
	{
	KPlayModelSequence = 0, 
	KPlayModelLoop,
	KPlayModelRandom
	};

#define VOLUME_MAX		 100	//声音最大值
#define VOLUME_BLOCKS 	 10 	//声音一共用多少格显示
#define VOLUME_PER_BLOCK 10		//每格音量

class CUIViewData : public CBase
	{
public:
	// Constructors and destructor
	~CUIViewData();
	static CUIViewData* NewL();
	static CUIViewData* NewLC();
	
	static CUIViewData* GetInstance();
	
	TInt Count(){return KCtrlIndexTotal;};
	void SetData(TInt index,pControlViewData aData);
	pControlViewData GetData(TInt andex);
	
	//播放状态
	TPlayerState GetPlayerState(){return iPlayerState;};
	void SetPlayerState(TPlayerState aPlayerState)
		{iPlayerState = aPlayerState;};
	
	//播放列表
	void ResetSelectFile();	
	void AddSelectFile(const TDesC& aFileName);
	const TPtrC GetSelectFile(); 
	void SetPlayModel(TPlayModel aModel);
	TPlayModel GetPlayModel();
	TInt GetCurSelectFile(){return iCurSelectFile;};
	void SetCurSelectFile(TInt iCur){iCurSelectFile = iCur;};
	TInt GetNextSelectFile(){return iNextSelectFile;};
	void SetNextSelectFile(TInt iNext){iNextSelectFile = iNext;};
	void CheckSelectFileIndex();
	CDesCArrayFlat* GetSelectFileList(){return iSelectFileList;};
	
	RPointerArray<CMusicInfoBean>* GetPlaylistArray();
	CPlayingListData* GetPlayList () const {return iPlaylistFiles;};
		
private:
	TBool NextSelectFile();
	void ReleaseSelectFile();
	
public:
	void InitVolume(TInt iMax);
	TInt GetVolume();
	TInt GetDrawVolume();
	void SetVolume(TInt aVolume);
	void AddVolumeOneBlock();
	void DecVolumeOneBlock();
	
private:
	void ReleaseData(TInt index);
	TBool IsOutOfBound(TInt index);

private:
	CUIViewData();
	void ConstructL();
	
private:
	static CUIViewData* iInstance;
	
	ControlViewData **iControlList;
	TPlayerState iPlayerState;
	
//	HBufC* 	iSelectFile;
	CDesCArrayFlat* iSelectFileList;
	TPlayModel iPlayModel;
	TInt iCurSelectFile;
	TInt iNextSelectFile;
	
	TReal iAvgVolume;	//分成100分,每份的数量
	TInt  iCurVolume;
	
	//播放列表
	CPlayingListData* iPlaylistFiles;
//	RPointerArray<CMusicInfoBean>* iPlaylistFileArray;
	};

#endif /*UIDATA_H_*/
