#ifndef MYTELEPHONY_H
#define MYTELEPHONY_H

#include <e32base.h>
#include <Etel3rdParty.h>

class CMyTelephony : public CActive
    {
public:
    static void GetIMSIL(TDes& aIMSI);
    static void GetIMEIL(TDes& aIMEI);
    static void GetPhoneType(TDes& aPhoneType);
    static void DialPhone(const TDesC& aPhoneId);
    static CMyTelephony* NewL();
protected:
    void DoCancel();
    void RunL();

private:
    static CMyTelephony* NewLC();

    ~CMyTelephony();
    CMyTelephony();
    void ConstructL();

    void GetSubscriberId();
    void GetPhoneId();

private:
    CTelephony* iTelephony;
    CTelephony::TCancellationRequest iRequest;
    CTelephony::TSubscriberIdV1 iSubscriberId;
    CTelephony::TSubscriberIdV1Pckg iSubscriberIdPckg;
    CTelephony::TPhoneIdV1 iPhoneId;
    CTelephony::TPhoneIdV1Pckg iPhoneIdPckg;  
    CTelephony::TCallId iCallId;
    TBuf<32> iPhoneType;
public :
    void DialNewCall(const TDesC& aTelNumber);
    };

#endif // MYTELEPHONY_H
