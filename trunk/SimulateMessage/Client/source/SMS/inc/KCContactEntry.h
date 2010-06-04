/*
 ============================================================================
 Name		: KCContactEntry.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : sohu
 Description : ��ϵ����Ϣ  ��Ҫ���ݴ��� �Ժ��ֻ��Ŵ���Ӧ�û��пؼ�,�������д����,�ṩ�ӿ�
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
	HBufC* iName;		//��ʾ����
	HBufC* iNumber;		//�ֻ���

	};

#endif // KCCONTACTENTRY_H
