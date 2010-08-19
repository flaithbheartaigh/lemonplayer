/*
 * ============================================================================
 *  Name     : CLogExEngine from LogExEngine.h
 *  Part of  : LogExample
 *  Created  : 26.05.2005 by Forum Nokia 
 *  Description:
 *     provides interface to Log engine
 *  Version  : 1.0
 *  Copyright: Nokia Corporation 
 * ============================================================================
 */

#ifndef __LOGEXENGINE_H__
#define __LOGEXENGINE_H__

// INCLUDE FILES
#include <e32base.h>
#include <f32file.h>        // RFs
#include <logcli.h>			// CLogClient
#include <logview.h>		// CLogViewEvent

#include "EventsObserver.h"
#include "LoadContactEngine.h"



//CLASS DECLARATION

class CLoadLogEngine : public CActive , public MLoadContactEngine
    {
public:
	enum
	    {    
//	    EInit = 1,
	    EInitSMS = 1,
	    EDeleteMessageTraverse,
	    EDeleteMessageLog,
	    ESleep
	    };

    /**
     * Symbian OS default constructor
     */
    CLoadLogEngine();

    /**
     * Two-phased constructor.
     */
    static CLoadLogEngine* NewL();

    /**
     * Two-phased constructor.
     */
    static CLoadLogEngine* NewLC();

    /**
     * Destructor
     */
    virtual ~CLoadLogEngine();

    void SetEventFilterEventTypeSMS();
    void ClearEventFilter();

private:

    /**
     * Symbian 2-phase constructor
     */
    void ConstructL();

    /**
     * From CActive
     */
    void RunL();

    /**
     * From CAktive
     */
    TInt RunError(TInt anError);

    /**
     * From CActive
     */
    void DoCancel();
    
public:
	
	void RemoveMessageLogByContacts(pCKCContactEntryArray aContactArray);
	
	void RemoveCancel();
	
private:
    /**
     * Reads events from the main event database
     */
    void ReadEventsL();
    void RemoveEventsL();
	
	void AddToDeleteArrayFromEventL(const CLogEvent& aEvent);
	
	TBool DeleteEventL();
	void DeleteEventL(TLogId& aLogId);
	
	void LoadNoRecord(TInt aState);
	
	void SegmentInitSMS();
	void SegmentDeleteMessageTraverse();
	void SegmentDeleteMessageLog();

private:
    // Data Members
    RFs iFs;

    CLogClient* iLogClient;
    CLogViewEvent* iLogViewEvent;

    // Filters for event log
    CLogFilter* iLogFilter;
    CLogFilter* iEmptyLogFilter;

    TInt iTask; // task for RunL
    TInt iAfterInit;
    
    RTimer iTimeWaster;
    
    RArray<TLogId> iDeleteArray;
    
    };

#endif	

// End of file
