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
	TUid GetUid() const {return iUid;};
	void SetUid(const TUid& aUid) {iUid = aUid; iEmputy = EFalse;};
	
	TTime GetTime() const {return iTime;};
	void SetTime(const TTime& aTime) {iTime = aTime;};
	
	const TDesC& GetName() const {return iName;};
	void SetName(const TDesC& aName) {iName.Copy(aName);};
	
	TUid GetTransUid() const {return iTransUid;};
	void SetTransUid(const TUid& aUid) {iTransUid = aUid;};
	
	const TDesC& GetTransName() const {return iTransName;};
	void SetTransName(const TDesC& aName) {iTransName.Copy(aName);};
	
	CRule* GetRule() const {return iRule;};
	void SetRule(const TInt& aType,const TInt& aCountdown,const TTime& aClock);
	
	TBool IsEmputy() const {return iEmputy;};
	void SetEmputy(TBool aEmputy) {iEmputy = aEmputy;};
	
	CRuleManager* GetRuleManager() const {return iRuleManager;};
	
	CTimeWorkManager* GetTimeWorkManager() const {return iTimeWork;};
private:
	TUid iUid;
	TTime iTime;
	TBuf<0x100> iName;
	
	TUid iTransUid;
	TBuf<0x100> iTransName;
	
	CRule* iRule;
	
	TBool iEmputy;
	
	CRuleManager* iRuleManager;
	CTimeWorkManager* iTimeWork;
	};

#endif // SHMODEL_H
