/*
 ============================================================================
 Name		: FileRecordAdapter.h
 Author	  	: zengcity 
 Version	 : 1.0
 Copyright   : 
 Description : 录制声音,保存文件.
 输入		: 保存文件名,格式,数据,
 输出		: 录制.
 ============================================================================
 */

#ifndef FILERECORDADAPTER_H
#define FILERECORDADAPTER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

#include <MdaAudioSampleEditor.h>
#include "RecorderDefine.h"
#include "LPDebug.h"
// CLASS DECLARATION

/**
 *  CFileRecordAdapter
 * 
 */
class CFileRecordAdapter : public CBase,public MMdaObjectStateChangeObserver
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFileRecordAdapter();

	static CFileRecordAdapter* NewL();
	static CFileRecordAdapter* NewLC();
	
public:
	//from MMdaObjectStateChangeObserver
	void MoscoStateChangeEvent(CBase* aObject, TInt aPreviousState, TInt aCurrentState, TInt aErrorCode);
	
public:
	//输入设置
	void SetFileName(const TDesC& aFileName);

	//开始录制
	void StartRecordL();
	
private:

	CFileRecordAdapter();
	void ConstructL();
	
private:
	//获取支持的格式
	void TestSupportedFormat();

private:
	TFileName iFileName;
	
	//录制类
	CMdaAudioRecorderUtility* iMdaAudioRecorderUtility;
	TRecorderAdapterStatus iStatus;
	
	DEBUG
	(
	CFileLogger* iFileLogger;
	)
	};

#endif // FILERECORDADAPTER_H
