/*
 ============================================================================
 Name		: KCContactEntry.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : sohu
 Description : 联系人信息  主要数据传递 以后手机号处理应该还有控件,所以最好写成类,提供接口
 ============================================================================
 */

#ifndef KCCONTACTENTRY_H
#define KCCONTACTENTRY_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CKCContactEntry
 * 
 */
class CKCContactEntry : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CKCContactEntry();

	/**
	 * Two-phased constructor.
	 */
	static CKCContactEntry* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CKCContactEntry* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CKCContactEntry();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	void SetNameL(const TDesC& aName);
	const TDesC& GetName() const {return *iName;};
	
	void SetNumberL(const TDesC& aNumber);
	const TDesC& GetNumber()const {return *iNumber;};
	
private:
	HBufC* iName;		//显示名字
	HBufC* iNumber;		//手机号

	};

#endif // KCCONTACTENTRY_H
