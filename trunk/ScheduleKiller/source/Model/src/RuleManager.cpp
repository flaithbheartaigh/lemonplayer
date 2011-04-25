/*
 ============================================================================
 Name		: RuleManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRuleManager implementation
 ============================================================================
 */

#include "RuleManager.h"

#include <COEMAIN.H>
#include <BAUTILS.H>
#include <StringLoader.h> 

#include "MacroUtil.h"
#include "Utils.h"
#include "CommonUtils.h"
#include "SHPlatform.h"
#include "QueryDlgUtil.h"

//_LIT(KRuleFile,"rule.dat");

//新增默认打开
_LIT(KRuleFile,"rule2.dat");
_LIT(KFavRuleFile,"favrule.dat");

_LIT8(KRuleSymbolSplit,"*");
_LIT8(KRuleSymbolEnd,"\n");
const TChar KCharRuleSymbolSplit = '*';
const TChar KCharRuleSymbolEnd = '\n';

const static TInt MAX_FAV_COUNT = 10;
//规则格式: name*uid*type*countdown/clock*rulename\n

CRuleManager::CRuleManager()
:iFavRule(NULL)
	{
	// No implementation required
	}

CRuleManager::~CRuleManager()
	{
//	WriteFavToFile();
	SAFE_DELETE(iFavRule)
	SAFE_DELETE_RPONTERARRAY(iRules)
	}

