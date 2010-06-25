/*
 ============================================================================
 Name		: SHModel.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSHModel declaration
 ============================================================================
 */

#ifndef SHMODEL_H
#define SHMODEL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <msvstd.h>
#include "SimMsgStruct.h"

// CLASS DECLARATION

/**
 *  CSHModel
 * 
 */
class CSHModel : public CBase
	{
public:
	enum TEditModel
		{
		EEditModelCreate,
		EEditModelLoadDraft,
		EEditmodelModify
		};
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CSHModel();

	/**
	 * Two-phased constructor.
	 */
	static CSHModel* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CSHModel* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CSHModel();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	void SetEditModel(TEditModel aModel) {iEditModel = aModel;};
	TInt GetEditModel() const {return iEditModel;};
	
	void SetEditMessage(SimMsgData* aMsg);
	SimMsgData* GetEditMessage() const {return iEditMessage;};
	
	void SetDraftMsg(TMsvId aMsg) {iDraftMsg = aMsg;};
	TMsvId GetDraftMsg() {return iDraftMsg;};
	
private:
	TEditModel iEditModel;
	SimMsgData* iEditMessage;
	TMsvId	iDraftMsg;
	};

#endif // SHMODEL_H
