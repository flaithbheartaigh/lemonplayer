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
//���׶ι���
CSmsSendByBoxEngine* CSmsSendByBoxEngine::NewL(MSmsSendByBoxNotify& aNotify)
	{
	CSmsSendByBoxEngine* self = new (ELeave) CSmsSendByBoxEngine(aNotify);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}
//���췽����
CSmsSendByBoxEngine::CSmsSendByBoxEngine(MSmsSendByBoxNotify& aNotify) :
	CActive(EPriorityStandard),iNotify(aNotify)
	{
	}
//������
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
//�ڶ��׶ι��캯����
void CSmsSendByBoxEngine::ConstructL()
	{
	//������Ϣ�Ự���󣮷������ӷ���������
	iSession = CMsvSession::OpenSyncL(*this);
	//�����ͻ��ˣͣԣ�ע���
	iMtmReg = CClientMtmRegistry::NewL(*iSession);
	//�ӣͣԣ�ע����л�ȡ�ͣԣͣ�
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

//��ʼ������
TInt CSmsSendByBoxEngine::Start()
	{
	TInt count = iMsgData->Count();
	if (count > 0)
		{
		CreateMsg();//������Ϣ��
		if (ValidateSMS())//��֤��Ϣȷ����ӵ���������Ϣ�࿪�������
			SendMsg();//������Ϣ��
		return KErrNone;
		}
	else
		return KErrNotFound;
	}
//������Ϣ��
void CSmsSendByBoxEngine::CreateMsg()
	{
	//���ö��Ų�����
	CMsgDataForSend* item = (*iMsgData)[0];
	TPtrC content = item->iContent->Des();
	TPtrC address = item->iAddress->Des();
	
	TMsvEntry indexEntry;
	indexEntry.iDate.UniversalTime();
	indexEntry.SetInPreparation(ETrue);
	indexEntry.iMtm = KUidMsgTypeSMS;
	indexEntry.iType = KUidMsvMessageEntry;
	indexEntry.iServiceId = iSmsMtm->ServiceId();//��ȡ��ǰ���ŷ���ʶ���롣

	iSmsMtm->SwitchCurrentEntryL(KMsvDraftEntryId);// ��ʵ�����������л����ݸ��䡣
	iSmsMtm->Entry().CreateL(indexEntry);//������Ϣ�����         
	//��ȡ������ģɣļ��л������Ĵ��롣
	iSmsId = indexEntry.Id();
	iSmsMtm->SwitchCurrentEntryL(iSmsId);
	//�����Ϣ���ġ�
	CRichText& body = iSmsMtm->Body();
	body.Reset();
	body.InsertL(0, content);
	indexEntry.iDescription.Set(content);
	//��ӽ����ߡ�
	iSmsMtm->AddAddresseeL(address);
	indexEntry.iDetails.Set(address);
	//���������
	iSmsMtm->Entry().ChangeL(indexEntry);
	//�ѵ�ǰ������������Ϣ���浽��Ϣ�洢�С�
	iSmsMtm->SaveMessageL();
	
	iMsgData->Remove(0);
	delete item;
	}
//��֤��Ϣȷ����ӵ���������Ϣ�࿪�������
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
//������Ϣ��
void CSmsSendByBoxEngine::SendMsg()
	{
	//���������л�ΪSMS��Ϣ��
	iSmsMtm->SwitchCurrentEntryL(iSmsId);
	//���ش�������Ϣ��
	iSmsMtm->LoadMessageL();
	//����SMS�������ĵĺ��롣
	CSmsSettings& settings = iSmsMtm->ServiceSettings();
	TInt numSCAddresses = settings.ServiceCenterCount();
	// Ӧ��ʼ����һ���������ĺ���
	if (numSCAddresses > 0)
		{
		TInt index = 0;
		index = settings.DefaultServiceCenter();

		if ((index < 0) || (index >= numSCAddresses))
			index = 0;
		//�õ��������ĺ��룺
		TPtrC serverCenterNum = settings.GetServiceCenter(index).Address();
		//��ֻ�����ڶ����ύ���͵���Ϣ��
		iSmsMtm->SmsHeader().SetServiceCenterAddressL(serverCenterNum);
		}

	CSmsSettings* sendOptions = CSmsSettings::NewL();
	CleanupStack::PushL(sendOptions);
	sendOptions->CopyL(iSmsMtm->ServiceSettings());
	sendOptions->SetDelivery(ESmsDeliveryImmediately);
	sendOptions->SetCharacterSet(TSmsDataCodingScheme::ESmsAlphabetUCS2);
	iSmsMtm->SmsHeader().SetSmsSettingsL(*sendOptions);
	CleanupStack::PopAndDestroy(sendOptions);
	//������Ϣ��
	iSmsMtm->SaveMessageL();
	// ���������
	TMsvEntry indexEntry = iSmsMtm->Entry().Entry();
	indexEntry.SetInPreparation(EFalse);
	indexEntry.SetSendingState(KMsvSendStateWaiting);
	iSmsMtm->Entry().ChangeL(indexEntry);
	//�������ݡ�
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

// ʵ����Ϣ�������Ự�ӿ���MMsvSessionObserver
void CSmsSendByBoxEngine::HandleSessionEventL(TMsvSessionEvent aEvent,
		TAny* aArg1, TAny* aArg2, TAny* aArg3)
	{
	}
