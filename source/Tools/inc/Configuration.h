/*
============================================================================
 Name		: Configuration.h
 Author	  : yaoyang
 Version	 :
 Copyright   : 
 Description : CConfiguration declaration
============================================================================
*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <f32file.h>

/************************************************************************/
/* ����					�޸�����			�޸�����                                                                     
	mystery302			2009.3.13			�����ڷ�UI�̻߳����µ�֧��
*/
/************************************************************************/

// CLASS DECLARATION

/**
*  CConfiguration
* 
*/

class TConfigItem
{
public:
	TBuf<32> iKey;
	TBuf<128> iValue;
};

class CConfiguration : public CBase
{
public: // Constructors and destructor

	/**
		* Destructor.
		*/
	~CConfiguration();

		/**
		* Two-phased constructor.
		*/
	static CConfiguration* NewL(const TDesC& aConfigFilePath);

		/**
		* Two-phased constructor.
		*/
	static CConfiguration* NewLC(const TDesC& aConfigFilePath);

	//new function 

	//ͨ��Key��ȡ�����ַ���
	TBool Get(const TDesC& aKey, TDes& aValue);

	//���������ļ�
	TBool Set(const TDesC& aKey, const TDesC& aValue);

private:

	/**
		* Constructor for performing 1st stage construction
	*/
	CConfiguration();

	/**
		* EPOC default constructor for performing 2nd stage construction
	*/
	void ConstructL(const TDesC& aConfigFilePath);

	//new function
	void ParseLine(TDesC& aLine, TDes& akey, TDes& aValue);
public:
	virtual TBool SaveL();
	virtual TBool SaveInternalL(RFs& aFs);
	virtual TBool LoadL();
	virtual TBool LoadInternalL(RFs& aFs);
private:
	//new data
	TBuf<128> iFilePath;
	HBufC8* iFileContent;
	CArrayFixFlat<TConfigItem>* iConfigItemArray; 
	TBool iHasSave;
};

#endif // CONFIGURATION_H

