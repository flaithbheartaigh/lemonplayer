/*
 ============================================================================
 Name		: MusicListMgr.h
 Author	  : zengcity
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMusicListMgr declaration
 ============================================================================
 */

#ifndef MUSICLISTMGR_H
#define MUSICLISTMGR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include "MFileOperate.h"
// CLASS DECLARATION
class CMusicInfoBean;

/**
 *  CMusicListMgr
 * 
 */
class CMusicListMgr : public CBase,
					  public MFileOperate
	{
public:
	// Constructors and destructor
	~CMusicListMgr();
	static CMusicListMgr* NewL();
	static CMusicListMgr* NewLC();
	
private:
	CMusicListMgr();
	void ConstructL();
	
public:
	virtual TInt ReadFile(const TDesC& aFileName);
	virtual TInt WriteFile(const TDesC& aFileName);
	
public:
	RPointerArray<CMusicInfoBean>* GetList()
		{return iList;};
	void SetList(RPointerArray<CMusicInfoBean>* aList)
		{iList = aList;};
	
private:
	void ReadInfoToBean(CMusicInfoBean* aBean,const TDesC8& aText);
	void ReadFileToBean(CMusicInfoBean* aBean,const TDesC8& aText);
	
	void WriteInfoToBean(CMusicInfoBean* aBean,TDes8& aText);
	void WriteFileToBean(CMusicInfoBean* aBean,TDes8& aText);
private:
	RPointerArray<CMusicInfoBean>* iList;

	};

#endif // MUSICLISTMGR_H
