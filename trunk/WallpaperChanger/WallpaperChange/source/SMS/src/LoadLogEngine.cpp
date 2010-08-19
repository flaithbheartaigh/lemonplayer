/*
 * ============================================================================
 *  Name     : CLogExEngine from LogExEngine.h
 *  Part of  : LogExample
 *  Created  : 26.05.2005 by Forum Nokia  
 *  Implementation notes:
 *  Version  : 1.0
 *  Copyright: Nokia Corporation
 * ============================================================================*/
//INCLUDE FILES
#include <eikenv.h>
#include <logwrap.h>
#include <logwrap.hrh>
#include <StringLoader.h> 
#include <cntdef.h> //TContactItemId
#include <OneKeyCleaner.rsg>

#include <e32math.h>	// Random()    
#include "LoadLogEngine.h"

const TInt KWastTimeDuration = 100000;
const TInt KWastTimeRemoveDuration = 100000;
_LIT(KEngineAddRandomText,"Engine-AddRandom");

// ====================== PUBLIC ============================

// ----------------------------------------------------------
// CLogExEngine::CLogExEngine():CActive(EPriorityStandard)
// Defines priority for object
// ----------------------------------------------------------
//	
CLoadLogEngine::CLoadLogEngine() :
	CActive(EPriorityStandard)
	{
	iHashTable = NULL;
	}

// ----------------------------------------------------
// CLogExEngine::~CLogExEngine()
// Destructor
// Frees reserved resources
// ----------------------------------------------------
//
CLoadLogEngine::~CLoadLogEngine()
	{
	Cancel();
	iTimeWaster.Close();

	ReleaseHashTable();

	delete iLogViewEvent;
	
	delete iLogClient;
	delete iLogFilter;
	delete iEmptyLogFilter;

	iDeleteArray.Close();

	iFs.Close();
	}

// ----------------------------------------------------
// CLogExEngine::NewL()
// Symbian 2-phase constructor
// ----------------------------------------------------
//
CLoadLogEngine* CLoadLogEngine::NewL()
	{
	CLoadLogEngine* self = CLoadLogEngine::NewLC();
	CleanupStack::Pop(self);
	return self;
	}

