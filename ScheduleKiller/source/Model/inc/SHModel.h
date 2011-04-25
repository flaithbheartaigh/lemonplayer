/*
 ============================================================================
 Name		: SHModel.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSHModel declaration
 ============================================================================
 */

#ifndef SHMODEL_H
#define SHMODEL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "RuleManager.h"
#include "TimeWorkManager.h"
#include "Rule.h"
#include "TaskInfoManager.h"
// CLASS DECLARATION

/**
 *  CSHModel
 * 
 */
class CSHModel : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CSHModel();

	/**
	 * Two-phased constructor.
	 */
	static CSHModel* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CSHModel* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CSHModel();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:	
	TUid GetTransUid() const {return iTransUid;};
	void SetTransUid(const TUid& aUid) {iTransUid = aUid;};
	
	const TDesC& GetTransName() const {return iTransName;};
	void SetTransName(const TDesC& aName) {iTransName.Copy(aName);};
	
	CRule* GetRule() const {return iRule;};
	void SetRule(const TInt& aType,const TInt& aCountdown,const TTime& aClock);
	
	CRuleManager* GetRuleManager() const {return iRuleManager;};
	
	CTimeWorkManager* GetTimeWorkManager() const {return iTimeWork;};
	
	CTaskInfoManager* GetTaskInfoManager() const {return iTaskInfoManager;};
private:
	
	TUid iTransUid;
	TBuf<0x100> iTransName;
	
	CRule* iRule;
	
	CRuleManager* iRuleManager;
	CTimeWorkManager* iTimeWork;
	CTaskInfoManager* iTaskInfoManager;
	};

#endif // SHMODEL_H
