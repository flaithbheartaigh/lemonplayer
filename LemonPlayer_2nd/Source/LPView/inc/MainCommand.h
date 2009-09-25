/*
 ============================================================================
 Name		: MainCommand.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMainCommand declaration
 ============================================================================
 */

#ifndef MAINCOMMAND_H
#define MAINCOMMAND_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <MAknFileSelectionObserver.h> 
#include "ScanFile.h"

// CLASS DECLARATION
class CLUDynamicWait;

/**
 *  CMainCommand
 * 
 */
class CMainCommand : public CBase,
					public ScanFileNotify,
					public MAknFileSelectionObserver
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CMainCommand();

	/**
	 * Two-phased constructor.
	 */
	static CMainCommand* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CMainCommand* NewLC();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CMainCommand();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	virtual void UpdateScan(const TDesC& aInfo);
	virtual void FinishScan(const TDesC& aInfo);
	
	virtual TBool OkToExitL (const TDesC &aDriveAndPath, const TEntry &aEntry);
	
public:
	void OpenAll();
	void OpenOne();
	void AddOne();
	
private:
	void StartOpenAll();
	void ShowSelectFile(TBool aOpen);
	
	void CreateInfo(const TDesC& aMsg,TDes& aInfo);
	
private:
	CLUDynamicWait* iWaitDlg;
	CScanFile *iFileScaner;
	};

#endif // MAINCOMMAND_H
