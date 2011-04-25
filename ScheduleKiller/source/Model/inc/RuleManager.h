/*
 ============================================================================
 Name		: RuleManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CRuleManager declaration
 ============================================================================
 */

#ifndef RULEMANAGER_H
#define RULEMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <f32file.h>
#include "Rule.h"
// CLASS DECLARATION

/**
 *  CRuleManager
 * 
 */
class CRuleManager : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CRuleManager();

	/**
	 * Two-phased constructor.
	 */
	static CRuleManager* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CRuleManager* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CRuleManager();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	//new func
	void AppendRule(const TDesC& aName,const TUid& aUid, const TInt& aType, const TInt& aCountDown, 
			const TTime& aTime, const TDesC& aRuleName);
	
	void AppendFavRule(const TDesC& aName,const TUid& aUid, const TInt& aType, const TInt& aCountDown, 
			const TTime& aTime);
	
	RPointerArray<CRule>* Rules() const {return iRules;};
	
	CRule* GetRule(const TInt& aIndex) const ;
	
	void Init();
	
	TBool Select(const TInt& aIndex);
	TBool Delete(const TInt& aIndex);
	TBool LunchRun(const TInt& aIndex);
	
	static void TimeFormat(const TTime& aTime,TDes8& aDes);
	static void TimeSet(const TDesC& aDes,TTime& aTime);
	
	void AutoLunch();
	void FavLunch();
private:
	//new func
	void WriteToFile(CRule* aRule);
	void WriteToFile(RFile& file,CRule* aRule);
	void WriteToFile(RPointerArray<CRule>* aRules);

	void WriteFavToFile();
	
	void ReadFromFile();
	void ReadFromFile(RFile& file);
	void ReadFromFile(const TDesC8& aFile,TInt aPos,CRule* aRule);
	
	void ReadFavFromFile();
	
	TBool Confirm(const TInt& aIndex);
	TBool Execute(const TInt& aIndex);
	
	TBool DeleteRule(const TInt& aIndex);
	TBool IsSame(const TDesC& aName,const TUid& aUid, const TInt& aType, const TInt& aCountDown, 
			const TTime& aTime);
private:
	RPointerArray<CRule>* iRules;
	CRule*		iFavRule;			//常用的规则
	};

#endif // RULEMANAGER_H
