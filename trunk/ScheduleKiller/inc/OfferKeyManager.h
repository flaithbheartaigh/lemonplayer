/*
 ============================================================================
 Name		: OfferKeyManager.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : COfferKeyManager declaration
 ============================================================================
 */

#ifndef OFFERKEYMANAGER_H
#define OFFERKEYMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coedef.h>
#include <w32std.h>
#include "TimeOutTimer.h"
#include "timeoutnotifier.h"

// CLASS DECLARATION

/**
 *  COfferKeyManager
 * 
 */
class COfferKeyManager : public CBase , public MTimeOutNotifier
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~COfferKeyManager();

	/**
	 * Two-phased constructor.
	 */
	static COfferKeyManager* NewL();

	/**
	 * Two-phased constructor.
	 */
	static COfferKeyManager* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	COfferKeyManager();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	//from base 
	void TimerExpired() ;
	
	//new func
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	
private:
	void StartTimer();
	
private:
	CTimeOutTimer* iTimer;
	TBool 	iActive;
	};

#endif // OFFERKEYMANAGER_H
