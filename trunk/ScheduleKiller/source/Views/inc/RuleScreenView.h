/*
 ============================================================================
 Name		: RuleScreenView.h
 Author	  : zengcity
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef RULESCREENVIEW_H
#define RULESCREENVIEW_H

// INCLUDES
#include <aknview.h>

#include "RuleScreenContainer.h"
// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CRuleScreenView view class.
 * 
 */
class CRuleScreenView : public CAknView
	{
public:
	// Constructors and destructor
	~CRuleScreenView();
	static CRuleScreenView* NewL();
	static CRuleScreenView* NewLC();

public:
	TUid Id() const;
	void HandleCommandL(TInt aCommand);
	void HandleStatusPaneSizeChange();
	void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

private:
	CRuleScreenView();
	void ConstructL();

protected:
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			const TDesC8& aCustomMessage);
	void DoDeactivate();

private:
	CRuleScreenContainer * iContainer;
	};

#endif