// ----------------------------------------------------
// CLogExEngine::NewLC()
// Symbian 2-phase constructor
// ----------------------------------------------------
//
CLoadLogEngine* CLoadLogEngine::NewLC()
	{
	CLoadLogEngine* self = new (ELeave) CLoadLogEngine();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// ================= PRIVATE ======================= 

// ----------------------------------------------------
// CLogExEngine::ConstructL()
// Symbian 2-phase constructor
// ----------------------------------------------------
//
void CLoadLogEngine::ConstructL()
	{
	User::LeaveIfError(iFs.Connect());

	// Establish connection to log engine
	iLogClient = CLogClient::NewL(iFs);

	// Log view and view for recent events events with standard priority
	iLogViewEvent = CLogViewEvent::NewL(*iLogClient);
	//	iLogViewRecent = CLogViewRecent::NewL(*iLogClient);

	// Filter for events
	iLogFilter = CLogFilter::NewL();
	iLogFilter->SetEventType(KLogCallEventTypeUid);
		iEmptyLogFilter = CLogFilter::NewL();

	iRemoveObserver = NULL;

	iHashTable = NULL;
	//	InitHashTable();

	iTask = ESleep; // Default task for RunL
	iAfterInit = ESleep;

	User::LeaveIfError(iTimeWaster.CreateLocal());
	CActiveScheduler::Add(this);
	}

// ----------------------------------------------------
// CLogExEngine::RunL()
// RunL
// ----------------------------------------------------
//
void CLoadLogEngine::RunL()
	{
	switch (iTask)
		{
//		case EInit:
//			SegmentInit();
//			break;
		case EInitSMS:
			{
			SegmentInitSMS();
			break;
			}
		case EDeleteMessageTraverse:
			{
			SegmentDeleteMessageTraverse();
			break;
			}
		case EDeleteMessageLog:
			{
			// Inform observers about deleted event if necessary
			SegmentDeleteMessageLog();
			}
			break;
		case ESleep:
		default:
			{
			break;
			}
		}
	}

//void CLoadLogEngine::SegmentInit()
//	{
//	if (iLogViewEvent->SetFilterL(*iLogFilter, iStatus))
//	//			if (iLogViewRecent->SetRecentListL(KLogNullRecentList, iStatus))
//		{
//		iTask = iAfterInit;
//		SetActive();
//		}
//	else
//		{
//		ReleaseHashTable();
//		LoadNoRecord(iAfterInit);
//		iTask = ESleep;
//		}
//	}
void CLoadLogEngine::SegmentInitSMS()
	{
	SetEventFilterEventTypeSMS();
	if (iLogViewEvent->SetFilterL(*iLogFilter, iStatus))
		{
		iTask = EDeleteMessageTraverse;
		iAfterInit = EDeleteMessageLog;
		SetActive();
		}
	else
		{
		iTask = EDeleteMessageLog;
		ReadEventsL();
		}
	}

void CLoadLogEngine::SegmentDeleteMessageTraverse()
	{// Notify observer about change if it has been set			
	AddToDeleteArrayFromEventL(iLogViewEvent->Event());
	//			AddToDeleteArrayFromEventL(iLogViewRecent->Event());

	// if there are more events in the log engine database...
	if (iLogViewEvent->NextL(iStatus))
	//			if (iLogViewRecent->NextL(iStatus))
		{
		// ... set active to get the next one
		SetActive();
		}
	else // no more events
		{
		ReadEventsL();
		iTask = iAfterInit;
//		SetActive();
		}
	}

void CLoadLogEngine::SegmentDeleteMessageLog()
	{
	if (!DeleteEventL())
		{
		Cancel();
//		iLogClient->Cancel();
		ReleaseHashTable();
		iTask = ESleep;
		if (iRemoveObserver)
			iRemoveObserver->RemoveMessageLogDone();		
		}
	}

// ----------------------------------------------------
// CLogExEngine::RunError()
// RunL can leave so we need to implement RunError method
// ----------------------------------------------------
//
TInt CLoadLogEngine::RunError(TInt anError)
	{
	return anError;
	}

// ----------------------------------------------------
// CLogExEngine::DoCancel()
// Method to cancel outstanding request
// ----------------------------------------------------
//
void CLoadLogEngine::DoCancel()
	{
	//Cancel appropriate request
	iTimeWaster.Cancel();

	switch (iTask)
		{	
		case EDeleteMessageTraverse:
			iLogViewEvent->Cancel();
			break;
		case EDeleteMessageLog:
			iLogClient->Cancel();
			ReleaseHashTable();
			break;
		case ESleep:
		default:
			break;
		}
	}

// ----------------------------------------------------
// CLogExEngine::SetEventFilterEventTypeVoice()
// Sets voice type events filtering
// ----------------------------------------------------

void CLoadLogEngine::SetEventFilterEventTypeSMS()
    {
    ClearEventFilter();
    iLogFilter->SetEventType(KLogShortMessageEventTypeUid);
    }

// ----------------------------------------------------
// CLogExEngine::ClearEventFilter()
// Clears filter
// ----------------------------------------------------

void CLoadLogEngine::ClearEventFilter()
	{
	// Empty the active filter copying empty filter to it	
	iLogFilter->Copy(*iEmptyLogFilter);
	}

// ----------------------------------------------------
// CLogExEngine::ReadEventsL()
// Reads events from main event database
// ----------------------------------------------------
//
void CLoadLogEngine::ReadEventsL()
	{
	Cancel();
	iTimeWaster.After(iStatus, KWastTimeDuration);
	SetActive();
	}

//因为删除调用等待对话框(有活动对象),需要延迟1秒
void CLoadLogEngine::RemoveEventsL()
	{
	Cancel();
	iTimeWaster.After(iStatus, KWastTimeRemoveDuration);
	SetActive();
	}


void CLoadLogEngine::AddToDeleteArrayFromEventL(const CLogEvent& aEvent)
	{
	if (IsInHashTable(aEvent.Number(), *iHashTable))
		{
		iDeleteArray.Append(aEvent.Id());
		}
	}

void CLoadLogEngine::RemoveMessageLogByContacts(
		pCKCContactEntryArray aContactArray)
	{
	iContactArray = aContactArray;

	iDeleteArray.Reset();

	InitHashTable();

	for (TInt i = 0; i < aContactArray->Count(); i++)
		{
		CKCContactEntry* entry = (*aContactArray)[i];
		TPtrC number = entry->GetNumber();
		InsertHashTable(number, *iHashTable);
		}
	//	SetEventFilterEventTypeVoice();
	iTask = EInitSMS;
	RemoveEventsL();
	}

TBool CLoadLogEngine::DeleteEventL()
	{
	if (iDeleteArray.Count() > 0)
		{
		TLogId id = iDeleteArray[0];
		iDeleteArray.Remove(0);
		DeleteEventL(id);
		return ETrue;
		}
	else
		return EFalse;
	}

void CLoadLogEngine::DeleteEventL(TLogId& aLogId)
	{
	//Cancel();
	iLogClient->DeleteEvent(aLogId, iStatus);
	//	iTask = EDeleteEvent;
	SetActive();
	}


void CLoadLogEngine::RemoveCancel()
	{
	Cancel();
	iTask = ESleep;
	}

//End of file
