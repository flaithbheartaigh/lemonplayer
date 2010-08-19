/*
 * ============================================================================
 *  Name     : MEvenstObserver from EventsObserver.h
 *  Part of  : LogExample
 *  Created  : 26.05.2005 by Forum Nokia 
 *  Description:
 *     Declares main application class.
 *  Version  : 1.0
 *  Copyright: Nokia Corporation
 * ============================================================================
 */

#ifndef __EVENTSOBSERVER_H__
#define __EVENTSOBSERVER_H__

// INCLUDE FILES

// CLASS DECLARATION
class MRemoveContentEngineObserver
	{
public:
	virtual void RemoveMessageLogDone() = 0;
	};
#endif

// End of file
