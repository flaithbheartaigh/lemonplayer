/*
 ============================================================================
 Name		: Rule.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRule declaration
 ============================================================================
 */

#ifndef RULE_H
#define RULE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "MacroUtil.h"
// CLASS DECLARATION

/**
 *  CRule
 * 
 */
class CRule : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CRule();

	/**
	 * Two-phased constructor.
	 */
	static CRule* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CRule* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CRule();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	TUid GetUid() const {return iUid;};
	void SetUid(const TUid& aUid) {iUid = aUid; };
	
	TPtrC GetName() const {return iName->Des();};
	void SetName(const TDesC& aName) {SAFE_DELETE(iName);iName = aName.AllocL();};
	
	TPtrC GetRuleName() const {return iRuleName->Des();};
	void SetRuleName(const TDesC& aName) {SAFE_DELETE(iRuleName);iRuleName = aName.AllocL();};
	
	TInt GetType() const {return iType;};
	void SetType(const TInt& aType) {iType = aType;};
	
	TTime GetClock() const {return iClock;};
	void SetClock(const TTime& aTime) {iClock = aTime;};
	
	TInt GetCountDown() const {return iCountDown;};
	void SetCountDown(const TInt& aCountDown) {iCountDown = aCountDown;};
	
private:
	TUid iUid;
	HBufC* iName;
	HBufC* iRuleName;
	TInt iType;
	TTime iClock;
	TInt iCountDown;

	};

#endif // RULE_H
