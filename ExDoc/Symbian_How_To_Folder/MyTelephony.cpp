// MyTelephony.cpp
//
#include <e32svr.h>
#include "MyTelephony.h"
#include <f32file.h>

class CTelephony;
CMyTelephony* CMyTelephony::NewLC()
	{
	CMyTelephony* self = new (ELeave) CMyTelephony;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyTelephony* CMyTelephony::NewL()
	{
	CMyTelephony* self = CMyTelephony::NewLC();
	CleanupStack::Pop(self);
	return self;
	}

void CMyTelephony::GetIMSIL(TDes& aIMSI)
	{
#ifndef __WINS__
	CMyTelephony* telephony = CMyTelephony::NewL();
	telephony->GetSubscriberId();
	aIMSI = telephony->iSubscriberId.iSubscriberId;

	delete telephony;
#else
	_LIT(KDebugIMSI, "000000000000000");
	aIMSI = KDebugIMSI;
#endif
	}

void CMyTelephony::GetIMEIL(TDes& aIMEI)
	{
#ifndef __WINS__ //真实设备 This only works on target machine
	CMyTelephony* telephony = CMyTelephony::NewL();
	telephony->GetPhoneId();
	aIMEI = telephony->iPhoneId.iSerialNumber;

	delete telephony;
#else //模拟器 Return a fake IMEI when working onemulator
	_LIT(KEmulatorImei, "000000000000000");
	aIMEI = KEmulatorImei;
#endif
	}

void CMyTelephony::GetPhoneType(TDes& aPhoneType)
	{
#ifndef __WINS__
	CMyTelephony* telephony = CMyTelephony::NewL();
	telephony->GetPhoneId();
	aPhoneType.Copy(telephony->iPhoneId.iManufacturer);
	aPhoneType.Append(telephony->iPhoneId.iModel);

	delete telephony;
#else //模拟器 Return a fake IMEI when working onemulator
	_LIT(KPhoneType, "Nokia5500d");
	aPhoneType = KPhoneType;
#endif
	}

void CMyTelephony::DialPhone(const TDesC& aPhoneId)
	{
#ifndef __WINS__ //真实设备 This only works on target machine
	CMyTelephony* telephony = CMyTelephony::NewLC();
	telephony->DialNewCall(aPhoneId);

#else //模拟器 Return a fake IMEI when working onemulator
#endif
	}
void CMyTelephony::DoCancel()
	{
	iTelephony->CancelAsync(iRequest);
	iTelephony->CancelAsync(CTelephony::EDialNewCallCancel);
	}

void CMyTelephony::RunL()
	{
	CActiveScheduler::Stop();
	}

CMyTelephony::~CMyTelephony()
	{
	delete iTelephony;
	}

CMyTelephony::CMyTelephony() :
	CActive(CActive::EPriorityStandard), iSubscriberIdPckg(iSubscriberId),
			iPhoneIdPckg(iPhoneId)
	{
	CActiveScheduler::Add(this);
	}

void CMyTelephony::ConstructL()
	{
	iTelephony = CTelephony::NewL();
	}

void CMyTelephony::GetSubscriberId()
	{
	Cancel();
	iRequest = CTelephony::EGetSubscriberIdCancel;
	iTelephony->GetSubscriberId(iStatus, iSubscriberIdPckg);
	SetActive();
	CActiveScheduler::Start();
	}

void CMyTelephony::GetPhoneId()
	{
	Cancel();
	iRequest = CTelephony::EGetPhoneIdCancel;
	iTelephony->GetPhoneId(iStatus, iPhoneIdPckg);
	SetActive();
	CActiveScheduler::Start();
	}

/*void CMyTelephony::GetType()
 {
 _LIT(KPath,"z:\\resource\\versions\\model.txt");
 Cancel();

 RFs fs;
 RFile typeFile;
 User::LeaveIfError(fs.Connect());
 TFileText myFile;
 User::LeaveIfError(typeFile.Open(fs, KPath, EFileShareReadersOnly));

 // Read from position 0: start of file
 myFile.Set(typeFile);
 myFile.Read(iPhoneType); // readBuf1 is now "write "

 fs.Close();
 SetActive();
 CActiveScheduler::Start();
 }*/
/*
 * 拨打电话
 * */
void CMyTelephony::DialNewCall(const TDesC& aTelNumber)
	{
	CTelephony::TTelNumber telNumber(aTelNumber);
	CTelephony::TCallParamsV1 callParams;
	callParams.iIdRestrict = CTelephony::ESendMyId;
	CTelephony::TCallParamsV1Pckg callParamsPckg(callParams);
	iTelephony->DialNewCall(iStatus, callParamsPckg, telNumber, iCallId);
	SetActive();
	}
