/*
 ============================================================================
 Name		: TaskInfoManager.h
 Author	  : JohnLZeng
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CTaskInfoManager declaration
 ============================================================================
 */

#ifndef TASKINFOMANAGER_H
#define TASKINFOMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <GULICON.H>
#include "MacroUtil.h"
// CLASS DECLARATION
typedef struct _TaskInfo
	{
	TUid 		iUid;
	TTime 		iTime;
	TBuf<0x100> iName;
	
	CGulIcon* 		iIcon;
	RArray<TInt> 	iNumArray;
	
	_TaskInfo()
		{
		iIcon = NULL;
		}
	
	~_TaskInfo()
		{
		SAFE_DELETE(iIcon)
		iNumArray.Close();
		}
	}TaskInfo,*pTaskInfo;
/**
 *  CTaskInfoManager
 * 
 */
class CTaskInfoManager : public CBase
	{
public:
	enum TTaskErr
		{
		ETaskErrNone = 0,
		ETaskErrDuplicate,
		ETaskErrTimeOut			//
		};
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CTaskInfoManager();

	/**
	 * Two-phased constructor.
	 */
	static CTaskInfoManager* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CTaskInfoManager* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CTaskInfoManager();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	RPointerArray<TaskInfo>& GetTaskList() const {return *iTaskList;};
	
	void ConvertClockNumber();
	TBool AppendTask(const TUid& aUid,const TDesC& aName,const TTime& aTime);
	TInt AppendTask(const TDesC& aName,const TUid& aUid, const TInt& aType, const TInt& aCountDown, 
			const TTime& aTime);
	void RemoveTask(TInt aIndex);
	
	void InitTest();
	
	const TTime& GetMinTime() const;
	void TimeOut();
	TBool ExistTask();
	
private:
	void ConvertClock(const TTime& aTime,RArray<TInt>& aArray );
	TInt ParseLeftTime(TInt aSecend,RArray<TInt>& aArray );
	TInt ParseNumber(TInt aNumber,RArray<TInt>& aArray);
	void KillProcess(const TUid& aUid);
	void ShutDown();
	
	TBool IsDuplicate(const TUid& aUid);
private:
	RPointerArray<TaskInfo>	*iTaskList;

	};

#endif // TASKINFOMANAGER_H
