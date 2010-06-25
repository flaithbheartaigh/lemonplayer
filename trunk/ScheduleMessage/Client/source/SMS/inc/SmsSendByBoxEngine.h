#ifndef VIDEOEGGSMSENGINE_H_
#define VIDEOEGGSMSENGINE_H_

#include <e32base.h>
#include <badesca.h>
#include <MSVAPI.H>
#include <eikenv.h>
#include <cmessagedata.h>
#include <sendui.h>
#include <SendUiConsts.h>
#include <gsmupdu.h>

#include <aknwaitdialog.h>

#include "MacroUtil.h"

class CMsvSession;
class CMsvEntry;
class CMsvEntrySelection;
class CClientMtmRegistry;
class CSmsClientMtm;

typedef struct _CMsgDataForSend
	{
	HBufC* iAddress;
	HBufC* iContent;
	
	_CMsgDataForSend()
		{
		iAddress = NULL;
		iContent = NULL;
		}
	
	~_CMsgDataForSend()
		{
		SAFE_DELETE(iAddress)
		SAFE_DELETE(iContent)
		}
	}CMsgDataForSend;
	
class MSmsSendByBoxNotify
	{
public:
	virtual void SendState(TInt aState) = 0; 
	};

class CSmsSendByBoxEngine : public CActive, public MMsvSessionObserver
	{
public:
	static CSmsSendByBoxEngine* NewL(MSmsSendByBoxNotify& aNotify);
	virtual ~CSmsSendByBoxEngine();
public:
	//from MMsvSessionObserver
	virtual void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1,
			TAny* aArg2, TAny* aArg3);
public:
//	void SetMsgContent(const TDesC& aContent);
//	void SetToAddrress(const TDesC& aAddress);
	void AppendAddressAndContent(const TDesC& aAddress,const TDesC& aContent);
	TInt Start();
	
	void ResetData();

private:
	CSmsSendByBoxEngine(MSmsSendByBoxNotify& aNotify);
	void ConstructL();

	void CreateMsg();
	TBool ValidateSMS();
	void SendMsg();

	//from CActive
	virtual void RunL();
	virtual void DoCancel();

private:
	CMsvSession* iSession;
	CClientMtmRegistry* iMtmReg;
	CSmsClientMtm* iSmsMtm;

	CMsvOperation* iOper;
	CMsvEntrySelection* iEntrySelection;

	TMsvId iSmsId;

//	TBuf<100> iMsgContent;
//	TBuf<11> iAddress;
	
	RPointerArray<CMsgDataForSend>* iMsgData;
	MSmsSendByBoxNotify& iNotify;
	};
#endif
