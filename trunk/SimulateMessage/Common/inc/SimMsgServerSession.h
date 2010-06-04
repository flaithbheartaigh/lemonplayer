/*
 ============================================================================
 Name		: SimMsgServerSession.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSimMsgServerSession declaration
 ============================================================================
 */

#ifndef SIMMSGSERVERSESSION_H
#define SIMMSGSERVERSESSION_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "SimMsgStruct.h"
// CLASS DECLARATION

/**
 *  CSimMsgServerSession
 * 
 */
class CSimMsgServerSession : public RSessionBase
	{
public:
	// Constructors and destructor

	CSimMsgServerSession();
	
public: // New functions

    /**
    * Connect.
    * Connects to the server and create a session.
    * @return Error code.
    */
    TInt Connect();

    /**
    * Version.
    * Gets the version number.
    * @return The version.
    */
    TVersion Version() const;
    
    TBool IsScheduleActive();
    
    void QueryAllTasks(RSimMsgDataArray& aArray);
    void AddTask(SimMsgData& aTask);
    void RemoveTask(SimMsgData& aTask);
    
    void ActiveSchedule();
    void DeactiveSchedule();
    

	};

#endif // SIMMSGSERVERSESSION_H
