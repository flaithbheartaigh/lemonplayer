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

_LIT(KRuleFile,"rule.dat");
_LIT8(KRuleSymbolSplit,"*");
_LIT8(KRuleSymbolEnd,"\n");
const TChar KCharRuleSymbolSplit = '*';
const TChar KCharRuleSymbolEnd = '\n';

//规则格式: name*uid*type*countdown/clock*rulename\n

CRuleManager::CRuleManager()
	{
	// No implementation required
	}

CRuleManager::~CRuleManager()
	{
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
	
	iRules->Insert(rule,0);
	
	WriteToFile(rule);
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
	file.Write(KRuleSymbolEnd);
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
		date.SetHour(CCommonUtils::StrToInt(aDes.Mid(pos+1)));
		date.SetSecond(0);
		date.SetMicroSecond(0);
		}
	
	aTime = TTime(date);
	}

void CRuleManager::Init()
	{
	ReadFromFile();
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
		CDesC8Array *array = CCommonUtils::SplitText(ptr.Left(pos),KCharRuleSymbolSplit);
		if (array->Count() == 5)
			{
			CRule* rule = CRule::NewL();
			
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
			
			iRules->Append(rule);
			}
		delete array;
		
		ptr.Delete(0,pos+1);
		pos = ptr.Locate(KCharRuleSymbolEnd);
		}

	delete text;
	}

TBool CRuleManager::Select(const TInt& aIndex)
	{
	if (aIndex < iRules->Count())
		{
		if (Confirm(aIndex))
			return Execute(aIndex);
		}
	return EFalse;
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
		app.Format(txt->Des(),timetxt);
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
	if (type == 0)
		{
		TTime time;
		time.HomeTime();
		time += TTimeIntervalMinutes(rule->GetCountDown());
		model->SetTime(time);
		}
	else
		{
		TTime now;
		now.HomeTime();
		TTime time;
		time = rule->GetClock();
		if (time > now)
			SHModel()->SetTime(time);
		else
			{
			SHErrFun(ELAWarnTimeLowerThanNow,ESHErrWarning);
			return EFalse;
			}
		}
	
	model->SetName(rule->GetName());
	model->SetUid(rule->GetUid());
	
	model->GetTimeWorkManager()->StartL(1000);
	
	return ETrue;
	}
