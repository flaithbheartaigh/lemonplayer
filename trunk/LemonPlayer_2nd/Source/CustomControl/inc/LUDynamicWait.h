/*
 ============================================================================
 Name		: LUDynamicWait.h
 Author	  :   zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CLUDynamicWait declaration
 				等待对话框,动态更新文字
 ============================================================================
 */

#ifndef LUDYNAMICWAIT_H
#define LUDYNAMICWAIT_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <AknWaitDialog.h> 
// CLASS DECLARATION

/**
 *  CLUDynamicWait
 * 
 */
class CLUDynamicWait : 	public CBase,
						public MProgressDialogCallback
	{
public:
	// Constructors and destructor
	~CLUDynamicWait();
	static CLUDynamicWait* NewL();
	static CLUDynamicWait* NewLC();

private:
	CLUDynamicWait();
	void ConstructL();
	
protected:  // Functions from base classes
    void DialogDismissedL( const TInt aButtonId );
	
public:
	void CloseWaitNoteL();
	void OpenWaitNoteL( const TInt aResourceId );
	//更新文字	
	void UpdateTextL(const TDesC& aText);
	
	void Finished();
	
private:
	//更新CBA
	void UpdateCBA(const TInt aId);
	
private:
	CAknWaitDialog* iWaitDialog;
	};

#endif // LUDYNAMICWAIT_H
