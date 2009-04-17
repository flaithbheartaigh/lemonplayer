/*
 ============================================================================
 Name		: FileRecordAdapter.h
 Author	  	: zengcity 
 Version	 : 1.0
 Copyright   : 
 Description : ¼������,�����ļ�.
 ����		: �����ļ���,��ʽ,����,
 ���		: ¼��.
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
	//��������
	void SetFileName(const TDesC& aFileName);

	//��ʼ¼��
	void StartRecordL();
	
private:

	CFileRecordAdapter();
	void ConstructL();
	
private:
	//��ȡ֧�ֵĸ�ʽ
	void TestSupportedFormat();

private:
	TFileName iFileName;
	
	//¼����
	CMdaAudioRecorderUtility* iMdaAudioRecorderUtility;
	TRecorderAdapterStatus iStatus;
	
	DEBUG
	(
	CFileLogger* iFileLogger;
	)
	};

#endif // FILERECORDADAPTER_H
