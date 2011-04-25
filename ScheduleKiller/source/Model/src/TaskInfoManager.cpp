/*
 ============================================================================
 Name		: TaskInfoManager.cpp
 Author	  : JohnLZeng
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTaskInfoManager implementation
 ============================================================================
 */

#include "TaskInfoManager.h"
#include "SHPlatform.h"
#include <aknsskininstance.h> 
#include <aknsutils.h> 
#include <aknkeylock.h> 
#include "AppDefine.h"
#include "LMSvgUtil.h"
CTaskInfoManager::CTaskInfoManager()
	{
	// No implementation required
	}

CTaskInfoManager::~CTaskInfoManager()
	{
	SAFE_DELETE_RPONTERARRAY(iTaskList)
	}

CTaskInfoManager* CTaskInfoManager::NewLC()
	{
	CTaskInfoManager* self = new (ELeave) CTaskInfoManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CTaskInfoManager* CTaskInfoManager::NewL()
	{
	CTaskInfoManager* self = CTaskInfoManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CTaskInfoManager::ConstructL()
	{
	iTaskList = new (ELeave) RPointerArray<TaskInfo>;
	}

void CTaskInfoManager::ConvertClockNumber()
	{
	for(TInt i=0; i<iTaskList->Count(); i++)
		{
		TaskInfo* task = (*iTaskList)[i];
		ConvertClock(task->iTime,task->iNumArray);
		}
	}

void CTaskInfoManager::ConvertClock(const TTime& aTime,RArray<TInt>& aArray )
	{
	TTime now;
	now.HomeTime();

	aArray.Reset();
	if (aTime > now)
		ParseLeftTime((TInt) (aTime.MicroSecondsFrom(now).Int64() / 1000000ll),
				aArray);
	}

TInt CTaskInfoManager::ParseLeftTime(TInt aSecend, RArray<TInt>& aArray)
	{
	TInt minute, secend;
	minute = aSecend / 60;
	secend = aSecend % 60;

	if (minute >= 10)
		{
		ParseNumber(minute, aArray);
		}
	else if (minute > 0)
		{
		aArray.Append(0);
		aArray.Append(minute);
		}
	else
		{
		aArray.Append(0);
		aArray.Append(0);
		}

	aArray.Append(10); //:

	aArray.Append(secend / 10);
	aArray.Append(secend % 10);

	return KErrNone;
	}

TInt CTaskInfoManager::ParseNumber(TInt aNumber, RArray<TInt>& aArray)
	{
	TInt high = aNumber / 10;
	TInt low = aNumber % 10;

	while (high)
		{
		aArray.Insert(low, 0);

		low = high % 10;
		high = high / 10;
		}
	aArray.Insert(low, 0);

	return KErrNone;
	}

TBool CTaskInfoManager::IsDuplicate(const TUid& aUid)
	{
	for (TInt i=0; i<iTaskList->Count(); i++)
		{
		pTaskInfo task = (*iTaskList)[i];
		if (task->iUid == aUid)
			return ETrue;
		}
	return EFalse;
	}
TBool CTaskInfoManager::AppendTask(const TUid& aUid,const TDesC& aName,const TTime& aTime)
	{
	if (IsDuplicate(aUid))
		return EFalse;
	
	pTaskInfo task = new TaskInfo;
	task->iUid = aUid;
	task->iName.Copy(aName);
	task->iTime = aTime;
	
	CGulIcon* icon;
	if (aUid == UID_SHUTDOWN)
		{
		icon = LMSvgUtil::GetIconFormResourceL(EMbmSchedulekillerShutdown,
				EMbmSchedulekillerShutdown_mask);
		}
	else
		{
		CFbsBitmap* AppIcon(NULL);
		CFbsBitmap* AppIconMsk(NULL);
		MAknsSkinInstance* skin = AknsUtils::SkinInstance();
		TRAPD(err, AknsUtils::CreateAppIconLC(skin, aUid, EAknsAppIconTypeList, AppIcon, AppIconMsk);CleanupStack::Pop(2));
	
		
		if (err == KErrNone)
			{
			icon = CGulIcon::NewL(AppIcon, AppIconMsk);
			}
		else
			{
			icon = AknsUtils::CreateGulIconL(skin, KAknsIIDQgnMenuUnknownLst,
					ETrue);
			}
		}
	task->iIcon = icon;
	
	ConvertClock(aTime,task->iNumArray);
	
	iTaskList->Append(task);
	return ETrue;
	}

TInt CTaskInfoManager::AppendTask(const TDesC& aName,const TUid& aUid, const TInt& aType, 
		const TInt& aCountDown,const TTime& aTime)
	{
	if (IsDuplicate(aUid))
		return ETaskErrDuplicate;
	
	SHModel()->GetRuleManager()->AppendFavRule(aName,aUid,aType,aCountDown,aTime);
	
	TTime time;
	if (aType == 0)
		{
		time.HomeTime();
		time += TTimeIntervalMinutes(aCountDown);
		}
	else
		{
		TTime now;
		now.HomeTime();
		time = aTime;
		if (time <= now)
			return ETaskErrTimeOut;
		}
	
	pTaskInfo task = new TaskInfo;
	task->iUid = aUid;
	task->iName.Copy(aName);
	task->iTime = time;
	
	CGulIcon* icon;
	if (aUid == UID_SHUTDOWN)
		{
		icon = LMSvgUtil::GetIconFormResourceL(EMbmSchedulekillerShutdown,
				EMbmSchedulekillerShutdown_mask);
		}
	else
		{
		CFbsBitmap* AppIcon(NULL);
		CFbsBitmap* AppIconMsk(NULL);
		MAknsSkinInstance* skin = AknsUtils::SkinInstance();
		TSize size = SHUI()->GetIconSize();
		TRAPD(err, AknsUtils::CreateAppIconLC(skin, aUid, EAknsAppIconTypeList, AppIcon, AppIconMsk);CleanupStack::Pop(2));
	
		if (err == KErrNone)
			{
			icon = CGulIcon::NewL(AppIcon, AppIconMsk);
			}
		else
			{
			icon = AknsUtils::CreateGulIconL(skin, KAknsIIDQgnMenuUnknownLst,
					ETrue);
			}
		}
	task->iIcon = icon;
	
	ConvertClock(time,task->iNumArray);
	
	iTaskList->Append(task);
	return ETaskErrNone;
	}
	

void CTaskInfoManager::RemoveTask(TInt aIndex)
	{
	if (aIndex < 0 || aIndex >= iTaskList->Count())
		return;
	
	pTaskInfo task = (*iTaskList)[aIndex];
	
	iTaskList->Remove(aIndex);
	delete task;
	}

const TTime& CTaskInfoManager::GetMinTime() const
{
	ASSERT(iTaskList->Count() != 0);
	
	TInt index = 0;
	TTime time = (*iTaskList)[0]->iTime;
	
	for(TInt i=1; i<iTaskList->Count(); i++)
		{
		pTaskInfo task = (*iTaskList)[i];
		if (time > task->iTime)
			{
			index = i;
			time = (*iTaskList)[i]->iTime;
			}
		}
	return (*iTaskList)[index]->iTime;
}

void CTaskInfoManager::TimeOut()
	{
	for (TInt i=iTaskList->Count()-1; i>=0; i--)
		{
		pTaskInfo task = (*iTaskList)[i];
		TTime time;
		time.HomeTime();
		if (task->iTime <= time)
			{
			KillProcess(task->iUid);
			
			iTaskList->Remove(i);
			delete task;
			}
		}
	}

TBool CTaskInfoManager::ExistTask()
	{
	return iTaskList->Count()>0;
	}

void CTaskInfoManager::KillProcess(const TUid& aUid)
	{
	if (aUid == UID_SHUTDOWN)
		{
		ShutDown();
		}
	else
		{
		TApaTaskList taskList(CEikonEnv::Static()->WsSession());
		TApaTask task = taskList.FindApp(aUid);
		if (task.Exists())
			{
			task.EndTask();
			task.KillTask();
			}
		}
	}

void CTaskInfoManager::ShutDown()
	{
	//½âËø
	RAknKeylock2 keyLock;
	if (keyLock.Connect() == KErrNone )
		{
		keyLock.DisableWithoutNote();
		}
	keyLock.Close();
	
	TRawEvent iRawEvent;
	iRawEvent.Set(TRawEvent::EKeyDown,EStdKeyDevice2);
	UserSvr::AddEvent(iRawEvent);
	iRawEvent.Set(TRawEvent::EKeyRepeat,EStdKeyDevice2);
	UserSvr::AddEvent(iRawEvent);
	}

void CTaskInfoManager::InitTest()
	{
	TTime time;
	time.HomeTime();
	//	time += TTimeIntervalSeconds(10);
	time += TTimeIntervalMinutes(30);
	
	for(TInt i=0; i<5; i++)
		AppendTask(TUid::Uid(0x101FF976),_L("Radio"),time);
	}
