/*
 ============================================================================
 Name		: TestEditorAppView.cpp
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <aknviewappui.h>

#include "EditorAppView.h"

#include "SHPlatform.h"

#include "MsgRecipientItem.h"
#include "SimMsgStruct.h"
#include "LoadMessageEngine.h"
#include "CommonUtils.h"
#include "QueryDlgUtil.h"

// ============================ MEMBER FUNCTIONS ===============================
CEditorAppView::CEditorAppView() :
	iHeader(NULL)
	{
	// No implementation required
	iContainer = NULL;
	}

CEditorAppView::~CEditorAppView()
	{
	delete iHeader;
	DoDeactivate();
	}

CEditorAppView* CEditorAppView::NewLC()
	{
	CEditorAppView* self = new (ELeave) CEditorAppView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CEditorAppView* CEditorAppView::NewL()
	{
	CEditorAppView* self = CEditorAppView::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CEditorAppView::ConstructL()
	{
	BaseConstructL(R_VIEW_EDITOR);

	//add your code here...

	}
/**
 * 
 * */
TUid CEditorAppView::Id() const
	{
	return TUid::Uid(ESimulateMessageEditViewId);
	}
void CEditorAppView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ECommandAddTask:
			SaveTask();
			break;
		case ECommandInsertContact:
			iContainer->DoUserAddRecipientL();
			break;
		case EAknSoftkeyBack:
			Back();
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
		}
	}

void CEditorAppView::Back()
	{
	TInt state = SHModel()->GetEditModel();
	if (state == CSHModel::EEditmodelModify)
		SaveTask();
	
	SHChangeView(ESimulateMessageMainScreenViewId);
	}

void CEditorAppView::HandleStatusPaneSizeChange()
	{
	if (iContainer != NULL)
		iContainer->SetRect(ClientRect());
	}

/**
 * 
 * */
void CEditorAppView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& aCustomMessage)
	{
	if (iContainer == NULL)
		{
		//		iContainer = CTestEditorAppContainer::NewL(ClientRect());
		iContainer = CMsgEditorView::NewL(*this, 0);

		TInt res(R_UNIEDITOR_TO);
		iContainer->AddControlFromResourceL(res, EMsgAddressControl, 0,
				EMsgHeader);

		res = R_UNIEDITOR_DATETIME;
		iContainer->AddControlFromResourceL(res, EMsgDateTimeControl,
				EMsgAppendControl, EMsgHeader);

		iContainer->ExecuteL(ClientRect(), 0);

		if (aCustomMessage.Length() > 0)
			{
			if (aCustomMessage.Compare(KViewChangeFromLoadDraft) == 0)
				{
				LoadMessage(SHModel()->GetDraftMsg());
				}
			else if (aCustomMessage.Compare(KViewChangeFromModify) == 0)
				{
				LoadMessage();
				}
			}

		AppUi()->AddToStackL(*this, iContainer);

		iContainer->DrawNow();
		//add your init code ...

		}
	}
void CEditorAppView::DoDeactivate()
	{
	if (iContainer != NULL)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}

CMsgBaseControl* CEditorAppView::CreateCustomControlL(TInt /*aControlType*/)
	{
	return NULL;
	}
void CEditorAppView::EditorObserver(TMsgEditorObserverFunc /*aFunc*/, TAny* /*aArg1*/,
		TAny* /*aArg2*/, TAny* /*aArg3*/)
	{
	}

void CEditorAppView::SaveTask()
	{
	CMsgRecipientArray* numbers = iContainer->GetNumbers();
	TTime time = iContainer->GetDateTime();
	TPtrC content = iContainer->GetContent();
	
	TInt count = numbers->Count();

	if (count <= 0)
		{
		ShowInfomationDlgL(R_NOTE_RECIPIENT_NULL);
		return;
		}
	
	for (TInt i = 0; i < count; i++)
		{
		CMsgRecipientItem* item = (*numbers)[i];
		HBufC* address = item->Address();
		HBufC* name = item->Name();

		SimMsgData* task = new (ELeave) SimMsgData;
		task->iNumber = address->AllocL();
		task->iName = name->AllocL();
		task->iTime = time;
		task->iContent = content.AllocL();

		SHSession().AddTask(*task);

		delete task;
		}
	
	SHChangeViewParam(ESimulateMessageMainScreenViewId,KViewChangeParamReboot);
	}

void CEditorAppView::LoadMessage(TMsvId aMsg)
	{
	CLoadMessageEngine* engine = CLoadMessageEngine::NewL();
	CleanupStack::PushL(engine);

	CSMSDraftInfo* info = engine->ReadMessage(aMsg);

	TInt count = info->iNames->Count();
	CMsgRecipientList* recipientList = CMsgRecipientList::NewL();
	CleanupStack::PushL(recipientList);
	for (TInt i = 0; i < count; i++)
		{
		TPtrC name = (*(info->iNames))[i];
		TPtrC number = (*(info->iNumbers))[i];
		CMsgRecipientItem* recipient = CMsgRecipientItem::NewL(name, number);

		recipientList->AppendL(recipient);
		}

	iContainer->SetNumberAndContent(*recipientList, info->iContent->Des());

	delete info;
	CleanupStack::PopAndDestroy(2);//recipients,engine
	}

void CEditorAppView::LoadMessage()
	{
	CLoadMessageEngine* engine = CLoadMessageEngine::NewL();
	CleanupStack::PushL(engine);

	SimMsgData* task = SHModel()->GetEditMessage();

	CMsgRecipientList* recipientList = CMsgRecipientList::NewL();
	CleanupStack::PushL(recipientList);

	TTime time = task->iTime;
	TPtrC name = task->iName->Des();
	TPtrC number = task->iNumber->Des();
	CMsgRecipientItem* recipient = CMsgRecipientItem::NewL(name, number);

	recipientList->AppendL(recipient);

	iContainer->SetNumberAndContent(*recipientList, task->iContent->Des());
	iContainer->SetDateTime(time);

	CleanupStack::PopAndDestroy(2);//recipients,engine
	}

// End of File
