/*
 ============================================================================
 Name		: SHModel.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSHModel implementation
 ============================================================================
 */

#include "SHModel.h"
#include "MacroUtil.h"

CSHModel::CSHModel()
	{
	// No implementation required
	}

CSHModel::~CSHModel()
	{
	SAFE_DELETE(iRule)
	SAFE_DELETE_ACTIVE(iTimeWork)
	SAFE_DELETE(iRuleManager)
	SAFE_DELETE(iTaskInfoManager)
	}

CSHModel* CSHModel::NewLC()
	{
	CSHModel* self = new (ELeave) CSHModel();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSHModel* CSHModel::NewL()
	{
	CSHModel* self = CSHModel::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CSHModel::ConstructL()
	{
	iRuleManager = CRuleManager::NewL();
	iTimeWork = CTimeWorkManager::NewL();
	iRule = CRule::NewL();
	iTaskInfoManager = CTaskInfoManager::NewL();
	}

void CSHModel::SetRule(const TInt& aType,const TInt& aCountdown,const TTime& aClock)
	{
	if (iRule)
		{
		iRule->SetType(aType);
		iRule->SetCountDown(aCountdown);
		iRule->SetClock(aClock);
		}
	}
