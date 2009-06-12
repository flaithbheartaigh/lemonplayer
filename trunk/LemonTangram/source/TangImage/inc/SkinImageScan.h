/*
 ============================================================================
 Name		: SkinImageScan.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSkinImageScan declaration
 ============================================================================
 */

#ifndef SKINIMAGESCAN_H
#define SKINIMAGESCAN_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "SkinScanDef.h"

// CLASS DECLARATION

/**
 *  CSkinImageScan
 * 
 */
class CSkinImageScan : public CBase
	{
public:
	// Constructors and destructor
	~CSkinImageScan();
	static CSkinImageScan* NewL();
	static CSkinImageScan* NewLC();

private:
	CSkinImageScan();
	void ConstructL();
	
public:
	void ScanFolder(const TDes& aFolder);
	RPointerArray<SkinImageStruct>& GetSkins() {return iSkins;};

private:
	RPointerArray<SkinImageStruct> iSkins;
	};

#endif // SKINIMAGESCAN_H