CRuleManager* CRuleManager::NewLC()
	{
	CRuleManager* self = new (ELeave) CRuleManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CRuleManager* CRuleManager::NewL()
	{
	CRuleManager* self = CRuleManager::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CRuleManager::ConstructL()
	{
	iRules = new (ELeave) RPointerArray<CRule>;
	iFavRule = CRule::NewL();
	}

CRule* CRuleManager::GetRule(const TInt& aIndex) const 
	{
	if (aIndex >=0 && aIndex < iRules->Count())
		{
			return (*iRules)[aIndex];
		}
	return NULL;
	}

void CRuleManager::AppendRule(const TDesC& aName,const TUid& aUid, const TInt& aType, const TInt& aCountDown, 
		const TTime& aTime, const TDesC& aRuleName)
	{
	CRule* rule = CRule::NewL();
	rule->SetName(aName);
	rule->SetUid(aUid);
	rule->SetType(aType);
	rule->SetCountDown(aCountDown);
	rule->SetClock(aTime);
	rule->SetRuleName(aRuleName);
	rule->SetLunchRun(0);
	
	iRules->Insert(rule,0);
	
	WriteToFile(rule);
	}

TBool CRuleManager::IsSame(const TDesC& aName,const TUid& aUid, const TInt& aType, const TInt& aCountDown, 
		const TTime& aTime)
	{
	if (aName == iFavRule->GetName() && aUid == iFavRule->GetUid() && aType == iFavRule->GetType())
		{
		if (aType == 0)
			{
			if (aCountDown == iFavRule->GetCountDown())
				return ETrue;
			}
		else 
			{
			if (aTime == iFavRule->GetClock())
				return ETrue;
			}
		}

	return EFalse;
	}

void CRuleManager::AppendFavRule(const TDesC& aName,const TUid& aUid, const TInt& aType, const TInt& aCountDown, 
		const TTime& aTime)
	{
	if (iFavRule == NULL)
		return;
	
	if (IsSame(aName,aUid,aType,aCountDown,aTime))
		{
		iFavRule->IncreaseFavCount();
		}
	else
		{
		iFavRule->SetName(aName);
		iFavRule->SetUid(aUid);
		iFavRule->SetType(aType);
		iFavRule->SetCountDown(aCountDown);
		iFavRule->SetClock(aTime);
		iFavRule->SetFavCount(0);
		}
	
	WriteFavToFile();
	}

void CRuleManager::WriteToFile(CRule* aRule)
	{
	TFileName filename;
	GetAppPath(filename);
	filename.Append(KRuleFile);
	
	int pos = filename.LocateReverse('\\');
	if (pos != KErrNotFound)
		{
		TPtrC dirName = filename.Left(pos + 1);
		CCoeEnv::Static()->FsSession().MkDirAll(dirName);
		}

	RFile file;
	TInt err;

	if (BaflUtils::FileExists(CCoeEnv::Static()->FsSession(), filename))
		err = file.Open(CCoeEnv::Static()->FsSession(), filename, EFileWrite
				| EFileStreamText);
	else
		err = file.Replace(CCoeEnv::Static()->FsSession(), filename,
				EFileWrite);
	if (KErrNone != err)
		{
		return;
		}
	CleanupClosePushL(file);

	TInt end = 0;
	file.Seek(ESeekEnd, end);

	WriteToFile(file,aRule);

	CleanupStack::PopAndDestroy(); // file

	}

void CRuleManager::WriteToFile(RFile& file,CRule* aRule)
	{
	HBufC8* name = CCommonUtils::ConvertToUTF8FromUnicode(aRule->GetName());
	file.Write(name->Des());
	delete name;
	file.Write(KRuleSymbolSplit);
	
	TBuf8<16> uid;
	uid.AppendNum((aRule->GetUid().iUid));
	file.Write(uid);
	file.Write(KRuleSymbolSplit);
	
	TBuf8<2> type;
	type.AppendNum(aRule->GetType());
	file.Write(type);
	file.Write(KRuleSymbolSplit);
	
	if (aRule->GetType() == 0)
		{
		TBuf8<8> count;
		count.AppendNum(aRule->GetCountDown());
		file.Write(count);
		}
	else
		{
		TBuf8<8> count;
		TimeFormat(aRule->GetClock(),count);
		file.Write(count);
		}	
	file.Write(KRuleSymbolSplit);
	
	HBufC8* rulename = CCommonUtils::ConvertToUTF8FromUnicode(aRule->GetRuleName());
	file.Write(rulename->Des());
	delete rulename;
	file.Write(KRuleSymbolSplit);
	
	TBuf8<2> lunch;
	lunch.AppendNum(aRule->IsLunchRun());
	file.Write(lunch);
	
	file.Write(KRuleSymbolEnd);
	}

void CRuleManager::WriteToFile(RPointerArray<CRule>* aRules)
	{
	TFileName filename;
	GetAppPath(filename);
	filename.Append(KRuleFile);
	
	int pos = filename.LocateReverse('\\');
	if (pos != KErrNotFound)
		{
		TPtrC dirName = filename.Left(pos + 1);
		CCoeEnv::Static()->FsSession().MkDirAll(dirName);
		}

	RFile file;
	TInt err;

	err = file.Replace(CCoeEnv::Static()->FsSession(), filename,
			EFileWrite);
	if (KErrNone != err)
		{
		return;
		}
	CleanupClosePushL(file);
	
	for(TInt i=0; i<aRules->Count(); i++)
		{
		CRule* rule = (*aRules)[i];
		WriteToFile(file,rule);
		}

	CleanupStack::PopAndDestroy(); // file	
	}

void CRuleManager::WriteFavToFile()
	{
	TFileName filename;
	GetAppPath(filename);
	filename.Append(KFavRuleFile);
	
	int pos = filename.LocateReverse('\\');
	if (pos != KErrNotFound)
		{
		TPtrC dirName = filename.Left(pos + 1);
		CCoeEnv::Static()->FsSession().MkDirAll(dirName);
		}

	RFile file;
	TInt err;

	err = file.Replace(CCoeEnv::Static()->FsSession(), filename,
			EFileWrite);
	if (KErrNone != err)
		{
		return;
		}
	CleanupClosePushL(file);	

	WriteToFile(file,iFavRule);
	TBuf8<4> num;
	num.AppendNum(iFavRule->GetFavCount());
	file.Write(num);

	CleanupStack::PopAndDestroy(); // file	
	}

void CRuleManager::TimeFormat(const TTime& aTime,TDes8& aDes)
	{
	TDateTime time = aTime.DateTime();
	TInt hour,minute;	
	hour = time.Hour() ;
	minute = time.Minute() ;
	
	aDes.AppendNum(hour);
	aDes.Append(':');
	aDes.AppendNum(minute);
	}

void CRuleManager::TimeSet(const TDesC& aDes,TTime& aTime)
	{
	TTime time;
	time.HomeTime();
	
	TDateTime date;
	date = time.DateTime();
	
	TInt pos = aDes.Locate(':');
	if (pos != KErrNotFound)
		{
		date.SetHour(CCommonUtils::StrToInt(aDes.Left(pos)));
		date.SetMinute(CCommonUtils::StrToInt(aDes.Mid(pos+1)));
		date.SetSecond(0);
		date.SetMicroSecond(0);
		}
	
	aTime = TTime(date);
	}

void CRuleManager::Init()
	{
	ReadFromFile();
	ReadFavFromFile();
	
	AutoLunch();
	FavLunch();
	}

void CRuleManager::ReadFromFile()
	{
	TFileName filename;
	GetAppPath(filename);
	filename.Append(KRuleFile);

	RFile file;
	TInt err;
	
	err = file.Open(CCoeEnv::Static()->FsSession(), filename, EFileRead);

	if (KErrNone != err)
		{
		return;
		}
	
	CleanupClosePushL(file);
	
	ReadFromFile(file);
	
	CleanupStack::PopAndDestroy(); // file
	}

void CRuleManager::ReadFavFromFile()
	{
	TFileName filename;
	GetAppPath(filename);
	filename.Append(KFavRuleFile);

	RFile file;
	TInt err;
	
	err = file.Open(CCoeEnv::Static()->FsSession(), filename, EFileRead);
	CleanupClosePushL(file);
	
	if (KErrNone != err)
		{
		CleanupStack::PopAndDestroy(); // file
		return;
		}
	
	TInt size;
	file.Size(size);
	
	if (size > 0)
		{
		HBufC8* text = HBufC8::NewL(size);
		TPtr8 ptr = text->Des();
		file.Read(ptr);
	
		TInt pos = ptr.Locate(KCharRuleSymbolEnd);
		if (pos != KErrNotFound)
			{
			ReadFromFile(ptr,pos,iFavRule);		
			ptr.Delete(0,pos+1);
			
			TInt num = CCommonUtils::StrToInt(ptr);
			iFavRule->SetFavCount(num);
			}
	
		delete text;
		}
	
	CleanupStack::PopAndDestroy(); // file
	}

void CRuleManager::ReadFromFile(RFile& file)
	{
	TInt size;
	file.Size(size);
	
	HBufC8* text = HBufC8::NewL(size);
	TPtr8 ptr = text->Des();
	file.Read(ptr);

	TInt pos = ptr.Locate(KCharRuleSymbolEnd);
	while (pos != KErrNotFound)
		{
		CRule* rule = CRule::NewL();
		ReadFromFile(ptr,pos,rule);
		iRules->Append(rule);
		
		ptr.Delete(0,pos+1);
		pos = ptr.Locate(KCharRuleSymbolEnd);
		}

	delete text;
	}

void CRuleManager::ReadFromFile(const TDesC8& aFile,TInt aPos,CRule* aRule)
	{
	CDesC8Array *array = CCommonUtils::SplitText(aFile.Left(aPos),KCharRuleSymbolSplit);
	if (array->Count() == 6)
		{
		CRule* rule = aRule;
		
		HBufC* name = CCommonUtils::ConvertToUnicodeFromUTF8((*array)[0]);
		rule->SetName(name->Des());
		delete name;
		
		TInt uid = CCommonUtils::StrToInt((*array)[1]);
		rule->SetUid(TUid::Uid(uid));
		
		TInt type = CCommonUtils::StrToInt((*array)[2]);
		rule->SetType(type);
		
		if (type == 0)
			{
			TInt countdown = CCommonUtils::StrToInt((*array)[3]);
			rule->SetCountDown(countdown);
			}
		else
			{
			TTime time;
			TBuf<8> timetxt;
			timetxt.Copy((*array)[3]);
			TimeSet(timetxt,time);
			rule->SetClock(time);
			}
		
		HBufC* rulename = CCommonUtils::ConvertToUnicodeFromUTF8((*array)[4]);
		rule->SetRuleName(rulename->Des());
		delete rulename;
		
		TInt lunch = CCommonUtils::StrToInt((*array)[5]);
		rule->SetLunchRun(lunch);
		}
	delete array;
	}

TBool CRuleManager::Select(const TInt& aIndex)
	{
	if (aIndex >=0 && aIndex < iRules->Count())
		{
		if (Confirm(aIndex))
			return Execute(aIndex);
		}
	return EFalse;
	}

TBool CRuleManager::Delete(const TInt& aIndex)
	{
	if (aIndex >=0 && aIndex < iRules->Count())
		{
			if (ShowConfirmationQueryL(R_TEXT_CONFIRM_DELETE_RULE))
				return DeleteRule(aIndex);
		}
	return EFalse;	
	}

TBool CRuleManager::LunchRun(const TInt& aIndex)
	{
	if (aIndex >=0 && aIndex < iRules->Count())
		{
		CRule* rule = (*iRules)[aIndex];
		if (rule->IsLunchRun())
			rule->SetLunchRun(0);
		else
			rule->SetLunchRun(1);
		
		WriteToFile(iRules);
		
		return ETrue;
		}
	return EFalse;
	}

TBool CRuleManager::DeleteRule(const TInt& aIndex)
	{
	CRule* rule = (*iRules)[aIndex];
	iRules->Remove(aIndex);
	delete rule;
	
	WriteToFile(iRules);
	
	return ETrue;
	}

TBool CRuleManager::Confirm(const TInt& aIndex)
	{
	CRule* rule = (*iRules)[aIndex];
	
	HBufC* confirm = StringLoader::LoadL(R_TEXT_RULE_CONFIRM);
	
	TPtrC rulename 	= rule->GetRuleName();
	TPtrC appname  	= rule->GetName();
	TInt type 		= rule->GetType();
	TInt countdown 	= rule->GetCountDown();
	TTime time 		= rule->GetClock();
	
	TBuf<16> app;
	if (type == 0)
		{
		HBufC* txt = StringLoader::LoadL(R_TEXT_TYPE_COUNTDOWN);		
		app.Format(txt->Des(),countdown);
		delete txt;
		}
	else
		{
		HBufC* txt = StringLoader::LoadL(R_TEXT_TYPE_CLOCKING);
		TBuf8<8> timetxt8;
		TBuf<8> timetxt;
		CRuleManager::TimeFormat(time,timetxt8);
		timetxt.Copy(timetxt8);
		app.Format(txt->Des(),&timetxt);
		delete txt;
		}
	
	TBuf<128> temp;
	temp.Format(confirm->Des(),&rulename,&appname,&app);
	delete confirm;
	
	return ShowConfirmationQueryL(temp);
	}
TBool CRuleManager::Execute(const TInt& aIndex)
	{
	CRule* rule = (*iRules)[aIndex];
	CSHModel* model = SHModel();
	
	TInt type = rule->GetType();
//	TTime time;
//	if (type == 0)
//		{
//		time.HomeTime();
//		time += TTimeIntervalMinutes(rule->GetCountDown());
//		}
//	else
//		{
//		TTime now;
//		now.HomeTime();
//		time = rule->GetClock();
//		if (time <= now)
//			{
//			SHErrFun(ELAWarnTimeLowerThanNow,ESHErrWarning);
//			return EFalse;
//			}
//		}
//	
//	model->GetTaskInfoManager()->AppendTask(rule->GetUid(),rule->GetName(),time);
	
	TInt err = model->GetTaskInfoManager()->AppendTask(rule->GetName(),rule->GetUid(),type,
			rule->GetCountDown(),rule->GetClock());
	
	if (err == CTaskInfoManager::ETaskErrDuplicate)
		{
		SHErrFun(ELAWarnDuplicateTask,ESHErrWarning);
		return EFalse;
		}
	if (err == CTaskInfoManager::ETaskErrTimeOut)
		{
		SHErrFun(ELAWarnTimeLowerThanNow,ESHErrWarning);
		return EFalse;
		}
	
//	model->GetTimeWorkManager()->StartL(1000);
	
	return ETrue;
	}

void CRuleManager::AutoLunch()
	{
	CSHModel* model = SHModel();
	for(TInt i=0; i<iRules->Count(); i++)
		{
		CRule* rule = (*iRules)[i];
		
		if (rule->IsLunchRun())
			{	
			TInt type = rule->GetType();
//			TTime time;
//			if (type == 0)
//				{
//				time.HomeTime();
//				time += TTimeIntervalMinutes(rule->GetCountDown());
//				}
//			else
//				{
//				TTime now;
//				now.HomeTime();
//				time = rule->GetClock();
//				if (time <= now)
//					continue;
//				}
//			
//			model->GetTaskInfoManager()->AppendTask(rule->GetUid(),rule->GetName(),time);
			
			TInt err = model->GetTaskInfoManager()->AppendTask(rule->GetName(),rule->GetUid(),type,
					rule->GetCountDown(),rule->GetClock());			
			}
		}
	}

void CRuleManager::FavLunch()
	{
	if (iFavRule == NULL)
		return;
	
	if (iFavRule->GetFavCount() >= MAX_FAV_COUNT)
		{
		TInt err = SHModel()->GetTaskInfoManager()->AppendTask(iFavRule->GetName(),iFavRule->GetUid(),iFavRule->GetType(),
				iFavRule->GetCountDown(),iFavRule->GetClock());		
		}
	}
