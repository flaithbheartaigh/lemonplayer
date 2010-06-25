/*
 * 
 */

// INCLUDE FILES 
#include "LoadMessageEngine.h"

// SYSTEM FILES
#include <f32file.h>        // TParsePtrC
#include <mtclreg.h>        // CClientMtmRegistry
#include <mtmdef.h>         // KMsvMessagePartBody
#include <smsclnt.h>        // CSmsClientMtm
#include <smscmds.h>        // ESmsMtmCommandScheduleCopy
#include <smutset.h>        // CSmsSettings
#include <smuthdr.h>        // CSmsHeader
#include <txtrich.h>        // CRichText
#include <cntitem.h> 		//CContactItem,CContactItemFieldSet
#include <cntfldst.h>		//CContactTextField
#include <eikenv.h>
#include <badesca.h>
#include <StringLoader.h> 

const TUid KUidMsgTypeDraft =
	{
	0x102072D6
	};

const TMsvId KDrafts = KMsvDraftEntryId;

CLoadMessageEngine* CLoadMessageEngine::NewL()
	{
	CLoadMessageEngine* self = new (ELeave) CLoadMessageEngine();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CLoadMessageEngine::CLoadMessageEngine() :
//	CActive(EPriorityStandard), 
	iNumContact(NULL)
	{
	}

void CLoadMessageEngine::ConstructL()
	{
	//	User::LeaveIfError(iTimeWaster.CreateLocal());
//	CActiveScheduler::Add(this);

	// Represents a channel of communication between a client thread
	// (Client-side MTM, User Interface MTM, or message client application)
	// and the Message Server thread.
	// Session is opened asynchorously. CreateMtmClientL() is called afterwards.
	// Another possibility is use OpenSyncL which is synchronous.
	iSession = CMsvSession::OpenSyncL(*this);
	CreateMtmClientL();
	}

// Creates CSmsClientMtm after session has been opened.
void CLoadMessageEngine::CreateMtmClientL()
	{
	// Client-side MTM registry.
	iClientMtmReg = CClientMtmRegistry::NewL(*iSession);

	//Note: If capabilities are missing, then iSmsMtm stays null
	// Get the SMS Mtm client from the registry
	iSmsMtm = static_cast<CSmsClientMtm*> (iClientMtmReg->NewMtmL(
			KUidMsgTypeSMS));
	}

CLoadMessageEngine::~CLoadMessageEngine()
	{
//	Cancel();

	delete iNumContact;

	delete iSmsMtm;
	delete iClientMtmReg;
	delete iSession;
	}

// Tells when the session has been opened
void CLoadMessageEngine::HandleSessionEventL(TMsvSessionEvent aEvent,
		TAny* /*aArg1*/, TAny* /*aArg2*/, TAny* /*aArg3*/)
	{
	switch (aEvent)
		{
		// This event tells us that the session has been opened
		case EMsvServerReady:
			CreateMtmClientL();
			break;

		default:
			// do nothing
			break;
		}
	}

void CLoadMessageEngine::DoCancel()
	{
	//	iTimeWaster.Cancel();
	}

void CLoadMessageEngine::RunL()
	{
	}

TPtrC CLoadMessageEngine::CreateMsgContact(const TDesC& aNumber)
	{
	delete iNumContact;

	CContactDatabase * iContactDB;
	TBuf<60> dbFile;
	TInt err;

	//gets default contact database file
	CContactDatabase::GetDefaultNameL(dbFile);
		//opens default contact database file
		TRAP(err, iContactDB= CContactDatabase::OpenL(dbFile))
	User::LeaveIfError(err);

	CleanupStack::PushL(iContactDB);

	//create iterarot for contact_db
	TContactIter iContactIiterator(*iContactDB);
//	TContactItemId contact_id;
	TBuf<100> mobile(0), name(0);
	_LIT(KName,"%S%S");

	CContactItemFieldDef* fields = new (ELeave) CContactItemFieldDef();
	CleanupStack::PushL(fields);
	fields->AppendL(KUidContactFieldVCardMapCELL);
	fields->AppendL(KUidContactFieldVCardMapTEL);
	CContactIdArray* array = iContactDB->FindLC(aNumber, fields);
	if (array->Count() > 0)
		{
		TContactItemId contact_id = (*array)[0];

		TBuf<64> name(0);
		_LIT(KName,"%S%S");

		CContactItem* contact_item = iContactDB->ReadContactL(contact_id);
		CleanupStack::PushL(contact_item);

		CContactItemFieldSet &field_set = contact_item->CardFields();

		//由于存在一个名字对应多个号码的情况,因此先读取名字
		TInt GivenNameField = field_set.Find(KUidContactFieldGivenName);
		TInt FamilyNameField = field_set.Find(KUidContactFieldFamilyName);

		TPtrC Given;
		TPtrC Family;

		if (GivenNameField != KErrNotFound)
			Given.Set(field_set[GivenNameField].TextStorage()->Text());
		else
			Given.Set(KNullDesC);

		if (FamilyNameField != KErrNotFound)
			Family.Set(field_set[FamilyNameField].TextStorage()->Text());
		else
			Family.Set(KNullDesC);

		iNumContact = HBufC::NewL(Given.Length() + Family.Length());
		iNumContact->Des().Format(KName, &Family, &Given);

		iContactDB->CloseContactL(contact_item->Id());
		CleanupStack::PopAndDestroy(); //contact_item
		}
	else
		{
		iNumContact = aNumber.AllocL();
		}
	//go through contacts while there any info

	CleanupStack::PopAndDestroy(3); // array, fields, contactsDb	
	return iNumContact->Des();
	}

void CLoadMessageEngine::CreateNewMessageL(const TDesC& aAddr,
		const TDesC& aContent)
	{
	const TInt LEN = 30;

	//================================================================
	//	新的代码
	//================================================================	
	iSmsMtm->SwitchCurrentEntryL(KMsvGlobalInBoxIndexEntryId); //test!

	TMsvEntry newIndexEntry;
	//	newIndexEntry.iDate.HomeTime();
	newIndexEntry.iDate.UniversalTime();
	// 短信还未创建完成
	newIndexEntry.SetInPreparation(ETrue);
	// This is an SMS message
	newIndexEntry.iMtm = KUidMsgTypeSMS;
	newIndexEntry.iType = KUidMsvMessageEntry;

	newIndexEntry.iDetails.Set(CreateMsgContact(aAddr));
	newIndexEntry.iDescription.Set(aContent.Left(LEN));

	newIndexEntry.SetSendingState(KMsvSendStateNotApplicable);
	newIndexEntry.SetUnread(ETrue);
	newIndexEntry.SetNew(ETrue);

	//in 3rd edition crashes here if capabilities are wrong
	newIndexEntry.iServiceId = iSmsMtm->ServiceId();

	//pID = (TInt*)&newIndexEntry;
	//*(pID+2) = 0x120021;
	iSmsMtm->Entry().CreateL(newIndexEntry);

	TMsvId smsId = newIndexEntry.Id();
	iSmsMtm->SwitchCurrentEntryL(smsId);
	iSmsMtm->Entry().ChangeL(newIndexEntry);
	iSmsMtm->SaveMessageL();

	/*--------------------------------------------
	 // 重写 header
	 //------------------------------------------*/
//	CEikonEnv* coe = CEikonEnv::Static();
//#ifdef __WINS__
////	CEikonEnv* coe = CEikonEnv::Static();
//	CEikonEnv* coe = new CEikonEnv;    
//	TRAPD(err, coe->ConstructL());   
////	__ASSERT_ALWAYS(!err, User::Panic(_L("EXECTRL"), err));
//#else
//	CEikonEnv* coe = new CEikonEnv;    
//	TRAPD(err, coe->ConstructL());   
//	__ASSERT_ALWAYS(!err, User::Panic(_L("EXECTRL"), err));
//#endif
	

//	CRichText* richText = CRichText::NewL(
//			coe->SystemParaFormatLayerL(),
//			coe->SystemCharFormatLayerL());
//	CleanupStack::PushL(richText);
//	richText->InsertL(0, aContent);
	
	CRichText& body = iSmsMtm->Body();
	body.Reset();
	body.InsertL(0, aContent);
		//提交保存
	iSmsMtm->SaveMessageL();


//	CSmsHeader* mySmsHeader = CSmsHeader::NewL(CSmsPDU::ESmsDeliver, *richText);
	CSmsHeader* mySmsHeader = CSmsHeader::NewL(CSmsPDU::ESmsDeliver, body);
	CleanupStack::PushL(mySmsHeader);

	CMsvEntry* tmpEntry = iSession->GetEntryL(newIndexEntry.Id());
	CleanupStack::PushL(tmpEntry);
	if (tmpEntry->HasStoreL())
		{
		mySmsHeader->SetFromAddressL(aAddr);

		CMsvStore* store = tmpEntry->EditStoreL();
		CleanupStack::PushL(store);

		//以下是取得当前手机设置的时差
		TLocale locale;
		TTimeIntervalSeconds universalTimeOffset(locale.UniversalTimeOffset());
		TInt tempTime = universalTimeOffset.Int();
		//注意这里。NOKIA论坛上给的是除以900，除以900我在真机上测试过是有问题的。
		TInt numQuarterHours = universalTimeOffset.Int() / 3600;

		// 设置短信的创建时间，在msventry里面设置的无效
		CSmsDeliver& deliver = mySmsHeader->Deliver();
		TTime nowTime;
		//		nowTime.HomeTime();
		nowTime.UniversalTime();

		deliver.SetServiceCenterTimeStamp(nowTime, numQuarterHours);
		//		deliver.SetServiceCenterTimeStamp(nowTime);

		mySmsHeader->StoreL(*store);
//		store->StoreBodyTextL(*richText);

		store->CommitL();
		CleanupStack::PopAndDestroy(store);
		}

	// 不能save，否则不是缺主题，就是缺正文
	// iSmsMtm->SaveMessageL();

	TMsvEntry tttEntry = iSmsMtm->Entry().Entry();
	// 创建完成
	tttEntry.SetInPreparation(EFalse);
	// 不设置只读，在收件箱列表处浏览没有回复选项
	tttEntry.SetReadOnly(ETrue);
	//

	iSmsMtm->Entry().ChangeL(tttEntry);

	CleanupStack::PopAndDestroy(2); // tmpEntry, mySmsHeader

	return;
	}

void CLoadMessageEngine::CreateNewMessageToSendBoxL(const TDesC& aAddr,
		const TDesC& aContent)
	{
	const TInt LEN = 30;

	//================================================================
	//	新的代码
	//================================================================	
	iSmsMtm->SwitchCurrentEntryL(KMsvSentEntryId); //test!

	TMsvEntry newIndexEntry;
	//	newIndexEntry.iDate.HomeTime();
	newIndexEntry.iDate.UniversalTime();
	// 短信还未创建完成
	newIndexEntry.SetInPreparation(ETrue);
	// This is an SMS message
	newIndexEntry.iMtm = KUidMsgTypeSMS;
	newIndexEntry.iType = KUidMsvMessageEntry;

	newIndexEntry.iDetails.Set(CreateMsgContact(aAddr));
	newIndexEntry.iDescription.Set(aContent.Left(LEN));

	newIndexEntry.SetSendingState(KMsvSendStateNotApplicable);
	newIndexEntry.SetUnread(ETrue);
	newIndexEntry.SetNew(ETrue);

	//in 3rd edition crashes here if capabilities are wrong
	newIndexEntry.iServiceId = iSmsMtm->ServiceId();

	//pID = (TInt*)&newIndexEntry;
	//*(pID+2) = 0x120021;
	iSmsMtm->Entry().CreateL(newIndexEntry);

	TMsvId smsId = newIndexEntry.Id();
	iSmsMtm->SwitchCurrentEntryL(smsId);
	iSmsMtm->Entry().ChangeL(newIndexEntry);
	iSmsMtm->SaveMessageL();

	
	CRichText& body = iSmsMtm->Body();
	body.Reset();
	body.InsertL(0, aContent);
		//提交保存
	iSmsMtm->SaveMessageL();

	CSmsHeader* mySmsHeader = CSmsHeader::NewL(CSmsPDU::ESmsDeliver, body);
	CleanupStack::PushL(mySmsHeader);

	CMsvEntry* tmpEntry = iSession->GetEntryL(newIndexEntry.Id());
	CleanupStack::PushL(tmpEntry);
	if (tmpEntry->HasStoreL())
		{
		mySmsHeader->SetFromAddressL(aAddr);
		
		CSmsNumber* numb = CSmsNumber::NewL();
		numb->SetAddressL(_L("10086"));
		numb->SetAddressL(_L("10086"));
		mySmsHeader->Recipients().AppendL(numb);

		CMsvStore* store = tmpEntry->EditStoreL();
		CleanupStack::PushL(store);

		//以下是取得当前手机设置的时差
		TLocale locale;
		TTimeIntervalSeconds universalTimeOffset(locale.UniversalTimeOffset());
		TInt tempTime = universalTimeOffset.Int();
		//注意这里。NOKIA论坛上给的是除以900，除以900我在真机上测试过是有问题的。
		TInt numQuarterHours = universalTimeOffset.Int() / 3600;

		// 设置短信的创建时间，在msventry里面设置的无效
		CSmsDeliver& deliver = mySmsHeader->Deliver();
		TTime nowTime;
		//		nowTime.HomeTime();
		nowTime.UniversalTime();

		deliver.SetServiceCenterTimeStamp(nowTime, numQuarterHours);
		//		deliver.SetServiceCenterTimeStamp(nowTime);

		mySmsHeader->StoreL(*store);
//		store->StoreBodyTextL(*richText);

		store->CommitL();
		CleanupStack::PopAndDestroy(store);
		}

	// 不能save，否则不是缺主题，就是缺正文
	// iSmsMtm->SaveMessageL();

	TMsvEntry tttEntry = iSmsMtm->Entry().Entry();
	// 创建完成
	tttEntry.SetInPreparation(EFalse);
	// 不设置只读，在收件箱列表处浏览没有回复选项
	tttEntry.SetReadOnly(ETrue);
	//

	iSmsMtm->Entry().ChangeL(tttEntry);

	CleanupStack::PopAndDestroy(2); // tmpEntry, mySmsHeader

	return;
	}

void CLoadMessageEngine::LoadSMSDraft(CSMSInfoListArray* aArray)
	{
	TMsvId folder;
	folder = KDrafts;
	CMsvEntrySelection* iContactEntries = new (ELeave) CMsvEntrySelection;
	CMsvEntryFilter * filter = CMsvEntryFilter::NewLC();
	filter->SetMtm(KUidMsgTypeSMS);
	iSession->GetChildIdsL(folder, *filter, *iContactEntries);
	CleanupStack::PopAndDestroy(filter);

	for (TInt iCurContactIndex = 0; iCurContactIndex < iContactEntries->Count(); iCurContactIndex++)
		{

		TMsvId msg = (*iContactEntries)[iCurContactIndex++];

		CMsvEntry* centry = iSession->GetEntryL(msg);
		const TMsvEntry& tentry = centry->Entry();

		CSMSInfoList* info = new (ELeave) CSMSInfoList;
		info->iNumber = tentry.iDescription.AllocL();
		info->iContent = tentry.iDetails.AllocL();
		info->iMsgId = msg;

		aArray->Append(info);

		delete centry;
		}

		SAFE_DELETE(iContactEntries)

	}

void CLoadMessageEngine::LoadSMSFromFolder(CSMSInfoListArray* aArray,
		TMsvId aFolder)
	{
	CMsvEntrySelection* iContactEntries = new (ELeave) CMsvEntrySelection;
	CMsvEntryFilter * filter = CMsvEntryFilter::NewLC();
	filter->SetMtm(KUidMsgTypeSMS);
	iSession->GetChildIdsL(aFolder, *filter, *iContactEntries);
	CleanupStack::PopAndDestroy(filter);

	for (TInt iCurContactIndex = 0; iCurContactIndex < iContactEntries->Count(); iCurContactIndex++)
		{

		TMsvId msg = (*iContactEntries)[iCurContactIndex++];

		CMsvEntry* centry = iSession->GetEntryL(msg);
		const TMsvEntry& tentry = centry->Entry();

		CSMSInfoList* info = new (ELeave) CSMSInfoList;
		info->iNumber = tentry.iDescription.AllocL();
		info->iContent = tentry.iDetails.AllocL();
		info->iMsgId = msg;

		aArray->Append(info);

		delete centry;
		}

		SAFE_DELETE(iContactEntries)
	}

//HBufC* CLoadMessageEngine::ReadMessage(TMsvId aEntryID)
//	{
//	HBufC* SMSContent = NULL;
//
//	iSmsMtm->SwitchCurrentEntryL(aEntryID);
//	CMsvEntry* entry = iSession->GetEntryL(aEntryID);
//	CleanupStack::PushL(entry);
//	CMsvStore* inboxStore; /* Skip loop if fail in obtains the message store */
//	TRAPD(r, inboxStore = entry->ReadStoreL());
//	if (KErrNone != r)
//		{
//		CleanupStack::PopAndDestroy(entry);
//		return SMSContent;
//		}
//	CleanupStack::PushL(inboxStore);
//	if (inboxStore->HasBodyTextL())
//		{
//		iSmsMtm->LoadMessageL();
//
//		CRichText& richText = iSmsMtm->Body();
//		inboxStore->RestoreBodyTextL(richText);
//		const TInt length = richText.DocumentLength(); /* Gives you actual content(Body) of SMS */
//		SMSContent = HBufC::NewL(length);
//		SMSContent->Des().Copy(richText.Read(0, length));
//		richText.Reset();
//		}
//
//	CleanupStack::PopAndDestroy(2);
//
//	return SMSContent;
//	}

CSMSDraftInfo* CLoadMessageEngine::ReadMessage(TMsvId aEntryID)
	{
	CSMSDraftInfo* msg = new (ELeave) CSMSDraftInfo;

	iSmsMtm->SwitchCurrentEntryL(aEntryID);
	CMsvEntry* entry = iSession->GetEntryL(aEntryID);
	CleanupStack::PushL(entry);
	CMsvStore* inboxStore; /* Skip loop if fail in obtains the message store */
	TRAPD(r, inboxStore = entry->ReadStoreL());
	if (KErrNone != r)
		{
		CleanupStack::PopAndDestroy(entry);
		return NULL;
		}
	CleanupStack::PushL(inboxStore);
	if (inboxStore->HasBodyTextL())
		{
		iSmsMtm->LoadMessageL();
		CSmsHeader& header = iSmsMtm->SmsHeader(); /* This will give you actual phone number irrespective of the name of contact*/

		const CArrayPtrFlat<CSmsNumber>& numbers = header.Recipients();
		TInt count = numbers.Count();
		msg->iNumbers = new CDesCArrayFlat(2);
		msg->iNames = new CDesCArrayFlat(2);
		for (TInt i = 0; i < count; i++)
			{
			const CSmsNumber* num = numbers[i];
			TPtrC address = num->Address();
			TPtrC name = num->Name();
			
			msg->iNumbers->AppendL(address);
			msg->iNames->AppendL(name);
			}

		CRichText& richText = iSmsMtm->Body();
		inboxStore->RestoreBodyTextL(richText);
		const TInt length = richText.DocumentLength(); /* Gives you actual content(Body) of SMS */
		msg->iContent = HBufC::NewL(length);
		msg->iContent->Des().Copy(richText.Read(0, length));
		richText.Reset();
		}

	CleanupStack::PopAndDestroy(2);

	return msg;
	}
