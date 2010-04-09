/*
 ============================================================================
 Name		: ThemeManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CThemeManager implementation
 ============================================================================
 */

#include "ThemeManager.h"
#include <centralrepository.h> // for CRepository
#include <e32math.h>

CThemeManager::CThemeManager() :
	iCurrent(-1)
	{
	// No implementation required
	}

CThemeManager::~CThemeManager()
	{
	iSession.Close();
	}

CThemeManager* CThemeManager::NewLC()
	{
	CThemeManager* self = new (ELeave) CThemeManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CThemeManager* CThemeManager::NewL()
	{
	CThemeManager* self = CThemeManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CThemeManager::ConstructL()
	{
	User::LeaveIfError(iSession.Connect());
	}

TInt CThemeManager::DisplayAll(RArray<TThemeInfo>& aArray)
	{
	CArrayPtr<CAknsSrvSkinInformationPkg>* skinInfoArray =
			iSession.EnumerateSkinPackagesL(EAknsSrvAll );
	//得到所有的主题项,存放到数组

	CleanupStack::PushL(skinInfoArray);

	CRepository* repository = CRepository::NewL(KCRUidPersonalisation);
	
	TInt retValue(KErrNone);
	if (skinInfoArray->Count() > 0)//主题的个数
		{
		for (TInt i = 0; i < skinInfoArray->Count(); i++)
			{
			CAknsSrvSkinInformationPkg* pkg;
			TThemeInfo info;
			TInt pos;

//			TInt err = repository->Get(KPslnActiveSkinLocation, pos);//当前主题的盘符
			
			pkg = skinInfoArray->At(i);
			info.iPID = pkg->PID();
			info.iName.Copy(pkg->Name());
//			if (pos == 0)
//				info.iLoacation = ESknLoactionPhone;
//			else if (pos == 2)
//				info.iLoacation = ESknLoactionMMC;
//			else 
//				info.iLoacation = ESknLoactionNone;

			aArray.Append(info);
			//TAknsPkgID pkgId = skinInfoArray->At(i)->PID();//得到每个主题的ID	        
			}
		}
	delete repository;
	repository = NULL;
	skinInfoArray->ResetAndDestroy();
	CleanupStack::PopAndDestroy();

	return retValue;
	}

TInt CThemeManager::GetCurrentTheme(TAknsPkgIDBuf& aTheme)
	{
	CRepository* repository = CRepository::NewL(KCRUidPersonalisation);
	TInt retVal = repository->Get(KPslnActiveSkinUid, aTheme);//得到当前主题的ID
	delete repository;
	repository = NULL;

	return retVal;
	}

TInt CThemeManager::GetCurrentTheme(TAknsPkgID& aTheme)
	{
	TAknsPkgIDBuf pidBuf;
	CRepository* repository = CRepository::NewL(KCRUidPersonalisation);
	TInt retVal = repository->Get(KPslnActiveSkinUid, pidBuf);//得到当前主题的ID
	aTheme.SetFromDesL(pidBuf);
	delete repository;
	repository = NULL;

	return retVal;
	}

TInt CThemeManager::SetTheme(const TAknsPkgIDBuf& aTheme)
	{
	CRepository* repository = CRepository::NewLC(KCRUidPersonalisation);
	TInt retVal = repository->Set(KPslnActiveSkinUid, aTheme);//设置当前主题的ID
	CleanupStack::PopAndDestroy();
	return retVal;
	}

TInt CThemeManager::SetTheme(const TAknsPkgID& aTheme)
	{
	TInt retVal;
	TAknsPkgIDBuf pidBuf;
	aTheme.CopyToDes(pidBuf);

	retVal = iSession.SetAllDefinitionSets(aTheme);

	if (retVal != KErrNone)
		return retVal;

	CRepository* repository = CRepository::NewLC(KCRUidPersonalisation);
	retVal = repository->Set(KPslnActiveSkinUid, pidBuf);//设置当前主题的ID
	CleanupStack::PopAndDestroy();
	
	return retVal;
	}

TInt CThemeManager::ChangeTheme()
	{
	TInt err;
	RArray<TThemeInfo> array;
	DisplayAll(array);

	if (array.Count() > 1)
		{
		for (TInt i = 0; i < 10; i++) //循环,确保选中index为另一款
			{
			TTime theTime;
			theTime.UniversalTime();
			TInt64 randSeed(theTime.Int64()); // 采用时间初始化随机数种子
			TInt index(Math::Rand(randSeed) % array.Count());

			if (index != iCurrent)
				{
				iCurrent = index;
				break;
				}
			}

		if (iCurrent >= 0 && iCurrent < array.Count())
			{
			const TThemeInfo& info = array[iCurrent];
			err = SetTheme(info.iPID);
			}
		}

	array.Close();

	return err;
	}
