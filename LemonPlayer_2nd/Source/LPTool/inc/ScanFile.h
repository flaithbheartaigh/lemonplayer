/*
 ============================================================================
 Name		: ScanFile.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CScanFile declaration
 ============================================================================
 */

#ifndef SCANFILE_H
#define SCANFILE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <f32file.h>
#include <badesca.h>
// CLASS DECLARATION

_LIT(KScanInfoSplit,";");
/**
 *  CScanFile
 * 
 */
class ScanFileNotify
	{
public:
	virtual void UpdateScan(const TDesC& aInfo) = 0;
	virtual void FinishScan(const TDesC& aInfo) = 0;
	};

class CScanFile : public CActive 
	{
public:
	enum EScanState
		{
		KScanInit = 0,
		KScanDriveC,
		KScanDriveCDone, 
		KScanDriveE,
		KScanDriveEDone
		};
public:
	// Constructors and destructor

	~CScanFile();
	static CScanFile* NewL(ScanFileNotify* aNotifier);
	static CScanFile* NewLC(ScanFileNotify* aNotifier);

private:
	CScanFile(ScanFileNotify* aNotifier);
	void ConstructL();

private: // From CActive
	void RunL();
	void DoCancel();
	
public:
	void StartL();
	
private:
	TBool Scaning();
	void ScanFromRoot(const TDesC& aDrive);
	TBool ScanNext();
	
	TBool IsAllowedFormat(const TDesC& aExt);
	
	void CreateInfo(TDes& aInfo);
	
private:
	RTimer iTimeWaster;
	ScanFileNotify* iNotifier;
	CDirScan* iDirScan;
	EScanState iScanState;
	
	TInt iTotalFolder;
	TInt iTotalFile;
	
	CDesCArray* iFormatArray;
	};

#endif // SCANFILE_H
