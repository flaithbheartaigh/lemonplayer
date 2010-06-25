#include <smutset.h>
#include <BADESCA.H>
#include <MSVSTD.H>
#include <LOGCLI.H> 
#include <LOGVIEW.H> 
#include <SMSCLNT.H>
#include <MTCLREG.H>
#include <Msvids.h>
#include <tpbkcontactitemfield.h> 
#include <cpbkcontactitem.h> 
#include <Smut.h>
#include <smuthdr.h>
#include <mtmdef.h>
#include <txtrich.h>
#include <e32std.h>
#include <smscmds.h>        // ESmsMtmCommandScheduleCopy 
#include <aknglobalnote.h>
#include <StringLoader.h>
#include "SmsSendByBoxEngine.h"
//两阶段构造
CSmsSendByBoxEngine* CSmsSendByBoxEngine::NewL(MSmsSendByBoxNotify& aNotify)
	{
	CSmsSendByBoxEngine* self = new (ELeave) CSmsSendByBoxEngine(aNotify);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}
//构造方法。
CSmsSendByBoxEngine::CSmsSendByBoxEngine(MSmsSendByBoxNotify& aNotify) :
	CActive(EPriorityStandard),iNotify(aNotify)
	{
	}
//析构。
CSmsSendByBoxEngine::~CSmsSendByBoxEngine()
	{
	DoCancel();

	iMsgData->ResetAndDestroy();
	delete iMsgData;

		SAFE_DELETE(iEntrySelection)
		SAFE_DELETE(iSmsMtm)
		SAFE_DELETE(iMtmReg)
		SAFE_DELETE(iSession)
	}
//第二阶段构造函数。
void CSmsSendByBoxEngine::ConstructL()
	{
	//建立消息会话对象．发送连接服务器请求。
	iSession = CMsvSession::OpenSyncL(*this);
	//创建客户端ＭＴＭ注册表
	iMtmReg = CClientMtmRegistry::NewL(*iSession);
	//从ＭＴＭ注册表中获取ＭＴＭ．
	iSmsMtm = static_cast<CSmsClientMtm*> (iMtmReg->NewMtmL(KUidMsgTypeSMS));

	//	TMsvSelectionOrdering sort;
	//	iMsvEntry = CMsvEntry::NewL(*iSession, KMsvGlobalInBoxIndexEntryId, sort);

	//	iEntrySelection = iMsvEntry->ChildrenL();
	iEntrySelection = new (ELeave) CMsvEntrySelection;
	CActiveScheduler::Add(this);

	iMsgData = new (ELeave) RPointerArray<CMsgDataForSend> ;
	}

void CSmsSendByBoxEngine::AppendAddressAndContent(const TDesC& aAddress,
		const TDesC& aContent)
	{
	CMsgDataForSend* item = new (ELeave) CMsgDataForSend();
	item->iAddress = aAddress.AllocL();
	item->iContent = aContent.AllocL();
	iMsgData->Append(item);
	}

void CSmsSendByBoxEngine::ResetData()
	{
	iMsgData->ResetAndDestroy();
	}

//开始函数。
TInt CSmsSendByBoxEngine::Start()
	{
	TInt count = iMsgData->Count();
	if (count > 0)
		{
		CreateMsg();//创建消息。
		if (ValidateSMS())//验证消息确保添加的数据与消息类开型相符。
			SendMsg();//发送消息。
		return KErrNone;
		}
	else
		return KErrNotFound;
	}
//创建消息。
void CSmsSendByBoxEngine::CreateMsg()
	{
	//设置短信参数。
	CMsgDataForSend* item = (*iMsgData)[0];
	TPtrC content = item->iContent->Des();
	TPtrC address = item->iAddress->Des();
	
	TMsvEntry indexEntry;
	indexEntry.iDate.UniversalTime();
	indexEntry.SetInPreparation(ETrue);
	indexEntry.iMtm = KUidMsgTypeSMS;
	indexEntry.iType = KUidMsvMessageEntry;
	indexEntry.iServiceId = iSmsMtm->ServiceId();//获取当前短信服务识别码。

	iSmsMtm->SwitchCurrentEntryL(KMsvDraftEntryId);// 先实例的上下文切换到草稿箱。
	iSmsMtm->Entry().CreateL(indexEntry);//创建消息数据项。         
	//获取并新项的ＩＤ及切换上下文代码。
	iSmsId = indexEntry.Id();
	iSmsMtm->SwitchCurrentEntryL(iSmsId);
	//添加消息正文。
	CRichText& body = iSmsMtm->Body();
	body.Reset();
	body.InsertL(0, content);
	indexEntry.iDescription.Set(content);
	//添加接收者。
	iSmsMtm->AddAddresseeL(address);
	indexEntry.iDetails.Set(address);
	//更新索引项。
	iSmsMtm->Entry().ChangeL(indexEntry);
	//把当前建立的完整信息保存到消息存储中。
	iSmsMtm->SaveMessageL();
	
	iMsgData->Remove(0);
	delete item;
	}
