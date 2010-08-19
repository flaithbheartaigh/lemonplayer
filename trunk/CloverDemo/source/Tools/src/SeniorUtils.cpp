/*
 ============================================================================
 Name		: SeniorUtils.cpp
 Author	  : SeniorUtils
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CSeniorUtils implementation
 ============================================================================
 */

#include "SeniorUtils.h"

#include <favouritessession.h> 		//RFavouritesSession
#include <favouritesdb.h> 			//RFavouritesDb
#include <apgcli.h>					//RApaLsSession
#include <apgtask.h>
#include <eikenv.h>					//CEikonEnv
CSeniorUtils::CSeniorUtils()
	{
	// No implementation required
	}

CSeniorUtils::~CSeniorUtils()
	{
	}

// 将应用程序带到前台
void CSeniorUtils::ShowApplication()
	{
	//RWsSession aWsSession = CEikonEnv::Static()->WsSession();
	//TApaTaskList taskList(aWsSession);
	//TApaTask aTask = taskList.FindApp(KUidkiwi);
	//aTask.BringToForeground();
	}

// 隐藏应用程序
void CSeniorUtils::HideApplication()
	{
	//	RWsSession aWsSession = CEikonEnv::Static()->WsSession();
	//	TApaTask aTask(aWsSession);
	//	TInt aId = CEikonEnv::Static()->RootWin().Identifier();
	//	aTask.SetWgId(aId);
	//	if (aWsSession.GetFocusWindowGroup() == aId)
	//	{
	//		aTask.SendToBackground();
	// 	}
	}

TThreadId CSeniorUtils::StartBroswerApp(const TDesC& aUrl)
	{
	TThreadId id(0);
	if (aUrl.Length() <= 0)
		return id;

	const TInt KBrowserUid1 = 0x1020724D;
	const TInt KBrowserUid2 = 0x10008D39;

	RApaLsSession appArcSession;
	User::LeaveIfError(appArcSession.Connect()); // connect to AppArc server

	HBufC* param = HBufC::NewLC(aUrl.Length() + 8);
	param->Des().Format(_L( "4 %S" ), &aUrl);

	// Wap Browser's constants UId
	TUid browserId(TUid::Uid(KBrowserUid1));

	TApaAppInfo appInfo;
	if (appArcSession.GetAppInfo(appInfo, browserId) != KErrNone)
		{
		browserId = TUid::Uid(KBrowserUid2);
		}

	TApaTaskList taskList(CEikonEnv::Static()->WsSession());
	TApaTask task = taskList.FindApp(browserId);
	if (task.Exists())
		{
		HBufC8* param8 = HBufC8::NewLC(param->Length() * 4);
		param8->Des().Append(*param);
		task.SendMessage(TUid::Uid(0), *param8); // Uid is not used
		CleanupStack::PopAndDestroy(); // param8
		}
	else
		{
		appArcSession.StartDocument(*param, browserId, id);
		//	appArcSession.Close();

		//	User::After(2*1000*1000);

		//	TApaTask task = taskList.FindApp( uid );

		//	if ( task.Exists() )
		//	{
		//		task.SendMessage( TUid::Uid(0), *pHtsUrl8 ); // UID is not used
		//	}
		}

	appArcSession.Close();
	CleanupStack::PopAndDestroy(); // param
	return id;
	}

void CSeniorUtils::AddBookmark(const TDesC& aUrl, const TDesC& aName)
	{
	RFavouritesSession iSession;
	User::LeaveIfError(iSession.Connect());
	CleanupClosePushL(iSession);

	RFavouritesDb db;
	// KBrowserBookmarks is picked up from the header
	User::LeaveIfError(db.Open(iSession, KBrowserBookmarks));
	CleanupClosePushL(db);

	CFavouritesItem* item = CFavouritesItem::NewLC();
	item->SetNameL(aName);
	item->SetParentFolder(KFavouritesRootUid);
	item->SetType(CFavouritesItem::EItem);
	item->SetUrlL(aUrl);

	User::LeaveIfError(db.Add(*item, ETrue));

	CleanupStack::PopAndDestroy(3, &iSession); // db, item	
	}

void CSeniorUtils::GetSofts(CDesCArray* aArray)
	{
	TInt num = 0;
	RApaLsSession ls;

	User::LeaveIfError(ls.Connect());
	CleanupClosePushL(ls);

	User::LeaveIfError(ls.GetAllApps());
	//	User::LeaveIfError(ls.GetEmbeddableApps());  

	ls.AppCount(num);

	TInt errCode(KErrNone);
	TApaAppInfo appInfo;
	while (!errCode)
		{
		errCode = ls.GetNextApp(appInfo);

		if (appInfo.iFullName.Length())
			{
			TBuf<1> driver;
			driver.Copy(appInfo.iFullName.Left(1));
			driver.UpperCase();
			if (driver.Compare(_L("Z")))
				{

				if (appInfo.iFullName.Right(8).CompareF(_L(".fakeapp")))
					{
					if (aArray)
						aArray->AppendL(appInfo.iCaption);
					}
				}
			}
		}
	CleanupStack::PopAndDestroy();	
	}
