/*
 * 
 */

#ifndef SMS_EXAMPLE_ENGINE
#define SMS_EXAMPLE_ENGINE

// INCLUDES 
#include <e32base.h> // CBase
#include <msvapi.h>  // MMsvSessionObserver
#include <badesca.h> // CDesCArrayFlat

#include "SMSDef.h"
#include "SimMsgStruct.h"
// FORWARD DECLARATIONS
class CClientMtmRegistry;
class CSmsClientMtm;
class MSMSExampleMtmsEngineObserver;

// CLASS DECLARATION

/**
 * SMS engine handles SMS message handling (i.e moving, deleting, copying,
 * retrieving message data).
 */
class CLoadMessageEngine : public CBase,
//public CActive,
		public MMsvSessionObserver
	{
public:

	/**
	 * Create new CSMSExampleMtmsEngine object
	 *
	 * @param aObserver a reference to MSMSExampleMtmsEngineObserver. 
	 * @return a pointer to the created instance of CSMSExampleMtmsEngine
	 */
	static CLoadMessageEngine* NewL();

	/**
	 * Destructor.
	 */
	~CLoadMessageEngine();


private:
	
	/**
	 * A constructor.
	 * @param aObserver Observer of this engine.
	 */
	CLoadMessageEngine();

	/**
	 * ConstructL()
	 */
	void ConstructL();

	/**
	 * Creates SMS client.
	 */
	void CreateMtmClientL();

private:
	// from MMsvSessionObserver
	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2,
			TAny* aArg3);
	// from CActive
	virtual void DoCancel();
	virtual void RunL();

public:
	void CreateNewMessageL(const TDesC& aAddr, const TDesC& aContent);
	void CreateNewMessageToSendBoxL(const TDesC& aAddr, const TDesC& aContent);
	void LoadSMSDraft(CSMSInfoListArray* aArray);
	void LoadSMSFromFolder(CSMSInfoListArray* aArray,TMsvId aFolder);
//	HBufC* ReadMessage(TMsvId entryID);
	CSMSDraftInfo* ReadMessage(TMsvId aEntryID);
	
private:
	TPtrC CreateMsgContact(const TDesC& aNumber);

private:
	// SMS client MTM interface
	CSmsClientMtm* iSmsMtm;

	// Represents a session to the messaging server
	CMsvSession* iSession;

	// This registry holds details of the all the Client-side 
	// MTMs currently available on the system. 
	CClientMtmRegistry* iClientMtmReg;
	
	HBufC* iNumContact;		//短信显示的收件人,通讯本中有则用通讯本数据,否则直接使用号码
	

	};

#endif  // SMS_EXAMPLE_ENGINE