//验证消息确保添加的数据与消息类开型相符。
TBool CSmsSendByBoxEngine::ValidateSMS()
	{
	TMsvPartList msgCheckParts = KMsvMessagePartBody | KMsvMessagePartRecipient
			| KMsvMessagePartOriginator | KMsvMessagePartDate;
	TMsvPartList msgFailParts = iSmsMtm->ValidateMessage(msgCheckParts);
	if (msgFailParts == KMsvMessagePartNone)
		return ETrue;
	else
		return EFalse;
	}
//发送消息。
void CSmsSendByBoxEngine::SendMsg()
	{
	//将上下文切换为SMS消息。
	iSmsMtm->SwitchCurrentEntryL(iSmsId);
	//加载创建的消息。
	iSmsMtm->LoadMessageL();
	//设置SMS服务中心的号码。
	CSmsSettings& settings = iSmsMtm->ServiceSettings();
	TInt numSCAddresses = settings.ServiceCenterCount();
	// 应该始终有一个服务中心号码
	if (numSCAddresses > 0)
		{
		TInt index = 0;
		index = settings.DefaultServiceCenter();

		if ((index < 0) || (index >= numSCAddresses))
			index = 0;
		//得到服务中心号码：
		TPtrC serverCenterNum = settings.GetServiceCenter(index).Address();
		//这只能用于短信提交类型的信息。
		iSmsMtm->SmsHeader().SetServiceCenterAddressL(serverCenterNum);
		}

	CSmsSettings* sendOptions = CSmsSettings::NewL();
	CleanupStack::PushL(sendOptions);
	sendOptions->CopyL(iSmsMtm->ServiceSettings());
	sendOptions->SetDelivery(ESmsDeliveryImmediately);
	sendOptions->SetCharacterSet(TSmsDataCodingScheme::ESmsAlphabetUCS2);
	iSmsMtm->SmsHeader().SetSmsSettingsL(*sendOptions);
	CleanupStack::PopAndDestroy(sendOptions);
	//保存消息。
	iSmsMtm->SaveMessageL();
	// 更新索引项。
	TMsvEntry indexEntry = iSmsMtm->Entry().Entry();
	indexEntry.SetInPreparation(EFalse);
	indexEntry.SetSendingState(KMsvSendStateWaiting);
	iSmsMtm->Entry().ChangeL(indexEntry);
	//发送数据。
	Cancel();
	iEntrySelection->Reset();
	iEntrySelection->AppendL(iSmsId);

	//	iMsvEntry = iSession->GetEntryL(KMsvDraftEntryId);

	TBuf8<1> dummyParams;
	iOper = iSmsMtm->InvokeAsyncFunctionL(ESmsMtmCommandScheduleCopy,
			*iEntrySelection, dummyParams, iStatus);
	//	iOper = iMsvEntry->CopyL(iSmsMtm->Entry().EntryId(), iSmsMtm->ServiceId(),
	//			iStatus);
	SetActive();
	}

void CSmsSendByBoxEngine::RunL()
	{
	if (iStatus == KErrNone)
		{
		TMsvEntry entry(iSmsMtm->Entry().Entry());
		TUint state = entry.SendingState();

		if (state == KMsvSendStateWaiting)
//		if (state == KMsvSendStateSent)
			{
			if (Start() != KErrNone)
				iNotify.SendState(0);
			}
		}
	}

void CSmsSendByBoxEngine::DoCancel()
	{
	if (iOper)
		{
		iOper->Cancel();
		delete iOper;
		iOper = NULL;
		}
	}

// 实现消息服务器会话接口类MMsvSessionObserver
void CSmsSendByBoxEngine::HandleSessionEventL(TMsvSessionEvent aEvent,
		TAny* aArg1, TAny* aArg2, TAny* aArg3)
	{
	}
