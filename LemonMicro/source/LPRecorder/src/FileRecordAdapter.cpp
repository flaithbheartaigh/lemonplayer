/*
 ============================================================================
 Name		: FileRecordAdapter.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFileRecordAdapter implementation
 ============================================================================
 */

#include "FileRecordAdapter.h"
#include "MacroUtil.h"

#include <aknnotewrappers.h> 

CFileRecordAdapter::CFileRecordAdapter()
	{
	// No implementation required
	}

CFileRecordAdapter::~CFileRecordAdapter()
	{
	SAFE_DELETE(iMdaAudioRecorderUtility);
	DEBUG(SAFE_DELETE(iFileLogger);)
	}

CFileRecordAdapter* CFileRecordAdapter::NewLC()
	{
	CFileRecordAdapter* self = new (ELeave)CFileRecordAdapter();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CFileRecordAdapter* CFileRecordAdapter::NewL()
	{
	CFileRecordAdapter* self=CFileRecordAdapter::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CFileRecordAdapter::ConstructL()
	{
	DEBUG(iFileLogger = CFileLogger::NewL(_L("c:\\CFileRecordAdapter.txt"));)
	iMdaAudioRecorderUtility = CMdaAudioRecorderUtility::NewL(*this, 0, 80, 
			EMdaPriorityPreferenceQuality);
	TestSupportedFormat();
	}

void CFileRecordAdapter::MoscoStateChangeEvent(CBase* /*Object*/, TInt aPreviousState, TInt CurrentState, TInt aErrorCode)
{
	if (aErrorCode != KErrNone)
		{	
			//If user wants record, but errors occurs, warning note is shown
			if (iStatus == ERecording)
				{
				_LIT(text, "Recording failed!");
				CAknWarningNote* note = new (ELeave) CAknWarningNote();
				note -> ExecuteLD(text);
				}
				
			iStatus = EStop;
		}
	//When recorder is ready and state is ERecording, recording may start
	else if (iStatus == ERecording && CurrentState == 1 && aPreviousState == 0)
		{
		// Set maximum gain for recording
	    iMdaAudioRecorderUtility->SetGain(iMdaAudioRecorderUtility->MaxGain());
	   	
	   	iMdaAudioRecorderUtility->SetPosition(TTimeIntervalMicroSeconds(0));
	   
	    iMdaAudioRecorderUtility->RecordL();
		}
	//If playing stops to end of the file, status changes to EStop	
	else if (iStatus == EPlaying && CurrentState == 1)
		{
				iStatus = EStop;				
		}
}

//输入设置
void CFileRecordAdapter::SetFileName(const TDesC& aFileName)
	{
	iFileName.Copy(aFileName);
	}

	//开始录制
void CFileRecordAdapter::StartRecordL()
	{
	iStatus = ERecording;
	
	iMdaAudioRecorderUtility->OpenFileL(iFileName);
	}

void CFileRecordAdapter::TestSupportedFormat()
	{
	_LIT(KTotal,"Supported:%d");
	_LIT(KFormat,"Format:%d");
	_LIT(KErr,"TestSupportedFormat err:%d");
	
	RArray<TFourCC> array;
	TRAPD(err,iMdaAudioRecorderUtility->GetSupportedDestinationDataTypesL(array));
	if (err != KErrNone)
		{
		TBuf<30> info;
		info.Format(KErr,err);
		DEBUGLOG(iFileLogger,info);
		return;
		}
	
	TBuf<30> total;
	total.Format(KTotal,array.Count());
	DEBUGLOG(iFileLogger,total);
	
	for(int i=0; i<array.Count(); i++)
		{
		TBuf<30> format;
		format.Format(KFormat,array[i]);
		DEBUGLOG(iFileLogger,format);
		}
	}