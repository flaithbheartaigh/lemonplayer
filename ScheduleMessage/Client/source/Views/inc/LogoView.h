/*
 ============================================================================
 Name		: LogoView.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLogoView declaration
 ============================================================================
 */

#ifndef LOGOVIEW_H
#define LOGOVIEW_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <aknview.h>
#include <avkon.hrh>
#include <f32file.h>

#include "LogoContainer.h"
#include "TimeOutNotifier.h"

// CLASS DECLARATION
class CTimeOutTimer;

/**
 *  CLogo
 * 
 */
class CLogoView : public CAknView, public MTimeOutNotifier
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CLogoView();

	/**
	 * Two-phased constructor.
	 */
	static CLogoView* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CLogoView* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CLogoView();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
//	void HandleStatusPaneSizeChange();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();
	
protected:
	virtual void TimerExpired();

private:
	CLogoContainer * iContainer;
	CTimeOutTimer* iTimer;
	};

#endif // LOGOVIEW_H
