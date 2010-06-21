/*
 * ==============================================================================
 *  Name        : timesession.h
 *  Part of     : CSSync
 *  Interface   :
 *  Description :
 *  Version     :
 *
 *  Copyright (c) 2006 Nokia Corporation.
 *  This material, including documentation and any related
 *  computer programs, is protected by copyright controlled by
 *  Nokia Corporation.
 * ==============================================================================
 */

#ifndef ___SIMULATEMESSAGESESSION_H__
#define ___SIMULATEMESSAGESESSION_H__

// INCLUDE FILES
#include <e32base.h>

#include "SimMsgStruct.h"

// FORWARD DECLARATIONS
class CSimulateMessageServer;

// CLASS DECLARATION
/**
 * CSimulateMessageServerSession.
 *  An instance of class CSimulateMessageServerSession is created for each client.
 */

;

class CSimulateMessageServerSession : public CSession2
	{
public:
	// Constructors and destructors

	/**
	 * NewL.
	 * Two-phased constructor.
	 * @param aServer The server.
	 * @return Pointer to created CSimulateMessageServerSession object.
	 */
	static CSimulateMessageServerSession* NewL(CSimulateMessageServer& aServer);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * @param aServer The server.
	 * @return Pointer to created CSimulateMessageServerSession object.
	 */
	static CSimulateMessageServerSession
			* NewLC(CSimulateMessageServer& aServer);

	/**
	 * ~CSimulateMessageServerSession.
	 * Destructor.
	 */
	virtual ~CSimulateMessageServerSession();

public:
	// Functions from base classes

	/**
	 * From CSession, ServiceL.
	 * Service request from client.
	 * @param aMessage Message from client
	 *                 (containing requested operation and any data).
	 */
	void ServiceL(const RMessage2& aMessage);

private:
	// Constructors and destructors

	/**
	 * CSimulateMessageServerSession.
	 * C++ default constructor.
	 * @param aServer The server.
	 */
	CSimulateMessageServerSession(CSimulateMessageServer& aServer);

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

private:
	// New methods

	/**
	 * PanicClient.
	 * Causes the client thread to panic.
	 * @param aMessage Message from client.
	 * @param aPanic Panic code.
	 */
	void PanicClient(const RMessagePtr2& aMessage, TInt aPanic) const;

	/**
	 * RequestTimeL.
	 * Handle the result of the client requesting the time.
	 * Gets the time and writes it back to the client synchronously.
	 * @param aMessage Message from client.
	 */
	void RequestTimeL(const RMessage2& aMessage);
	
	void SendDriver(const RMessage2& aMessage);
	void QueryState(const RMessage2& aMessage);
	void QueryAllLength(const RMessage2& aMessage);
	void QueryAllData(const RMessage2& aMessage);
	void QueryRemovedLength(const RMessage2& aMessage);
	void QueryRemovedData(const RMessage2& aMessage);
	void QueryAllTasks(const RMessage2& aMessage);
	void AddTask(const RMessage2& aMessage);
	void RemoveTask(const RMessage2& aMessage);
	TInt ClearRemoved();
	
	TInt QueryAllTasks(RSimMsgDataArray& aArray);
	TInt AddTask(SimMsgData* aTask);
	TInt RemoveTask(const SimMsgData& aTask);
	
	void AddTaskToArray(SimMsgData* aTask,RSimMsgDataArray& aArray);
	
	TInt ReadDataFromFile(RSimMsgDataArray& aArray);
	TInt WriteDataToFile(const RSimMsgDataArray& aArray);
	
	TInt ParseDataBuffer(HBufC8* aBuffer,RSimMsgDataArray& aArray);
	TInt WriteData(RFile& aFile,const SimMsgData& aTask);
	
	TBool IsSameTask(const SimMsgData& aTask1,const SimMsgData& aTask2);

private:
	// Data

	/**
	 * iServer, reference to the server.
	 */
	CSimulateMessageServer& iServer;
	
	};

#endif // ___SIMULATEMESSAGESESSION_H__

// End of File
