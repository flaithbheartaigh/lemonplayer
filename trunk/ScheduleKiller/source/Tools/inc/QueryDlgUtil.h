#ifndef _QUERYDLGUTIL_H__
#define _QUERYDLGUTIL_H__

#include <e32std.h>
#include <e32base.h>

TBool ShowConfirmationQueryL( const TInt& aTextResourceId );
TBool ShowConfirmationQueryL( const TDesC& aText );

TInt StartWaitingDlg(const TInt& aTextResourceId);
void EndWaitingDlg(const TInt& aDlgId);

void ShowInfomationDlgL(const TInt& aTextResourceId);
void ShowInfomationDlgL(const TDesC& aDes);

TBool ShowInputDlgL(const TInt& aTextResourceId,TDes& aText);

TBool ShowModalInfoDlgL(const TInt& aTextHeaderId,const TDesC& aDes);
TBool ShowModalInfoDlgL(const TInt& aTextHeaderId,const TInt& aTextResourceId);

TBool ShowModalAboutDlgL(const TInt& aTextHeaderId,const TInt& aTextResourceId);
TBool ShowModalAboutDlgL(const TInt& aTextHeaderId,const TDesC& aDes);
TBool ShowModalAboutLinkDlgL(const TInt& aTextHeaderId,const TDesC& aDes,TCallBack &aCallBack);
TBool ShowModalAboutLinkDlgL(const TInt& aTextHeaderId,const TDesC& aMsg,const TDesC& aLink,TCallBack &aCallBack);
TBool ShowModalAboutLinkDlgL(const TInt& aTitleHeaderId,const TDesC& aMsg,const TInt& aTextHeaderId,
		TCallBack &aCallBack);

#endif
